/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

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

#line 135 "yacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE_IDENTIFIER = 4,            /* TYPE_IDENTIFIER  */
  YYSYMBOL_FLOAT_CONSTANT = 5,             /* FLOAT_CONSTANT  */
  YYSYMBOL_INTEGER_CONSTANT = 6,           /* INTEGER_CONSTANT  */
  YYSYMBOL_CHARACTER_CONSTANT = 7,         /* CHARACTER_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 8,             /* STRING_LITERAL  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_PLUSPLUS = 11,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 12,                /* MINUSMINUS  */
  YYSYMBOL_BAR = 13,                       /* BAR  */
  YYSYMBOL_AMP = 14,                       /* AMP  */
  YYSYMBOL_BARBAR = 15,                    /* BARBAR  */
  YYSYMBOL_AMPAMP = 16,                    /* AMPAMP  */
  YYSYMBOL_ARROW = 17,                     /* ARROW  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_LSS = 19,                       /* LSS  */
  YYSYMBOL_GTR = 20,                       /* GTR  */
  YYSYMBOL_LEQ = 21,                       /* LEQ  */
  YYSYMBOL_GEQ = 22,                       /* GEQ  */
  YYSYMBOL_EQL = 23,                       /* EQL  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_DOTDOTDOT = 25,                 /* DOTDOTDOT  */
  YYSYMBOL_LP = 26,                        /* LP  */
  YYSYMBOL_RP = 27,                        /* RP  */
  YYSYMBOL_LB = 28,                        /* LB  */
  YYSYMBOL_RB = 29,                        /* RB  */
  YYSYMBOL_LR = 30,                        /* LR  */
  YYSYMBOL_RR = 31,                        /* RR  */
  YYSYMBOL_PERIOD = 32,                    /* PERIOD  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_EXCL = 34,                      /* EXCL  */
  YYSYMBOL_STAR = 35,                      /* STAR  */
  YYSYMBOL_SLASH = 36,                     /* SLASH  */
  YYSYMBOL_PERCENT = 37,                   /* PERCENT  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_COLON = 39,                     /* COLON  */
  YYSYMBOL_AUTO_SYM = 40,                  /* AUTO_SYM  */
  YYSYMBOL_STATIC_SYM = 41,                /* STATIC_SYM  */
  YYSYMBOL_TYPEDEF_SYM = 42,               /* TYPEDEF_SYM  */
  YYSYMBOL_STRUCT_SYM = 43,                /* STRUCT_SYM  */
  YYSYMBOL_ENUM_SYM = 44,                  /* ENUM_SYM  */
  YYSYMBOL_SIZEOF_SYM = 45,                /* SIZEOF_SYM  */
  YYSYMBOL_UNION_SYM = 46,                 /* UNION_SYM  */
  YYSYMBOL_IF_SYM = 47,                    /* IF_SYM  */
  YYSYMBOL_ELSE_SYM = 48,                  /* ELSE_SYM  */
  YYSYMBOL_WHILE_SYM = 49,                 /* WHILE_SYM  */
  YYSYMBOL_DO_SYM = 50,                    /* DO_SYM  */
  YYSYMBOL_FOR_SYM = 51,                   /* FOR_SYM  */
  YYSYMBOL_CONTINUE_SYM = 52,              /* CONTINUE_SYM  */
  YYSYMBOL_BREAK_SYM = 53,                 /* BREAK_SYM  */
  YYSYMBOL_RETURN_SYM = 54,                /* RETURN_SYM  */
  YYSYMBOL_SWITCH_SYM = 55,                /* SWITCH_SYM  */
  YYSYMBOL_CASE_SYM = 56,                  /* CASE_SYM  */
  YYSYMBOL_DEFAULT_SYM = 57,               /* DEFAULT_SYM  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_translation_unit = 60,          /* translation_unit  */
  YYSYMBOL_external_declaration = 61,      /* external_declaration  */
  YYSYMBOL_function_definition = 62,       /* function_definition  */
  YYSYMBOL_63_1 = 63,                      /* @1  */
  YYSYMBOL_64_2 = 64,                      /* @2  */
  YYSYMBOL_declaration_list_opt = 65,      /* declaration_list_opt  */
  YYSYMBOL_declaration_list = 66,          /* declaration_list  */
  YYSYMBOL_declaration = 67,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 68,    /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 69,   /* storage_class_specifier  */
  YYSYMBOL_init_declarator_list_opt = 70,  /* init_declarator_list_opt  */
  YYSYMBOL_init_declarator_list = 71,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 72,           /* init_declarator  */
  YYSYMBOL_initializer = 73,               /* initializer  */
  YYSYMBOL_initializer_list = 74,          /* initializer_list  */
  YYSYMBOL_type_specifier = 75,            /* type_specifier  */
  YYSYMBOL_struct_type_specifier = 76,     /* struct_type_specifier  */
  YYSYMBOL_77_3 = 77,                      /* @3  */
  YYSYMBOL_78_4 = 78,                      /* @4  */
  YYSYMBOL_79_5 = 79,                      /* @5  */
  YYSYMBOL_80_6 = 80,                      /* @6  */
  YYSYMBOL_struct_or_union = 81,           /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 82,   /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 83,        /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 84,    /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 85,         /* struct_declarator  */
  YYSYMBOL_enum_type_specifier = 86,       /* enum_type_specifier  */
  YYSYMBOL_87_7 = 87,                      /* @7  */
  YYSYMBOL_88_8 = 88,                      /* @8  */
  YYSYMBOL_enumerator_list = 89,           /* enumerator_list  */
  YYSYMBOL_enumerator = 90,                /* enumerator  */
  YYSYMBOL_91_9 = 91,                      /* @9  */
  YYSYMBOL_declarator = 92,                /* declarator  */
  YYSYMBOL_pointer = 93,                   /* pointer  */
  YYSYMBOL_direct_declarator = 94,         /* direct_declarator  */
  YYSYMBOL_95_10 = 95,                     /* @10  */
  YYSYMBOL_parameter_type_list_opt = 96,   /* parameter_type_list_opt  */
  YYSYMBOL_parameter_type_list = 97,       /* parameter_type_list  */
  YYSYMBOL_parameter_list = 98,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 99,     /* parameter_declaration  */
  YYSYMBOL_abstract_declarator_opt = 100,  /* abstract_declarator_opt  */
  YYSYMBOL_abstract_declarator = 101,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 102, /* direct_abstract_declarator  */
  YYSYMBOL_statement_list_opt = 103,       /* statement_list_opt  */
  YYSYMBOL_statement_list = 104,           /* statement_list  */
  YYSYMBOL_statement = 105,                /* statement  */
  YYSYMBOL_labeled_statement = 106,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 107,       /* compound_statement  */
  YYSYMBOL_108_11 = 108,                   /* @11  */
  YYSYMBOL_expression_statement = 109,     /* expression_statement  */
  YYSYMBOL_selection_statement = 110,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 111,      /* iteration_statement  */
  YYSYMBOL_for_expression = 112,           /* for_expression  */
  YYSYMBOL_expression_opt = 113,           /* expression_opt  */
  YYSYMBOL_jump_statement = 114,           /* jump_statement  */
  YYSYMBOL_primary_expression = 115,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 116,       /* postfix_expression  */
  YYSYMBOL_arg_expression_list_opt = 117,  /* arg_expression_list_opt  */
  YYSYMBOL_arg_expression_list = 118,      /* arg_expression_list  */
  YYSYMBOL_unary_expression = 119,         /* unary_expression  */
  YYSYMBOL_cast_expression = 120,          /* cast_expression  */
  YYSYMBOL_type_name = 121,                /* type_name  */
  YYSYMBOL_multiplicative_expression = 122, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 123,      /* additive_expression  */
  YYSYMBOL_relational_expression = 124,    /* relational_expression  */
  YYSYMBOL_equality_expression = 125,      /* equality_expression  */
  YYSYMBOL_logical_and_expression = 126,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 127,    /* logical_or_expression  */
  YYSYMBOL_assignment_expression = 128,    /* assignment_expression  */
  YYSYMBOL_constant_expression_opt = 129,  /* constant_expression_opt  */
  YYSYMBOL_constant_expression = 130,      /* constant_expression  */
  YYSYMBOL_expression = 131                /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   453

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  287

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    83,    84,    88,    89,    94,    94,    96,
      96,   100,   101,   105,   107,   111,   115,   116,   117,   118,
     121,   122,   123,   126,   127,   131,   132,   135,   137,   141,
     142,   146,   147,   151,   152,   153,   161,   162,   160,   164,
     165,   164,   168,   172,   173,   176,   177,   183,   187,   188,
     191,   197,   196,   199,   199,   201,   205,   206,   210,   212,
     211,   217,   218,   221,   222,   226,   227,   229,   232,   232,
     241,   242,   245,   246,   251,   253,   256,   258,   262,   263,
     266,   267,   269,   272,   274,   276,   277,   280,   285,   286,
     290,   292,   295,   296,   297,   298,   299,   300,   304,   305,
     309,   309,   315,   316,   320,   321,   322,   326,   327,   328,
     332,   335,   336,   340,   341,   342,   348,   349,   350,   351,
     352,   353,   358,   359,   360,   361,   362,   363,   364,   368,
     369,   372,   373,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   390,   391,   396,   401,   402,   403,   404,
     408,   409,   410,   414,   415,   416,   417,   418,   422,   423,
     424,   428,   429,   433,   434,   439,   440,   443,   444,   447,
     450
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "TYPE_IDENTIFIER", "FLOAT_CONSTANT", "INTEGER_CONSTANT",
  "CHARACTER_CONSTANT", "STRING_LITERAL", "PLUS", "MINUS", "PLUSPLUS",
  "MINUSMINUS", "BAR", "AMP", "BARBAR", "AMPAMP", "ARROW", "SEMICOLON",
  "LSS", "GTR", "LEQ", "GEQ", "EQL", "NEQ", "DOTDOTDOT", "LP", "RP", "LB",
  "RB", "LR", "RR", "PERIOD", "COMMA", "EXCL", "STAR", "SLASH", "PERCENT",
  "ASSIGN", "COLON", "AUTO_SYM", "STATIC_SYM", "TYPEDEF_SYM", "STRUCT_SYM",
  "ENUM_SYM", "SIZEOF_SYM", "UNION_SYM", "IF_SYM", "ELSE_SYM", "WHILE_SYM",
  "DO_SYM", "FOR_SYM", "CONTINUE_SYM", "BREAK_SYM", "RETURN_SYM",
  "SWITCH_SYM", "CASE_SYM", "DEFAULT_SYM", "$accept", "program",
  "translation_unit", "external_declaration", "function_definition", "@1",
  "@2", "declaration_list_opt", "declaration_list", "declaration",
  "declaration_specifiers", "storage_class_specifier",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", "type_specifier",
  "struct_type_specifier", "@3", "@4", "@5", "@6", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_type_specifier",
  "@7", "@8", "enumerator_list", "enumerator", "@9", "declarator",
  "pointer", "direct_declarator", "@10", "parameter_type_list_opt",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "abstract_declarator_opt", "abstract_declarator",
  "direct_abstract_declarator", "statement_list_opt", "statement_list",
  "statement", "labeled_statement", "compound_statement", "@11",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_expression", "expression_opt", "jump_statement",
  "primary_expression", "postfix_expression", "arg_expression_list_opt",
  "arg_expression_list", "unary_expression", "cast_expression",
  "type_name", "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_and_expression",
  "logical_or_expression", "assignment_expression",
  "constant_expression_opt", "constant_expression", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-224)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     131,  -224,  -224,    96,   -17,  -224,  -224,  -224,  -224,    18,
    -224,    24,   131,  -224,  -224,  -224,    96,   196,   196,  -224,
      35,  -224,  -224,    14,    22,    25,  -224,     5,    38,  -224,
    -224,    47,    23,  -224,    15,  -224,  -224,    50,    64,    86,
      22,  -224,   198,  -224,    90,   120,  -224,    96,   354,    86,
     102,  -224,  -224,  -224,   196,  -224,  -224,  -224,  -224,  -224,
     198,   198,   367,   367,   198,   310,   198,   198,   408,  -224,
     260,   138,  -224,   156,   136,   117,   129,   124,   164,  -224,
     151,  -224,  -224,   120,   149,    67,  -224,  -224,   158,   354,
    -224,  -224,  -224,  -224,    39,   196,    16,   171,  -224,   178,
    -224,  -224,  -224,  -224,   198,  -224,  -224,  -224,    58,   186,
     192,  -224,  -224,   310,  -224,  -224,  -224,   218,   198,   198,
     219,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,  -224,    80,   185,  -224,   120,
    -224,   110,    39,    96,    26,  -224,   255,   196,  -224,    96,
      84,   198,  -224,    89,  -224,  -224,   130,  -224,   174,   297,
     134,  -224,   198,  -224,   199,  -224,   200,   202,  -224,   228,
    -224,  -224,  -224,  -224,  -224,   156,   156,   136,   136,   136,
     136,   117,   117,   129,   124,  -224,   198,  -224,  -224,   354,
      32,     4,  -224,  -224,  -224,  -224,  -224,   203,   205,   255,
     233,   207,   250,   198,   244,   198,   235,   245,   255,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,   257,  -224,   251,   252,
     253,   130,   196,   198,  -224,  -224,  -224,  -224,  -224,   198,
    -224,  -224,  -224,  -224,  -224,    96,   198,   198,   231,   198,
    -224,  -224,   265,  -224,   198,   248,   255,  -224,  -224,  -224,
    -224,  -224,  -224,   264,   268,  -224,  -224,   271,   272,   277,
     299,   309,  -224,   301,   255,  -224,  -224,  -224,   255,   255,
     198,   255,   198,   255,  -224,   281,  -224,   303,  -224,   313,
    -224,   255,   315,   198,  -224,  -224,  -224
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    65,    35,     0,    63,    20,    21,    22,    43,    53,
      44,     0,     2,     3,     5,     6,    23,    17,    16,    33,
      39,    34,     9,     0,    62,     0,    64,    55,     0,     1,
       4,     0,    24,    25,    27,    19,    18,    42,     0,     0,
      61,    68,   167,    66,     0,     0,    15,     0,     0,     0,
       0,    40,   100,    10,    70,   116,   118,   117,   119,   120,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     133,   143,   146,   150,   153,   158,   161,   163,   165,   170,
       0,   168,   169,     0,    58,     0,    56,    26,    27,     0,
      28,    29,     8,    37,     0,    11,    78,     0,    71,    72,
      74,   143,   140,   139,     0,   134,   135,   136,    78,     0,
       0,   138,   137,     0,   141,   127,   128,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,    54,     0,
      31,     0,     0,     0,     0,    45,    88,    12,    13,    23,
      70,   167,    76,    80,    77,    79,    81,    69,     0,    70,
      80,   145,     0,   121,     0,   126,     0,   130,   131,     0,
     125,   166,   147,   148,   149,   151,   152,   154,   155,   156,
     157,   159,   160,   162,   164,    52,     0,    57,    30,     0,
       0,     0,    48,    50,    41,    46,   102,     0,     0,     0,
       0,     0,     0,   111,     0,     0,     0,     0,    89,    90,
      92,    93,    94,    95,    96,    97,     0,    14,     0,     0,
       0,    82,    70,   167,    73,    75,   144,   142,   124,     0,
     123,    60,    32,    38,    47,     0,     0,     0,     0,   111,
     114,   115,     0,   112,     0,     0,     0,   101,    91,   103,
      85,    83,    84,     0,     0,   132,    49,     0,     0,     0,
       0,     0,   113,     0,     0,    99,    87,    86,     0,     0,
       0,     0,   111,     0,    98,   104,   107,     0,   109,     0,
     106,     0,     0,   111,   105,   108,   110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -224,  -224,  -224,   322,  -224,  -224,  -224,  -224,  -224,   -81,
       8,  -224,  -224,  -224,   288,   -84,  -224,   -83,  -224,  -224,
    -224,  -224,  -224,  -224,   204,  -132,  -224,   107,  -224,  -224,
    -224,   266,   208,  -224,    -1,     0,   -20,  -224,   -53,  -224,
    -224,   190,   259,   -95,   -86,  -224,  -224,  -167,  -224,   -10,
    -224,  -224,  -224,  -224,  -224,  -223,  -224,  -224,  -224,  -224,
    -224,   122,   -33,   256,    42,   166,    33,   225,   237,  -224,
    -111,  -142,   -35,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    11,    12,    13,    14,    49,    39,   146,   147,    15,
      96,    17,    31,    32,    33,    90,   141,    18,    19,    50,
     142,    38,    94,    20,   144,   145,   191,   192,    21,    44,
      28,    85,    86,   137,    22,    23,    24,    54,   218,    98,
      99,   100,   154,   155,   156,   207,   208,   209,   210,   211,
      95,   212,   213,   214,   260,   242,   215,    69,    70,   166,
     167,    71,    72,   109,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   216
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      82,    97,    25,    40,    26,   140,    82,   168,    16,   220,
     171,   143,   195,    91,   148,    34,   261,     1,     4,     1,
      16,    27,   234,   110,    29,    35,    36,   102,   103,    53,
       2,   107,   238,   111,   112,   -51,     2,   235,    37,    92,
       3,   248,   150,     2,   151,    -7,    88,    82,    41,   279,
      42,     4,    43,    48,    91,   219,    47,   194,   195,   143,
     286,   143,   110,   233,   219,    46,   217,   221,    45,     8,
       9,   110,    10,   108,   221,     8,     9,   169,    10,   265,
     -36,   254,     8,     9,   159,    10,   151,     1,     2,   172,
     173,   174,     1,     4,    51,   152,   153,   274,   138,     1,
     139,   275,   276,   149,   278,   232,   280,   143,   160,    82,
     150,   185,   151,   139,   284,   150,    52,   151,   255,     4,
      83,   108,     3,    84,     5,     6,     7,     8,     9,   226,
      10,     4,    93,    40,     1,     2,   127,   128,   129,   130,
     133,   188,   193,   189,    82,   125,   126,    82,    88,    25,
     153,   231,   131,   132,    91,   149,   222,     3,   223,   160,
     159,   243,   151,    82,   181,   182,     4,   175,   176,   253,
     245,     5,     6,     7,     8,     9,   121,    10,     2,   134,
     135,    82,   101,   101,   105,   106,   101,   -59,   101,   101,
     114,   122,   123,   124,   257,   258,    48,   243,   157,   224,
       2,    55,   263,    56,    57,    58,    59,    60,    61,    62,
      63,   158,    64,   162,     5,     6,     7,     8,     9,   163,
      10,   165,   170,   186,    65,   240,   227,   228,   277,   236,
     243,   237,    66,    67,   193,   229,     5,     6,     7,     8,
       9,   243,    10,    68,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   230,    55,   239,
      56,    57,    58,    59,    60,    61,    62,    63,   241,    64,
     244,   115,   116,   196,   246,   249,   247,   117,   250,   251,
     259,    65,   252,   262,   101,    52,   118,   264,   119,    66,
      67,   266,   120,   177,   178,   179,   180,   267,   268,   269,
      68,     2,   197,   270,   198,   199,   200,   201,   202,   203,
     204,   205,   206,    55,     2,    56,    57,    58,    59,    60,
      61,    62,    63,   159,    64,   151,   271,   272,   273,   281,
     282,   283,     4,   285,    30,    87,    65,     5,     6,     7,
       8,     9,   256,    10,    66,    67,   190,   187,   225,   136,
       5,     6,     7,     8,     9,    68,    10,    55,   183,    56,
      57,    58,    59,    60,    61,    62,    63,   161,    64,   164,
      55,   184,    56,    57,    58,    59,    60,    61,    62,    63,
      65,    64,     0,     0,    89,     0,     0,     0,    66,    67,
       0,     0,     0,   104,     0,     0,     0,     0,     0,    68,
       0,    66,    67,     0,     0,     0,     0,     0,     0,     0,
       0,    55,    68,    56,    57,    58,    59,    60,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,     0,     0,     0,     0,     0,
       0,     0,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68
};

static const yytype_int16 yycheck[] =
{
      42,    54,     3,    23,     4,    89,    48,   118,     0,   151,
     121,    94,   144,    48,    95,    16,   239,     3,    35,     3,
      12,     3,    18,    65,     0,    17,    18,    60,    61,    39,
       4,    64,   199,    66,    67,    30,     4,    33,     3,    49,
      26,   208,    26,     4,    28,    30,    47,    89,    26,   272,
      28,    35,    27,    38,    89,   150,    33,    31,   190,   142,
     283,   144,   104,    31,   159,    18,   147,   153,    30,    43,
      44,   113,    46,    65,   160,    43,    44,   119,    46,   246,
      30,   223,    43,    44,    26,    46,    28,     3,     4,   122,
     123,   124,     3,    35,    30,    96,    96,   264,    31,     3,
      33,   268,   269,    95,   271,   189,   273,   190,   108,   151,
      26,    31,    28,    33,   281,    26,    30,    28,   229,    35,
      30,   113,    26,     3,    40,    41,    42,    43,    44,   162,
      46,    35,    30,   153,     3,     4,    19,    20,    21,    22,
      16,    31,   143,    33,   186,     9,    10,   189,   149,   150,
     150,   186,    23,    24,   189,   147,    26,    26,    28,   159,
      26,   203,    28,   205,   131,   132,    35,   125,   126,   222,
     205,    40,    41,    42,    43,    44,    38,    46,     4,    15,
      29,   223,    60,    61,    62,    63,    64,    38,    66,    67,
      68,    35,    36,    37,   236,   237,    38,   239,    27,    25,
       4,     3,   244,     5,     6,     7,     8,     9,    10,    11,
      12,    33,    14,    27,    40,    41,    42,    43,    44,    27,
      46,     3,     3,    38,    26,    18,    27,    27,   270,    26,
     272,    26,    34,    35,   235,    33,    40,    41,    42,    43,
      44,   283,    46,    45,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    29,     3,    26,
       5,     6,     7,     8,     9,    10,    11,    12,    18,    14,
      26,    11,    12,    18,    39,    18,    31,    17,    27,    27,
      49,    26,    29,    18,   162,    30,    26,    39,    28,    34,
      35,    27,    32,   127,   128,   129,   130,    29,    27,    27,
      45,     4,    47,    26,    49,    50,    51,    52,    53,    54,
      55,    56,    57,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    26,    14,    28,    27,    18,    27,    48,
      27,    18,    35,    18,    12,    47,    26,    40,    41,    42,
      43,    44,   235,    46,    34,    35,   142,   139,   158,    83,
      40,    41,    42,    43,    44,    45,    46,     3,   133,     5,
       6,     7,     8,     9,    10,    11,    12,   108,    14,   113,
       3,   134,     5,     6,     7,     8,     9,    10,    11,    12,
      26,    14,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    45,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    26,    35,    40,    41,    42,    43,    44,
      46,    59,    60,    61,    62,    67,    68,    69,    75,    76,
      81,    86,    92,    93,    94,    92,    93,     3,    88,     0,
      61,    70,    71,    72,    92,    68,    68,     3,    79,    64,
      94,    26,    28,    27,    87,    30,    18,    33,    38,    63,
      77,    30,    30,   107,    95,     3,     5,     6,     7,     8,
       9,    10,    11,    12,    14,    26,    34,    35,    45,   115,
     116,   119,   120,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,    30,     3,    89,    90,    72,    92,    30,
      73,   130,   107,    30,    80,   108,    68,    96,    97,    98,
      99,   119,   120,   120,    26,   119,   119,   120,    68,   121,
     131,   120,   120,    26,   119,    11,    12,    17,    26,    28,
      32,    38,    35,    36,    37,     9,    10,    19,    20,    21,
      22,    23,    24,    16,    15,    29,    89,    91,    31,    33,
      73,    74,    78,    75,    82,    83,    65,    66,    67,    68,
      26,    28,    92,    93,   100,   101,   102,    27,    33,    26,
      93,   100,    27,    27,   121,     3,   117,   118,   128,   131,
       3,   128,   120,   120,   120,   122,   122,   123,   123,   123,
     123,   124,   124,   125,   126,    31,    38,    90,    31,    33,
      82,    84,    85,    92,    31,    83,    18,    47,    49,    50,
      51,    52,    53,    54,    55,    56,    57,   103,   104,   105,
     106,   107,   109,   110,   111,   114,   131,    67,    96,   101,
     129,   102,    26,    28,    25,    99,   120,    27,    27,    33,
      29,   130,    73,    31,    18,    33,    26,    26,   105,    26,
      18,    18,   113,   131,    26,   130,    39,    31,   105,    18,
      27,    27,    29,    96,   129,   128,    85,   131,   131,    49,
     112,   113,    18,   131,    39,   105,    27,    29,    27,    27,
      26,    27,    18,    27,   105,   105,   105,   131,   105,   113,
     105,    48,    27,    18,   105,    18,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    63,    62,    64,
      62,    65,    65,    66,    66,    67,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    75,    77,    78,    76,    79,
      80,    76,    76,    81,    81,    82,    82,    83,    84,    84,
      85,    87,    86,    88,    86,    86,    89,    89,    90,    91,
      90,    92,    92,    93,    93,    94,    94,    94,    95,    94,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     104,   104,   105,   105,   105,   105,   105,   105,   106,   106,
     108,   107,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   113,   113,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   122,   122,   122,   122,
     123,   123,   123,   124,   124,   124,   124,   124,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     131
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     4,     0,
       3,     0,     1,     1,     2,     3,     1,     1,     2,     2,
       1,     1,     1,     0,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     0,     0,     7,     0,
       0,     6,     2,     1,     1,     1,     2,     3,     1,     3,
       1,     0,     6,     0,     5,     2,     1,     3,     1,     0,
       4,     2,     1,     1,     2,     1,     3,     4,     0,     5,
       0,     1,     1,     3,     1,     3,     2,     2,     0,     1,
       1,     1,     2,     3,     3,     3,     4,     4,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     3,
       0,     5,     1,     2,     5,     7,     5,     5,     7,     5,
       5,     0,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     4,     4,     3,     3,     2,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     1,     4,     2,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     0,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: translation_unit  */
#line 79 "yacc.y"
                           { root = makeNode(N_PROGRAM, NIL, yyvsp[0], NIL); checkForwardReference(); }
#line 1514 "yacc.tab.c"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 83 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1520 "yacc.tab.c"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 84 "yacc.y"
                                                { yyval = linkDeclaratorList(yyvsp[-1], yyvsp[0]); }
#line 1526 "yacc.tab.c"
    break;

  case 5: /* external_declaration: function_definition  */
#line 88 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1532 "yacc.tab.c"
    break;

  case 6: /* external_declaration: declaration  */
#line 89 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 1538 "yacc.tab.c"
    break;

  case 7: /* @1: %empty  */
#line 94 "yacc.y"
                                            { yyval = setFunctionDeclaratorSpecifier(yyvsp[0], yyvsp[-1]); }
#line 1544 "yacc.tab.c"
    break;

  case 8: /* function_definition: declaration_specifiers declarator @1 compound_statement  */
#line 95 "yacc.y"
                             { yyval = setFunctionDeclaratorBody(yyvsp[-1], yyvsp[0]); }
#line 1550 "yacc.tab.c"
    break;

  case 9: /* @2: %empty  */
#line 96 "yacc.y"
                        { yyval = setFunctionDeclaratorSpecifier(yyvsp[0], makeSpecifier(int_type, 0)); }
#line 1556 "yacc.tab.c"
    break;

  case 10: /* function_definition: declarator @2 compound_statement  */
#line 97 "yacc.y"
                             { yyval = setFunctionDeclaratorBody(yyvsp[-1], yyvsp[0]); }
#line 1562 "yacc.tab.c"
    break;

  case 11: /* declaration_list_opt: %empty  */
#line 100 "yacc.y"
                                { yyval = NIL; }
#line 1568 "yacc.tab.c"
    break;

  case 12: /* declaration_list_opt: declaration_list  */
#line 101 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1574 "yacc.tab.c"
    break;

  case 13: /* declaration_list: declaration  */
#line 105 "yacc.y"
                                { yyval= yyvsp[0]; }
#line 1580 "yacc.tab.c"
    break;

  case 14: /* declaration_list: declaration_list declaration  */
#line 107 "yacc.y"
                                        { yyval = linkDeclaratorList(yyvsp[-1], yyvsp[0]); }
#line 1586 "yacc.tab.c"
    break;

  case 15: /* declaration: declaration_specifiers init_declarator_list_opt SEMICOLON  */
#line 111 "yacc.y"
                                                                        { yyval = setDeclaratorListSpecifier(yyvsp[-1], yyvsp[-2]); }
#line 1592 "yacc.tab.c"
    break;

  case 16: /* declaration_specifiers: type_specifier  */
#line 115 "yacc.y"
                                { yyval = makeSpecifier(yyvsp[0], 0); }
#line 1598 "yacc.tab.c"
    break;

  case 17: /* declaration_specifiers: storage_class_specifier  */
#line 116 "yacc.y"
                                        { yyval = makeSpecifier(0, yyvsp[0]); }
#line 1604 "yacc.tab.c"
    break;

  case 18: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 117 "yacc.y"
                                                { yyval = updateSpecifier(yyvsp[0], yyvsp[-1], 0); }
#line 1610 "yacc.tab.c"
    break;

  case 19: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 118 "yacc.y"
                                                                { yyval = updateSpecifier(yyvsp[0], 0, yyvsp[-1]); }
#line 1616 "yacc.tab.c"
    break;

  case 20: /* storage_class_specifier: AUTO_SYM  */
#line 121 "yacc.y"
                                { yyval = S_AUTO; }
#line 1622 "yacc.tab.c"
    break;

  case 21: /* storage_class_specifier: STATIC_SYM  */
#line 122 "yacc.y"
                        { yyval = S_STATIC; }
#line 1628 "yacc.tab.c"
    break;

  case 22: /* storage_class_specifier: TYPEDEF_SYM  */
#line 123 "yacc.y"
                        { yyval = S_TYPEDEF; }
#line 1634 "yacc.tab.c"
    break;

  case 23: /* init_declarator_list_opt: %empty  */
#line 126 "yacc.y"
                        { yyval = NIL; }
#line 1640 "yacc.tab.c"
    break;

  case 24: /* init_declarator_list_opt: init_declarator_list  */
#line 127 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1646 "yacc.tab.c"
    break;

  case 25: /* init_declarator_list: init_declarator  */
#line 131 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1652 "yacc.tab.c"
    break;

  case 26: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 132 "yacc.y"
                                                     { yyval = linkDeclaratorList(yyvsp[-2], yyvsp[0]); }
#line 1658 "yacc.tab.c"
    break;

  case 27: /* init_declarator: declarator  */
#line 135 "yacc.y"
                        { yyval = yyvsp[0]; }
#line 1664 "yacc.tab.c"
    break;

  case 28: /* init_declarator: declarator ASSIGN initializer  */
#line 137 "yacc.y"
                                                { yyval = setDeclaratorInit(yyvsp[-2], yyvsp[0]); }
#line 1670 "yacc.tab.c"
    break;

  case 29: /* initializer: constant_expression  */
#line 141 "yacc.y"
                                        { yyval = makeNode(N_INIT_LIST_ONE, NIL, yyvsp[0], NIL); }
#line 1676 "yacc.tab.c"
    break;

  case 30: /* initializer: LR initializer_list RR  */
#line 142 "yacc.y"
                                        { yyval = yyvsp[-1]; }
#line 1682 "yacc.tab.c"
    break;

  case 31: /* initializer_list: initializer  */
#line 146 "yacc.y"
                        { yyval = makeNode(N_INIT_LIST_NIL, NIL, NIL, NIL); }
#line 1688 "yacc.tab.c"
    break;

  case 32: /* initializer_list: initializer_list COMMA initializer  */
#line 147 "yacc.y"
                                                { yyval = makeNodeList(N_INIT_LIST, yyvsp[-2], yyvsp[0]); }
#line 1694 "yacc.tab.c"
    break;

  case 33: /* type_specifier: struct_type_specifier  */
#line 151 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1700 "yacc.tab.c"
    break;

  case 34: /* type_specifier: enum_type_specifier  */
#line 152 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1706 "yacc.tab.c"
    break;

  case 35: /* type_specifier: TYPE_IDENTIFIER  */
#line 153 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1712 "yacc.tab.c"
    break;

  case 36: /* @3: %empty  */
#line 161 "yacc.y"
          { yyval = setTypeStructOrEnumIdentifier(yyvsp[-1], yyvsp[0], ID_STRUCT); }
#line 1718 "yacc.tab.c"
    break;

  case 37: /* @4: %empty  */
#line 162 "yacc.y"
             { yyval = current_id; current_level++; }
#line 1724 "yacc.tab.c"
    break;

  case 38: /* struct_type_specifier: struct_or_union IDENTIFIER @3 LR @4 struct_declaration_list RR  */
#line 163 "yacc.y"
          { checkForwardReference(); yyval = setTypeField(yyvsp[-4], yyvsp[-1]); current_level--; current_id = yyvsp[-2]; }
#line 1730 "yacc.tab.c"
    break;

  case 39: /* @5: %empty  */
#line 164 "yacc.y"
                                { yyval = makeType(yyvsp[0]); }
#line 1736 "yacc.tab.c"
    break;

  case 40: /* @6: %empty  */
#line 165 "yacc.y"
              { yyval = current_id; current_level++; }
#line 1742 "yacc.tab.c"
    break;

  case 41: /* struct_type_specifier: struct_or_union @5 LR @6 struct_declaration_list RR  */
#line 167 "yacc.y"
          { checkForwardReference(); yyval = setTypeField(yyvsp[-4], yyvsp[-1]); current_level--; current_id = yyvsp[-2]; }
#line 1748 "yacc.tab.c"
    break;

  case 42: /* struct_type_specifier: struct_or_union IDENTIFIER  */
#line 168 "yacc.y"
                                        { yyval = getTypeOfStructOrEnumRefIdentifier(yyvsp[-1], yyvsp[0], ID_STRUCT); }
#line 1754 "yacc.tab.c"
    break;

  case 43: /* struct_or_union: STRUCT_SYM  */
#line 172 "yacc.y"
                        { yyval = T_STRUCT; }
#line 1760 "yacc.tab.c"
    break;

  case 44: /* struct_or_union: UNION_SYM  */
#line 173 "yacc.y"
                                { yyval = T_UNION; }
#line 1766 "yacc.tab.c"
    break;

  case 45: /* struct_declaration_list: struct_declaration  */
#line 176 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1772 "yacc.tab.c"
    break;

  case 46: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 177 "yacc.y"
                                                        { yyval = linkDeclaratorList(yyvsp[-1], yyvsp[0]); }
#line 1778 "yacc.tab.c"
    break;

  case 47: /* struct_declaration: type_specifier struct_declarator_list SEMICOLON  */
#line 184 "yacc.y"
          { yyval = setStructDeclaratorListSpecifier(yyvsp[-1], yyvsp[-2]); }
#line 1784 "yacc.tab.c"
    break;

  case 48: /* struct_declarator_list: struct_declarator  */
#line 187 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 1790 "yacc.tab.c"
    break;

  case 49: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 188 "yacc.y"
                                                                { yyval = linkDeclaratorList(yyvsp[-2], yyvsp[0]); }
#line 1796 "yacc.tab.c"
    break;

  case 50: /* struct_declarator: declarator  */
#line 191 "yacc.y"
                        { yyval = yyvsp[0]; }
#line 1802 "yacc.tab.c"
    break;

  case 51: /* @7: %empty  */
#line 197 "yacc.y"
          { yyval = setTypeStructOrEnumIdentifier(T_ENUM, yyvsp[0], ID_ENUM); }
#line 1808 "yacc.tab.c"
    break;

  case 52: /* enum_type_specifier: ENUM_SYM IDENTIFIER @7 LR enumerator_list RR  */
#line 198 "yacc.y"
                                        { yyval = setTypeField(yyvsp[-3], yyvsp[-1]); }
#line 1814 "yacc.tab.c"
    break;

  case 53: /* @8: %empty  */
#line 199 "yacc.y"
                        { yyval = makeType(T_ENUM); }
#line 1820 "yacc.tab.c"
    break;

  case 54: /* enum_type_specifier: ENUM_SYM @8 LR enumerator_list RR  */
#line 200 "yacc.y"
                                        { yyval = setTypeField(yyvsp[-3], yyvsp[-1]); }
#line 1826 "yacc.tab.c"
    break;

  case 55: /* enum_type_specifier: ENUM_SYM IDENTIFIER  */
#line 202 "yacc.y"
          { yyval = getTypeOfStructOrEnumRefIdentifier(T_ENUM, yyvsp[0], ID_ENUM); }
#line 1832 "yacc.tab.c"
    break;

  case 56: /* enumerator_list: enumerator  */
#line 205 "yacc.y"
                        { yyval = yyvsp[0]; }
#line 1838 "yacc.tab.c"
    break;

  case 57: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 206 "yacc.y"
                                                { yyval = linkDeclaratorList(yyvsp[-2], yyvsp[0]); }
#line 1844 "yacc.tab.c"
    break;

  case 58: /* enumerator: IDENTIFIER  */
#line 210 "yacc.y"
                        { yyval = setDeclaratorKind(makeIdentifier(yyvsp[0]), ID_ENUM_LITERAL); }
#line 1850 "yacc.tab.c"
    break;

  case 59: /* @9: %empty  */
#line 212 "yacc.y"
          { yyval = setDeclaratorKind(makeIdentifier(yyvsp[0]), ID_ENUM_LITERAL); }
#line 1856 "yacc.tab.c"
    break;

  case 60: /* enumerator: IDENTIFIER @9 ASSIGN constant_expression  */
#line 213 "yacc.y"
                                        { yyval = setDeclaratorInit(yyvsp[-2], yyvsp[0]); }
#line 1862 "yacc.tab.c"
    break;

  case 61: /* declarator: pointer direct_declarator  */
#line 217 "yacc.y"
                                                { yyval = setDeclaratorElementType(yyvsp[0], yyvsp[-1]); }
#line 1868 "yacc.tab.c"
    break;

  case 62: /* declarator: direct_declarator  */
#line 218 "yacc.y"
                                                        { yyval = yyvsp[0]; }
#line 1874 "yacc.tab.c"
    break;

  case 63: /* pointer: STAR  */
#line 221 "yacc.y"
                                { yyval = makeType(T_POINTER); }
#line 1880 "yacc.tab.c"
    break;

  case 64: /* pointer: STAR pointer  */
#line 222 "yacc.y"
                        { yyval = setTypeElementType(yyvsp[0], makeType(T_POINTER)); }
#line 1886 "yacc.tab.c"
    break;

  case 65: /* direct_declarator: IDENTIFIER  */
#line 226 "yacc.y"
                        { yyval = makeIdentifier(yyvsp[0]); }
#line 1892 "yacc.tab.c"
    break;

  case 66: /* direct_declarator: LP declarator RP  */
#line 227 "yacc.y"
                                { yyval = yyvsp[-1]; }
#line 1898 "yacc.tab.c"
    break;

  case 67: /* direct_declarator: direct_declarator LB constant_expression_opt RB  */
#line 230 "yacc.y"
          { yyval = setDeclaratorElementType(yyvsp[-3], setTypeExpr(makeType(T_ARRAY), yyvsp[-1])); }
#line 1904 "yacc.tab.c"
    break;

  case 68: /* @10: %empty  */
#line 232 "yacc.y"
                               { yyval = current_id; current_level++; }
#line 1910 "yacc.tab.c"
    break;

  case 69: /* direct_declarator: direct_declarator LP @10 parameter_type_list_opt RP  */
#line 236 "yacc.y"
          { checkForwardReference(); current_id = yyvsp[-2]; current_level--; 
	  	yyval = setDeclaratorElementType(yyvsp[-4], setTypeField(makeType(T_FUNC), yyvsp[-1])); }
#line 1917 "yacc.tab.c"
    break;

  case 70: /* parameter_type_list_opt: %empty  */
#line 241 "yacc.y"
                        { yyval = NIL; }
#line 1923 "yacc.tab.c"
    break;

  case 71: /* parameter_type_list_opt: parameter_type_list  */
#line 242 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1929 "yacc.tab.c"
    break;

  case 72: /* parameter_type_list: parameter_list  */
#line 245 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1935 "yacc.tab.c"
    break;

  case 73: /* parameter_type_list: parameter_list COMMA DOTDOTDOT  */
#line 248 "yacc.y"
          { yyval = linkDeclaratorList(yyvsp[-2], setDeclaratorKind(makeDummyIdentifier(), ID_PARM)); }
#line 1941 "yacc.tab.c"
    break;

  case 74: /* parameter_list: parameter_declaration  */
#line 251 "yacc.y"
                                         { yyval = yyvsp[0]; }
#line 1947 "yacc.tab.c"
    break;

  case 75: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 253 "yacc.y"
                                                        { yyval = linkDeclaratorList(yyvsp[-2], yyvsp[0]); }
#line 1953 "yacc.tab.c"
    break;

  case 76: /* parameter_declaration: declaration_specifiers declarator  */
#line 256 "yacc.y"
                                                        { yyval = setParameterDeclaratorSpecifier(yyvsp[0], yyvsp[-1]); }
#line 1959 "yacc.tab.c"
    break;

  case 77: /* parameter_declaration: declaration_specifiers abstract_declarator_opt  */
#line 259 "yacc.y"
          { yyval = setParameterDeclaratorSpecifier(setDeclaratorType(makeDummyIdentifier(), yyvsp[0]), yyvsp[-1]); }
#line 1965 "yacc.tab.c"
    break;

  case 78: /* abstract_declarator_opt: %empty  */
#line 262 "yacc.y"
                        { yyval = NIL; }
#line 1971 "yacc.tab.c"
    break;

  case 79: /* abstract_declarator_opt: abstract_declarator  */
#line 263 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 1977 "yacc.tab.c"
    break;

  case 80: /* abstract_declarator: pointer  */
#line 266 "yacc.y"
                        { yyval = makeType(T_POINTER); }
#line 1983 "yacc.tab.c"
    break;

  case 81: /* abstract_declarator: direct_abstract_declarator  */
#line 267 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 1989 "yacc.tab.c"
    break;

  case 82: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 269 "yacc.y"
                                             { yyval = setTypeElementType(yyvsp[0], makeType(T_POINTER)); }
#line 1995 "yacc.tab.c"
    break;

  case 83: /* direct_abstract_declarator: LP abstract_declarator RP  */
#line 272 "yacc.y"
                                        { yyval = yyvsp[-1]; }
#line 2001 "yacc.tab.c"
    break;

  case 84: /* direct_abstract_declarator: LB constant_expression_opt RB  */
#line 274 "yacc.y"
                                        { yyval = setTypeExpr(makeType(T_ARRAY), yyvsp[-1]); }
#line 2007 "yacc.tab.c"
    break;

  case 85: /* direct_abstract_declarator: LP parameter_type_list_opt RP  */
#line 276 "yacc.y"
                                        { yyval = setTypeExpr(makeType(T_FUNC), yyvsp[-1]); }
#line 2013 "yacc.tab.c"
    break;

  case 86: /* direct_abstract_declarator: direct_abstract_declarator LB constant_expression_opt RB  */
#line 278 "yacc.y"
          { yyval = setTypeElementType(yyvsp[-3], setTypeExpr(makeType(T_ARRAY), yyvsp[-1])); }
#line 2019 "yacc.tab.c"
    break;

  case 87: /* direct_abstract_declarator: direct_abstract_declarator LP parameter_type_list_opt RP  */
#line 281 "yacc.y"
          { yyval = setTypeElementType(yyvsp[-3], setTypeExpr(makeType(T_FUNC), yyvsp[-1])); }
#line 2025 "yacc.tab.c"
    break;

  case 88: /* statement_list_opt: %empty  */
#line 285 "yacc.y"
                        { yyval = makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL); }
#line 2031 "yacc.tab.c"
    break;

  case 89: /* statement_list_opt: statement_list  */
#line 286 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2037 "yacc.tab.c"
    break;

  case 90: /* statement_list: statement  */
#line 290 "yacc.y"
                                { yyval = makeNode(N_STMT_LIST, yyvsp[0], NIL, makeNode(N_STMT_LIST_NIL, NIL, NIL, NIL)); }
#line 2043 "yacc.tab.c"
    break;

  case 91: /* statement_list: statement_list statement  */
#line 292 "yacc.y"
                                        { yyval = makeNodeList(N_STMT_LIST, yyvsp[-1], yyvsp[0]); }
#line 2049 "yacc.tab.c"
    break;

  case 92: /* statement: labeled_statement  */
#line 295 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 2055 "yacc.tab.c"
    break;

  case 93: /* statement: compound_statement  */
#line 296 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2061 "yacc.tab.c"
    break;

  case 94: /* statement: expression_statement  */
#line 297 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2067 "yacc.tab.c"
    break;

  case 95: /* statement: selection_statement  */
#line 298 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2073 "yacc.tab.c"
    break;

  case 96: /* statement: iteration_statement  */
#line 299 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2079 "yacc.tab.c"
    break;

  case 97: /* statement: jump_statement  */
#line 300 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 2085 "yacc.tab.c"
    break;

  case 98: /* labeled_statement: CASE_SYM constant_expression COLON statement  */
#line 304 "yacc.y"
                                                        { yyval = makeNode(N_STMT_LABEL_CASE, yyvsp[-2], NIL, yyvsp[0]); }
#line 2091 "yacc.tab.c"
    break;

  case 99: /* labeled_statement: DEFAULT_SYM COLON statement  */
#line 305 "yacc.y"
                                                { yyval = makeNode(N_STMT_LABEL_DEFAULT, NIL, yyvsp[0], NIL); }
#line 2097 "yacc.tab.c"
    break;

  case 100: /* @11: %empty  */
#line 309 "yacc.y"
             { yyval = current_id; current_level++;}
#line 2103 "yacc.tab.c"
    break;

  case 101: /* compound_statement: LR @11 declaration_list_opt statement_list_opt RR  */
#line 311 "yacc.y"
          { checkForwardReference(); yyval = makeNode(N_STMT_COMPOUND, yyvsp[-2], NIL,yyvsp[-1]); current_id = yyvsp[-3]; current_level--; }
#line 2109 "yacc.tab.c"
    break;

  case 102: /* expression_statement: SEMICOLON  */
#line 315 "yacc.y"
                        { yyval = makeNode(N_STMT_EMPTY, NIL, NIL, NIL); }
#line 2115 "yacc.tab.c"
    break;

  case 103: /* expression_statement: expression SEMICOLON  */
#line 316 "yacc.y"
                                { yyval = makeNode(N_STMT_EXPRESSION, NIL, yyvsp[-1], NIL); }
#line 2121 "yacc.tab.c"
    break;

  case 104: /* selection_statement: IF_SYM LP expression RP statement  */
#line 320 "yacc.y"
                                                { yyval = makeNode(N_STMT_IF, yyvsp[-2], NIL, yyvsp[0]); }
#line 2127 "yacc.tab.c"
    break;

  case 105: /* selection_statement: IF_SYM LP expression RP statement ELSE_SYM statement  */
#line 321 "yacc.y"
                                                                { yyval = makeNode(N_STMT_IF_ELSE, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 2133 "yacc.tab.c"
    break;

  case 106: /* selection_statement: SWITCH_SYM LP expression RP statement  */
#line 322 "yacc.y"
                                                { yyval = makeNode(N_STMT_SWITCH, yyvsp[-2], NIL, yyvsp[0]); }
#line 2139 "yacc.tab.c"
    break;

  case 107: /* iteration_statement: WHILE_SYM LP expression RP statement  */
#line 326 "yacc.y"
                                                        { yyval = makeNode(N_STMT_WHILE, yyvsp[-2], NIL, yyvsp[0]); }
#line 2145 "yacc.tab.c"
    break;

  case 108: /* iteration_statement: DO_SYM statement WHILE_SYM LP expression RP SEMICOLON  */
#line 327 "yacc.y"
                                                                        { yyval = makeNode(N_STMT_DO, yyvsp[-5], NIL, yyvsp[-2]); }
#line 2151 "yacc.tab.c"
    break;

  case 109: /* iteration_statement: FOR_SYM LP for_expression RP statement  */
#line 328 "yacc.y"
                                                        { yyval = makeNode(N_STMT_FOR, yyvsp[-2], NIL, yyvsp[0]); }
#line 2157 "yacc.tab.c"
    break;

  case 110: /* for_expression: expression_opt SEMICOLON expression_opt SEMICOLON expression_opt  */
#line 332 "yacc.y"
                                                                                { yyval = makeNode(N_FOR_EXP, yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 2163 "yacc.tab.c"
    break;

  case 111: /* expression_opt: %empty  */
#line 335 "yacc.y"
                        { yyval = NIL; }
#line 2169 "yacc.tab.c"
    break;

  case 112: /* expression_opt: expression  */
#line 336 "yacc.y"
                        { yyval = yyvsp[0]; }
#line 2175 "yacc.tab.c"
    break;

  case 113: /* jump_statement: RETURN_SYM expression_opt SEMICOLON  */
#line 340 "yacc.y"
                                                { yyval = makeNode(N_STMT_RETURN, NIL, yyvsp[-1], NIL); }
#line 2181 "yacc.tab.c"
    break;

  case 114: /* jump_statement: CONTINUE_SYM SEMICOLON  */
#line 341 "yacc.y"
                                        { yyval = makeNode(N_STMT_CONTINUE, NIL, NIL, NIL); }
#line 2187 "yacc.tab.c"
    break;

  case 115: /* jump_statement: BREAK_SYM SEMICOLON  */
#line 342 "yacc.y"
                                { yyval = makeNode(N_STMT_BREAK, NIL, NIL, NIL); }
#line 2193 "yacc.tab.c"
    break;

  case 116: /* primary_expression: IDENTIFIER  */
#line 348 "yacc.y"
                        { yyval = makeNode(N_EXP_IDENT, NIL, getIdentifierDeclared(yyvsp[0]), NIL); }
#line 2199 "yacc.tab.c"
    break;

  case 117: /* primary_expression: INTEGER_CONSTANT  */
#line 349 "yacc.y"
                                { yyval = makeNode(N_EXP_INT_CONST, NIL, yyvsp[0], NIL); }
#line 2205 "yacc.tab.c"
    break;

  case 118: /* primary_expression: FLOAT_CONSTANT  */
#line 350 "yacc.y"
                                { yyval = makeNode(N_EXP_FLOAT_CONST, NIL, yyvsp[0], NIL); }
#line 2211 "yacc.tab.c"
    break;

  case 119: /* primary_expression: CHARACTER_CONSTANT  */
#line 351 "yacc.y"
                                { yyval = makeNode(N_EXP_CHAR_CONST, NIL, yyvsp[0], NIL); }
#line 2217 "yacc.tab.c"
    break;

  case 120: /* primary_expression: STRING_LITERAL  */
#line 352 "yacc.y"
                                { yyval = makeNode(N_EXP_STRING_LITERAL, NIL, yyvsp[0], NIL); }
#line 2223 "yacc.tab.c"
    break;

  case 121: /* primary_expression: LP expression RP  */
#line 353 "yacc.y"
                                { yyval= yyvsp[-1]; }
#line 2229 "yacc.tab.c"
    break;

  case 122: /* postfix_expression: primary_expression  */
#line 358 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2235 "yacc.tab.c"
    break;

  case 123: /* postfix_expression: postfix_expression LB expression RB  */
#line 359 "yacc.y"
                                                { yyval = makeNode(N_EXP_ARRAY, yyvsp[-3], NIL, yyvsp[-1]); }
#line 2241 "yacc.tab.c"
    break;

  case 124: /* postfix_expression: postfix_expression LP arg_expression_list_opt RP  */
#line 360 "yacc.y"
                                                                { yyval = makeNode(N_EXP_FUNCTION_CALL, yyvsp[-3], NIL, yyvsp[-1]); }
#line 2247 "yacc.tab.c"
    break;

  case 125: /* postfix_expression: postfix_expression PERIOD IDENTIFIER  */
#line 361 "yacc.y"
                                                { yyval = makeNode(N_EXP_STRUCT, yyvsp[-2], NIL, yyvsp[0]); }
#line 2253 "yacc.tab.c"
    break;

  case 126: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 362 "yacc.y"
                                                { yyval = makeNode(N_EXP_ARROW, yyvsp[-2], NIL, yyvsp[0]); }
#line 2259 "yacc.tab.c"
    break;

  case 127: /* postfix_expression: postfix_expression PLUSPLUS  */
#line 363 "yacc.y"
                                                        { yyval = makeNode(N_EXP_POST_INC, NIL, yyvsp[-1], NIL); }
#line 2265 "yacc.tab.c"
    break;

  case 128: /* postfix_expression: postfix_expression MINUSMINUS  */
#line 364 "yacc.y"
                                                        { yyval = makeNode(N_EXP_POST_DEC, NIL, yyvsp[-1], NIL); }
#line 2271 "yacc.tab.c"
    break;

  case 129: /* arg_expression_list_opt: %empty  */
#line 368 "yacc.y"
                        { yyval = NIL; }
#line 2277 "yacc.tab.c"
    break;

  case 130: /* arg_expression_list_opt: arg_expression_list  */
#line 369 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2283 "yacc.tab.c"
    break;

  case 131: /* arg_expression_list: assignment_expression  */
#line 372 "yacc.y"
                                { yyval = makeNode(N_ARG_LIST, yyvsp[0], NIL, makeNode(N_ARG_LIST_NIL, NIL, NIL, NIL)); }
#line 2289 "yacc.tab.c"
    break;

  case 132: /* arg_expression_list: arg_expression_list COMMA assignment_expression  */
#line 373 "yacc.y"
                                                                { yyval = makeNodeList(N_ARG_LIST, yyvsp[-2], yyvsp[0]); }
#line 2295 "yacc.tab.c"
    break;

  case 133: /* unary_expression: postfix_expression  */
#line 378 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2301 "yacc.tab.c"
    break;

  case 134: /* unary_expression: PLUSPLUS unary_expression  */
#line 379 "yacc.y"
                                                { yyval = makeNode(N_EXP_PRE_INC, NIL, yyvsp[0], NIL); }
#line 2307 "yacc.tab.c"
    break;

  case 135: /* unary_expression: MINUSMINUS unary_expression  */
#line 380 "yacc.y"
                                        { yyval = makeNode(N_EXP_PRE_DEC, NIL, yyvsp[0], NIL); }
#line 2313 "yacc.tab.c"
    break;

  case 136: /* unary_expression: AMP cast_expression  */
#line 381 "yacc.y"
                                                { yyval = makeNode(N_EXP_AMP, NIL, yyvsp[0], NIL); }
#line 2319 "yacc.tab.c"
    break;

  case 137: /* unary_expression: STAR cast_expression  */
#line 382 "yacc.y"
                                                { yyval = makeNode(N_EXP_STAR, NIL, yyvsp[0], NIL); }
#line 2325 "yacc.tab.c"
    break;

  case 138: /* unary_expression: EXCL cast_expression  */
#line 383 "yacc.y"
                                                { yyval = makeNode(N_EXP_NOT, NIL, yyvsp[0], NIL); }
#line 2331 "yacc.tab.c"
    break;

  case 139: /* unary_expression: MINUS cast_expression  */
#line 384 "yacc.y"
                                                { yyval = makeNode(N_EXP_MINUS, NIL, yyvsp[0], NIL); }
#line 2337 "yacc.tab.c"
    break;

  case 140: /* unary_expression: PLUS cast_expression  */
#line 385 "yacc.y"
                                                { yyval = makeNode(N_EXP_PLUS, NIL, yyvsp[0], NIL); }
#line 2343 "yacc.tab.c"
    break;

  case 141: /* unary_expression: SIZEOF_SYM unary_expression  */
#line 386 "yacc.y"
                                        { yyval = makeNode(N_EXP_SIZE_EXP, NIL, yyvsp[0], NIL); }
#line 2349 "yacc.tab.c"
    break;

  case 142: /* unary_expression: SIZEOF_SYM LP type_name RP  */
#line 387 "yacc.y"
                                        { yyval = makeNode(N_EXP_SIZE_TYPE, NIL, yyvsp[-2], NIL); }
#line 2355 "yacc.tab.c"
    break;

  case 143: /* cast_expression: unary_expression  */
#line 390 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2361 "yacc.tab.c"
    break;

  case 144: /* cast_expression: LP type_name RP cast_expression  */
#line 391 "yacc.y"
                                                { yyval = makeNode(N_EXP_CAST, yyvsp[-2], NIL, yyvsp[0]); }
#line 2367 "yacc.tab.c"
    break;

  case 145: /* type_name: declaration_specifiers abstract_declarator_opt  */
#line 396 "yacc.y"
                                                                { yyval = setTypeNameSpecifier(yyvsp[0], yyvsp[-1]); }
#line 2373 "yacc.tab.c"
    break;

  case 146: /* multiplicative_expression: cast_expression  */
#line 401 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2379 "yacc.tab.c"
    break;

  case 147: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 402 "yacc.y"
                                                                { yyval = makeNode(N_EXP_MUL, yyvsp[-2], NIL, yyvsp[0]); }
#line 2385 "yacc.tab.c"
    break;

  case 148: /* multiplicative_expression: multiplicative_expression SLASH cast_expression  */
#line 403 "yacc.y"
                                                                { yyval = makeNode(N_EXP_DIV, yyvsp[-2], NIL, yyvsp[0]); }
#line 2391 "yacc.tab.c"
    break;

  case 149: /* multiplicative_expression: multiplicative_expression PERCENT cast_expression  */
#line 404 "yacc.y"
                                                                { yyval = makeNode(N_EXP_MOD, yyvsp[-2], NIL, yyvsp[0]); }
#line 2397 "yacc.tab.c"
    break;

  case 150: /* additive_expression: multiplicative_expression  */
#line 408 "yacc.y"
                                                { yyval = yyvsp[0]; }
#line 2403 "yacc.tab.c"
    break;

  case 151: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 409 "yacc.y"
                                                                { yyval = makeNode(N_EXP_ADD, yyvsp[-2], NIL, yyvsp[0]); }
#line 2409 "yacc.tab.c"
    break;

  case 152: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 410 "yacc.y"
                                                                { yyval = makeNode(N_EXP_SUB, yyvsp[-2], NIL, yyvsp[0]); }
#line 2415 "yacc.tab.c"
    break;

  case 153: /* relational_expression: additive_expression  */
#line 414 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2421 "yacc.tab.c"
    break;

  case 154: /* relational_expression: relational_expression LSS additive_expression  */
#line 415 "yacc.y"
                                                        { yyval = makeNode(N_EXP_LSS, yyvsp[-2], NIL, yyvsp[0]); }
#line 2427 "yacc.tab.c"
    break;

  case 155: /* relational_expression: relational_expression GTR additive_expression  */
#line 416 "yacc.y"
                                                        { yyval = makeNode(N_EXP_GTR, yyvsp[-2], NIL, yyvsp[0]); }
#line 2433 "yacc.tab.c"
    break;

  case 156: /* relational_expression: relational_expression LEQ additive_expression  */
#line 417 "yacc.y"
                                                        { yyval = makeNode(N_EXP_LEQ, yyvsp[-2], NIL, yyvsp[0]); }
#line 2439 "yacc.tab.c"
    break;

  case 157: /* relational_expression: relational_expression GEQ additive_expression  */
#line 418 "yacc.y"
                                                        { yyval = makeNode(N_EXP_GEQ, yyvsp[-2], NIL, yyvsp[0]); }
#line 2445 "yacc.tab.c"
    break;

  case 158: /* equality_expression: relational_expression  */
#line 422 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2451 "yacc.tab.c"
    break;

  case 159: /* equality_expression: equality_expression EQL relational_expression  */
#line 423 "yacc.y"
                                                        { yyval = makeNode(N_EXP_EQL, yyvsp[-2], NIL, yyvsp[0]); }
#line 2457 "yacc.tab.c"
    break;

  case 160: /* equality_expression: equality_expression NEQ relational_expression  */
#line 424 "yacc.y"
                                                        { yyval = makeNode(N_EXP_NEQ, yyvsp[-2], NIL, yyvsp[0]); }
#line 2463 "yacc.tab.c"
    break;

  case 161: /* logical_and_expression: equality_expression  */
#line 428 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2469 "yacc.tab.c"
    break;

  case 162: /* logical_and_expression: logical_and_expression AMPAMP equality_expression  */
#line 429 "yacc.y"
                                                                { yyval = makeNode(N_EXP_AND, yyvsp[-2], NIL, yyvsp[0]); }
#line 2475 "yacc.tab.c"
    break;

  case 163: /* logical_or_expression: logical_and_expression  */
#line 433 "yacc.y"
                                        { yyval = yyvsp[0]; }
#line 2481 "yacc.tab.c"
    break;

  case 164: /* logical_or_expression: logical_or_expression BARBAR logical_and_expression  */
#line 434 "yacc.y"
                                                                { yyval = makeNode(N_EXP_OR, yyvsp[-2], NIL, yyvsp[0]); }
#line 2487 "yacc.tab.c"
    break;

  case 165: /* assignment_expression: logical_or_expression  */
#line 439 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2493 "yacc.tab.c"
    break;

  case 166: /* assignment_expression: unary_expression ASSIGN assignment_expression  */
#line 440 "yacc.y"
                                                        { yyval = makeNode(N_EXP_ASSIGN, yyvsp[-2], NIL, yyvsp[0]); }
#line 2499 "yacc.tab.c"
    break;

  case 167: /* constant_expression_opt: %empty  */
#line 443 "yacc.y"
                        { yyval = NIL; }
#line 2505 "yacc.tab.c"
    break;

  case 168: /* constant_expression_opt: constant_expression  */
#line 444 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2511 "yacc.tab.c"
    break;

  case 169: /* constant_expression: expression  */
#line 447 "yacc.y"
                        { yyval = yyvsp[0]; }
#line 2517 "yacc.tab.c"
    break;

  case 170: /* expression: assignment_expression  */
#line 450 "yacc.y"
                                { yyval = yyvsp[0]; }
#line 2523 "yacc.tab.c"
    break;


#line 2527 "yacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 453 "yacc.y"



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
