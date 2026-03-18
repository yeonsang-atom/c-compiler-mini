// A1 Header File ‘type.h’

#define NIL 0

typedef enum {FALSE,TRUE} BOOLEAN;

/*
 * 프로그램 중의 명령문이나 수식들을 보관하기 위한 구조체
 * 효율적으로 보관하기 위해 삼진 트리 형태로 저장 및 관리한다.
 * 종류는 아래와 같다.
 */
typedef enum e_node_name {
    N_NULL,
    N_PROGRAM,
    N_EXP_IDENT,
    N_EXP_INT_CONST,
    N_EXP_FLOAT_CONST,
    N_EXP_CHAR_CONST,
    N_EXP_STRING_LITERAL,
    N_EXP_ARRAY,
    N_EXP_FUNCTION_CALL,
    N_EXP_STRUCT,
    N_EXP_ARROW,
    N_EXP_POST_INC,
    N_EXP_POST_DEC,
    N_EXP_PRE_INC,
    N_EXP_PRE_DEC,
    N_EXP_AMP,
    N_EXP_STAR,
    N_EXP_NOT,
    N_EXP_PLUS,
    N_EXP_MINUS,
    N_EXP_SIZE_EXP,
    N_EXP_SIZE_TYPE,
    N_EXP_CAST,
    N_EXP_MUL,
    N_EXP_DIV,
    N_EXP_MOD,
    N_EXP_ADD,
    N_EXP_SUB,
    N_EXP_LSS,
    N_EXP_GTR,
    N_EXP_LEQ,
    N_EXP_GEQ,
    N_EXP_NEQ,
    N_EXP_EQL,
    N_EXP_AND,
    N_EXP_OR,
    N_EXP_ASSIGN,
    N_ARG_LIST,
    N_ARG_LIST_NIL,
    N_STMT_LABEL_CASE,
    N_STMT_LABEL_DEFAULT,
    N_STMT_COMPOUND,
    N_STMT_EMPTY,
    N_STMT_EXPRESSION,
    N_STMT_IF,
    N_STMT_IF_ELSE,
    N_STMT_SWITCH,
    N_STMT_WHILE,
    N_STMT_DO,
    N_STMT_FOR,
    N_STMT_RETURN,
    N_STMT_CONTINUE,
    N_STMT_BREAK,
    N_FOR_EXP,
    N_STMT_LIST,
    N_STMT_LIST_NIL,
    N_INIT_LIST,
    N_INIT_LIST_ONE,
    N_INIT_LIST_NIL
} NODE_NAME;

typedef enum {Q_NULL,Q_CONST,Q_VOLATILE} Q_KIND;

/*
 * 각 명칭에 대한 정보를 저장하기 위해 심볼 테이블 자료 구조를 사용.
 * A_ID : syntax_analysis를 위한 Symbol Table이다.
 * S_KIND : specifier의 종류 (auto, static, typedef 등)
 * ID_KIND : 식별자의 종류 (variable, function, struct, enum 등)
 */
typedef enum {S_NULL,S_AUTO,S_STATIC,S_TYPEDEF,S_EXTERN,S_REGISTER} S_KIND;
typedef enum {ID_NULL,ID_VAR,ID_FUNC,ID_PARM,ID_FIELD,ID_TYPE,ID_ENUM, ID_STRUCT,ID_ENUM_LITERAL} ID_KIND;
typedef struct s_node {
    NODE_NAME name;
    int line;
    int value;
    struct s_type *type;
    struct s_node *llink;
    struct s_node *clink;
    struct s_node *rlink;
} A_NODE;

/*
 * 원시 프로그램에서 선언한 모든 타입에 대한 정보를 저장하기 위한 타입 테이블
 * A_TYPE : 타입 테이블
 * T_KIND : 타입의 종류
 */
typedef enum {T_NULL,T_ENUM,T_ARRAY,T_STRUCT,T_UNION,T_FUNC,T_POINTER,T_VOID} T_KIND;
typedef struct s_type {
    T_KIND kind;
    int size;
    int local_var_size;
    struct s_type *element_type;
    struct s_id *field;
    struct s_node *expr;
    int line;
    BOOLEAN check;
    BOOLEAN prt; 
} A_TYPE;

typedef struct s_id {
    char *name;
    ID_KIND kind;
    S_KIND specifier;
    int level;
    int address;
    int value;
    A_NODE *init;
    A_TYPE *type;
    int line;
    struct s_id *prev;
    struct s_id *link;
} A_ID;

/*
 * 프로그램 중에 사용된 모든 실수형 상수, 스트링 리터럴, 전역변수의 초기화 수식으로 표현된 상수들을
 * 리터럴 테이블에 모아 놓고, 코드 생성 과정에서 사용하도록 함. 상수들을 계산하여 저장하기 위함.
 * A_LITERAL : 리터럴 테이블
 * LIT_VAL : 상수형 리터럴의 정수, 실수, 스트링 등 세 가지 종류의 리터럴 값을 저장하기 위한 union
 */
typedef union {int i; float f; char c; char *s;} LIT_VALUE;
typedef struct lit {
    int addr;
    A_TYPE *type; 
    LIT_VALUE value;
} A_LITERAL;

/*
 * 프로그램에서 사용하는 명칭을 선언하는 선언자의 타입이나 기억장소 형태 등에 관한
 * 정보를 저장하기 위해 사용하는 '선언 명시자 테이블'
 * S_KIND enum 자료를 같이 사용한다.
 */
typedef struct {
    A_TYPE *type;
    S_KIND stor;
    int line;
} A_SPECIFIER;
