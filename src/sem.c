/*
 * 2024 컴파일러 과제6 : Semantic Analysis
 * by. Yeonsang Jeong
 * 
 * 시멘틱 분석기의 역할
 * 1. 선언문의 모든 명칭이나 타입의 성질 분석
 * 2. 선언문의 타입을 재귀적으로 탐색하며 크기 계산
 * 3. 변수나 파라미터의 경우 :
 *      a. 타입을 분석하여 크기를 계산
 *      b. 프로그램 실행 시 활성화 레코드에서 위치할 주소 계산
 * 4. 함수인 경우 :
 *      a. 리턴 타입 분석
 *      b. 파라미터 목록을 분석, 크기 계산, 주소 계산, 올바른 타입인지 검사
 *      c. 함수의 바디의 복합문을 분석, 선언한 지역 변수의 크기 계산 및 저장
 * 5. 모든 수식 분석 -> 연산자 및 피연산자 타입과 규칙 검사
 * 6. 모든 명령문 / 수식의 정당성 분석 및 검사
 * 7. 원시 프로그램의 모든 상수 수집 및 저장
 */

#include "type.h"
#include <string.h>

float   atof();
void    semantic_analysis(A_NODE *);
void    set_literal_address(A_NODE *);
int     put_literal(A_LITERAL, int);
void    sem_program(A_NODE *);
A_TYPE* sem_expression(A_NODE *);

int     sem_statement(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
int     sem_statement_list(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);

void    sem_for_expression(A_NODE *);
int     sem_A_TYPE(A_TYPE *);
int     sem_declaration_list(A_ID *, int);
int     sem_declaration(A_ID *, int);
void    sem_arg_expr_list(A_NODE *, A_ID *);

A_ID*   getStructFieldIdentifier(A_TYPE *, char *);
A_ID*   getPointerFieldIdentifier(A_TYPE *, char *);
A_NODE* convertScalarToInteger(A_NODE *);
A_NODE* convertUsualAssignmentConversion(A_TYPE *, A_NODE *);
A_NODE* convertUsualUnaryConversion(A_NODE *);
A_TYPE* convertUsualBinaryConversion(A_NODE *);
A_NODE* convertCastingConversion(A_NODE *, A_TYPE *);

BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *);
BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *);
BOOLEAN isModifiableLvalue(A_NODE *);
BOOLEAN isConstantZeroExp(A_NODE *);
BOOLEAN isSameParameterType(A_ID *, A_ID *);
BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *);
BOOLEAN isIntType(A_TYPE *);
BOOLEAN isFloatType(A_TYPE *);
BOOLEAN isArithmeticType(A_TYPE *);
BOOLEAN isAnyIntegerType(A_TYPE *);
BOOLEAN isIntegralType(A_TYPE *);
BOOLEAN isStructOrUnionType(A_TYPE *);
BOOLEAN isFunctionType(A_TYPE *);
BOOLEAN isScalarType(A_TYPE *);
BOOLEAN isPointerType(A_TYPE *);
BOOLEAN isPointerOrArrayType(A_TYPE *);
BOOLEAN isArrayType(A_TYPE *);
BOOLEAN isStringType(A_TYPE *);
BOOLEAN isVoidType(A_TYPE *);

A_LITERAL   checkTypeAndConvertLiteral(A_LITERAL, A_TYPE *, int);
A_LITERAL   getTypeAndValueOfExpression(A_NODE *);
A_TYPE*     setTypeElementType(A_TYPE *, A_TYPE *);
A_TYPE*     makeType(T_KIND);

void    setTypeSize(A_TYPE *, int);
void    semantic_warning(int, int);
void    semantic_error();

A_NODE* makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);

extern A_TYPE *int_type, *float_type, *char_type, *string_type, *void_type;

int global_address = 12;
int semantic_err = 0;

#define LIT_MAX 100

A_LITERAL literal_table[LIT_MAX];

int literal_no = 0;
int literal_size = 0;

/* ------------------------------------------------------ */
/* 시멘틱 분석기의 메인 함수 프로그램 */
void semantic_analysis(A_NODE *node)
{
    sem_program(node);
    set_literal_address(node);
}

/*
    시멘틱 분석 후, 시멘틱 분석 과정에 발견 혹은 생성된
    리터럴 테이블들이 프로그램 실행 시 보관될 상수 영역에서의 주소를 계산한다.
    즉, 노드에 저장된 value 값을 확인하여 리터럴의 주소를 계산하고 저장한다.    
*/
void set_literal_address(A_NODE *node)
{
    for(int i = 1; i <= literal_no; i++) {
        literal_table[i].addr += node->value;
    }
    node->value += literal_size;
}

/* 
    신택스 트리의 루트 노드부터 신택스 트리 및 관련 심볼 테이블과 타입 테이블을 모두 분석하고,
    원시 프로그램에서 선언된 전역 변수의 크기를 계산한다.
    여기서 크기란 각 변수나 명칭이 차지하는 bytes를 의미한다.
    추후, 기계어(어셈블리어) 변환 및 코딩을 위해 계산 과정이 필요하다.
*/
void sem_program(A_NODE *node)
{
    int i;
    // 시작 노드는 루트 노드로, 노드의 명칭은 항상 N_PROGRAM이다.
    // global address는 0 레벨의 base로 부터 12번지이다.
    // 이 값을 루트 노드의 value 값으로 저장.
    switch(node->name) {
        case N_PROGRAM:
            i = sem_declaration_list(node->clink, 12);
            node->value = global_address;
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
}

/*
    프로그램에 있는 리터럴을 리터럴 테이블 목록에 저장하고,
    목록에서의 그 리터럴 위치를 반환한다.
*/
int put_literal(A_LITERAL lit, int ll)
{
    float ff;
    // 리터럴 테이블이 가득 찬 경우 
    if(literal_no >= LIT_MAX)
        semantic_error(93, ll);
    else
        literal_no++;
    
    // 리터럴 테이블에 새로운 리터럴에 대한 정보를 저장.
    literal_table[literal_no] = lit;
    literal_table[literal_no].addr = literal_size;
    
    // 리터럴이 나올 수 있는 kind의 종료는 두 가지이다.
    // 1. 나열형 변수에 A, B와 같이 상수 명칭을 선언하는 경우
    //   ex) enum kim = { A, B, C };
    // 2. 문자열 리터럴인 경우
    //   ex) char *s = "SSU";
    if(lit.type->kind == T_ENUM)
        literal_size += 4;
    else if(isStringType(lit.type))
        literal_size += strlen(lit.value.s) + 1;
    
    // 기계어는 4 byte씩 실행 단위이기 때문에 할당되는 공간을 올림형 4의 배수로 설정
    if(literal_size % 4)
        literal_size = literal_size / 4 * 4 + 4;

    return(literal_no);
}

/*
 * 수식을 나타내는 신택스 트리의 루트 노드로부터 트리와 그에 연결된 심볼 및 타입 테이블들을 분석하고,
 * 명령문들에 나타난 지역 변수들의 크기를 계산하여 그 값을 리턴한다.
 * 구성 요소 분석 : 수식을 구성하는 여러 요소들을 모두 재귀적으로 분석
 * 수식의 특성에 따른 타입 호환성을 위해 필요에 따라 수식의 타입을 변환
 * 수식의 제한 사항을 검사
 * 수식의 lvalue 여부 결정, 노드에 저장
 * 타입 계산 : 수식의 최종적인 타입을 계산하여 노드에 저장하고 그 값을 리턴
 * 그 외 기타 필요한 정보를 수집, 계산 및 저장한다.
 */
A_TYPE *sem_expression(A_NODE *node)
{
    A_TYPE *result = NIL;
    A_TYPE *t, *t1, *t2;
    A_ID *id;
    A_LITERAL lit;
    int i;
    BOOLEAN lvalue = FALSE;

    switch(node->name) {
        // 단순 명칭인 경우 명칭의 종류는 ID_VAR, ID_PARM, ID_FUNC, ID_ENUM_LITERAL만 가능
        // 즉, 필드 명칭이나 태그 명칭 struct, union은 불가능
        // 수식의 타입은 해당 명칭의 타입과 같으며, ID_ENUM_LITERAL의 경우 int_type이다.
        case N_EXP_IDENT:
            id = node->clink;
            switch(id->kind) {
                case ID_VAR:
                case ID_PARM:
                    result = id->type;
                    if(!isArrayType(result))
                        lvalue = TRUE;
                    break;
                case ID_FUNC:
                    result = id->type;
                    break;
                case ID_ENUM_LITERAL:
                    result = int_type;
                    break;
                default:
                    semantic_error(38, node->line, id->name);
                    break;
            }
            break;
        // 상수형 + 문자열 리터럴인 경우, 해당 상수의 타입과 수식의 타입이 같고,
        // lvalue 수식이 아님.
        case N_EXP_INT_CONST:
            result = int_type;
            break;
        case N_EXP_FLOAT_CONST:
            lit.type = float_type;
            lit.value.f = atof(node->clink);
            node->clink = put_literal(lit, node->line);
            result = float_type;
            break;
        case N_EXP_CHAR_CONST:
            result = char_type;
            break;
        case N_EXP_STRING_LITERAL:
            lit.type = string_type;
            lit.value.s = node->clink;
            node->clink = put_literal(lit, node->line);
            result = string_type;
            break;
        // 배열 참조 수식인 경우, llink와 rlink 각각 분석하여 수식의 타입을 계산한다.
        // 이항 연산자 변환 규칙을 사용하고 llink(함수 명칭)의 type은 포인터 타입이거나 배열형 타입이어야하며,
        // rlink([ ]안의 내용)의 타입은 서수형 타입이어야 한다.
        // 수식의 타입은 타입의 엘리먼트 타입으로 정해진다. (배열의 최종 타입)
        // 계산한 수식의 타입이 배열형 타입이 아닌 경우에만 lvalue 수식이다.
        case N_EXP_ARRAY:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);

            t = convertUsualBinaryConversion(node);
            t1 = node->llink->type;
            t2 = node->rlink->type;
            if(isPointerOrArrayType(t1))
                result = t1->element_type;
            else
                semantic_error(32, node->line);

            if(!isIntegralType(t2))
                semantic_error(29, node->line);
            
            if(!isArrayType(result))
                lvalue = TRUE;
            break;
        // 구조체 필드 참조 혹은 포인터 간접 참조 수식인 경우,
        // '.', '->'
        // '.'인 경우 : struct, union 타입이며, 필드 명칭을 검사해서 식별자가 있어야 함.
        // '->'인 경우 : struct, union을 가리키는 포인터 타입이며, 필드 명칭 검사해서 식별자 있어야 함.
        // 두 경우 모두 수식의 타입은 해당 필드의 타입이고, 계산한 수식의 타입이 배열형이 아닌 경우 lvalue 수식임.
        case N_EXP_STRUCT:
            t = sem_expression(node->llink);
            id = getStructFieldIdentifier(t, node->rlink);

            if(id) {
                result = id->type;
                if(node->llink->value && !isArrayType(result))
                    lvalue = TRUE;
            }
            else
                semantic_error(37, node->line);
            node->rlink = id;
            break;
        case N_EXP_ARROW:
            t = sem_expression(node->llink);
            id = getPointerFieldIdentifier(t, node->rlink);
            if(id) {
                result = id->type;
                if(!isArrayType)
                    lvalue = TRUE;
            }
            else
                semantic_error(37, node->line);
            node->rlink = id;
            break;
        // 함수 호출 수식인 경우, ex) fun();
        // 함수 명칭을 분석하여 그 수식의 타입을 얻고, 단항 연산자 변환 규칙을 적용하여 변환.
        // 타입은 함수형 타입의 포인터 타입이어야 함.
        // 함수 호출의 괄호 안 즉, 파라미터 부분을 확인하여 함수형 타입의 매개변수의 타입과 개수가 일치하는 지 확인하고,
        // 필요하다면 타입 변환 연산자 타입 변환 규칙에 따라 변환
        // 수식의 타입은 함수형 타입의 엘리먼트 타입으로 리턴 타입이 된다.
        case N_EXP_FUNCTION_CALL:
            t = sem_expression(node->llink);
            node->llink = convertUsualUnaryConversion(node->llink);
            t = node->llink->type;
            if(isPointerType(t) && isFunctionType(t->element_type)) {
                sem_arg_expr_list(node->rlink, t->element_type->field);
                result = t->element_type->element_type;
            }
            else
                semantic_error(21, node->line);
            break;
        // 후위 증감 연산자의 경우 : a++, b--
        // 연산자 앞에 나오는 변수의 타입을 얻고, 그 타입이 스칼라 타입인지 확인한다.
        // 수식의 타입은 변수의 타입으로 설정한다. 즉, a가 int_type이라면, a++ 또한 int_type임.
        case N_EXP_POST_INC:
        case N_EXP_POST_DEC:
            result = sem_expression(node->clink);
            if(!isScalarType(result))
                semantic_error(27, node->line);
            if(!isModifiableLvalue(node->clink))
                semantic_error(60, node->line);
            break;
        // 타입 변환 연산자의 경우 : (type_name) cast_expression
        // 괄호 안의 casting 할 타입과 type_name 뒤에 오는 수식의 타입을 얻는다.
        // 수식의 타입이 변환할 casting 연산자로의 타입 변환 가능 여부를 확인한다.
        case N_EXP_CAST:
            result = node->llink;
            i = sem_A_TYPE(result);
            t = sem_expression(node->rlink);
            if(!isAllowableCastingConversion(result, t))
                semantic_error(58, node->line);
            break;
        // sizeof 연산자를 갖는 수식의 경우,
        // sizeof 연산자 뒤에 오는 unary_expression과 (type_name)의 타입을 얻는다.
        // void 타입, 함수형 타입 및 크기가 생략된 배열형 타입은 허용 불가
        // 수식의 타입은 int_type
        case N_EXP_SIZE_TYPE:
            t = node->clink;
            i = sem_A_TYPE(result);
            if(!isArrayType(t) && t->size == 0 || isFunctionType(t) || isVoidType(t))
                semantic_error(39, node->line);
            else
                node->clink = i;
            result = int_type;
            break;
        case N_EXP_SIZE_EXP:
            t = sem_expression(node->clink);
            if((node->clink->name != N_EXP_IDENT || (((A_ID*)node->clink->clink)->kind != ID_PARM)) 
                && (isArrayType(t) && t->size == 0 || isFunctionType(t)))
                semantic_error(39, node->line);
            else
                node->clink = t->size;
            result = int_type;
            break;
        // +, -, ! 단항 연산자의 경우 : +a, -a, !a
        // 연산자 뒤에 오는 변수의 타입을 얻고, 그 타입은 산술형 타입이어야 한다.
        // 단항 연산자 변환 규칙을 적용하여 변환하고, 수식의 최종 타입은 변환 규칙을 전환한 타입이 된다.
        // 단, ! 연산자 수식의 타입은 int_type이다.
        case N_EXP_PLUS:
        case N_EXP_MINUS:
            t = sem_expression(node->clink);
            if(isArithmeticType(t)) {
                node->clink = convertUsualUnaryConversion(node->clink);
                result = node->clink->type;
            }
            else
                semantic_error(13, node->line);
            break;
        case N_EXP_NOT:
            t = sem_expression(node->clink);
            if(isScalarType(t)) {
                node->clink = convertUsualUnaryConversion(node->clink);
                result = int_type;
            }
            else
                semantic_error(27, node->line);
            break;
        // 단항 연산자 &의 경우 : &a
        // & 연산자 뒤에 오는 수식을 분석하여 타입을 얻고, 함수형 타입이거나 lvalue 수식의 객체이어야 한다.
        // (호출 가능한 객체(함수), 변수, 배열, 구조체 멤버처럼 메모리 주소를 가진 값.)
        case N_EXP_AMP:
            t = sem_expression(node->clink);
            if(node->clink->value == TRUE || isFunctionType(t)) {
                result = setTypeElementType(makeType(T_POINTER), t);
                result->size = 4;
            }
            else
                semantic_error(60, node->line);
            break;
        // 단항 연산자 *의 경우 : *a
        // * 연산자 뒤에 오는 수식을 분석하여 타입을 얻고, 어떤 타입을 가리키는 포인터 타입이어야 한다.
        // 최종적으로 전체 수식의 타입은 그 포인터의 엘리먼트 타입, 즉 포인터가 가리키는 타입이 된다.
        // 스칼라 타입이나 구조체 타입을 가리키는 포인터의 경우 lvalue 수식이다.
        case N_EXP_STAR:
            t = sem_expression(node->clink);
            node->clink = convertUsualUnaryConversion(node->clink);
            if(isPointerType(t)) {
                result = t->element_type;
                if(isStructOrUnionType(result) || isScalarType(result))
                    lvalue = TRUE;
            }
            else
                semantic_error(31, node->line);
            break;
        // 전위 증감 연산자인 경우 : ++a, --b
        // 연산자 뒤에 오는 변수(a, b)의 타입을 얻고, 그 값이 스칼라 타입인지 확인한다.
        // 수식 자체의 타입은 변수의 타입으로 설정한다.
        case N_EXP_PRE_INC:
        case N_EXP_PRE_DEC:
            result = sem_expression(node->clink);
            if(!isScalarType(result))
                semantic_error(27, node->line);
            if(!isModifiableLvalue(node->clink))
                semantic_error(60, node->line);
            break;
        // *, /, % 연산자의 경우,
        // 연산자 앞 뒤 각각의 수식의 타입을 얻고,
        // *, /에서 두 수식의 타입은 모두 산술형 타입이고, % 연산자의 앞 뒤 두 수식의 타입은 서수형 타입이다.
        // 연산자 기준 앞 뒤의 수식 모두 이항 연산자 변환 규칙을 적용하여 변환한다.
        case N_EXP_MUL:
        case N_EXP_DIV:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isArithmeticType(t1) && isArithmeticType(t2))
                result = convertUsualBinaryConversion(node);
            else
                semantic_error(28, node->line);
            break;
        case N_EXP_MOD:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isIntegralType(t1) && isIntegralType(t2))
                result = convertUsualBinaryConversion(node);
            else
                semantic_error(29, node->line);
            result = int_type;
            break;
        // +, - 연산자인 경우,
        // 연산자 기준 앞 뒤 수식의 타입을 얻고, 이 타입은 모두 산술형 타입이거나,
        // 하나는 객체의 포인터 타입이고 다른 하나는 정수형 타입의 상수이어야 한다.
        // (ex) int *ptr2 = ptr + 2; 과 같은 경우이다.)
        // 추가로 뺄셈의 경우 [주소 - 주소]의 경우도 존재 (int diff = end - start; end와 start는 주소를 나타내는 변수)
        case N_EXP_ADD:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isArithmeticType(t1) && isArithmeticType(t2))
                result = convertUsualBinaryConversion(node);
            else if(isPointerType(t1) && isIntegralType(t2))
                result = t1;
            else if(isIntegralType(t1) && isPointerType(t2))
                result = t2;
            else
                semantic_error(24, node->line);
            break;
        case N_EXP_SUB:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isArithmeticType(t1) && isArithmeticType(t2))
                result = convertUsualBinaryConversion(node);
            else if(isPointerType(t1) && isIntegralType(t2))
                result = t1;
            else if(isCompatiblePointerType(t1, t2))
                result = t2;
            else
                semantic_error(24, node->line);
            break;
        // 관계 연산자의 경우,
        // 관계 연산자 기준 앞 뒤 수식들의 타입을 얻고, 
        // 그 타입은 둘 다 산술형 타입이거나, 호환적인 포인터 타입이다.
        case N_EXP_LSS:
        case N_EXP_GTR:
        case N_EXP_LEQ:
        case N_EXP_GEQ:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isArithmeticType(t1) && isArithmeticType(t2))
                t = convertUsualBinaryConversion(node);
            else if(!isCompatiblePointerType(t1, t2))
                semantic_error(40, node->line);
            result = int_type;
            break;
        // ==, != 인 경우,
        // 연산자 기준 앞 뒤 수식의 타입을 확인하고, 그 타입은 둘 다 산술형 타입이거나,
        // 호환적인 포인터 타입이거나, 하나는 포인터 타입 + 하나는 정수형 타입의 상수 0 이어야 한다.
        // 연산자 기준 앞 뒤 수식이 모두 산술형 타입인 경우에만 이항 연산자 변환 규칙을 적용하여 변환.
        // 최종 수식의 타입은 TRUE, FALSE를 나타내는 int_type이다.
        case N_EXP_NEQ:
        case N_EXP_EQL:
            t1 = sem_expression(node->llink);
            t2 = sem_expression(node->rlink);
            if(isArithmeticType(t1) && isArithmeticType(t2))
                t = convertUsualBinaryConversion(node);
            else if(!isCompatiblePointerType(t1, t2) &&
                        (!isPointerType(t1) || !isConstantZeroExp(node->rlink)) &&
                        (!isPointerType(t2) || !isConstantZeroExp(node->llink)))
                semantic_error(40, node->line);
            result = int_type;
            break;
        // 논리 연산자 ||, && 인 경우,
        // 연산자 기준 앞 뒤 수식의 타입을 확인하고, 이 타입은 스칼라 타입이어야 한다.
        // 수식은 단항 연산자 변환 규칙을 적용하여 변환한다.
        case N_EXP_AND:
        case N_EXP_OR:
            t = sem_expression(node->llink);
            if(isScalarType(t))
                node->llink = convertUsualUnaryConversion(node->llink);
            else
                semantic_error(27, node->line);

            t = sem_expression(node->rlink);
            if(isScalarType(t))
                node->llink = convertUsualUnaryConversion(node->rlink);
            else
                semantic_error(27, node->line); 

            result = int_type;
            break;
        // 할당 연산자 (치환 연산자)의 경우,
        // 연산자 기준 앞 뒤 수식의 타입을 확인하고, 앞에 오는 수식은 변경이 가능한 lvalue 수식이어야한다.
        // 앞 뒤 수식의 타입이 서로 치환이 가능한 지 확인하고 치환 연산자 변환 규칙을 적용하여 변환한다.
        // 최종적인 수식의 타입은 앞의 수식의 타입으로 설정된다.
        case N_EXP_ASSIGN:
            result = sem_expression(node->llink);
            if(!isModifiableLvalue(node->llink))
                semantic_error(60, node->line);

            t = sem_expression(node->rlink);
            if(isAllowableAssignmentConversion(result, t, node->rlink)) {
                if(isArithmeticType(result) && isArithmeticType(t))
                    node->rlink = convertUsualAssignmentConversion(result, node->rlink);
            }
            else
                semantic_error(58, node->line);
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
    node->type = result;
    node->value = lvalue;
    return(result);
}

/*
    함수 선언문에서 정의된 매개변수 목록과 함수 호출 수식의 목록이 
    서로 그 개수와 타입이 일치하는지 검사하고 변환해야 한다.
*/
void sem_arg_expr_list(A_NODE *node, A_ID *id)
{
    A_TYPE *t;
    A_ID *a;
    int arg_size = 0;

    switch(node->name) {
        case N_ARG_LIST:
            if(id == 0) // id == 0 이라면 함수 프로토타입에 있는 인자의 개수보다 함수 호출 부분의 인자가 더 많은 경우 : too many argument
                semantic_error(34, node->line);
            else {
                if(id->type) {
                    t = sem_expression(node->llink);
                    node->llink = convertUsualUnaryConversion(node->llink);
                    if(isAllowableCastingConversion(id->type, node->llink->type))
                        node->llink = convertCastingConversion(node->llink, id->type);
                    else
                        semantic_error(59, node->line);

                    sem_arg_expr_list(node->rlink, id->link);
                }
                else {      /* 함수 파라미터의 부분에 '...'이 인자로 오는 경우 : DOTDOTDOT*/
                    t = sem_expression(node->llink);
                    sem_arg_expr_list(node->rlink, id);
                }
                arg_size = node->llink->type->size + node->rlink->value;
            }
            break;
        // ARG_LIST의 말단으로 마지막 노드이다. 해당 노드에는 아무런 값 없으며, arugment list의 마지막임을 표시.
        case N_ARG_LIST_NIL:
            // 함수 호출 부분의 인자는 끝났는데, 프로토타입 부분의 인자가 남은 경우.
            // 즉 few argument인 경우
            if(id && id->type)
                semantic_error(35, node->line);
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
    if(arg_size % 4)
        arg_size = arg_size / 4 * 4 + 4;
    node->value = arg_size;
}

/*
    주어진 수식이 lvalue 수식이며 변경이 가능한 장소인지 검사한다.
    노드에 이미 계산된 value 값이 있어야하며, void 타입이거나, 함수형 타입이면 안된다.
*/
BOOLEAN isModifiableLvalue(A_NODE *node)
{
    if(node->value == FALSE || isVoidType(node->type) || isFunctionType(node->type))
        return(FALSE);
    else
        return(TRUE);
}

/*
    명령문을 나타내는 신택스 트리의 루트 노드로부터 트리와 그에 연결된 심볼 및 타입 테이블들을
    분석하고, 명령문들에 나타난 지역 변수들의 크기를 계산하여 그 값을 리턴한다.
    ex) compound_statement의 경우 해당 괄호 내에 int 형 변수가 4개 있다면
        해당 복합문의 베이스로부터 시작을 12번지로 해서 +4번지씩 하여 크기를 계산.
*/
int sem_statement(A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw, BOOLEAN brk, BOOLEAN cnt)
{
    int local_size = 0, i;
    A_LITERAL lit;
    A_TYPE *t;

    switch(node->name) {
        // case, default와 같은 LABEL statement인 경우,
        // case와 default 뒤에 나오는 statement를 분석하기 위해 sem_statement()를 호출
        // 이 때, addr을 매개변수로 전달하고, 그 명령문 안에 나오는 지역변수들의 크기를 반환 받아
        // 그 값을 local_size에 저장하여 최종 반환한다.
        // 추가로 case문의 경우 case 바로 뒤에 오는 constant_expression이
        // 서수형 타입인지 검사하고 값을 계산한다.
        case N_STMT_LABEL_CASE:
            if(sw == FALSE)
                semantic_error(71, node->line);
            lit = getTypeAndValueOfExpression(node->llink);
            if(isIntegralType(lit.type))
                node->llink = lit.value.i;
            else
                semantic_error(51, node->line);
            
            local_size = sem_statement(node->rlink, addr, ret, sw, brk, cnt);
            break;
        case N_STMT_LABEL_DEFAULT:
            if(sw == FALSE)
                semantic_error(72, node->line);
            local_size = sem_statement(node->clink, addr, ret, sw, brk, cnt);
            break;
        // 복합문의 경우, 괄호 안의 선언문에 대한 정보인 심볼 테이블 목록 검사를 위해 sem_declaration_list()를
        // 호출하여 지역 변수들이 실행 시 activation record에 할당될 주소를 addr부터 설정하고 할당 후의 최종 크기를 반환 받는다.
        // 복합문 내의 명령문들을 분석하기 위해 sem_statement_list() 또한 호출하며, 할당 될 주소 값을 계산하여
        // (addr + sem_declaration_list의 반환 값)을 매개 변수로 한다.
        case N_STMT_COMPOUND:
            if(node->llink)
                local_size = sem_declaration_list(node->llink, addr);
            local_size += sem_statement_list(node->rlink, local_size + addr, ret, sw, brk, cnt);
            break;
        // 해당 수식에 대해 sem_expression()을 통해 분석한다.
        case N_STMT_EMPTY:
            break;
        // if-else, switch와 같은 선택문의 경우,
        // if-else : if( )에서 괄호 안에 오는 수식이 스칼라 타입인지 검사한다.
        // switch : switch( )에서 괄호 안에 오는 수식이 서수형 타입인지 검사한다.
        // 두 경우 모두 명령문 분석을 위해서는 sem_statement()를 호출한다.
        case N_STMT_EXPRESSION:
            t = sem_expression(node->clink);
            break;
        case N_STMT_IF:
            t = sem_expression(node->llink);
            if(isScalarType(t))
                node->llink = convertScalarToInteger(node->llink);
            else
                semantic_error(50, node->line);
            local_size = sem_statement(node->rlink, addr, ret, FALSE, brk, cnt);
            break;
        case N_STMT_IF_ELSE:
            t = sem_expression(node->llink);
            if(isScalarType(t))
                node->llink = convertScalarToInteger(node->llink);
            else
                semantic_error(50, node->line);
            local_size = sem_statement(node->clink, addr, ret, FALSE, brk, cnt);
            i = sem_statement(node->rlink, addr, ret, FALSE, brk, cnt);
            if(local_size < i)
                local_size = i;
            break;
        case N_STMT_SWITCH:
            t = sem_expression(node->llink);
            if(!isIntegralType(t))
                semantic_error(50, node->line);
            local_size = sem_statement(node->rlink, addr, ret, TRUE, TRUE, cnt);
            break;
        // while, for, do-while 반복문의 경우,
        // while, do-while의 경우 ()안의 수식이 스칼라 타입인지 확인하고,
        // for의 괄호 안의 두 번째 수식이 스칼라 타입인지 확인한다.
        // statement를 분석하기 위해 sem_statement 함수를 호출한다.
        // 선택문과 마찬가지로 새로운 선언문이 없으므로 전달 받은 addr을 그대로 전달하여
        // statement를 분석하고 지역변수의 크기를 받아 리턴한다.
        case N_STMT_WHILE:
            t = sem_expression(node->llink);
            if(isScalarType(t))
                node->llink = convertScalarToInteger(node->llink);
            else
                semantic_error(50, node->line);
            local_size = sem_statement(node->rlink, addr, ret, FALSE, TRUE, TRUE);
            break;
        case N_STMT_DO:
            local_size = sem_statement(node->llink, addr, ret, FALSE, TRUE, TRUE);
            t = sem_expression(node->rlink);
            if(isScalarType(t))
                node->rlink = convertScalarToInteger(node->rlink);
            else
                semantic_error(50, node->line);
            break;
        case N_STMT_FOR:
            sem_for_expression(node->llink);
            local_size = sem_statement(node->rlink, addr, ret, FALSE, TRUE, TRUE);
            break;
        // jump statement (go-to 제외) : return, continue, break
        // return문에 수식 있는 경우 그 수식 분석 필요
        // 새로운 선언문 없으므로 리턴 따로 하지 않음 (즉, 0을 리턴)
        case N_STMT_CONTINUE:
            if(cnt == FALSE)
                semantic_error(74, node->line);
            break;
        case N_STMT_BREAK:
            if(brk == FALSE)
                semantic_error(73, node->line);
            break;
        case N_STMT_RETURN:
            if(node->clink) {
                t = sem_expression(node->clink);
                if(isAllowableCastingConversion(ret, t))
                    node->clink = convertCastingConversion(node->clink, ret);
                else
                    semantic_error(57, node->line);
            }
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
    node->value = local_size;
    return(local_size);
}

/*
    for 명령문에서 예약어 뒤에 있는 세 개의 수식을 분석한다.
    두 번째 수식은 스칼라 타입이어야 함.
*/
void sem_for_expression(A_NODE *node)
{
    A_TYPE *t;

    switch(node->name) {
        case N_FOR_EXP:
            if(node->llink)
                t = sem_expression(node->llink);
            if(node->clink) {
                t = sem_expression(node->clink);
                if(isScalarType(t))
                    node->clink = convertScalarToInteger(node->clink);
                else
                    semantic_error(49, node->line);
            }
            if(node->rlink)
                t = sem_expression(node->rlink);
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
}

/*
    명령문들의 목록을 나타내는 신택스 트리의 루트 노드로부터 차례로 연결된 명령문들을 분석한다.
    각 명령문들에 나타난 지역 변수들의 크기를 계산하고, 그들 중 최대 값으로 리턴한다.
    추가로 명령문을 둘러싸고 있는 상위 명령문의 정보를 전달하는 역할도 한다.
    1. return문 다음에 나오는 수식의 타입이 return문을 포함하고 있는
        함수의 리턴 타입과 일치 해야한다.
    2. continue문의 경우는 반복문 속 안에 나와야 한다.
    3. break문은 반복문이나 switch문 속에 나와야 한다.
    4. case 와 default는 switch문 속에 나와야 한다.
*/
int sem_statement_list(A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw, BOOLEAN brk, BOOLEAN cnt)
{
    int size, i;

    switch(node->name) {
        case N_STMT_LIST:
            size = sem_statement(node->llink, addr, ret, sw, brk, cnt);
            i = sem_statement_list(node->rlink, addr, ret, sw, brk, cnt);
            if(size < i)
                size = i;
            break;
        case N_STMT_LIST_NIL:
            size = 0;
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
    node->value = size;
    return(size);
}

/*
    타입 테이블에 나타난 정보 및 관련 심볼 테이블과 타입 테이블들을
    분석하여 그 타입의 크기를 계산하여 타입 테이블에 저장하고, 그 값을 리턴한다.
*/
int sem_A_TYPE(A_TYPE *t)
{
    A_ID *id;
    A_TYPE *tt;
    A_LITERAL lit;
    int result = 0, i;

    if(t->check)
        return(t->size);
    t->check = 1;

    switch(t->kind) {
        case T_NULL:
            semantic_error(80, t->line);
            break;
        case T_ENUM:
            i = 0;
            id = t->field;
            while(id) {
                if(id->init) {
                    lit = getTypeAndValueOfExpression(id->init);
                    if(!isIntType(lit.type))
                        semantic_error(81, id->line);
                    i = lit.value.i;
                }
                id->init = i++;
                id = id->link;
            }
            result = 4;
            break;
        case T_ARRAY:
            if(t->expr) {
                lit = getTypeAndValueOfExpression(t->expr);
                if(!isIntType(lit.type) || lit.value.i <= 0) {
                    semantic_error(82, t->line);
                    t->expr = 0;
                }
                else
                    t->expr = lit.value.i;
            }
            i = sem_A_TYPE(t->element_type) * (int)t->expr;
            if(isVoidType(t->element_type) || isFunctionType(t->element_type))
                semantic_error(83, t->line);
            else
                result = i;
            break;
        case T_STRUCT:
            id = t->field;
            while(id) {
                result = sem_declaration(id, result);
                id = id->link;
            }
            break;
        case T_UNION:
            id = t->field;
            while(id) {
                i = sem_declaration(id, 0);
                if(i > result)
                    result = i;
                id = id->link;
            }
            break;
        case T_FUNC:
            tt = t->element_type;
            i = sem_A_TYPE(tt);
            if(isArrayType(tt) || isFunctionType(tt))
                semantic_error(85, t->line);

            i = sem_declaration_list(t->field, 12) + 12;
            if(t->expr) {
                i = i + sem_statement(t->expr, i, t->element_type, FALSE, FALSE, FALSE);
            }
            t->local_var_size = i;
            break;
        case T_POINTER:
            i = sem_A_TYPE(t->element_type);
            result = 4;
            break;
        case T_VOID:
            break;
        default:
            semantic_error(90, t->line);
            break;
    }
    t->size = result;
    return(result);
}

int sem_declaration_list(A_ID *id, int addr)
{
    int i = addr;
    while(id) {
        addr += sem_declaration(id, addr);
        id = id->link;
    }
    return(addr - i);
}

/*
    하나의 심볼 테이블의 명칭을 분석한다.
*/
int sem_declaration(A_ID *id, int addr)
{
    A_TYPE *t;
    int size = 0, i;
    A_LITERAL lit;

    switch(id->kind) {
        // 변수 명칭인 경우,
        // 파라미터로 받은 프로그램 실행 시 할당될 메모리 주소 값을 설정
        // 그 심볼 테이블에 연결된 타입 정보 분석, 크기 계산
        // 지역 변수인 경우, 파라미터로 주어진 주소 값을 갖도록 설정하고
        // 전역 변수 혹은 static 변수인 경우, 그동안 선언된 모든 전역 변수의 크기로 설정한다.
        case ID_VAR:
            i = sem_A_TYPE(id->type);
            if(isArrayType(id->type) && id->type->expr == NIL)
                semantic_error(86, id->line);
            if(i % 4)
                i = i / 4 * 4 + 4;
            if(id->specifier == S_STATIC)
                id->level = 0;
            if(id->level == 0) {
                id->address = global_address;
                global_address += i;
            }
            else {
                id->address = addr;
                size = i;
            }
            break;
        // 파라미터로 주어진 주소 addr 값을 갖도록 설정
        case ID_FIELD:
            i = sem_A_TYPE(id->type);
            if(isFunctionType(id->type) || isVoidType(id->type))
                semantic_error(84, id->line);
            if(i % 4)
                i = i / 4 * 4 + 4;
            id->address = addr;
            size = i;
            break;
        // 함수 명칭인 경우,
        // 연결된 타입 정보를 분석하고, 함수의 리턴 타입, 파라미터와 같은 정보를 분석
        // body를 가리키는 신택스 트리를 recursive하게 분석한다.
        case ID_FUNC:
            i = sem_A_TYPE(id->type);
            break;
        // 파라미터 명칭인 경우,
        // 파라미터의 타입 정보를 분석하고 지역변수와 동일하게 수행
        // 파라미터를 우선적으로 단항 연산자 변환 규칙으로 변환하고
        // 파라미터의 타입이 배열형 타입이거나 함수형 타입인 경우는
        // 각각 배열의 주소와 함수의 주소를 의미하므로 크기를 4로 설정한다.
        case ID_PARM:
            if(id->type) {
                size = sem_A_TYPE(id->type);
                if(id->type == char_type)
                    id->type = int_type;
                else if(isArrayType(id->type)) {
                    id->type->kind = T_POINTER;
                    id->type->size = 4;
                }
                else if(isFunctionType(id->type)) {
                    t = makeType(T_POINTER);
                    t->element_type = id->type;
                    t->size = 4;
                    id->type = t;
                }
                size = id->type->size;
                if(size % 4)
                    size = size / 4 * 4 + 4;
                id->address = addr;
            }
            break;
        // 타입 명칭인 경우,
        // 단순하게 타입에 대한 정보만 recursive하게 분석.
        case ID_TYPE:
            i = sem_A_TYPE(id->type);
            break;
        default:
            semantic_error(89, id->line, id->name);
            break;
    }
    return(size);
}

/*
    주어진 타입이 구조체 타입인지 검사하고, 파라미터로 주어진 명칭이
    필드 명칭 목록에 있는지 검사하여 그 심볼 테이블 주소를 리턴한다.
*/
A_ID *getStructFieldIdentifier(A_TYPE *t, char *s)
{
    A_ID *id = NIL;
    if(isStructOrUnionType(t)) {
        id = t->field;
        while(id) {
            if(strcmp(id->name, s) == 0)
                break;
            id = id->link;
        }
    }
    return(id);
}

/*
    주어진 타입이 구조체 타입을 가리키는 포인터 타입인가 검사하고,
    파라미터로 주어진 명칭이 필드 명칭 목록에 있는지 검사하여 그 심볼 테이블 주소를 리턴.
*/
A_ID *getPointerFieldIdentifier(A_TYPE *t, char *s)
{
    A_ID *id = NIL;
    if(t && t->kind == T_POINTER) {
        t = t->element_type;
        if(isStructOrUnionType(t)) {
            id = t->field;
            while(id) {
                if(strcmp(id->name, s) == 0)
                    break;
                id = id->link;
            }
        }
    }
    return(id);
}

/*
    함수의 두 파라미터의 타입이 같은지 확인
*/
BOOLEAN isSameParameterType(A_ID *a, A_ID *b)
{
    while(a) {
        if(b == NIL || isNotSameType(a->type, b->type))
            return(FALSE);
        a = a->link;
        b = b->link;
    }
    if(b)
        return(FALSE);
    else
        return(TRUE);
}

/*
    주어진 두 타입의 호환성을 검사
*/
BOOLEAN isCompatibleType(A_TYPE *t1, A_TYPE *t2)
{
    if(isArrayType(t1) && isArrayType(t2)) {
        if(t1->size == 0 || t2->size == 0 || t1->size == t2->size)
            return(isCompatibleType(t1->element_type, t2->element_type));
        else
            return(FALSE);
    }
    else if(isFunctionType(t1) && isFunctionType(t2)) {
        if(isSameParameterType(t1->field, t2->field))
            return(isCompatibleType(t1->element_type, t2->element_type));
        else
            return(FALSE);
    }
    else if(isPointerType(t1) && isPointerType(t2))
        return(isCompatibleType(t1->element_type, t2->element_type));
    else
        return(t1 == t2);
}

/*
    주어진 수식이 정수형 상수 0을 나타내는 수식인지 검사.
    즉 node->name이 N_EXP_INT_CONST인 경우이다.
*/
BOOLEAN isConstantZeroExp(A_NODE *node)
{
    if(node->name == N_EXP_INT_CONST && node->clink == 0)
        return(TRUE);
}

/*
    주어진 두 타입이 서로 호환적인 포인터 타입인지 검사
*/
BOOLEAN isCompatiblePointerType(A_TYPE *t1, A_TYPE *t2)
{
    if(isPointerType(t1) && isPointerType(t2))
        return(isCompatibleType(t1->element_type, t2->element_type));
    else
        return(FALSE);
}

/*
    스칼라 타입의 수식을 정수형 타입으로 변환
*/
A_NODE *convertScalarToInteger(A_NODE *node)
{
    if(isFloatType(node->type)) {
        semantic_warning(16, node->line);
        node = makeNode(N_EXP_CAST, int_type, NIL, node);
    }
    node->type = int_type;
    return(node);
}

/*
    주어진 수식을 치환 연산자 변환 규칙에 따라 주어진 타입으로 변환
*/
A_NODE *convertUsualAssignmentConversion(A_TYPE *t1, A_NODE *node)
{
    A_TYPE *t2;
    t2 = node->type;

    if(!isCompatibleType(t1, t2)) {
        semantic_warning(11, node->line);
        node = makeNode(N_EXP_CAST, t1, NIL, node);
        node->type = t1;
    }
    return(node);
}

/*
    주어진 수식을 단항 연산자 변환 규칙에 따라 타입 변환
*/
A_NODE *convertUsualUnaryConversion(A_NODE *node)
{
    A_TYPE *t;
    t = node->type;
    if(t == char_type) {
        t = int_type;
        node = makeNode(N_EXP_CAST, t, NIL, node);
        node->type = t;
    }
    else if(isArrayType(t)) {
        t = setTypeElementType(makeType(T_POINTER), t->element_type);
        t->size = 4;
        node = makeNode(N_EXP_CAST, t, NIL, node);
        node->type = t;
    }
    else if(isFunctionType(t)) {
        t = setTypeElementType(makeType(T_POINTER), t);
        t->size = 4;
        node = makeNode(N_EXP_AMP, NIL, node, NIL);
        node->type = t;
    }

    return(node);
}

/*
    주어진 수식을 이항 연산자 변환 규칙에 따라 타입 변환
*/
A_TYPE *convertUsualBinaryConversion(A_NODE *node)
{
    A_TYPE *t1, *t2, *result = NIL;
    t1 = node->llink->type;
    t2 = node->rlink->type;

    if(isFloatType(t1) && !isFloatType(t2)) {
        semantic_warning(14, node->line);
        node->rlink = makeNode(N_EXP_CAST, t1, NIL, node->rlink);
        node->rlink->type = t1;
        result = t1;
    }
    else if(!isFloatType(t1) && isFloatType(t2)) {
        semantic_warning(14, node->line);
        node->llink = makeNode(N_EXP_CAST, t2, NIL, node->llink);
        node->llink->type = t2;
        result = t2;
    }
    else if(t1 == t2)
        result = t1;
    else
        result = int_type;

    return(result);
}

/*
    주어진 수식을 타입 변환 연산자 변환 규칙에 따라 주어진 타입으로 변환
*/
A_NODE *convertCastingConversion(A_NODE *node, A_TYPE *t1)
{
    A_TYPE *t2;
    t2 = node->type;

    if(!isCompatibleType(t1, t2)) {
        semantic_warning(12, node->line);
        node = makeNode(N_EXP_CAST, t1, NIL, node);
        node->type = t1;
    }
    return(node);
}

/*
    주어진 두 타입이 치환 연산자 변환 규칙에 따라 변환 가능한지 검사
*/
BOOLEAN isAllowableAssignmentConversion(A_TYPE *t1, A_TYPE *t2, A_NODE *node)
{
    if(isArithmeticType(t1) && isArithmeticType(t2))
        return(TRUE);
    else if(isStructOrUnionType(t1) && isCompatibleType(t1, t2))
        return(TRUE);
    else if(isPointerType(t1) && (isConstantZeroExp(node) || isCompatiblePointerType(t1, t2)))
        return(TRUE);
    else
        return(FALSE);
}

/*
    주어진 두 타입이 서로 타입 변환 연산자 변환 규칙에 따라 변환이 가능한지 검사
*/
BOOLEAN isAllowableCastingConversion(A_TYPE *t1, A_TYPE *t2)
{
    if(isAnyIntegerType(t1) && (isAnyIntegerType(t2) || isFloatType(t2) || isPointerType(t2)))
        return(TRUE);
    else if(isFloatType(t1) && isArithmeticType(t2))
        return(TRUE);
    else if(isPointerType(t1) && (isAnyIntegerType(t2) || isPointerType(t2)))
        return(TRUE);
    else if(isVoidType(t1))
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isFloatType(A_TYPE *t)
{
    if(t == float_type)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isArithmeticType(A_TYPE *t)
{
    if(t && t->kind == T_ENUM)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isScalarType(A_TYPE *t)
{
    if(t && ((t->kind == T_ENUM) || (t->kind == T_POINTER)))
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isAnyIntegerType(A_TYPE *t)
{
    if(t && (t == int_type || t == char_type))
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isIntegralType(A_TYPE *t)
{
    if(t && t->kind == T_ENUM && t != float_type)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isFunctionType(A_TYPE *t)
{
    if(t && t->kind == T_FUNC)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isStructOrUnionType(A_TYPE *t)
{
    if(t && (t->kind == T_STRUCT || t->kind == T_UNION))
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isPointerType(A_TYPE *t)
{
    if(t && t->kind == T_POINTER)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isPointerOrArrayType(A_TYPE *t)
{
    if(t && (t->kind == T_POINTER || t->kind == T_ARRAY))
        return(TRUE);
    else        
        return(FALSE);
}

BOOLEAN isIntType(A_TYPE *t)
{
    if(t && t == int_type)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isVoidType(A_TYPE *t)
{
    if(t && t == void_type)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isArrayType(A_TYPE *t)
{
    if(t && t->kind == T_ARRAY)
        return(TRUE);
    else    
        return(FALSE);
}

BOOLEAN isStringType(A_TYPE *t)
{
    if(t && (t->kind == T_POINTER || t->kind == T_ARRAY) && t->element_type == char_type)
        return(TRUE);
    else
        return(FALSE);
}

/*
    주어진 리터럴의 타입을 인자로 받은 타입으로 변환한다.
*/
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL result, A_TYPE *t, int ll)
{
    if(result.type == int_type && t == int_type ||
            result.type == char_type && t == char_type ||
            result.type == float_type && t == float_type)
        ;
    else if(result.type == int_type && t == float_type) {
        result.type = float_type;
        result.value.f = result.value.i;
    }
    else if(result.type == int_type && t == char_type) {
        result.type = char_type;
        result.value.c = result.value.i;
    }
    else if(result.type == float_type && t == int_type) {
        result.type = int_type;
        result.value.i = result.value.f;
    }
    else if(result.type == char_type && t == int_type) {
        result.type = int_type;
        result.value.i = result.value.c;
    }
    else
        semantic_error(41, ll);

    return(result);
}

/*
    주어진 신택스 트리로부터 수식의 값과 타입을 계산하여 리터럴 테이블을 만들고 그 주소를 리턴
*/
A_LITERAL getTypeAndValueOfExpression(A_NODE *node)
{
    A_TYPE *t;
    A_ID *id;
    A_LITERAL result, r;
    result.type = NIL;

    switch(node->name) {
        case N_EXP_IDENT:
            id = node->clink;
            if(id->kind != ID_ENUM_LITERAL)
                semantic_error(19, node->line, id->name);
            else {
                result.type = int_type;
                result.value.i = id->init;
            }
            break;
        case N_EXP_INT_CONST:
            result.type = int_type;
            result.value.i = (int)node->clink;
            break;
        case N_EXP_CHAR_CONST:
            result.type = char_type;
            result.value.c = (char)node->clink;
            break;
        case N_EXP_FLOAT_CONST:
            result.type = float_type;
            result.value.f = atof(node->clink);
            break;
        case N_EXP_STRING_LITERAL:
        case N_EXP_ARRAY:
        case N_EXP_FUNCTION_CALL:
        case N_EXP_STRUCT:
        case N_EXP_ARROW:
        case N_EXP_POST_INC:
        case N_EXP_PRE_INC:
        case N_EXP_POST_DEC:
        case N_EXP_PRE_DEC:
        case N_EXP_AMP:
        case N_EXP_STAR:
        case N_EXP_NOT:
            semantic_error(18, node->line);
            break;
        case N_EXP_MINUS:
            result = getTypeAndValueOfExpression(node->clink);
            if(result.type == int_type)
                result.value.i = -result.value.i;
            else if(result.type == float_type)
                result.value.f = -result.value.f;
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_SIZE_EXP:
            t = sem_expression(node->clink);
            result.type = int_type;
            result.value.i = t->size;
            break;
        case N_EXP_SIZE_TYPE:
            result.type = int_type;
            result.value.i = sem_A_TYPE(node->clink);
            break;
        case N_EXP_CAST:
            result = getTypeAndValueOfExpression(node->rlink);
            result = checkTypeAndConvertLiteral(result, (A_TYPE *)node->llink, node->line);
            break;
        case N_EXP_MUL:
            result = getTypeAndValueOfExpression(node->llink);
            r = getTypeAndValueOfExpression(node->rlink);
            
            if(result.type == int_type && r.type == int_type) {
                result.type = int_type;
                result.value.i = result.value.i * r.value.i;
            }
            else if(result.type == int_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.i * r.value.f;
            }
            else if(result.type == float_type && r.type == int_type) {
                result.type = float_type;
                result.value.f = result.value.f * r.value.i;
            }
            else if(result.type == float_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.f * r.value.f;
            }
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_DIV:
            result = getTypeAndValueOfExpression(node->llink);
            r = getTypeAndValueOfExpression(node->rlink);

            if(result.type == int_type && r.type == int_type) {
                result.type = int_type;
                result.value.i = result.value.i / r.value.i;
            }
            else if(result.type == int_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.i / r.value.f;
            }
            else if(result.type == float_type && r.type == int_type) {
                result.type = float_type;
                result.value.f = result.value.f / r.value.i;
            }
            else if(result.type == float_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.f / r.value.f;
            }
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_MOD:
            result = getTypeAndValueOfExpression(node->llink);
            r = getTypeAndValueOfExpression(node->rlink);

            if(result.type == int_type && r.type == int_type)
                result.value.i = result.value.i % r.value.i;
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_ADD:
            result = getTypeAndValueOfExpression(node->llink);
            r = getTypeAndValueOfExpression(node->rlink);

            if(result.type == int_type && r.type == int_type) {
                result.type = int_type;
                result.value.i = result.value.i + r.value.i;
            }
            else if(result.type == int_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.i + r.value.f;
            }
            else if(result.type == float_type && r.type == int_type) {
                result.type = float_type;
                result.value.f = result.value.f + r.value.i;
            }
            else if(result.type == float_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.f + r.value.f;
            }
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_SUB:
            result = getTypeAndValueOfExpression(node->llink);
            r = getTypeAndValueOfExpression(node->rlink);

            if(result.type == int_type && r.type == int_type) {
                result.type = int_type;
                result.value.i = result.value.i - r.value.i;
            }
            else if(result.type == int_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.i - r.value.f;
            }
            else if(result.type == float_type && r.type == int_type) {
                result.type = float_type;
                result.value.f = result.value.f - r.value.i;
            }
            else if(result.type == float_type && r.type == float_type) {
                result.type = float_type;
                result.value.f = result.value.f - r.value.f;
            }
            else
                semantic_error(18, node->line);
            break;
        case N_EXP_LSS:
        case N_EXP_GTR:
        case N_EXP_LEQ:
        case N_EXP_GEQ:
        case N_EXP_NEQ:
        case N_EXP_EQL:
        case N_EXP_AND:
        case N_EXP_OR:
        case N_EXP_ASSIGN:
            semantic_error(18, node->line);
            break;
        default:
            semantic_error(90, node->line);
            break;
    }
    return(result);
}

void semantic_error(int i, int ll, char *s)
{
    semantic_err++;
    printf("*** semantic error at line %d: ", ll);

    switch(i) {
        case 13:
            printf("arith type expr required in unary operation\n");
            break;
        case 18:
            printf("illegal constant expression\n");
            break;
        case 19:
            printf("illegal identifier %s in constant expression\n", s);
            break;
        case 21:
            printf("illegal type in function call expression\n");
            break;
        case 24:
            printf("incompatible type in additive expression\n");
            break;
        case 27:
            printf("scalar type expr required in expression\n");
            break;
        case 28:
            printf("arith type expression required in binary operation\n");
            break;
        case 29:
            printf("integral type expression required in expression\n");
            break;
        case 31:
            printf("pointer type expr required in pointer operation\n");
            break;
        case 32:
            printf("array type required in array expression\n");
            break;
        case 34:
            printf("too many arguments in function call\n");
            break;
        case 35:
            printf("too few arguments in function call\n");
            break;
        case 37:
            printf("illegal struct field identifier in struct reference expr\n");
            break;
        case 38:
            printf("illegal kind of identifier %s in expression\n");
            break;
        case 39:
            printf("illegal type size in sizeof operation\n");
            break;
        case 40:
            printf("illegal expression type in relational operation\n");
            break;
        case 41:
            printf("incompatible type in literal\n");
            break;
        case 49:
            printf("scalar type expr required in middle of for-expr\n");
            break;
        case 50:
            printf("integral type expression required in statement\n");
            break;
        case 51:
            printf("illegal expression type in case lable\n");
            break;
        case 57:
            printf("not permitted type conversion in return expression\n");
            break;
        case 58:
            printf("not permitted type casting in expression\n");
            break;
        case 59:
            printf("not permitted type conversion in argument\n");
            break;
        case 60:
            printf("expression is not an lvalue\n");
            break;
        case 71:
            printf("case label not within a switch statement\n");
            break;
        case 72:
            printf("default label not within a switch statement\n");
            break;
        case 73:
            printf("break statement not within loop or switch statement\n");
            break;
        case 74:
            printf("continue statement not within a loop\n");
            break;
        case 80:
            printf("undefined type\n");
            break;
        case 81:
            printf("integer type expression required in enumerator\n");
            break;
        case 82:
            printf("illegal array size or type\n");
            break;
        case 83:
            printf("illegal element type of array declarator\n");
            break;
        case 84:
            printf("illegal type in struct or union field\n");
            break;
        case 85:
            printf("invalid function return type\n");
            break;
        case 86:
            printf("illegal array size or empty array\n");
            break;
        case 89:
            printf("unknown identifier kind: %s\n", s);
            break;
        case 90:
            printf("fatal compiler error in parse result\n");
            break;
        case 93:
            printf("too many literals in source program\n");
            break;
        default:
            printf("unknown\n");
            break;
    }
}

void semantic_warning(int i, int ll)
{
    printf("--- warning at line %d: ", ll);

    switch(i) {
        case 11:
            printf("incompatible types in assignment expression\n");
            break;
        case 12:
            printf("incompatible types in argument or return expr\n");
            break;
        case 14:
            printf("incompatible types in binary expression\n");
            break;
        case 16:
            printf("integer type expression is required\n");
            break;
        default:
            printf("unknown\n");
            break;
    }
}