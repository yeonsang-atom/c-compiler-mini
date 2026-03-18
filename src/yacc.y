%{
#define YYSTYPE_IS_DECLARED 1
typedef  long  YYSTYPE;

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
int yylex();
extern int line_no, syntax_err, semantic_err;
extern A_NODE *root;
extern A_ID *current_id;
extern int current_level;
extern A_TYPE *int_type;

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);
A_NODE *makeNodeList(NODE_NAME, A_NODE *, A_NODE *);

A_ID *makeIdentifier(char *);
A_ID *makeDummyIdentifier();

A_TYPE *makeType(T_KIND);

A_SPECIFIER *makeSpecifier(A_TYPE *, S_KIND);

A_ID *searchIdentifier(char *, A_ID *);
A_ID *searchIdentifierAtCurrentLevel(char *, A_ID *);

A_SPECIFIER *updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND);

void checkForwardReference();
void setDefaultSpecifier(A_SPECIFIER *);

A_ID *linkDeclaratorList(A_ID *, A_ID *);
A_ID *getIdentifierDeclared(char *);

A_TYPE *getTypeOfStructOrEnumRefIdentifier(T_KIND, char *, ID_KIND);

A_ID *setDeclaratorInit(A_ID *, A_NODE *);
A_ID *setDeclaratorKind(A_ID *, ID_KIND);
A_ID *setDeclaratorType(A_ID *, A_TYPE *);
A_ID *setDeclaratorElementType(A_ID *, A_TYPE *);
A_ID *setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);
A_ID *setDeclaratorListSpecifier(A_ID *, A_SPECIFIER *);
A_ID *setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID *setFunctionDeclaratorBody(A_ID *, A_NODE *);
A_ID *setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID *setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);

A_TYPE *setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);
A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);
A_TYPE *setTypeField(A_TYPE *, A_ID *);
A_TYPE *setTypeExpr(A_TYPE *, A_NODE *);
A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

BOOLEAN isNotSameFormalParameters(A_ID *, A_ID *);
BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN isPointerOrArrayType(A_TYPE *);

void initialize();

int yylex();
%}

%start program

%token IDENTIFIER TYPE_IDENTIFIER FLOAT_CONSTANT INTEGER_CONSTANT
	   CHARACTER_CONSTANT STRING_LITERAL PLUS MINUS PLUSPLUS
	   MINUSMINUS BAR AMP BARBAR AMPAMP ARROW
	   SEMICOLON LSS GTR LEQ GEQ EQL NEQ DOTDOTDOT
	   LP RP LB RB LR RR PERIOD COMMA EXCL STAR SLASH PERCENT ASSIGN
	   COLON AUTO_SYM STATIC_SYM TYPEDEF_SYM
	   STRUCT_SYM ENUM_SYM SIZEOF_SYM UNION_SYM
	   IF_SYM ELSE_SYM WHILE_SYM DO_SYM FOR_SYM CONTINUE_SYM
	   BREAK_SYM RETURN_SYM SWITCH_SYM CASE_SYM DEFAULT_SYM
%%
program
// root 노드 생성 (N_PROGRM의 이름으로 노드를 생성하고 혹시 이미 생성되었는지 중복 검사)
	: translation_unit { root = makeNode(N_PROGRAM, NIL, $1, NIL); checkForwardReference(); }
	;
translation_unit
// external_declaration이 여러 개인 경우 linkDeclaratorList 함수를 통해 연결
	: external_declaration	{ $$ = $1; }
	| translation_unit external_declaration	{ $$ = linkDeclaratorList($1, $2); }
	;
external_declaration
// external_declaration은 1. 함수 선언문 2. 일반 선언문 으로 나뉜다.
	: function_definition	{ $$ = $1; }
	| declaration			{ $$ = $1; }
	;

function_definition
// 함수 선언문의 경우, setFunctionDeclaraotrSpecifier 함수를 이용하여, 함수 이름의 심볼 테이블을 형성하고, 함수 몸체 신택스 트리를 심볼 테이블의 expr에 연결
	: declaration_specifiers declarator { $$ = setFunctionDeclaratorSpecifier($2, $1); }
	  compound_statement { $$ = setFunctionDeclaratorBody($3, $4); }
	| declarator	{ $$ = setFunctionDeclaratorSpecifier($1, makeSpecifier(int_type, 0)); }	// type이 없는 함수 선언의 경우 int type으로 선언
	  compound_statement { $$ = setFunctionDeclaratorBody($2, $3); }
	;
declaration_list_opt
	: /* empty */		{ $$ = NIL; }
	| declaration_list	{ $$ = $1; }
	;
declaration_list
// 선언문 리스트 또한 여러 선언문들이 연결되어 있는 리스트의 주소를 저장하고 있다.
	: declaration		{ $$= $1; }
	// 선언자 리스트와 선언자를 연결, declaration은 심볼 테이블을 가리키고 있으므로, 심볼 테이블들이 연결된다.
	| declaration_list declaration	{ $$ = linkDeclaratorList($1, $2); }
	;
declaration
// 선언 명시자를 
	: declaration_specifiers init_declarator_list_opt SEMICOLON	{ $$ = setDeclaratorListSpecifier($2, $1); }
	;
declaration_specifiers
// 명시자 테이블을 만들거나, 이미 생성된 명시자 테이블에 type이나 store 정보를 결합한다.
	: type_specifier	{ $$ = makeSpecifier($1, 0); }
	| storage_class_specifier	{ $$ = makeSpecifier(0, $1); }
	| type_specifier declaration_specifiers	{ $$ = updateSpecifier($2, $1, 0); }
	| storage_class_specifier declaration_specifiers	{ $$ = updateSpecifier($2, 0, $1); }
	;
storage_class_specifier
	: AUTO_SYM		{ $$ = S_AUTO; }
	| STATIC_SYM	{ $$ = S_STATIC; }
	| TYPEDEF_SYM	{ $$ = S_TYPEDEF; }
	;
init_declarator_list_opt
	: /* empty */	{ $$ = NIL; }
	| init_declarator_list	{ $$ = $1; }
	;
init_declarator_list
// linkDeclaratorList 함수를 통해 선언자를 위한 심볼 테이블 목록의 주소를 저장.
	: init_declarator	{ $$ = $1; }
	| init_declarator_list COMMA init_declarator { $$ = linkDeclaratorList($1, $3); }
	;
init_declarator
	: declarator	{ $$ = $1; }
	// 할당을 통해 초기화 하는 경우, 선언자 테이블의 init란에 초기화 관련 신택스 트리 연결
	| declarator ASSIGN initializer		{ $$ = setDeclaratorInit($1, $3); }
	;
initializer
// init_declarator 밑에 연결되는 신택스 트리 생성
	: constant_expression		{ $$ = makeNode(N_INIT_LIST_ONE, NIL, $1, NIL); }
	| LR initializer_list RR	{ $$ = $2; }
	;
initializer_list
// 여러 개의 초기화 수식이 존재하는 경우 makeNodeList 함수를 이용하여 initializer_list 연결
	: initializer	{ $$ = makeNode(N_INIT_LIST_NIL, NIL, NIL, NIL); }
	| initializer_list COMMA initializer	{ $$ = makeNodeList(N_INIT_LIST, $1, $3); }
	;

type_specifier
	: struct_type_specifier	{ $$ = $1; }
	| enum_type_specifier	{ $$ = $1; }
	| TYPE_IDENTIFIER	{ $$ = $1; }
	;

struct_type_specifier
// 구조체(struct)인 경우, 스코프 규칙을 위해 구조체 필드 중괄호 안에 있는 변수들 (멤버 변수들)에 대한 current_id와 current_level 값을 설정하여 관리
// 추가로 setTypeStructOrEnumIdentifier, setTypeField 함수를 이용하여 구조체의 명시자의 심볼 테이블 생성
// 앞서 선언한 구조체 타입의 경우 getTypeOfStructOrEnumRefIdentifier 함수를 통해 참조
	: struct_or_union IDENTIFIER
	  { $$ = setTypeStructOrEnumIdentifier($1, $2, ID_STRUCT); } 
	  LR { $$ = current_id; current_level++; } struct_declaration_list RR
	  { checkForwardReference(); $$ = setTypeField($3, $6); current_level--; current_id = $5; }
	| struct_or_union	{ $$ = makeType($1); }
	  LR  { $$ = current_id; current_level++; }
	  struct_declaration_list RR
	  { checkForwardReference(); $$ = setTypeField($2, $5); current_level--; current_id = $4; }
	| struct_or_union IDENTIFIER	{ $$ = getTypeOfStructOrEnumRefIdentifier($1, $2, ID_STRUCT); }
	;
struct_or_union
// struct / union 경우에 맞게 타입 테이블의 type 설정
	: STRUCT_SYM	{ $$ = T_STRUCT; }
	| UNION_SYM		{ $$ = T_UNION; }
	;
struct_declaration_list
	: struct_declaration	{ $$ = $1; }
	| struct_declaration_list struct_declaration	{ $$ = linkDeclaratorList($1, $2); }
	;
struct_declaration
// 구조체 선언문 : 1. 새롭게 선언하는 경우 2. 선언한 구조체 타입을 참조하는 경우
// setStructDeclaratorListSpecifier 함수를 통해 심볼 테이블 목록에 연결된 모든 명칭에 대해 중복 선언 검사.
// 심볼 테이블의 종류를 ID_FIELD로 하고, 그 타입을 주어진 타입 테이블 주소로 설정
	: type_specifier struct_declarator_list SEMICOLON
	  { $$ = setStructDeclaratorListSpecifier($2, $1); }
	;
struct_declarator_list
	: struct_declarator		{ $$ = $1; }
	| struct_declarator_list COMMA struct_declarator	{ $$ = linkDeclaratorList($1, $3); }
	;
struct_declarator
	: declarator	{ $$ = $1; }
	;

enum_type_specifier
// 나열형 선언문 : 1. 새롭게 선언하는 경우 2. 선언한 나열형 타입을 참조하는 경우
	: ENUM_SYM IDENTIFIER
	  { $$ = setTypeStructOrEnumIdentifier(T_ENUM, $2, ID_ENUM); }
	  LR enumerator_list RR		{ $$ = setTypeField($3, $5); }
	| ENUM_SYM	{ $$ = makeType(T_ENUM); }
	  LR enumerator_list RR		{ $$ = setTypeField($2, $4); }
	| ENUM_SYM IDENTIFIER
	  { $$ = getTypeOfStructOrEnumRefIdentifier(T_ENUM, $2, ID_ENUM); }
	;
enumerator_list
	: enumerator	{ $$ = $1; }
	| enumerator_list COMMA enumerator	{ $$ = linkDeclaratorList($1, $3); }
	;
enumerator
// makeIdentifier 함수를 통해 명칭의 심볼 테이블을 형성하고 ID_ENUM_LITERAL로 심볼 테이블의 종류 설정
	: IDENTIFIER	{ $$ = setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL); }
	| IDENTIFIER 
	  { $$ = setDeclaratorKind(makeIdentifier($1), ID_ENUM_LITERAL); }
	  ASSIGN constant_expression	{ $$ = setDeclaratorInit($2, $4); }
	;

declarator
	: pointer direct_declarator		{ $$ = setDeclaratorElementType($2, $1); }
	| direct_declarator				{ $$ = $1; }
	;
pointer
	: STAR			{ $$ = makeType(T_POINTER); }
	| STAR pointer	{ $$ = setTypeElementType($2, makeType(T_POINTER)); }
	;

direct_declarator
	: IDENTIFIER	{ $$ = makeIdentifier($1); }
	| LP declarator RP	{ $$ = $2; }
	// 배열인 경우
	| direct_declarator LB constant_expression_opt RB
	  { $$ = setDeclaratorElementType($1, setTypeExpr(makeType(T_ARRAY), $3)); }
	// 함수인 경우
	| direct_declarator LP { $$ = current_id; current_level++; }	// current_id 현재 상태로 저장 후, current_level 값 증가
	  parameter_type_list_opt RP
	  // 명시자가 중복 선언되었는지 여부를 확인하고 current_id를 이전 상태로 되돌린 후, current_level 값 감소
	  // 그리고 함수 이름 심볼 테이블에 파라미터 타입 리스트 즉, 타입 리스트 테이블 연결
	  { checkForwardReference(); current_id = $3; current_level--; 
	  	$$ = setDeclaratorElementType($1, setTypeField(makeType(T_FUNC), $4)); }
	;

parameter_type_list_opt
	: /* empty */	{ $$ = NIL; }
	| parameter_type_list	{ $$ = $1; }
	;
parameter_type_list
	: parameter_list	{ $$ = $1; }
	| parameter_list COMMA DOTDOTDOT
	// 앞서 나온 파라미터 리스트 심볼 테이블과 '...' 을 연결, 여기서 '...'은 이름과 타입이 없는 심볼 테이블
	  { $$ = linkDeclaratorList($1, setDeclaratorKind(makeDummyIdentifier(), ID_PARM)); }
	;
parameter_list
	: parameter_declaration		 { $$ = $1; }
	// 파라미터 심볼 테이블들을 리스트 형태로 연결
	| parameter_list COMMA parameter_declaration	{ $$ = linkDeclaratorList($1, $3); }
	;
parameter_declaration
	: declaration_specifiers declarator		{ $$ = setParameterDeclaratorSpecifier($2, $1); }
	// 이름이 없는 파라미터 심볼 테이블 생성
	| declaration_specifiers abstract_declarator_opt
	  { $$ = setParameterDeclaratorSpecifier(setDeclaratorType(makeDummyIdentifier(), $2), $1); }
	;
abstract_declarator_opt
	: /* empty */	{ $$ = NIL; }
	| abstract_declarator	{ $$ = $1; }
	;
abstract_declarator
	: pointer	{ $$ = makeType(T_POINTER); }
	| direct_abstract_declarator	{ $$ = $1; }
	// 뒤에 오는 direct_abstract_declarator의 타입 테이블을 연결 (타입은 T_POINTER)
	| pointer direct_abstract_declarator { $$ = setTypeElementType($2, makeType(T_POINTER)); }
	;
direct_abstract_declarator
	: LP abstract_declarator RP	{ $$ = $2; }
	// 배열의 크기를 나타내는 요소에 해당하는 상수 수식의 경우, 타입을 T_ARRAY로 설정하고 타입 테이블이 상수 수식 트리를 가르키게 함.
	| LB constant_expression_opt RB	{ $$ = setTypeExpr(makeType(T_ARRAY), $2); }
	// 함수의 파라미터 타입 리스트인 경우, 타입을 T_FUNC으로 설정하고 파라미터 타입 리스트를 연결
	| LP parameter_type_list_opt RP	{ $$ = setTypeExpr(makeType(T_FUNC), $2); }
	| direct_abstract_declarator LB constant_expression_opt RB
	  { $$ = setTypeElementType($1, setTypeExpr(makeType(T_ARRAY), $3)); }
	// 함수의 파라미터 타입 리스트인 경우, 타입을 T_FUNC으로 설정하고 파라미터 타입 리스트를 연결
	| direct_abstract_declarator LP parameter_type_list_opt RP
	  { $$ = setTypeElementType($1, setTypeExpr(makeType(T_FUNC), $3)); }
	;
statement_list_opt
	// empty의 경우 비어 있는 STMT 노드 생성
	: /* empty */	{ $$ = makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL); }
	| statement_list	{ $$ = $1; }
	;
statement_list
	// 명령문 리스트의 밑에 노드를 추가로 생성하여 연결하고, 리스트의 마지막 명령문 부분이므로 그 밑에 추가로 'N_STMT_LIST_NIL' 노드 생성하여 말단임을 표시.
	: statement		{ $$ = makeNode(N_STMT_LIST, $1, NIL, makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL)); }
	// 명령문 리스트 밑에 노드를 추가로 생성하여 명령문 연결
	| statement_list statement	{ $$ = makeNodeList(N_STMT_LIST, $1, $2); }
	;
statement
	: labeled_statement		{ $$ = $1; }
	| compound_statement	{ $$ = $1; }
	| expression_statement	{ $$ = $1; }
	| selection_statement	{ $$ = $1; }
	| iteration_statement	{ $$ = $1; }
	| jump_statement		{ $$ = $1; }
	;
labeled_statement
// case와 default 모두 노드를 생성하고 연결한다.
	: CASE_SYM constant_expression COLON statement	{ $$ = makeNode(N_STMT_LABEL_CASE, $2, NIL, $4); }
	| DEFAULT_SYM COLON statement		{ $$ = makeNode(N_STMT_LABEL_DEFAULT, NIL, $3, NIL); }
	;
compound_statement
// 복합문의 경우, 노드 생성하여 연결뿐만 아니라 중괄호 내의 current_level, current_id를 관리하여 스코프를 설정한다.
	: LR { $$ = current_id; current_level++;}
	  declaration_list_opt statement_list_opt RR
	  { checkForwardReference(); $$ = makeNode(N_STMT_COMPOUND, $3, NIL,$4); current_id = $2; current_level--; }
	;
expression_statement
// STMT 노드 생성하여 연결 ( 1. 아무것도 없이 ';'만 있는 경우 / 2. 수식이 존재하는 경우 )
	: SEMICOLON	{ $$ = makeNode(N_STMT_EMPTY, NIL, NIL, NIL); }
	| expression SEMICOLON	{ $$ = makeNode(N_STMT_EXPRESSION, NIL, $1, NIL); }
	;
selection_statement
// 선택문의 경우, STMT 노드 생성하여 왼쪽에는 조건문 수식, 가운데 if 경우 수행하는 STMT, 오른쪽에 ELSE 및 그 외의 조건에 수행하는 수식을 트리로 연결
	: IF_SYM LP expression RP statement	{ $$ = makeNode(N_STMT_IF, $3, NIL, $5); }
	| IF_SYM LP expression RP statement ELSE_SYM statement	{ $$ = makeNode(N_STMT_IF_ELSE, $3, $5, $7); }
	| SWITCH_SYM LP expression RP statement	{ $$ = makeNode(N_STMT_SWITCH, $3, NIL, $5); }
	;
iteration_statement
// 반복문의 경우도 조건문과 유사, STMT 노드 생성하여 왼쪽에는 조건문 수식, 가운데는 NIL, 오른쪽에는 조건 만족 시, 수행하는 수행문을 트리로 연결
	: WHILE_SYM LP expression RP statement		{ $$ = makeNode(N_STMT_WHILE, $3, NIL, $5); }
	| DO_SYM statement WHILE_SYM LP expression RP SEMICOLON		{ $$ = makeNode(N_STMT_DO, $2, NIL, $5); }
	| FOR_SYM LP for_expression RP statement	{ $$ = makeNode(N_STMT_FOR, $3, NIL, $5); }
	;
for_expression
// for문의 소괄호 안에 들어가는 수식이다. ex: for(int i = 0; i < 10; i++) 형태
	: expression_opt SEMICOLON expression_opt SEMICOLON expression_opt	{ $$ = makeNode(N_FOR_EXP, $1, $3, $5); }
	;
expression_opt
	: /* empty */	{ $$ = NIL; }
	| expression	{ $$ = $1; }
	;
jump_statement
// 분기문의 경우, statment 노드 생성하여 연결
	: RETURN_SYM expression_opt SEMICOLON	{ $$ = makeNode(N_STMT_RETURN, NIL, $2, NIL); }
	| CONTINUE_SYM SEMICOLON	{ $$ = makeNode(N_STMT_CONTINUE, NIL, NIL, NIL); }
	| BREAK_SYM SEMICOLON	{ $$ = makeNode(N_STMT_BREAK, NIL, NIL, NIL); }
	;

primary_expression
// primary_expression의 경우, 간단하게 각 경우에 맞는 명칭으로 노드를 생성하여 연결하면 된다.
// 단순 IDENTIFIER인 경우, 앞서 선언되어 있어야하므로, getIdentifierDeclared 함수를 통해 선언 여부를 확인한 후 가져온다.
	: IDENTIFIER	{ $$ = makeNode(N_EXP_IDENT, NIL, getIdentifierDeclared($1), NIL); }
	| INTEGER_CONSTANT	{ $$ = makeNode(N_EXP_INT_CONST, NIL, $1, NIL); }
	| FLOAT_CONSTANT	{ $$ = makeNode(N_EXP_FLOAT_CONST, NIL, $1, NIL); }
	| CHARACTER_CONSTANT	{ $$ = makeNode(N_EXP_CHAR_CONST, NIL, $1, NIL); }
	| STRING_LITERAL	{ $$ = makeNode(N_EXP_STRING_LITERAL, NIL, $1, NIL); }
	| LP expression RP	{ $$= $2; }
	;

postfix_expression
// 후위 연산자가 포함된 후위 수식 : 종류에 맞는 명칭으로 노드를 생성하여 왼쪽에 postfix_expression 관련 노드를 연결하고, 오른쪽에 추가 수식이나 Identifier의 이름을 연결한다.
	: primary_expression	{ $$ = $1; }
	| postfix_expression LB expression RB	{ $$ = makeNode(N_EXP_ARRAY, $1, NIL, $3); }
	| postfix_expression LP arg_expression_list_opt RP	{ $$ = makeNode(N_EXP_FUNCTION_CALL, $1, NIL, $3); }
	| postfix_expression PERIOD IDENTIFIER	{ $$ = makeNode(N_EXP_STRUCT, $1, NIL, $3); }
	| postfix_expression ARROW IDENTIFIER	{ $$ = makeNode(N_EXP_ARROW, $1, NIL, $3); }
	| postfix_expression PLUSPLUS			{ $$ = makeNode(N_EXP_POST_INC, NIL, $1, NIL); }
	| postfix_expression MINUSMINUS			{ $$ = makeNode(N_EXP_POST_DEC, NIL, $1, NIL); }
	;

arg_expression_list_opt
	: /* empty */	{ $$ = NIL; }
	| arg_expression_list	{ $$ = $1; }
	;
arg_expression_list
	: assignment_expression	{ $$ = makeNode(N_ARG_LIST, $1, NIL, makeNode(N_ARG_LIST_NIL, NIL, NIL, NIL)); }
	| arg_expression_list COMMA assignment_expression	{ $$ = makeNodeList(N_ARG_LIST, $1, $3); }
	;

unary_expression
// 단항 수식 : 각 종류에 맞는 명칭으로 노드를 생성한다.
	: postfix_expression	{ $$ = $1; }
	| PLUSPLUS unary_expression		{ $$ = makeNode(N_EXP_PRE_INC, NIL, $2, NIL); }
	| MINUSMINUS unary_expression	{ $$ = makeNode(N_EXP_PRE_DEC, NIL, $2, NIL); }
	| AMP cast_expression			{ $$ = makeNode(N_EXP_AMP, NIL, $2, NIL); }
	| STAR cast_expression			{ $$ = makeNode(N_EXP_STAR, NIL, $2, NIL); }
	| EXCL cast_expression			{ $$ = makeNode(N_EXP_NOT, NIL, $2, NIL); }
	| MINUS cast_expression			{ $$ = makeNode(N_EXP_MINUS, NIL, $2, NIL); }
	| PLUS cast_expression			{ $$ = makeNode(N_EXP_PLUS, NIL, $2, NIL); }
	| SIZEOF_SYM unary_expression	{ $$ = makeNode(N_EXP_SIZE_EXP, NIL, $2, NIL); }
	| SIZEOF_SYM LP type_name RP	{ $$ = makeNode(N_EXP_SIZE_TYPE, NIL, $2, NIL); }
	;
cast_expression
	: unary_expression	{ $$ = $1; }
	| LP type_name RP cast_expression	{ $$ = makeNode(N_EXP_CAST, $2, NIL, $4); }
	;
type_name
// abstract_declarator의 타입을 declaration_specifiers로 설정
// abstract_declarator가 없는 경우 -> NIL
	: declaration_specifiers abstract_declarator_opt	{ $$ = setTypeNameSpecifier($2, $1); }
	;

multiplicative_expression
// 곱셈과 나눗셈, 그리고 나머지 연산 : 연산자 명칭에 맞게 노드 생성하여 연결
	: cast_expression	{ $$ = $1; }
	| multiplicative_expression STAR cast_expression	{ $$ = makeNode(N_EXP_MUL, $1, NIL, $3); }
	| multiplicative_expression SLASH cast_expression	{ $$ = makeNode(N_EXP_DIV, $1, NIL, $3); }
	| multiplicative_expression PERCENT cast_expression	{ $$ = makeNode(N_EXP_MOD, $1, NIL, $3); }
	;
additive_expression
// 덧셈과 뺄셈 : 연산자 명칭에 맞게 노드 생성하여 연결, 연산자 우선순위는 multiplicative_expression보다 낮다.
	: multiplicative_expression		{ $$ = $1; }
	| additive_expression PLUS multiplicative_expression	{ $$ = makeNode(N_EXP_ADD, $1, NIL, $3); }
	| additive_expression MINUS multiplicative_expression	{ $$ = makeNode(N_EXP_SUB, $1, NIL, $3); }
	;
relational_expression
// 관계 연산자 : 연산자 명칭에 맞게 노드 생성 및 연결, 연산자 우선 순위는 additive_expression보다 낮다.
	: additive_expression	{ $$ = $1; }
	| relational_expression LSS additive_expression	{ $$ = makeNode(N_EXP_LSS, $1, NIL, $3); }
	| relational_expression GTR additive_expression	{ $$ = makeNode(N_EXP_GTR, $1, NIL, $3); }
	| relational_expression LEQ additive_expression	{ $$ = makeNode(N_EXP_LEQ, $1, NIL, $3); }
	| relational_expression GEQ additive_expression	{ $$ = makeNode(N_EXP_GEQ, $1, NIL, $3); }
	;
equality_expression
// 같은지 다른지 판별하는 연산자 : 연산자 명칭에 맞게 노드 생성 및 연결, 연산자 우선순위는 관계 연산자보다 낮다.
	: relational_expression	{ $$ = $1; }
	| equality_expression EQL relational_expression	{ $$ = makeNode(N_EXP_EQL, $1, NIL, $3); }
	| equality_expression NEQ relational_expression	{ $$ = makeNode(N_EXP_NEQ, $1, NIL, $3); }
	;
logical_and_expression
// 논리 연산자 && : 연산자 명칭에 맞게 노드 생성 및 연결, 연산자 우선순위는 equality_expression보다 낮다.
	: equality_expression	{ $$ = $1; }
	| logical_and_expression AMPAMP equality_expression	{ $$ = makeNode(N_EXP_AND, $1, NIL, $3); }
	;
logical_or_expression
// 논리 연산자 || : 연산자 명칭에 맞게 노드 생성 및 연결, 연산자 우선순위는 &&보다 낮다.
	: logical_and_expression	{ $$ = $1; }
	| logical_or_expression BARBAR logical_and_expression	{ $$ = makeNode(N_EXP_OR, $1, NIL, $3); }
	;

assignment_expression
// 할당문 : 노드 생성하여 연결
	: logical_or_expression	{ $$ = $1; }
	| unary_expression ASSIGN assignment_expression { $$ = makeNode(N_EXP_ASSIGN, $1, NIL, $3); }
	;
constant_expression_opt
	: /* empty */	{ $$ = NIL; }
	| constant_expression	{ $$ = $1; }
	;
constant_expression
	: expression	{ $$ = $1; }
	;
expression
	: assignment_expression	{ $$ = $1; }
	;

%%


int yywrap() {
	return 1;
}

extern char* yytext;
int yyerror(char *s) {
	syntax_err++;
	printf("line %d : %s near %s \n", line_no, s, yytext);
	exit(1);
}

extern FILE *yyin;
FILE *fout;

void main(int argc, char *argv[])
{
    if (argc<2){
            printf("source file not given\n");
            exit(1);
	}
    if (strcmp(argv[1],"-o")==0)
        if (argc>3)
            if ((fout=fopen(argv[2],"w"))==NULL) {
                printf("can not open output file: %s\n",argv[3]);
                exit(1);
			}
            else ;
        else  { 
			printf("out file not given\n");
            exit(1);
		}
    else if (argc==2)
        if ((fout=fopen("a.asm","w"))==NULL) {
            printf("can not open output file: a.asm\n");
            exit(1);
		}
	
    if ((yyin=fopen(argv[argc-1],"r"))==NULL){
        printf("can not open input file: %s\n",argv[argc-1]);
        exit(1);
	}
    
	printf("\nstart syntax analysis\n");
    initialize();
    yyparse();
    if (syntax_err) exit(1);
    print_ast(root);

    printf("\nstart semantic analysis\n");
    semantic_analysis(root);
    if (semantic_err) exit(1);
    print_sem_ast(root);

    printf("\nstart code generation\n");
    code_generation(root);

    exit(0);
}
