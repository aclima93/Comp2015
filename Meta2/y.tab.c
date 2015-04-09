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
     FuncDeclarationList = 258,
     VarDeclarationList = 259,
     OP = 260,
     CommaIDList = 261,
     ASSIGN = 262,
     BEGIN_token = 263,
     DO = 264,
     ELSE = 265,
     END = 266,
     FORWARD = 267,
     FUNCTION = 268,
     IF = 269,
     OUTPUT = 270,
     PARAMSTR = 271,
     PROGRAM = 272,
     RBRAC = 273,
     REPEAT = 274,
     THEN = 275,
     UNTIL = 276,
     VAL = 277,
     VAR = 278,
     WHILE = 279,
     WRITELN = 280,
     ID = 281,
     STRING = 282,
     REALLIT = 283,
     INTLIT = 284,
     OP2 = 285,
     OR = 286,
     OP3 = 287,
     AND = 288,
     OP4 = 289,
     NOT = 290
   };
#endif
/* Tokens.  */
#define FuncDeclarationList 258
#define VarDeclarationList 259
#define OP 260
#define CommaIDList 261
#define ASSIGN 262
#define BEGIN_token 263
#define DO 264
#define ELSE 265
#define END 266
#define FORWARD 267
#define FUNCTION 268
#define IF 269
#define OUTPUT 270
#define PARAMSTR 271
#define PROGRAM 272
#define RBRAC 273
#define REPEAT 274
#define THEN 275
#define UNTIL 276
#define VAL 277
#define VAR 278
#define WHILE 279
#define WRITELN 280
#define ID 281
#define STRING 282
#define REALLIT 283
#define INTLIT 284
#define OP2 285
#define OR 286
#define OP3 287
#define AND 288
#define OP4 289
#define NOT 290




/* Copy the first part of user declarations.  */
#line 1 "mpascanner.y"


#include<stdio.h>
#include <stdlib.h>

#include "custom_structures.h"

node* makenode(nodeType t, node* f1, node* f2, node* f3);
node* makeleafInt(int i);
node* makeleafString(char* s);
node* makeleafDouble(double d);



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
#line 15 "mpascanner.y"
{
	int integer;
	char* string;
	double real;
	node* node_pointer;
}
/* Line 193 of yacc.c.  */
#line 187 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 200 "y.tab.c"

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
#define YYLAST   157

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,    35,     2,
      42,    43,     2,     2,    45,     2,    41,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    40,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    34,     2,    39,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    36,    37,
      38
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
     176,   180,   183,   187,   189,   191,   194,   196,   198,   200,
     202,   204,   206,   208,   210,   215,   219
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    40,    49,    41,    -1,    17,    26,
      42,    15,    43,    -1,    50,    55,    64,    -1,    23,    52,
      40,    51,    -1,    -1,    52,    40,    51,    -1,    -1,    53,
      44,    26,    -1,    26,    54,    -1,    45,    26,    54,    -1,
      -1,    56,    -1,    57,    40,    56,    -1,    -1,    58,    40,
      12,    -1,    59,    40,    63,    -1,    58,    40,    63,    -1,
      13,    26,    60,    44,    26,    -1,    13,    26,    44,    26,
      -1,    13,    26,    -1,    42,    62,    61,    43,    -1,    40,
      62,    61,    -1,    -1,    23,    53,    44,    26,    -1,    53,
      44,    26,    -1,    50,    64,    -1,    65,    -1,     8,    66,
      11,    -1,    68,    67,    -1,    40,    68,    67,    -1,    -1,
      65,    -1,    14,    73,    20,    68,    10,    68,    -1,    14,
      73,    20,    68,    -1,    24,    73,     9,    68,    -1,    19,
      66,    21,    73,    -1,    22,    42,    16,    42,    73,    43,
      45,    26,    43,    -1,    69,    -1,    25,    70,    -1,    26,
       7,    73,    -1,    -1,    71,    -1,    -1,    42,    73,    72,
      43,    -1,    42,    27,    72,    43,    -1,    45,    73,    72,
      -1,    45,    27,    72,    -1,    -1,    73,    74,    73,    -1,
      75,    73,    -1,    42,    73,    43,    -1,    29,    -1,    28,
      -1,    26,    76,    -1,    26,    -1,    36,    -1,    31,    -1,
      30,    -1,    32,    -1,    37,    -1,    32,    -1,    38,    -1,
      42,    73,    77,    43,    -1,    45,    73,    77,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    77,    79,    81,    82,    85,    86,    89,
      91,    93,    94,    97,    99,   100,   103,   104,   105,   108,
     109,   112,   114,   116,   117,   120,   121,   124,   126,   128,
     130,   132,   133,   136,   137,   138,   139,   140,   141,   142,
     143,   146,   147,   150,   151,   154,   155,   158,   159,   160,
     164,   165,   166,   167,   168,   169,   170,   173,   174,   175,
     176,   177,   180,   181,   184,   186,   187
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FuncDeclarationList",
  "VarDeclarationList", "OP", "CommaIDList", "ASSIGN", "BEGIN_token", "DO",
  "ELSE", "END", "FORWARD", "FUNCTION", "IF", "OUTPUT", "PARAMSTR",
  "PROGRAM", "RBRAC", "REPEAT", "THEN", "UNTIL", "VAL", "VAR", "WHILE",
  "WRITELN", "ID", "STRING", "REALLIT", "INTLIT", "OP2", "OR", "OP3",
  "'!'", "'|'", "'&'", "AND", "OP4", "NOT", "'~'", "';'", "'.'", "'('",
  "')'", "':'", "','", "$accept", "Prog", "ProgHeading", "ProgBlock",
  "VarPart", "VarDeclarationSemic_Repeat", "VarDeclaration", "IDList",
  "CommaID_Repeat", "FuncPart", "FuncDeclaration_Repeat",
  "FuncDeclaration", "FuncHeading", "FuncIdent", "FormalParamList",
  "SemicFormalParams_Repeat", "FormalParams", "FuncBlock", "StatPart",
  "CompStat", "StatList", "SemicStat_Repeat", "Stat",
  "IDAssignExpr_Optional", "WritelnPList_Optional", "WritelnPList",
  "CommaExprString_Repeat", "Expr", "OP1_Or_OP2_Or_OP3_Or_OP4",
  "OP3_Or_Not", "ParamList", "CommaExpr_Repeat", 0
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
     285,   286,   287,    33,   124,    38,   288,   289,   290,   126,
      59,    46,    40,    41,    58,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    49,    50,    50,    51,    51,    52,
      53,    54,    54,    55,    56,    56,    57,    57,    57,    58,
      58,    59,    60,    61,    61,    62,    62,    63,    64,    65,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    76,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     3,     4,     0,     3,     0,     3,
       2,     3,     0,     1,     3,     0,     3,     3,     3,     5,
       4,     2,     4,     3,     0,     4,     3,     2,     1,     3,
       2,     3,     0,     1,     6,     4,     4,     4,     9,     1,
       2,     3,     0,     1,     0,     4,     4,     3,     3,     0,
       3,     2,     3,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     0
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
      24,    20,     0,    56,    54,    53,    62,    63,     0,     0,
       0,     0,     0,     0,     0,    40,    43,     0,    29,    42,
      30,    27,     7,     0,     0,     0,     0,    19,     0,    55,
       0,    42,    59,    58,    60,    57,    61,     0,    51,     0,
       0,    42,    49,    49,    41,    32,     0,    26,    24,    22,
      66,    52,    35,    50,    37,     0,    36,     0,     0,     0,
      31,    25,    23,     0,     0,    42,     0,    49,    49,    46,
      45,    66,    64,    34,     0,    48,    47,    65,     0,     0,
      38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     9,    53,    35,    36,    14,    24,    17,
      18,    19,    20,    21,    40,    86,    60,    54,    29,    47,
      48,    80,    49,    50,    75,    76,   118,    69,    97,    70,
      89,   124
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int8 yypact[] =
{
     -12,    -6,    12,   -26,   -11,  -100,     9,    22,     1,    -2,
      29,     0,     2,     6,     8,  -100,    24,    46,  -100,    17,
      18,    20,  -100,    42,  -100,     1,    43,   -33,    37,  -100,
    -100,    29,    -4,     9,     2,  -100,    32,  -100,   -16,    48,
      31,    60,    37,    35,    60,    36,    78,  -100,    79,    51,
    -100,  -100,  -100,    46,  -100,  -100,  -100,     1,     1,    59,
      67,  -100,    73,    66,  -100,  -100,  -100,  -100,    60,   -14,
      60,    91,    97,     4,    38,  -100,  -100,    60,  -100,    37,
    -100,  -100,  -100,    81,   107,   -16,    75,  -100,    60,  -100,
      84,    37,  -100,  -100,  -100,  -100,  -100,    60,   100,    60,
      96,    37,    72,    64,   100,    51,   108,  -100,    67,  -100,
      74,  -100,   116,   100,   100,    60,  -100,    55,    98,    99,
    -100,  -100,  -100,    60,   101,    37,    92,    72,    64,  -100,
    -100,    74,  -100,  -100,    94,  -100,  -100,  -100,   114,   102,
    -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,  -100,  -100,   137,    89,   139,   -37,   115,  -100,
     117,  -100,  -100,  -100,  -100,    44,    65,   118,   103,   -15,
     111,    49,   -76,  -100,  -100,  -100,   -99,   -44,  -100,  -100,
    -100,    26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      73,    59,    30,   105,   119,     1,    91,    58,    52,    38,
      12,    39,     5,   101,     6,   112,    92,    93,    94,     8,
       4,    83,    95,    96,    90,   116,    98,    12,   135,   136,
     103,     7,     8,   104,    92,    93,    94,    11,    30,    15,
      95,    96,    16,    22,   110,    28,    25,    23,    59,   133,
      27,    41,    26,   113,    28,   114,    42,    31,    32,    43,
      33,    44,    45,    46,    63,   102,    64,    65,    34,    37,
      66,   126,    57,   128,    61,    62,    67,    72,    74,   131,
      68,    63,   127,    64,    65,    77,    63,    66,    64,    65,
      78,    79,    66,    67,    92,    93,    94,    68,    67,    87,
      95,    96,    68,    84,    92,    93,    94,    85,    88,   117,
      95,    96,    99,   100,    92,    93,    94,   117,   109,   123,
      95,    96,    92,    93,    94,   106,   125,   111,    95,    96,
      92,    93,    94,   107,   121,   134,    95,    96,   115,   138,
     139,   129,   130,    10,   132,   140,    82,    13,    51,    56,
     108,    55,   122,    71,   120,     0,    81,   137
};

static const yytype_int16 yycheck[] =
{
      44,    38,    17,    79,   103,    17,    20,    23,    12,    42,
      26,    44,     0,     9,    40,    91,    30,    31,    32,    23,
      26,    58,    36,    37,    68,   101,    70,    26,   127,   128,
      74,    42,    23,    77,    30,    31,    32,    15,    53,    41,
      36,    37,    13,    43,    88,     8,    40,    45,    85,   125,
      26,    14,    44,    97,     8,    99,    19,    40,    40,    22,
      40,    24,    25,    26,    26,    27,    28,    29,    26,    26,
      32,   115,    40,   117,    26,    44,    38,    42,    42,   123,
      42,    26,    27,    28,    29,     7,    26,    32,    28,    29,
      11,    40,    32,    38,    30,    31,    32,    42,    38,    26,
      36,    37,    42,    44,    30,    31,    32,    40,    42,    45,
      36,    37,    21,    16,    30,    31,    32,    45,    43,    45,
      36,    37,    30,    31,    32,    44,    10,    43,    36,    37,
      30,    31,    32,    26,    26,    43,    36,    37,    42,    45,
      26,    43,    43,     6,    43,    43,    57,     8,    31,    34,
      85,    33,   108,    42,   105,    -1,    53,   131
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    47,    48,    26,     0,    40,    42,    23,    49,
      50,    15,    26,    52,    53,    41,    13,    55,    56,    57,
      58,    59,    43,    45,    54,    40,    44,    26,     8,    64,
      65,    40,    40,    40,    26,    51,    52,    26,    42,    44,
      60,    14,    19,    22,    24,    25,    26,    65,    66,    68,
      69,    56,    12,    50,    63,    63,    54,    40,    23,    53,
      62,    26,    44,    26,    28,    29,    32,    38,    42,    73,
      75,    66,    42,    73,    42,    70,    71,     7,    11,    40,
      67,    64,    51,    53,    44,    40,    61,    26,    42,    76,
      73,    20,    30,    31,    32,    36,    37,    74,    73,    21,
      16,     9,    27,    73,    73,    68,    44,    26,    62,    43,
      73,    43,    68,    73,    73,    42,    68,    45,    72,    72,
      67,    26,    61,    45,    77,    10,    73,    27,    73,    43,
      43,    73,    43,    68,    43,    72,    72,    77,    45,    26,
      43
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
#line 75 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ProgType, (yyvsp[(1) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 3:
#line 77 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ProgHeadingType, makeleafString((yyvsp[(2) - (5)].string)), NULL, NULL);}
    break;

  case 4:
#line 79 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ProgBlockType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 5:
#line 81 "mpascanner.y"
    {(yyval.node_pointer) = makenode(VarPartType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 6:
#line 82 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 7:
#line 85 "mpascanner.y"
    {(yyval.node_pointer) = makenode(VarDeclarationListType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 8:
#line 86 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 9:
#line 89 "mpascanner.y"
    {(yyval.node_pointer) = makenode(VarDeclarationType, (yyvsp[(1) - (3)].node_pointer), makeleafString((yyvsp[(3) - (3)].string)), NULL);}
    break;

  case 10:
#line 91 "mpascanner.y"
    {(yyval.node_pointer) = makenode(IDListType, makeleafString((yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 11:
#line 93 "mpascanner.y"
    {(yyval.node_pointer) = makenode(CommaIDListType, makeleafString((yyvsp[(2) - (3)].string)), NULL, NULL);}
    break;

  case 12:
#line 94 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 13:
#line 97 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncPartType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 14:
#line 99 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationListType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 15:
#line 100 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 16:
#line 103 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationType, (yyvsp[(1) - (3)].node_pointer), NULL, NULL);}
    break;

  case 17:
#line 104 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 18:
#line 105 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncDeclarationType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 19:
#line 108 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncHeadingType, makeleafString((yyvsp[(2) - (5)].string)), (yyvsp[(3) - (5)].node_pointer), makeleafString((yyvsp[(5) - (5)].string)));}
    break;

  case 20:
#line 109 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncHeadingType, makeleafString((yyvsp[(2) - (4)].string)), makeleafString((yyvsp[(4) - (4)].string)), NULL);}
    break;

  case 21:
#line 112 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncIdentType, makeleafString((yyvsp[(2) - (2)].string)), NULL, NULL);}
    break;

  case 22:
#line 114 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FormalParamsListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 23:
#line 116 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FormalParamsListType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 24:
#line 117 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 25:
#line 120 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FormalParamsType, (yyvsp[(2) - (4)].node_pointer), makeleafString((yyvsp[(4) - (4)].string)), NULL);}
    break;

  case 26:
#line 121 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FormalParamsType, (yyvsp[(1) - (3)].node_pointer), makeleafString((yyvsp[(3) - (3)].string)), NULL);}
    break;

  case 27:
#line 124 "mpascanner.y"
    {(yyval.node_pointer) = makenode(FuncBlockType, (yyvsp[(1) - (2)].node_pointer), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 28:
#line 126 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatPartType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 29:
#line 128 "mpascanner.y"
    {(yyval.node_pointer) = makenode(CompStatType, (yyvsp[(2) - (3)].node_pointer), NULL, NULL);}
    break;

  case 30:
#line 130 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatListType, (yyvsp[(1) - (2)].node_pointer), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 31:
#line 132 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatListType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 32:
#line 133 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 33:
#line 136 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 34:
#line 137 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (6)].node_pointer), (yyvsp[(4) - (6)].node_pointer), (yyvsp[(6) - (6)].node_pointer));}
    break;

  case 35:
#line 138 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 36:
#line 139 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 37:
#line 140 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(4) - (4)].node_pointer), NULL);}
    break;

  case 38:
#line 141 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(5) - (9)].node_pointer), makeleafString((yyvsp[(8) - (9)].string)), NULL);}
    break;

  case 39:
#line 142 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 40:
#line 143 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, (yyvsp[(2) - (2)].node_pointer), NULL, NULL);}
    break;

  case 41:
#line 146 "mpascanner.y"
    {(yyval.node_pointer) = makenode(StatType, makeleafString((yyvsp[(1) - (3)].string)), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 42:
#line 147 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 43:
#line 150 "mpascanner.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, (yyvsp[(1) - (1)].node_pointer), NULL, NULL);}
    break;

  case 44:
#line 151 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 45:
#line 154 "mpascanner.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 46:
#line 155 "mpascanner.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, makeleafString((yyvsp[(2) - (4)].string)), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 47:
#line 158 "mpascanner.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 48:
#line 159 "mpascanner.y"
    {(yyval.node_pointer) = makenode(WritelnPListType, makeleafString((yyvsp[(2) - (3)].string)), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 49:
#line 160 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;

  case 50:
#line 164 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ExprType, (yyvsp[(1) - (3)].node_pointer), (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer));}
    break;

  case 51:
#line 165 "mpascanner.y"
    {(yyval.node_pointer) = makenode(OPType, (yyvsp[(1) - (2)].node_pointer), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 52:
#line 166 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ExprType, (yyvsp[(2) - (3)].node_pointer), NULL, NULL);}
    break;

  case 53:
#line 167 "mpascanner.y"
    {(yyval.node_pointer) = makeleafInt((yyvsp[(1) - (1)].integer));}
    break;

  case 54:
#line 168 "mpascanner.y"
    {(yyval.node_pointer) = makeleafDouble((yyvsp[(1) - (1)].real));}
    break;

  case 55:
#line 169 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ExprType, makeleafString((yyvsp[(1) - (2)].string)), (yyvsp[(2) - (2)].node_pointer), NULL);}
    break;

  case 56:
#line 170 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 57:
#line 173 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 58:
#line 174 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 59:
#line 175 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 60:
#line 176 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 61:
#line 177 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 62:
#line 180 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 63:
#line 181 "mpascanner.y"
    {(yyval.node_pointer) = makeleafString((yyvsp[(1) - (1)].string));}
    break;

  case 64:
#line 184 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ParamListType, (yyvsp[(2) - (4)].node_pointer), (yyvsp[(3) - (4)].node_pointer), NULL);}
    break;

  case 65:
#line 186 "mpascanner.y"
    {(yyval.node_pointer) = makenode(ExprType, (yyvsp[(2) - (3)].node_pointer), (yyvsp[(3) - (3)].node_pointer), NULL);}
    break;

  case 66:
#line 187 "mpascanner.y"
    {(yyval.node_pointer) = NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 1848 "y.tab.c"
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


#line 190 "mpascanner.y"

int main(){
	yyparse();
}

