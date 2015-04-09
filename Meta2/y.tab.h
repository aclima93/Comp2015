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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "mpascanner.y"
{
	int integer;
	char* string;
	double real;
	node* node_pointer;
}
/* Line 1529 of yacc.c.  */
#line 126 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

