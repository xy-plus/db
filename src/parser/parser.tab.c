/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 ".\\parser.y"

#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#include <cstdio>
#define __STRICT_ANSI__
#else
#include <cstdio>
#endif

#include <stdlib.h>
#include <string>
#include "../global.h"
#include "tree.h"

int yylex();
void yyerror(const char *);

class Tree;

/* Line 371 of yacc.c  */
#line 88 "parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SELECT = 258,
     DELETE = 259,
     UPDATE = 260,
     INSERT = 261,
     CREATE = 262,
     DROP = 263,
     USE = 264,
     SHOW = 265,
     TABLES = 266,
     DATABASE = 267,
     TABLE = 268,
     STAR = 269,
     FROM = 270,
     WHERE = 271,
     OPERATOR = 272,
     VALUES = 273,
     SET = 274,
     INTO = 275,
     DATABASES = 276,
     DEFAULT = 277,
     CONSTRAINT = 278,
     CHANGE = 279,
     ALTER = 280,
     ADD = 281,
     RENAME = 282,
     REFERENCES = 283,
     FOREIGN = 284,
     ON = 285,
     TO = 286,
     FORCE = 287,
     KINT = 288,
     KFLOAT = 289,
     KVARCHAR = 290,
     KDATE = 291,
     INTEGER = 292,
     FLOAT = 293,
     STRING = 294,
     IDENTIFIER = 295,
     DATE = 296,
     EQ = 297,
     GT = 298,
     LT = 299,
     GE = 300,
     LE = 301,
     NE = 302,
     NOTNULL = 303,
     PRIMARY = 304,
     DESC = 305,
     INDEX = 306,
     T_NULL = 307,
     IS = 308,
     AND = 309
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 21 ".\\parser.y"

    int ivalue;
    float fvalue;
    char *string;
    Tree *tree;
    SelectTree *selectTree;
    DeleteTree *deleteTree;
    AttributesTree *attributesTree;
    AttributeTree *attributeTree;
    RelationsTree *relationsTree;
    WhereClauseTree *whereClauseTree;
    ConditionsTree *conditionsTree;
    ComparisonTree *comparisonTree;
    ConstValuesTree *constValuesTree;
    ConstValueTree *constValueTree;
    ColumnsTree *columnsTree;
    ColumnTree *columnTree;
    InsertValueTree *insertValueTree;
    TypeTree *typeTree;
    SetClauseTree *setClauseTree;
    OperatorTree *operatorTree;
    PrimarySetTree *primarySetTree;
    AddPrimaryTree *addPrimaryTree;
    DropPrimaryTree *dropPrimaryTree;
    ForeignSetTree *foreignSetTree;
    AddForeignTree *addForeignTree;
    RenameTree *renameTree;


/* Line 387 of yacc.c  */
#line 212 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 240 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  212

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      56,    57,     2,     2,    58,     2,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      25,    28,    32,    36,    39,    42,    49,    53,    56,    62,
      71,    78,    88,    93,    99,   105,   111,   120,   126,   136,
     143,   149,   155,   162,   169,   175,   186,   193,   209,   216,
     218,   222,   225,   229,   234,   240,   245,   256,   258,   263,
     268,   270,   272,   276,   282,   284,   288,   290,   292,   294,
     296,   298,   302,   306,   310,   314,   317,   318,   320,   324,
     328,   330,   332,   334,   336,   338,   340,   342,   346,   352,
     354,   358,   360,   364,   366,   370,   372,   374,   376,   378,
     380
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    -1,    61,    62,    -1,    63,    55,
      -1,    64,    55,    -1,    65,    55,    -1,    66,    55,    -1,
      67,    55,    -1,    55,    -1,    10,    21,    -1,     7,    12,
      83,    -1,     8,    12,    83,    -1,     9,    83,    -1,    10,
      11,    -1,     7,    13,    84,    56,    68,    57,    -1,     8,
      13,    84,    -1,    50,    84,    -1,     6,    20,    84,    18,
      71,    -1,     6,    20,    84,    56,    82,    57,    18,    71,
      -1,     6,    20,    84,    18,    71,    32,    -1,     6,    20,
      84,    56,    82,    57,    18,    71,    32,    -1,     4,    15,
      84,    75,    -1,     5,    84,    19,    79,    75,    -1,     3,
      14,    15,    81,    75,    -1,     3,    80,    15,    81,    75,
      -1,     7,    51,    87,    30,    84,    56,    82,    57,    -1,
       8,    51,    87,    30,    84,    -1,    25,    13,    84,    26,
      51,    87,    56,    82,    57,    -1,    25,    13,    84,     8,
      51,    87,    -1,    25,    13,    84,    26,    69,    -1,    25,
      13,    84,     8,    88,    -1,    25,    13,    84,    24,    88,
      69,    -1,    25,    13,    84,    27,    31,    84,    -1,    25,
      13,    84,     8,    49,    -1,    25,    13,    84,    26,    23,
      86,    49,    56,    82,    57,    -1,    25,    13,    84,     8,
      49,    86,    -1,    25,    13,    84,    26,    23,    85,    29,
      56,    82,    57,    28,    84,    56,    82,    57,    -1,    25,
      13,    84,     8,    29,    85,    -1,    69,    -1,    68,    58,
      69,    -1,    88,    70,    -1,    88,    70,    48,    -1,    88,
      70,    22,    73,    -1,    88,    70,    48,    22,    73,    -1,
      49,    56,    82,    57,    -1,    29,    85,    56,    82,    57,
      28,    84,    56,    82,    57,    -1,    33,    -1,    33,    56,
      37,    57,    -1,    35,    56,    37,    57,    -1,    36,    -1,
      34,    -1,    56,    72,    57,    -1,    71,    58,    56,    72,
      57,    -1,    73,    -1,    72,    58,    73,    -1,    37,    -1,
      39,    -1,    38,    -1,    41,    -1,    52,    -1,    77,    78,
      77,    -1,    77,    78,    73,    -1,    77,    53,    52,    -1,
      77,    53,    48,    -1,    16,    76,    -1,    -1,    74,    -1,
      76,    54,    74,    -1,    84,    59,    88,    -1,    88,    -1,
      42,    -1,    47,    -1,    43,    -1,    44,    -1,    45,    -1,
      46,    -1,    88,    42,    73,    -1,    79,    58,    88,    42,
      73,    -1,    77,    -1,    80,    58,    77,    -1,    84,    -1,
      81,    58,    84,    -1,    88,    -1,    82,    58,    88,    -1,
      40,    -1,    40,    -1,    40,    -1,    40,    -1,    40,    -1,
      40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,    97,   102,   104,   106,   108,   110,   112,
     117,   126,   133,   140,   147,   156,   163,   170,   177,   184,
     191,   198,   205,   212,   220,   226,   235,   243,   251,   259,
     270,   277,   285,   293,   301,   308,   315,   322,   329,   339,
     344,   351,   357,   363,   369,   375,   380,   387,   391,   395,
     399,   403,   410,   414,   421,   426,   437,   441,   446,   450,
     455,   463,   467,   471,   475,   483,   488,   494,   499,   506,
     512,   520,   524,   528,   532,   536,   540,   547,   552,   559,
     564,   571,   577,   589,   594,   601,   606,   611,   616,   621,
     626
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "DELETE", "UPDATE", "INSERT",
  "CREATE", "DROP", "USE", "SHOW", "TABLES", "DATABASE", "TABLE", "STAR",
  "FROM", "WHERE", "OPERATOR", "VALUES", "SET", "INTO", "DATABASES",
  "DEFAULT", "CONSTRAINT", "CHANGE", "ALTER", "ADD", "RENAME",
  "REFERENCES", "FOREIGN", "ON", "TO", "FORCE", "KINT", "KFLOAT",
  "KVARCHAR", "KDATE", "INTEGER", "FLOAT", "STRING", "IDENTIFIER", "DATE",
  "EQ", "GT", "LT", "GE", "LE", "NE", "NOTNULL", "PRIMARY", "DESC",
  "INDEX", "T_NULL", "IS", "AND", "';'", "'('", "')'", "','", "'.'",
  "$accept", "program", "stmt", "sysStmt", "dbStmt", "tbStmt", "idxStmt",
  "alterStmt", "fieldList", "field", "type", "valueLists", "valueList",
  "value", "comparisonClause", "whereClause", "conditions", "col", "op",
  "setClause", "colList", "tableList", "columnList", "dbName", "tbName",
  "fkName", "pkName", "idxName", "colName", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    59,    40,    41,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      63,    64,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    69,    69,    69,    69,    70,    70,    70,
      70,    70,    71,    71,    72,    72,    73,    73,    73,    73,
      73,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    83,    84,    85,    86,    87,
      88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     1,
       2,     3,     3,     2,     2,     6,     3,     2,     5,     8,
       6,     9,     4,     5,     5,     5,     8,     5,     9,     6,
       5,     5,     6,     6,     5,    10,     6,    15,     6,     1,
       3,     2,     3,     4,     5,     4,    10,     1,     4,     4,
       1,     1,     3,     5,     1,     3,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     2,     0,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,     0,     2,     0,     0,     0,     0,     0,     0,
      90,    79,     0,     0,    70,     0,    86,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    13,    14,    10,     0,
      17,     1,     3,     4,     5,     6,     7,     8,     0,     0,
       0,     0,    66,     0,     0,    11,     0,    89,     0,    12,
      16,     0,     0,    66,    81,    66,    80,    90,    69,     0,
      22,    66,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,    25,    67,    65,     0,     0,    23,
       0,     0,    18,     0,    83,     0,     0,     0,    39,     0,
       0,    27,     0,    34,     0,    31,     0,     0,     0,    30,
       0,    82,     0,    71,    73,    74,    75,    76,    72,     0,
       0,     0,    56,    58,    57,    59,    60,    77,     0,    54,
      20,     0,     0,     0,    87,     0,     0,    15,     0,    47,
      51,     0,    50,    41,     0,    38,    88,    36,    29,    32,
      87,     0,     0,     0,    33,    68,    64,    63,    62,    61,
       0,    52,     0,     0,     0,    84,     0,     0,    40,     0,
       0,     0,    42,     0,     0,     0,     0,    78,    55,     0,
      19,     0,    45,     0,     0,    43,     0,    26,     0,     0,
       0,    53,    21,     0,    48,    49,    44,     0,     0,    28,
       0,     0,    35,     0,     0,     0,     0,     0,     0,    46,
       0,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    97,    98,
     143,    92,   128,   129,    85,    70,    86,    87,   120,    71,
      22,    63,    93,    36,    23,   135,   147,    58,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -79
static const yytype_int16 yypact[] =
{
     149,    -6,    14,    -5,    42,    -2,     3,    30,    12,    73,
      -5,   -79,    96,   -79,    37,    57,    64,    68,    74,    78,
     106,   -79,   -11,   117,   -79,    -5,   -79,   119,    -5,    30,
      -5,   105,    30,    -5,   105,   -79,   -79,   -79,   -79,    -5,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,    -5,    -5,
     140,   141,   168,   141,     1,   -79,   129,   -79,   156,   -79,
     -79,   157,    89,   -10,   -79,   -10,   -79,   -79,   -79,   140,
     -79,    -7,   146,   133,   141,    35,    -5,    -5,   -12,   141,
      38,   159,    -5,   -79,   -79,   -79,   137,   124,   141,   -79,
      87,    87,   -20,   -37,   -79,   152,   138,   -16,   -79,    98,
     139,   -79,   152,   153,   105,   -79,    35,   158,   105,   -79,
      -5,   -79,   140,   -79,   -79,   -79,   -79,   -79,   -79,    43,
     123,   154,   -79,   -79,   -79,   -79,   -79,   -79,    11,   -79,
     -79,   144,   184,   141,   -79,   147,   141,   -79,    35,   150,
     -79,   151,   -79,    -8,   141,   -79,   -79,   -79,   -79,   -79,
     160,   176,   161,   155,   -79,   -79,   -79,   -79,   -79,   -79,
      87,   -79,    87,    87,   133,   -79,   141,    60,   -79,   171,
     175,    87,   191,    79,   162,   163,   141,   -79,   -79,    84,
     -14,    86,   -79,   164,   165,   -79,    87,   -79,   141,   141,
      90,   -79,   -79,   186,   -79,   -79,   -79,    92,   115,   -79,
      -5,   187,   -79,   167,    -5,   141,   169,   121,   141,   -79,
     125,   -79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   204,   -79,   -79,   -79,   -79,   -79,   -79,   -75,
     -79,    53,    61,   -77,   108,   -39,   -79,     0,   -79,   -79,
     -79,   177,   -78,    27,    -3,   -42,   120,   -32,     2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -89
static const yytype_int16 yytable[] =
{
      27,    21,    61,    24,    49,   109,    69,    40,    19,    69,
      29,    30,   130,   127,   171,    32,    33,   102,   192,    73,
     132,   133,    52,    37,    83,    54,    84,    56,    67,    25,
      60,   149,    89,    38,    20,    26,    62,   103,   131,   104,
     172,   137,   138,   158,   131,    64,    64,    50,    82,    31,
      66,    88,    24,    68,    34,    72,    55,    74,   167,    59,
     145,   107,    28,   168,    95,   151,   173,    95,   161,   162,
      35,    24,   148,   100,   101,    67,   153,    99,    67,   111,
     105,   106,    99,   177,    96,   178,    39,    96,   181,   108,
     121,   156,    43,    48,   185,   157,    41,    78,   190,     1,
       2,     3,     4,     5,     6,     7,     8,   154,    99,   196,
     197,   198,    44,    79,    24,    80,    81,   182,   133,    45,
     159,     9,    24,    46,   122,   123,   124,   207,   125,    47,
     210,   139,   140,   141,   142,   165,   187,   133,    53,   126,
      99,   191,   162,   193,   133,    57,    10,   199,   133,   201,
     133,    11,     1,     2,     3,     4,     5,     6,     7,     8,
     122,   123,   124,    20,   125,   -86,   113,   114,   115,   116,
     117,   118,   202,   133,     9,   126,    51,   119,   209,   133,
      20,    67,   211,   133,    69,    75,    76,    77,    90,    91,
     110,   112,   134,   146,   136,   144,   160,   203,   150,    10,
     163,   206,   164,   166,    11,   174,   169,   170,   183,   -88,
     175,   176,   184,   186,   200,   204,    42,   180,   188,   189,
     155,   194,   195,   205,   179,   208,    65,   152
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       3,     1,    34,     1,    15,    80,    16,    10,    14,    16,
      12,    13,    32,    90,    22,    12,    13,    29,    32,    18,
      57,    58,    25,    11,    63,    28,    65,    30,    40,    15,
      33,   106,    71,    21,    40,    40,    39,    49,    58,    51,
      48,    57,    58,   120,    58,    48,    49,    58,    58,    51,
      50,    58,    50,    51,    51,    53,    29,    56,   136,    32,
     102,    23,    20,   138,    29,   107,   144,    29,    57,    58,
      40,    69,   104,    76,    77,    40,   108,    75,    40,    82,
      78,    79,    80,   160,    49,   162,    13,    49,   166,    51,
      88,    48,    55,    15,   171,    52,     0,     8,   176,     3,
       4,     5,     6,     7,     8,     9,    10,   110,   106,   186,
     188,   189,    55,    24,   112,    26,    27,    57,    58,    55,
     120,    25,   120,    55,    37,    38,    39,   205,    41,    55,
     208,    33,    34,    35,    36,   133,    57,    58,    19,    52,
     138,    57,    58,    57,    58,    40,    50,    57,    58,    57,
      58,    55,     3,     4,     5,     6,     7,     8,     9,    10,
      37,    38,    39,    40,    41,    59,    42,    43,    44,    45,
      46,    47,    57,    58,    25,    52,    59,    53,    57,    58,
      40,    40,    57,    58,    16,    56,    30,    30,    42,    56,
      31,    54,    40,    40,    56,    56,    42,   200,    40,    50,
      56,   204,    18,    56,    55,    29,    56,    56,    37,    49,
      49,    56,    37,    22,    28,    28,    12,   164,    56,    56,
     112,    57,    57,    56,   163,    56,    49,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    25,
      50,    55,    61,    62,    63,    64,    65,    66,    67,    14,
      40,    77,    80,    84,    88,    15,    40,    84,    20,    12,
      13,    51,    12,    13,    51,    40,    83,    11,    21,    13,
      84,     0,    62,    55,    55,    55,    55,    55,    15,    15,
      58,    59,    84,    19,    84,    83,    84,    40,    87,    83,
      84,    87,    84,    81,    84,    81,    77,    40,    88,    16,
      75,    79,    88,    18,    56,    56,    30,    30,     8,    24,
      26,    27,    58,    75,    75,    74,    76,    77,    58,    75,
      42,    56,    71,    82,    88,    29,    49,    68,    69,    88,
      84,    84,    29,    49,    51,    88,    88,    23,    51,    69,
      31,    84,    54,    42,    43,    44,    45,    46,    47,    53,
      78,    88,    37,    38,    39,    41,    52,    73,    72,    73,
      32,    58,    57,    58,    40,    85,    56,    57,    58,    33,
      34,    35,    36,    70,    56,    85,    40,    86,    87,    69,
      40,    85,    86,    87,    84,    74,    48,    52,    73,    77,
      42,    57,    58,    56,    18,    88,    56,    82,    69,    56,
      56,    22,    48,    82,    29,    49,    56,    73,    73,    72,
      71,    82,    57,    37,    37,    73,    22,    57,    56,    56,
      82,    57,    32,    57,    57,    57,    73,    82,    82,    57,
      28,    57,    57,    84,    28,    56,    84,    82,    56,    57,
      82,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 96 ".\\parser.y"
    { }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 98 ".\\parser.y"
    { }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 103 ".\\parser.y"
    { }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 105 ".\\parser.y"
    { }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 107 ".\\parser.y"
    { }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 109 ".\\parser.y"
    { }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 111 ".\\parser.y"
    { }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 113 ".\\parser.y"
    { }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 118 ".\\parser.y"
    {
            (yyval.tree) = new ShowDatabaseTree();
            Tree::setInstance((yyval.tree));
            Tree::run();
        }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 127 ".\\parser.y"
    {
            (yyval.tree) = new CreateDatabaseTree((yyvsp[(3) - (3)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (3)].string);
            Tree::run();
        }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 134 ".\\parser.y"
    {
            (yyval.tree) = new DropDatabaseTree((yyvsp[(3) - (3)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (3)].string);
            Tree::run();
        }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 141 ".\\parser.y"
    {
            (yyval.tree) = new UseDatabaseTree((yyvsp[(2) - (2)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(2) - (2)].string);
            Tree::run();
        }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 148 ".\\parser.y"
    {
            (yyval.tree) = new DescTableTree("");
            Tree::setInstance((yyval.tree));
            Tree::run();
        }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 157 ".\\parser.y"
    {
            (yyval.tree) = new CreateTableTree((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].columnsTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            Tree::run();
        }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 164 ".\\parser.y"
    {
            (yyval.tree) = new DropTableTree((yyvsp[(3) - (3)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (3)].string);
            Tree::run();
        }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 171 ".\\parser.y"
    {
            (yyval.tree) = new DescTableTree((yyvsp[(2) - (2)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(2) - (2)].string);
            Tree::run();
        }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 178 ".\\parser.y"
    {
            (yyval.tree) = new InsertTree((yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].insertValueTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (5)].string);
            Tree::run();
        }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 185 ".\\parser.y"
    {
            (yyval.tree) = new InsertTree((yyvsp[(3) - (8)].string), (yyvsp[(5) - (8)].attributesTree), (yyvsp[(8) - (8)].insertValueTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (8)].string);
            Tree::run();
        }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 192 ".\\parser.y"
    {
            (yyval.tree) = new InsertTree((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].insertValueTree), true);
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            Tree::run();
        }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 199 ".\\parser.y"
    {
            (yyval.tree) = new InsertTree((yyvsp[(3) - (9)].string), (yyvsp[(5) - (9)].attributesTree), (yyvsp[(8) - (9)].insertValueTree), true);
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (9)].string);
            Tree::run();
        }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 206 ".\\parser.y"
    {
            (yyval.tree) = new DeleteTree((yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].whereClauseTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (4)].string);
            Tree::run();
        }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 213 ".\\parser.y"
    {
            // 这里不考虑WhereClause，因为update加上whereclause后就不能逐列修改了
            (yyval.tree) = new UpdateTree(std::string((yyvsp[(2) - (5)].string)), (yyvsp[(4) - (5)].setClauseTree), (yyvsp[(5) - (5)].whereClauseTree)); 
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(2) - (5)].string);
            Tree::run();
        }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 221 ".\\parser.y"
    {
            (yyval.tree) = new SelectTree((yyvsp[(4) - (5)].relationsTree), (yyvsp[(5) - (5)].whereClauseTree));
            Tree::setInstance((yyval.tree));
            Tree::run();
        }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 227 ".\\parser.y"
    {
            (yyval.tree) = new SelectTree((yyvsp[(2) - (5)].attributesTree), (yyvsp[(4) - (5)].relationsTree), (yyvsp[(5) - (5)].whereClauseTree));
            Tree::setInstance((yyval.tree));
            Tree::run();
        }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 236 ".\\parser.y"
    {
            (yyval.tree) = new CreateIndexTree((yyvsp[(3) - (8)].string), (yyvsp[(5) - (8)].string), (yyvsp[(7) - (8)].attributesTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (8)].string);
            delete (yyvsp[(5) - (8)].string);
            Tree::run();
        }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 244 ".\\parser.y"
    {
            (yyval.tree) = new DropIndexTree((yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (5)].string);
            delete (yyvsp[(5) - (5)].string);
            Tree::run();
        }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 252 ".\\parser.y"
    {
            (yyval.tree) = new CreateIndexTree((yyvsp[(6) - (9)].string), (yyvsp[(3) - (9)].string), (yyvsp[(8) - (9)].attributesTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (9)].string);
            delete (yyvsp[(6) - (9)].string);
            Tree::run();
        }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 260 ".\\parser.y"
    {
            (yyval.tree) = new DropIndexTree((yyvsp[(6) - (6)].string), (yyvsp[(3) - (6)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            delete (yyvsp[(6) - (6)].string);
            Tree::run();
        }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 271 ".\\parser.y"
    {
            (yyval.tree) = new AddAttrTree((yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].columnTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (5)].string);
            Tree::run();
        }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 278 ".\\parser.y"
    {
            (yyval.tree) = new DropAttrTree((yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (5)].string);
            delete (yyvsp[(5) - (5)].string);
            Tree::run();
        }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 286 ".\\parser.y"
    {
            (yyval.tree) = new AlterAttrTree((yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].string), (yyvsp[(6) - (6)].columnTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            delete (yyvsp[(5) - (6)].string);
            Tree::run();
        }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 294 ".\\parser.y"
    {
            (yyval.tree) = new RenameTree((yyvsp[(3) - (6)].string), (yyvsp[(6) - (6)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            delete (yyvsp[(6) - (6)].string);
            Tree::run();
        }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 302 ".\\parser.y"
    {
            (yyval.tree) = new DropPrimaryTree((yyvsp[(3) - (5)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (5)].string);
            Tree::run();
        }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 309 ".\\parser.y"
    {
            (yyval.tree) = new AddPrimaryTree((yyvsp[(3) - (10)].string), (yyvsp[(9) - (10)].attributesTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (10)].string);
            Tree::run();
        }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 316 ".\\parser.y"
    {
            (yyval.tree) = new DropPrimaryTree((yyvsp[(3) - (6)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            Tree::run();
        }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 323 ".\\parser.y"
    {
            (yyval.tree) = new AddForeignTree((yyvsp[(6) - (15)].string), (yyvsp[(3) - (15)].string), (yyvsp[(12) - (15)].string), (yyvsp[(9) - (15)].attributesTree), (yyvsp[(14) - (15)].attributesTree));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (15)].string);
            Tree::run();
        }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 330 ".\\parser.y"
    {
            (yyval.tree) = new DropForeignTree((yyvsp[(3) - (6)].string), (yyvsp[(6) - (6)].string));
            Tree::setInstance((yyval.tree));
            delete (yyvsp[(3) - (6)].string);
            Tree::run();
        }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 340 ".\\parser.y"
    {
            (yyval.columnsTree) = new ColumnsTree();
            (yyval.columnsTree)->addColumn((yyvsp[(1) - (1)].columnTree));
        }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 345 ".\\parser.y"
    {
            (yyval.columnsTree)->addColumn((yyvsp[(3) - (3)].columnTree));
        }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 352 ".\\parser.y"
    {
            (yyval.columnTree) = new ColumnTree((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].typeTree)->getType(), (yyvsp[(2) - (2)].typeTree)->getLen());
            delete (yyvsp[(1) - (2)].string);
            delete (yyvsp[(2) - (2)].typeTree);
        }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 358 ".\\parser.y"
    {
            (yyval.columnTree) = new ColumnTree((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].typeTree)->getType(), (yyvsp[(2) - (3)].typeTree)->getLen(), 1);
            delete (yyvsp[(1) - (3)].string);
            delete (yyvsp[(2) - (3)].typeTree);
        }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 364 ".\\parser.y"
    {
            (yyval.columnTree) = new ColumnTree((yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].typeTree)->getType(), (yyvsp[(2) - (4)].typeTree)->getLen(), 0, (yyvsp[(4) - (4)].constValueTree));
            delete (yyvsp[(1) - (4)].string);
            delete (yyvsp[(2) - (4)].typeTree);
        }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 370 ".\\parser.y"
    {
            (yyval.columnTree) = new ColumnTree((yyvsp[(1) - (5)].string), (yyvsp[(2) - (5)].typeTree)->getType(), (yyvsp[(2) - (5)].typeTree)->getLen(), 1, (yyvsp[(5) - (5)].constValueTree));
            delete (yyvsp[(1) - (5)].string);
            delete (yyvsp[(2) - (5)].typeTree);
        }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 376 ".\\parser.y"
    {
            // 这里检查columnList里出现的所有名称是否在fieldList里出现过
            (yyval.columnTree) = new PrimarySetTree((yyvsp[(3) - (4)].attributesTree));
        }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 381 ".\\parser.y"
    {
            (yyval.columnTree) = new ForeignSetTree((yyvsp[(2) - (10)].string), (yyvsp[(7) - (10)].string), (yyvsp[(4) - (10)].attributesTree), (yyvsp[(9) - (10)].attributesTree));
        }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 388 ".\\parser.y"
    {
            (yyval.typeTree) = new TypeTree(AttrType::T_INT);
        }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 392 ".\\parser.y"
    {
            (yyval.typeTree) = new TypeTree(AttrType::T_INT, (yyvsp[(3) - (4)].ivalue));
        }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 396 ".\\parser.y"
    {
            (yyval.typeTree) = new TypeTree(AttrType::T_STRING, (yyvsp[(3) - (4)].ivalue));
        }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 400 ".\\parser.y"
    {
            (yyval.typeTree) = new TypeTree(AttrType::T_DATE, 15);
        }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 404 ".\\parser.y"
    {
            (yyval.typeTree) = new TypeTree(AttrType::T_FLOAT);
        }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 411 ".\\parser.y"
    {
            (yyval.insertValueTree) = new InsertValueTree((yyvsp[(2) - (3)].constValuesTree));
        }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 415 ".\\parser.y"
    {
            (yyval.insertValueTree)->addConstValues((yyvsp[(4) - (5)].constValuesTree));
        }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 422 ".\\parser.y"
    {
            (yyval.constValuesTree) = new ConstValuesTree();
            (yyval.constValuesTree)->addConstValue((yyvsp[(1) - (1)].constValueTree));
        }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 427 ".\\parser.y"
    {
            (yyval.constValuesTree)->addConstValue((yyvsp[(3) - (3)].constValueTree));
        }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 438 ".\\parser.y"
    {
            (yyval.constValueTree) = new ConstValueTree((yyvsp[(1) - (1)].ivalue));
        }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 442 ".\\parser.y"
    {
            (yyval.constValueTree) = new ConstValueTree((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 447 ".\\parser.y"
    {
            (yyval.constValueTree) = new ConstValueTree((yyvsp[(1) - (1)].fvalue));
        }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 451 ".\\parser.y"
    {
            (yyval.constValueTree) = new ConstValueTree((yyvsp[(1) - (1)].string), true);
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 456 ".\\parser.y"
    {
            (yyval.constValueTree) = new ConstValueTree(0);
            (yyval.constValueTree)->setNull();
        }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 464 ".\\parser.y"
    {
            (yyval.comparisonTree) = new ComparisonTree((yyvsp[(1) - (3)].attributeTree), (yyvsp[(2) - (3)].operatorTree)->op, (yyvsp[(3) - (3)].attributeTree));
        }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 468 ".\\parser.y"
    {
            (yyval.comparisonTree) = new ComparisonTree((yyvsp[(1) - (3)].attributeTree), (yyvsp[(2) - (3)].operatorTree)->op, (yyvsp[(3) - (3)].constValueTree));
        }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 472 ".\\parser.y"
    {
            (yyval.comparisonTree) = new ComparisonTree((yyvsp[(1) - (3)].attributeTree), CmpOP::T_ISNULL);
        }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 476 ".\\parser.y"
    {
            (yyval.comparisonTree) = new ComparisonTree((yyvsp[(1) - (3)].attributeTree), CmpOP::T_ISNOTNULL);
        }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 484 ".\\parser.y"
    {
            (yyval.whereClauseTree) = new WhereClauseTree((yyvsp[(2) - (2)].conditionsTree));
        }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 488 ".\\parser.y"
    {
            (yyval.whereClauseTree) = nullptr;
        }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 495 ".\\parser.y"
    {
            (yyval.conditionsTree) = new ConditionsTree();
            (yyval.conditionsTree)->addComparison((yyvsp[(1) - (1)].comparisonTree));
        }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 500 ".\\parser.y"
    {
            (yyval.conditionsTree)->addComparison((yyvsp[(3) - (3)].comparisonTree));
        }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 507 ".\\parser.y"
    {
            (yyval.attributeTree) = new AttributeTree((yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string));
            delete (yyvsp[(1) - (3)].string);
            delete (yyvsp[(3) - (3)].string);
        }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 513 ".\\parser.y"
    {
            (yyval.attributeTree) = new AttributeTree((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 521 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_EQ);
        }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 525 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_NE);
        }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 529 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_GT);
        }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 533 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_LT);
        }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 537 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_GE);
        }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 541 ".\\parser.y"
    {
            (yyval.operatorTree) = new OperatorTree(CmpOP::T_LE);
        }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 548 ".\\parser.y"
    {
            (yyval.setClauseTree) = new SetClauseTree();
            (yyval.setClauseTree)->addClause((yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].constValueTree));
        }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 553 ".\\parser.y"
    {
            (yyval.setClauseTree)->addClause((yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].constValueTree));
        }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 560 ".\\parser.y"
    {
            (yyval.attributesTree) = new AttributesTree();
            (yyval.attributesTree)->addAttribute((yyvsp[(1) - (1)].attributeTree));
        }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 565 ".\\parser.y"
    {
            (yyval.attributesTree)->addAttribute((yyvsp[(3) - (3)].attributeTree));
        }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 572 ".\\parser.y"
    {
            (yyval.relationsTree) = new RelationsTree();
            (yyval.relationsTree)->addRelation((yyvsp[(1) - (1)].string));
            delete (yyvsp[(1) - (1)].string);
        }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 578 ".\\parser.y"
    {
            (yyval.relationsTree)->addRelation((yyvsp[(3) - (3)].string));
            delete (yyvsp[(3) - (3)].string);
        }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 590 ".\\parser.y"
    {
            (yyval.attributesTree) = new AttributesTree();
            (yyval.attributesTree)->addAttribute(new AttributeTree((yyvsp[(1) - (1)].string)));
        }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 595 ".\\parser.y"
    {
            (yyval.attributesTree)->addAttribute(new AttributeTree((yyvsp[(3) - (3)].string)));
        }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 602 ".\\parser.y"
    { }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 607 ".\\parser.y"
    { }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 612 ".\\parser.y"
    { }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 617 ".\\parser.y"
    { }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 622 ".\\parser.y"
    { }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 627 ".\\parser.y"
    { }
    break;


/* Line 1792 of yacc.c  */
#line 2420 "parser.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 630 ".\\parser.y"


void yyerror(const char *msg) {
    printf("YACC error: %s\n", msg);
}
