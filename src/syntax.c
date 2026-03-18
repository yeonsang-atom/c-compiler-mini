#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "type.h"
#include "yacc.tab.h"

extern char *yytext;

A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_NODE *root;
A_ID *current_id = NIL;

int syntax_err = 0;
int line_no = 1;
int current_level = 0;

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

//void syntax_error(int i, ...);
void syntax_error();
void initialize();

// 신택스 트리를 위한 새로운 노드 생성
A_NODE *makeNode(NODE_NAME n, A_NODE *a, A_NODE *b, A_NODE *c) {
    A_NODE *m;
    m = (A_NODE *)malloc(sizeof(A_NODE));
    m->name = n;
    m->llink = a;
    m->clink = b;
    m->rlink = c;
    m->type = NIL;
    m->line = line_no;
    m->value = 0;
    return(m);
}

A_NODE *makeNodeList(NODE_NAME n, A_NODE *a, A_NODE *b) {
    A_NODE *m, *k;
    k = a;
    
    while(k->rlink)
        k = k->rlink;

    m = (A_NODE *)malloc(sizeof(A_NODE));
    m->name = k->name;
    m->llink = NIL;
    m->clink = NIL;
    m->rlink = NIL;
    m->type = NIL;
    m->line = line_no;
    m->value = 0;
    k->name = n;
    k->llink = b;
    k->rlink = m;
    return(a);
}

// 식별자를 위해 새로운 선언자 생성 즉, A_ID 생성
A_ID *makeIdentifier(char *s) {
    A_ID *id;
    id = malloc(sizeof(A_ID));
    id->name = s;
    id->kind = 0;
    id->specifier = 0;
    id->level = current_level;
    id->address = 0;
    id->init = NIL;
    id->type = NIL;
    id->link = NIL;
    id->line = line_no;
    id->value = 0;
    id->prev = current_id;
    current_id = id;
    return(id);
}

// 가짜 식별자 위해 새로운 선언자 생성 즉, A_ID 생성 : 이름이 없는 식별자
A_ID *makeDummyIdentifier() {
    A_ID *id;
    id = malloc(sizeof(A_ID));
    id->name = "";
    id->kind = 0;
    id->specifier = 0;
    id->level = current_level;
    id->address = 0;
    id->init = NIL;
    id->type = NIL;
    id->link = NIL;
    id->line = line_no;
    id->value = 0;
    id->prev = 0;
    return(id);
}

// 새로운 타입 생성
A_TYPE *makeType(T_KIND k) {
    A_TYPE *t;
    t = malloc(sizeof(A_TYPE));
    t->kind = k;
    t->size = 0;
    t->local_var_size = 0;
    t->element_type = NIL;
    t->field = NIL;
    t->expr = NIL;
    t->check = FALSE;
    t->prt = FALSE;
    t->line = line_no;
    return(t);
}

// 새로운 명시자 생성
A_SPECIFIER *makeSpecifier(A_TYPE *t, S_KIND s) {
    A_SPECIFIER *p;
    p = malloc(sizeof(A_SPECIFIER));
    p->type = t;
    p->stor = s;
    p->line = line_no;
    return(p);
}

A_ID *searchIdentifier(char *s, A_ID *id) {
    while(id) {
        if(strcmp(id->name, s) == 0)
            break;
        
        id = id->prev;
    }
    return(id);
}

// 같은 current_level에 명시자가 있는지 확인
A_ID *searchIdentifierAtCurrentLevel(char *s, A_ID *id) {
    while(id) {
        // 확인하려는 id의 레벨이 현재 id의 레벨보다 작다면 찾고자 하는 id 존재하지 않음.
        if(id->level < current_id->level)
            return(NIL);
        if(strcmp(id->name, s) == 0)
            break;
        
        id = id->prev;
    }
    return(id);
}

// 명시자의 중복 선언 여부를 검사
void checkForwardReference() {
    A_ID *id;
    A_TYPE *t;

    // 중복 선언 여부를 검사하는 것이기 때문에 id의 종류가 ID_NULL이거나 struct, enum type인데 그 타입의 필드가 없다면 신택스 에러.
    id = current_id;
    while(id) {
        if(id->level < current_level)
            break;
        
        t = id->type;
        if(id->kind == ID_NULL)
            syntax_error(31, id->name);
        else if((id->kind == ID_STRUCT || id->kind == ID_ENUM) && t->field == NIL)
            syntax_error(32, id->name);
        
        id = id->prev;
    }
}

// 명시자의 디폴트 값을 설정한다. C언어에서 따로 명시되지 않았다면 type, stor은 각각 int와 auto가 default 값이다.
void setDefaultSpecifier(A_SPECIFIER *p) {
    A_TYPE *t;
    
    if(p->type == NIL)
        p->type = int_type;

    if(p->stor == S_NULL)
        p->stor = S_AUTO;
}

// 명시자의 타입과 종류 업데이트
A_SPECIFIER *updateSpecifier(A_SPECIFIER *p, A_TYPE *t, S_KIND s) {
    if(t) {
        if(p->type) {
            if(p->type == t)
                ;
            else
                syntax_error(24);
        }
        else
            p->type = t;
    }
    if(s) {
        if(p->stor) {
            if(p->stor == s)
                ;
            else
                syntax_error(24);
        }
        else
            p->stor = s;
    }
    return(p);
}

// 선언자 리스트 두개를 연결 (심볼 테이블 두 개를 연결)
A_ID *linkDeclaratorList(A_ID *id1, A_ID *id2) {
    A_ID *m = id1;
    if(id1 == NIL)
        return(id2);
    
    // id1의 말단으로 이동한 후에 id2를 그 뒤에 연결
    while(m->link)
        m = m->link;
    
    m->link = id2;
    return(id1);
}

// primary expression에서 identifier가 선언되어 있는지를 확인
A_ID *getIdentifierDeclared(char *s) {
    A_ID *id;
    id = searchIdentifier(s, current_id);
    
    // 만약 문자열 s에 해당하는 심볼 테이블이 없는 경우, 선언되어 있지 않음 -> 즉, 신택스 에러
   if(id == NIL)
        syntax_error(13, s);

    return(id);
}

// struct, enum으로 선언된 identifier의 타입을 가져오는 함수
A_TYPE *getTypeOfStructOrEnumRefIdentifier(T_KIND k, char *s, ID_KIND kk) {
    A_TYPE *t;
    A_ID *id;
    id = searchIdentifier(s, current_id);

    if(id) {
        if(id->kind == kk && id->type->kind == k)
            return(id->type);
        else
            syntax_error(11, s);
    }

    // 선언된 identifier가 없는 경우 새로운 struct, enum 식별자를 생성
    t = makeType(k);
    id = makeIdentifier(s);
    id->kind = kk;
    id->type = t;
    return(t);
}

// 심볼 테이블의 선언자에 대한 초기화가 있는 경우, 그에 관한 신택스 트리를 연결
A_ID *setDeclaratorInit(A_ID *id, A_NODE *n) {
    id->init = n;
    return(id);
}

// 심볼 테이블의 선언자에 대한 종류를 설정
A_ID *setDeclaratorKind(A_ID *id, ID_KIND k) {
    A_ID *a;
    a = searchIdentifierAtCurrentLevel(id->name, id->prev);
    
    // 같은 current_level에 선언이 되어 있는 경우 에러
    if(a)
        syntax_error(12, id->name);
    
    id->kind = k;
    return(id);
}

// 심볼 테이블의 선언자에 대한 타입을 설정
// 추후 setDeclaratorTypeAndKind 함수에서 사용
A_ID *setDeclaratorType(A_ID *id, A_TYPE *t) {
    id->type = t;
    return(id);
}

A_ID *setDeclaratorElementType(A_ID *id, A_TYPE *t) {
    A_TYPE *tt;
    if(id->type == NIL)
        id->type = t;
    else {
        tt = id->type;
        while(tt->element_type)
            tt = tt->element_type;
        tt->element_type = t;
    }
    return(id);
}

// 심볼 테이블에서 선언자의 타입과 종류를 설정
A_ID *setDeclaratorTypeAndKind(A_ID *id, A_TYPE *t, ID_KIND k) {
    id = setDeclaratorElementType(id, t);
    id = setDeclaratorKind(id, k);
    return(id);
}

// 심볼 테이블에서 함수 명칭 선언자인지 확인하고 그에 대한 리턴 타입 확인 및 설정
A_ID *setFunctionDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p) {
    A_ID *a;
    
    // 함수 명칭 선언자에 이미 stor가 존재하는 경우 신택스 에러
    if(p->stor)
        syntax_error(25);
    
    // 우선 int, auto인 디폴트 값으로 세팅
    setDefaultSpecifier(p);
    
    // 함수 명칭 선언자에 링크된 타입 테이블의 종류가 T_FUNC 가 아닌 경우 에러
    if(id->type->kind != T_FUNC) {
        syntax_error(21);
        return(id);
    }
    else {  // T_FUNC인 경우 id의 종류와 타입, elment의 타입 설정
        id = setDeclaratorElementType(id, p->type);
        id->kind = ID_FUNC;
    }

    // 중복 선언 여부 확인 (프로토타입 선언인지 등등)
    a = searchIdentifierAtCurrentLevel(id->name, id->prev);
    if(a) {
        if(a->kind != ID_FUNC || a->type->expr)
            syntax_error(12, id->name);
        else {  // 이미 앞서 함수의 명칭이 심볼 테이블에 있는 경우 : 프로토타입 선언으로 인해 심볼 테이블에 존재하는 경우
            // 해당 프로토 타입 선언에서의 파라미터와 리턴 타입 확인
            if(isNotSameFormalParameters(a->type->field, id->type->field))
                syntax_error(22, id->name);
            if(isNotSameType(a->type->element_type, id->type->element_type))
                syntax_error(26, a->name);
        }
    }
    // 함수 명칭 심볼 테이블에 연결된 타입 테이블의 필드 값을 설정하고, 그 필드 값을 통해 current_id 설정
    a = id->type->field;
    while(a) {
        if(strlen(a->name))
            current_id = a;
        else if (a->type)
            syntax_error(23);
        a = a->link;
    }
    return(id);
}

// 함수 몸체를 타입 심볼 테이블의 expr에 연결
A_ID *setFunctionDeclaratorBody(A_ID *id, A_NODE *n) {
    id->type->expr = n;
    return(id);
}

// 선언자 리스트의 타입과 종류를 storage_class 기반으로 설정
A_ID *setDeclaratorListSpecifier(A_ID *id, A_SPECIFIER *p) {
    A_ID *a;
    setDefaultSpecifier(p);
    a = id;

    while(a) {  // a의 link를 따라가며 각 심볼 테이블에서의 kind, specifier, stor 등의 정보를 저장
        if(strlen(a->name) && searchIdentifierAtCurrentLevel(a->name, a->prev))
            syntax_error(12, a->name);
        
        a = setDeclaratorElementType(a, p->type);
        if(p->stor == S_TYPEDEF)
            a->kind = ID_TYPE;
        else if(a->type->kind == T_FUNC)
            a->kind = ID_FUNC;
        else
            a->kind = ID_VAR;
        
        a->specifier = p->stor;
        if(a->specifier == S_NULL)
            a->specifier = S_AUTO;
        
        a = a->link;
    }
    return(id);
}

// 파라미터에 해당하는 심볼 테이블과 그 타입 테이블의 element_type 설정
A_ID *setParameterDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p) {
    // 중복 선언 확인
    if(searchIdentifierAtCurrentLevel(id->name, id->prev))
        syntax_error(12, id->name);
    
    // 파라미터의 storage_class 확인 및 void 타입 여부 확인
    // 함수 파라미터의 stor은 없어야하고, 파라미터의 명칭이 존재하는데 void 타입일 수 없음.
    if(p->stor || p->type == void_type)
        syntax_error(14);
    
    setDefaultSpecifier(p);
    id = setDeclaratorElementType(id, p->type);
    id->kind = ID_PARM;
    return(id);
}

A_ID *setStructDeclaratorListSpecifier(A_ID *id, A_TYPE *t) {
    A_ID *a;
    a = id;
    while(a) {
        // 해당 current_level에서의 중복 선언 여부 확인
        if(searchIdentifierAtCurrentLevel(a->name, a->prev))
            syntax_error(12, a->name);
        
        a = setDeclaratorElementType(a, t);
        a->kind = ID_FIELD;
        a = a->link;
    }
    return(id);
}

A_TYPE *setTypeNameSpecifier(A_TYPE *t, A_SPECIFIER *p) {
    if(p->stor)
        syntax_error(20);
    
    setDefaultSpecifier(p);
    t = setTypeElementType(t, p->type);
    return(t);
}

// element_type의 type을 설정, 즉 최종 타입 결정
A_TYPE *setTypeElementType(A_TYPE *t, A_TYPE *s) {
    A_TYPE *q;
    if(t == NIL)
        return(s);
    q = t;
    while(q->element_type)
        q = q->element_type;
    q->element_type = s;
    return(t);
}

// 타입 테이블의 필드 값 설정 및 연결
A_TYPE *setTypeField(A_TYPE *t, A_ID *n) {
    t->field = n;
    return(t);
}

// 타입 테이블의 expr에 초기화 수식 연결
A_TYPE *setTypeExpr(A_TYPE *t, A_NODE *n) {
    t->expr = n;
    return(t);
}

// struct 식별자의 타입 설정
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND k, char *s, ID_KIND kk) {
    A_TYPE *t;
    A_ID *id, *a;

    // 중복 선언 여부와 전방 참조 여부 확인
    a = searchIdentifierAtCurrentLevel(s, current_id);
    if(a) {
        if(a->kind == kk && a->type->kind == k) {
            if(a->type->field)
                syntax_error(12, s);
            else
                return(a->type);
        }
        else
            syntax_error(12, s);
    }

    // 문자열 s를 name으로 하는 심볼 테이블이 존재하지 않는다면 심볼 테이블 생성 후, 타입 설정
    id = makeIdentifier(s);
    t = makeType(k);
    id->type = t;
    id->kind = kk;
    return(t);
}

// 심볼 테이블의 타입과 종류 설정
A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *t, ID_KIND k, A_ID *id) {
    if(searchIdentifierAtCurrentLevel(id->name, id->prev))
        syntax_error(12, id->name);
    
    id->type = t;
    id->kind = k;
    return(t);
}

BOOLEAN isNotSameFormalParameters(A_ID *a, A_ID *b) {
    if(a == NIL)
        return(FALSE);
    
    while(a) {
        if(b == NIL || isNotSameType(a->type, b->type))
            return(TRUE);
        
        a = a->link;
        b = b->link;
    }

    if(b)
        return(TRUE);
    else
        return(FALSE);
}

BOOLEAN isNotSameType(A_TYPE *t1, A_TYPE *t2) {
    if(isPointerOrArrayType(t1) || isPointerOrArrayType(t2))
        return(isNotSameType(t1->element_type, t2->element_type));
    else
        return(t1 != t2);
}

/*
BOOLEAN isPointerOrArrayType(A_TYPE *t) {
    if(t->kind == T_POINTER || t->kind == T_ARRAY)
        return(TRUE);
    else
        return(FALSE);
}
*/

void initialize() {
    // int, float, char, void 등의 기본 타입을 설정하고 추후 시멘틱 분석에서 필요한 각 타입의 사이즈 설정
    int_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("int"));
    float_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("float"));
    char_type = setTypeAndKindOfDeclarator(makeType(T_ENUM), ID_TYPE, makeIdentifier("char"));
    void_type = setTypeAndKindOfDeclarator(makeType(T_VOID), ID_TYPE, makeIdentifier("void"));
    string_type = setTypeElementType(makeType(T_POINTER), char_type);

    int_type->size = 4;     int_type->check = TRUE;
    float_type->size = 4;   float_type->check = TRUE;
    char_type->size = 1;    char_type->check = TRUE;
    void_type->size = 0;    void_type->check = TRUE;
    string_type->size = 4;  string_type->check = TRUE;

    // printf 라이브러리 함수
    setDeclaratorTypeAndKind(
        makeIdentifier("printf"),
        setTypeField(
            setTypeElementType(makeType(T_FUNC), void_type),
            linkDeclaratorList(
                setDeclaratorTypeAndKind(makeDummyIdentifier(), string_type, ID_PARM),
                setDeclaratorKind(makeDummyIdentifier(), ID_PARM))),
        ID_FUNC);

    // scanf 라이브러리 함수
    setDeclaratorTypeAndKind(
        makeIdentifier("scanf"),
        setTypeField(
            setTypeElementType(makeType(T_FUNC), void_type),
            linkDeclaratorList(
                setDeclaratorTypeAndKind(makeDummyIdentifier(), string_type, ID_PARM),
                setDeclaratorKind(makeDummyIdentifier(), ID_PARM))),
        ID_FUNC);

    // malloc() 라이브러리 함수 -> (int)
    setDeclaratorTypeAndKind(
        makeIdentifier("malloc"),
        setTypeField(
            setTypeElementType(makeType(T_FUNC), string_type),
            setDeclaratorTypeAndKind(makeDummyIdentifier(), int_type, ID_PARM)),
        ID_FUNC);
}


void syntax_error(int i, char *s) {
    syntax_err++;
    printf("line %d : syntax error : ", line_no);

    switch(i) {
        case 11:
            printf("illegal referencing struct or union identfier %s", s);
            break;
        case 12:
            printf("redeclaration of identifier %s", s);
            break;
        case 13:
            printf("undefined identifier %s", s);
            break;
        case 14:
            printf("illegal type specifier in formal parameter");
            break;
        case 20:
            printf("illegal storage class in type specifier");
            break;
        case 21:
            printf("illegal function declarator");
            break;
        case 22:
            printf("conflicting parm type in prototype function %s", s);
            break;
        case 23:
            printf("empty parameter name");
            break;
        case 24:
            printf("illegal declaration specifiers");
            break;
        case 25:
            printf("illegal function specifiers");
            break;
        case 26:
            printf("illegal or conflicting return type in function %s", s);
            break;
        case 31:
            printf("undefined type for identifier %s", s);
            break;
        case 32:
            printf("incomplete forward reference for identifier %s", s);
            break;
        default:
            printf("unknown");
            break;
    }

    if(strlen(yytext) == 0)
        printf(" at end\n");
    else
        printf(" near %s\n", yytext);
}
