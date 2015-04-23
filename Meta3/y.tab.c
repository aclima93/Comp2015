/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ASSIGN = 258,
     BEGIN_token = 259,
     DO = 260,
     ELSE = 261,
     END = 262,
     FORWARD = 263,
     FUNCTION = 264,
     IF = 265,
     OUTPUT = 266,
     PARAMSTR = 267,
     PROGRAM = 268,
     REPEAT = 269,
     THEN = 270,
     UNTIL = 271,
     VAL = 272,
     VAR = 273,
     WHILE = 274,
     WRITELN = 275,
     RESERVED = 276,
     ID = 277,
     STRING = 278,
     REALLIT = 279,
     INTLIT = 280,
     OP2 = 281,
     OR = 282,
     OP3 = 283,
     AND = 284,
     OP4 = 285,
     NOT = 286
   };
#endif
/* Tokens.  */
#define ASSIGN 258
#define BEGIN_token 259
#define DO 260
#define ELSE 261
#define END 262
#define FORWARD 263
#define FUNCTION 264
#define IF 265
#define OUTPUT 266
#define PARAMSTR 267
#define PROGRAM 268
#define REPEAT 269
#define THEN 270
#define UNTIL 271
#define VAL 272
#define VAR 273
#define WHILE 274
#define WRITELN 275
#define RESERVED 276
#define ID 277
#define STRING 278
#define REALLIT 279
#define INTLIT 280
#define OP2 281
#define OR 282
#define OP3 283
#define AND 284
#define OP4 285
#define NOT 286




/* Copy the first part of user declarations.  */
#line 1 "mpasemantic.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ASTree.h"
#include "STable.h"

void yyerror(char *s);

extern char* yytext;
extern int yyleng;

extern int line;
extern int col;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "mpasemantic.y"
{
	char* string;
	node* node_pointer;
}
/* Line 193 of yacc.c.  */
#line 182 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 195 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      32,    33,     2,     2,    37,     2,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    34,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    14,    18,    23,    24,    28,    29,
      33,    36,    40,    41,    43,    47,    48,    52,    56,    60,
      66,    71,    74,    79,    83,    84,    89,    93,    96,    98,
     102,   105,   109,   110,   112,   119,   124,   129,   134,   144,
     146,   149,   153,   154,   156,   157,   162,   167,   171,   175,
     176,   178,   182,   186,   190,   193,   195,   199,   203,   205,
     208,   212,   214,   216,   219,   221,   226,   230
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    34,    41,    35,    -1,    13,    22,
      32,    11,    33,    -1,    42,    47,    56,    -1,    18,    44,
      34,    43,    -1,    -1,    44,    34,    43,    -1,    -1,    45,
      36,    22,    -1,    22,    46,    -1,    37,    22,    46,    -1,
      -1,    48,    -1,    49,    34,    48,    -1,    -1,    50,    34,
       8,    -1,    51,    34,    55,    -1,    50,    34,    55,    -1,
       9,    22,    52,    36,    22,    -1,     9,    22,    36,    22,
      -1,     9,    22,    -1,    32,    54,    53,    33,    -1,    34,
      54,    53,    -1,    -1,    18,    45,    36,    22,    -1,    45,
      36,    22,    -1,    42,    56,    -1,    57,    -1,     4,    58,
       7,    -1,    60,    59,    -1,    34,    60,    59,    -1,    -1,
      57,    -1,    10,    65,    15,    60,     6,    60,    -1,    10,
      65,    15,    60,    -1,    19,    65,     5,    60,    -1,    14,
      58,    16,    65,    -1,    17,    32,    12,    32,    65,    33,
      37,    22,    33,    -1,    61,    -1,    20,    62,    -1,    22,
       3,    65,    -1,    -1,    63,    -1,    -1,    32,    65,    64,
      33,    -1,    32,    23,    64,    33,    -1,    37,    65,    64,
      -1,    37,    23,    64,    -1,    -1,    66,    -1,    66,    26,
      66,    -1,    66,    28,    67,    -1,    66,    27,    67,    -1,
      28,    67,    -1,    67,    -1,    67,    30,    67,    -1,    67,
      29,    67,    -1,    68,    -1,    31,    68,    -1,    32,    65,
      33,    -1,    25,    -1,    24,    -1,    22,    69,    -1,    22,
      -1,    32,    65,    70,    33,    -1,    37,    65,    70,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    76,    78,    80,    81,    84,    85,    88,
      90,    92,    93,    96,    98,    99,   102,   103,   104,   107,
     108,   111,   113,   115,   116,   119,   120,   123,   125,   127,
     129,   131,   137,   140,   141,   142,   143,   149,   150,   151,
     152,   155,   156,   159,   160,   163,   164,   167,   168,   169,
     172,   173,   176,   177,   178,   179,   182,   183,   184,   187,
     188,   189,   190,   191,   192,   195,   197,   198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGN", "BEGIN_token", "DO", "ELSE",
  "END", "FORWARD", "FUNCTION", "IF", "OUTPUT", "PARAMSTR", "PROGRAM",
  "REPEAT", "THEN", "UNTIL", "VAL", "VAR", "WHILE", "WRITELN", "RESERVED",
  "ID", "STRING", "REALLIT", "INTLIT", "OP2", "OR", "OP3", "AND", "OP4",
  "NOT", "'('", "')'", "';'", "'.'", "':'", "','", "$accept", "Prog",
  "ProgHeading", "ProgBlock", "VarPart", "VarDeclarationSemic_Repeat",
  "VarDeclaration", "IDList", "CommaID_Repeat", "FuncPart",
  "FuncDeclaration_Repeat", "FuncDeclaration", "FuncHeading", "FuncIdent",
  "FormalParamList", "SemicFormalParams_Repeat", "FormalParams",
  "FuncBlock", "StatPart", "CompStat", "StatList", "SemicStat_Repeat",
  "Stat", "IDAssignExpr_Optional", "WritelnPList_Optional", "WritelnPList",
  "CommaExprString_Repeat", "Expr", "SimpleExpr", "Term", "Factor",
  "ParamList", "CommaExpr_Repeat", 0
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
     285,   286,    40,    41,    59,    46,    58,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    41,    42,    42,    43,    43,    44,
      45,    46,    46,    47,    48,    48,    49,    49,    49,    50,
      50,    51,    52,    53,    53,    54,    54,    55,    56,    57,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    69,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     3,     4,     0,     3,     0,     3,
       2,     3,     0,     1,     3,     0,     3,     3,     3,     5,
       4,     2,     4,     3,     0,     4,     3,     2,     1,     3,
       2,     3,     0,     1,     6,     4,     4,     4,     9,     1,
       2,     3,     0,     1,     0,     4,     4,     3,     3,     0,
       1,     3,     3,     3,     2,     1,     3,     3,     1,     2,
       3,     1,     1,     2,     1,     4,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     6,     0,     0,     0,
      15,     0,    12,     0,     0,     2,     0,     0,    13,     0,
       0,     0,     3,     0,    10,     8,     0,    21,    42,     4,
      28,    15,     6,     6,    12,     5,     0,     9,     0,     0,
       0,     0,    42,     0,     0,    44,     0,    33,     0,    32,
      39,    14,    16,     0,    18,    17,    11,     8,     0,     0,
      24,    20,     0,    64,    62,    61,     0,     0,     0,     0,
      50,    55,    58,     0,     0,     0,     0,    40,    43,     0,
      29,    42,    30,    27,     7,     0,     0,     0,     0,    19,
       0,    63,    54,    59,     0,    42,     0,     0,     0,     0,
       0,     0,     0,    42,    49,    49,    41,    32,     0,    26,
      24,    22,    67,    60,    35,    51,    53,    52,    57,    56,
      37,     0,    36,     0,     0,     0,    31,    25,    23,     0,
       0,    42,     0,    49,    49,    46,    45,    67,    65,    34,
       0,    48,    47,    66,     0,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    53,    35,    36,    14,    24,    17,
      18,    19,    20,    21,    40,    88,    60,    54,    29,    47,
      48,    82,    49,    50,    77,    78,   124,    69,    70,    71,
      72,    91,   130
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int8 yypact[] =
{
      -7,   -13,    12,   -16,   -11,   -90,     8,    20,    40,    -1,
      61,    38,    37,    42,    39,   -90,    60,    79,   -90,    50,
      52,    55,   -90,    68,   -90,    40,    69,   -25,     0,   -90,
     -90,    61,    -5,     8,    37,   -90,    58,   -90,    25,    71,
      59,    41,     0,    62,    41,    64,    94,   -90,    91,    65,
     -90,   -90,   -90,    79,   -90,   -90,   -90,    40,    40,    66,
      67,   -90,    78,    72,   -90,   -90,    56,    56,    41,    88,
      22,    23,   -90,    89,    95,   101,     5,   -90,   -90,    41,
     -90,     0,   -90,   -90,   -90,    73,    86,    25,    77,   -90,
      41,   -90,    23,   -90,    80,     0,    41,    56,    56,    56,
      56,    41,    82,     0,    74,    74,   -90,    65,    90,   -90,
      67,   -90,    81,   -90,   109,    28,    23,    23,   -90,   -90,
     -90,    41,   -90,    36,    83,    84,   -90,   -90,   -90,    41,
      87,     0,    92,    74,    74,   -90,   -90,    81,   -90,   -90,
      85,   -90,   -90,   -90,    97,    93,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,   -90,   115,    70,   116,   -33,    96,   -90,
      98,   -90,   -90,   -90,   -90,    13,    44,    99,    75,   -15,
     100,    26,   -80,   -90,   -90,   -90,   -89,   -44,    43,   -58,
      76,   -90,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      75,   107,    30,    52,    28,    59,     1,    38,    92,     4,
      41,    39,     5,     8,    42,   114,   125,    43,     6,    44,
      45,     7,    46,   122,    94,    85,     8,    63,   104,    64,
      65,    11,   105,    66,    15,   106,    67,    68,    30,   116,
     117,   118,   119,    58,   141,   142,   112,    12,    96,    97,
      98,   139,    99,   100,    59,    97,    98,   120,    63,   133,
      64,    65,    12,    63,    66,    64,    65,    67,    68,    66,
      16,    22,    67,    68,    23,    26,    25,   132,    63,   134,
      64,    65,    27,    28,    31,   137,    32,    67,    68,    33,
      34,    37,    57,    61,    74,    62,    76,    79,    80,    81,
      89,    87,    86,    95,    90,   101,   103,   102,   109,   108,
     111,   123,   127,   113,   121,   131,   135,   136,   129,   145,
     138,    10,   144,   128,    13,   140,   146,    84,    83,    51,
      56,   110,    55,   126,   143,     0,     0,     0,     0,   115,
       0,     0,    73,    93
};

static const yytype_int16 yycheck[] =
{
      44,    81,    17,     8,     4,    38,    13,    32,    66,    22,
      10,    36,     0,    18,    14,    95,   105,    17,    34,    19,
      20,    32,    22,   103,    68,    58,    18,    22,    23,    24,
      25,    11,    76,    28,    35,    79,    31,    32,    53,    97,
      98,    99,   100,    18,   133,   134,    90,    22,    26,    27,
      28,   131,    29,    30,    87,    27,    28,   101,    22,    23,
      24,    25,    22,    22,    28,    24,    25,    31,    32,    28,
       9,    33,    31,    32,    37,    36,    34,   121,    22,   123,
      24,    25,    22,     4,    34,   129,    34,    31,    32,    34,
      22,    22,    34,    22,    32,    36,    32,     3,     7,    34,
      22,    34,    36,    15,    32,    16,     5,    12,    22,    36,
      33,    37,    22,    33,    32,     6,    33,    33,    37,    22,
      33,     6,    37,   110,     8,    33,    33,    57,    53,    31,
      34,    87,    33,   107,   137,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    42,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    39,    40,    22,     0,    34,    32,    18,    41,
      42,    11,    22,    44,    45,    35,     9,    47,    48,    49,
      50,    51,    33,    37,    46,    34,    36,    22,     4,    56,
      57,    34,    34,    34,    22,    43,    44,    22,    32,    36,
      52,    10,    14,    17,    19,    20,    22,    57,    58,    60,
      61,    48,     8,    42,    55,    55,    46,    34,    18,    45,
      54,    22,    36,    22,    24,    25,    28,    31,    32,    65,
      66,    67,    68,    58,    32,    65,    32,    62,    63,     3,
       7,    34,    59,    56,    43,    45,    36,    34,    53,    22,
      32,    69,    67,    68,    65,    15,    26,    27,    28,    29,
      30,    16,    12,     5,    23,    65,    65,    60,    36,    22,
      54,    33,    65,    33,    60,    66,    67,    67,    67,    67,
      65,    32,    60,    37,    64,    64,    59,    22,    53,    37,
      70,     6,    65,    23,    65,    33,    33,    65,    33,    60,
      33,    64,    64,    70,    37,    22,    33
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 74 "mpasemantic.y"
    {(yyval.node_pointer) = createTree(makenode(ProgType, (yyvsp[(1) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL));}
    break;

  case 3:
#line 76 "mpasemantic.y"
    {(yyval.node_pointer) = makeleaf(IDType, (yyvsp[(2) - (5)].string));}
    break;

  case 4:
#line 78 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ProgBlockType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 5:
#line 80 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(VarPartType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 6:
#line 81 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(VarPartType, NULL, NULL, NULL);}
    break;

  case 7:
#line 84 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(VarDeclarationListType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 8:
#line 85 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 9:
#line 88 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(VarDeclarationType, (yyvsp[(1) - (3)].node_pointer), makeleaf(IDType, (yyvsp[(3) - (3)].string)), NULL);}
    break;

  case 10:
#line 90 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(IDListType, makeleaf(IDType, (yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 11:
#line 92 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(CommaIDListType, makeleaf(IDType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 12:
#line 93 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 13:
#line 96 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncPartType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 14:
#line 98 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationListType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 15:
#line 99 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 16:
#line 102 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationType, (yyvsp[(1) - (3)].node_pointer), NULL, NULL);}
    break;

  case 17:
#line 103 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncDefinition2Type, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 18:
#line 104 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncDefinitionType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 19:
#line 107 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncHeadingType, makeleaf(IDType, (yyvsp[(2) - (5)].string)), (yyvsp[(3) - (5)].node_pointer), makeleaf(IDType, (yyvsp[(5) - (5)].string)));}
    break;

  case 20:
#line 108 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncHeadingType, makeleaf(IDType, (yyvsp[(2) - (4)].string)), makeleaf(IDType, (yyvsp[(4) - (4)].string)), makenode(FuncParamsListType, NULL, NULL, NULL));}
    break;

  case 21:
#line 111 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncIdentType, makeleaf(IDType, (yyvsp[(2) - (2)].string)), NULL, NULL);}
    break;

  case 22:
#line 113 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncParamsListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 23:
#line 115 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncParamsListType2, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 24:
#line 116 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 25:
#line 119 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(VarParamsType, (yyvsp[(2) - (4)].node_pointer), makeleaf(IDType, (yyvsp[(4) - (4)].string)), NULL);}
    break;

  case 26:
#line 120 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ParamsType, (yyvsp[(1) - (3)].node_pointer), makeleaf(IDType, (yyvsp[(3) - (3)].string)), NULL);}
    break;

  case 27:
#line 123 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FuncBlockType, (yyvsp[(1) - (2)].node_pointer), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 28:
#line 125 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(1) - (1)].node_pointer);}
    break;

  case 29:
#line 127 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(CompStatType, (yyvsp[(2) - (3)].node_pointer), NULL, NULL);}
    break;

  case 30:
#line 129 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(StatListType, (yyvsp[(1) - (2)].node_pointer), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 31:
#line 131 "mpasemantic.y"
    {
																						if((yyvsp[(3) - (3)].node_pointer) != NULL)
																							(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);
																						else
																							(yyval.node_pointer) = (yyvsp[(2) - (3)].node_pointer);
																					}
    break;

  case 32:
#line 137 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 33:
#line 140 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(1) - (1)].node_pointer);}
    break;

  case 34:
#line 141 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(IfElseStatType, (yyvsp[(2) - (6)].node_pointer), (yyvsp[(4) - (6)].node_pointer), (yyvsp[(6) - (6)].node_pointer));}
    break;

  case 35:
#line 142 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(IfElseStatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), makenode(StatListType, NULL, NULL, NULL));}
    break;

  case 36:
#line 143 "mpasemantic.y"
    {
																						if((yyvsp[(4) - (4)].node_pointer) == NULL){
																							(yyvsp[(4) - (4)].node_pointer) = makenode(StatListType, NULL, NULL, NULL);
																						}
																						(yyval.node_pointer) = makenode(WhileStatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);
																					}
    break;

  case 37:
#line 149 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(RepeatStatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 38:
#line 150 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ValParamStatType, (yyvsp[(5) - (9)].node_pointer), makeleaf(IDType, (yyvsp[(8) - (9)].string)), NULL);}
    break;

  case 39:
#line 151 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(1) - (1)].node_pointer);}
    break;

  case 40:
#line 152 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(2) - (2)].node_pointer);}
    break;

  case 41:
#line 155 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(AssignStatType, makeleaf(IDType, (yyvsp[(1) - (3)].string)), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 42:
#line 156 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 43:
#line 159 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(WriteLnStatType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 44:
#line 160 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 45:
#line 163 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 46:
#line 164 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, makeleaf(StringType, (yyvsp[(2) - (4)].string)), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 47:
#line 167 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 48:
#line 168 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, makeleaf(StringType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 49:
#line 169 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 50:
#line 172 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ExprType, NULL, (yyvsp[(1) - (1)].node_pointer), NULL);}
    break;

  case 51:
#line 173 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ExprType, (yyvsp[(1) - (3)].node_pointer), makeleaf(OPType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 52:
#line 176 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(SimpleExprType, (yyvsp[(1) - (3)].node_pointer), makeleaf(OPType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 53:
#line 177 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(SimpleExprType, (yyvsp[(1) - (3)].node_pointer), makeleaf(OPType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 54:
#line 178 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(SimpleExprType, NULL, makeleaf(UnaryOPType, (yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer));}
    break;

  case 55:
#line 179 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(1) - (1)].node_pointer);}
    break;

  case 56:
#line 182 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(OPTermListType, (yyvsp[(1) - (3)].node_pointer), makeleaf(OPType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 57:
#line 183 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(OPTermListType, (yyvsp[(1) - (3)].node_pointer), makeleaf(OPType, (yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 58:
#line 184 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(1) - (1)].node_pointer);}
    break;

  case 59:
#line 187 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FactorType, NULL, makeleaf(UnaryOPType, (yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer));}
    break;

  case 60:
#line 188 "mpasemantic.y"
    {(yyval.node_pointer) = (yyvsp[(2) - (3)].node_pointer);}
    break;

  case 61:
#line 189 "mpasemantic.y"
    {(yyval.node_pointer) = makeleaf(IntType, (yyvsp[(1) - (1)].string));}
    break;

  case 62:
#line 190 "mpasemantic.y"
    {(yyval.node_pointer) = makeleaf(DoubleType, (yyvsp[(1) - (1)].string));}
    break;

  case 63:
#line 191 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(FactorType, NULL, makeleaf(CallType, (yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer));}
    break;

  case 64:
#line 192 "mpasemantic.y"
    {(yyval.node_pointer) = makeleaf(IDType, (yyvsp[(1) - (1)].string));}
    break;

  case 65:
#line 195 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ParamListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 66:
#line 197 "mpasemantic.y"
    {(yyval.node_pointer) = makenode(ExprListType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 67:
#line 198 "mpasemantic.y"
    {(yyval.node_pointer) = NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 1854 "y.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 201 "mpasemantic.y"


int main(int argc, char** args){

	errorCounter = 0;

	// read input and create Abstract Syntax Tree
	yyparse();
	
	// terminate program if any errors were found
	if(errorCounter)
		return 0;

    // checks which flags were requested
	char c;
	int i;
	for(i = 1; i < argc; i++) {

		c = getopt(argc, args, "st");

		switch(c){

			case 't':

				printTree = 1;
	      		break;
	        
			case 's':

				printSymbolTable = 1;
	        	break;

			default:
	    		break;
		}
	}

    if(printTree){
    	// print AST recursively, starting from root node
		printNode(root, ProgType);
    }
	
	// mandatory, as per request
    if( printTree && printSymbolTable ){
    	printf("\n");
    }

    // create Symbol Table

	if(printSymbolTable){
		// print the Symbol Table
	}

	freeNode(root);

	return 0;
}

void yyerror(char *s) {

     printf ("Line %d, col %d: %s: %s\n", line, (int)(col-strlen(yytext)), s, yytext);
     errorCounter++;

}




