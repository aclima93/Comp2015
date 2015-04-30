/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "mpasemantic.y"
{
	tokenInfo* info;
	node* node_pointer;
}
/* Line 1529 of yacc.c.  */
#line 116 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

