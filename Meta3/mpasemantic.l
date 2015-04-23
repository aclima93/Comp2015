%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ASTree.h"
#include "STable.h"

#include "y.tab.h"

int line = 1;
int col = 1;

int commentCols;
int commentLines;
char* readString;

%}

%X COMMENT STRINGLIT


word				[a-zA-Z]+
number				[0-9]+

NEWLINE				"\n"
WHITESPACE			" "|"\t"|"\r"

ASSIGN				":="
BEGIN_token			[bB][eE][gG][iI][nN]
COLON				":"
COMMA				","
DO					[dD][oO]
DOT					"."
ELSE				[eE][lL][sS][eE]
END					[eE][nN][dD]
FORWARD				[fF][oO][rR][wW][aA][rR][dD]
FUNCTION			[fF][uU][nN][cC][tT][iI][oO][nN]
IF					[iI][fF]
LBRAC				"("
NOT					[nN][oO][tT]
OUTPUT				[oO][uU][tT][pP][uU][tT]
PARAMSTR			[pP][aA][rR][aA][mM][sS][tT][rR]
PROGRAM				[pP][rR][oO][gG][rR][aA][mM]
RBRAC				")"
REPEAT				[rR][eE][pP][eE][aA][tT]
SEMIC				";"
THEN				[tT][hH][eE][nN]
UNTIL				[uU][nN][tT][iI][lL]
VAL					[vV][aA][lL]
VAR					[vV][aA][rR]
WHILE				[wW][hH][iI][lL][eE]
WRITELN				[wW][rR][iI][tT][eE][lL][nN]

MOD					[mM][oO][dD]
DIV					[dD][iI][vV]
AND					[aA][nN][dD]
OR 					[oO][rR]

OP1					{AND}|{OR}
OP2					"<>"|"<="|">="|"<"|">"|"="
OP3					[+-]
OP4					"*"|"/"|{MOD}|{DIV}


RESERVED			{ABS}|{ABSOLUTE}|{ARCTAN}|{ARRAY}|{ASM}|{CASE}|{CHAR}|{CHR}|{CONST}|{COS}|{CONSTRUCTOR}|{DESTRUCTOR}|{DISPOSE}|{DOWNTO}|{EOF}|{EOLN}|{EXIT}|{EXP}|{FILE}|{FOR}|{GET}|{GOTO}|{IMPLEMENTATION}|{IN}|{INHERITED}|{INLINE}|{INPUT}|{LABEL}|{LN}|{MAXINT}|{NEW}|{NIL}|{OBJECT}|{ODD}|{OF}|{OPERATOR}|{ORD}|{PACK}|{PACKED}|{PAGE}|{PRED}|{PROCEDURE}|{PUT}|{READ}|{READLN}|{RECORD}|{REINTRODUCE}|{RESET}|{REWRITE}|{ROUND}|{SELF}|{SET}|{SHL}|{SHR}|{SIN}|{SQR}|{SQRT}|{SUCC}|{TEXT}|{TO}|{TRUNC}|{TYPE}|{UNIT}|{UNPACK}|{WITH}|{WRITE}|{XOR}

ABS 				[aA][bB][sS]
ABSOLUTE			[aA][bB][sS][oO][lL][uU][tT][eE]
ARCTAN				[aA][rR][cC][tT][aA][nN]
ARRAY				[aA][rR][rR][aA][yY]
ASM					[aA][sS][mM]
CASE				[cC][aA][sS][eE]
CHAR 				[cC][hH][aA][rR]
CHR 				[cC][hH][rR]
CONST				[cC][oO][nN][sS][tT]
CONSTRUCTOR			[cC][oO][nN][sS][tT][rR][uU][cC][tT][oO][rR]
COS 				[cC][oO][sS]
DESTRUCTOR			[dD][eE][sS][tT][rR][uU][cC][tT][oO][rR]
DISPOSE				[dD][iI][sS][pP][oO][sS][eE]
DOWNTO				[dD][oO][wW][nN][tT][oO]
EOF					[eE][oO][fF]
EOLN				[eE][oO][lL][nN]
EXIT				[eE][xX][iI][tT]
EXP					[eE][xX][pP]
FILE				[fF][iI][lL][eE]
FOR   				[fF][oO][rR]
GET					[gG][eE][tT]
GOTO				[gG][oO][tT][oO]
IMPLEMENTATION		[iI][mM][pP][lL][eE][mM][eE][nN][tT][aA][tT][iI][oO][nN]
IN 					[iI][nN]
INHERITED			[iI][nN][hH][eE][rR][iI][tT][eE][dD]
INLINE				[iI][nN][lL][iI][nN][eE]
INPUT				[iI][nN][pP][uU][tT]
LABEL				[lL][aA][bB][eE][lL]
LN 					[lL][nN]
MAXINT				[mM][aA][xX][iI][nN][tT]
NEW					[nN][eE][wW]
NIL					[nN][iI][lL]
OBJECT				[oO][bB][jJ][eE][cC][tT]
ODD					[oO][dD][dD]
OF					[oO][fF]
OPERATOR			[oO][pP][eE][rR][aA][tT][oO][rR]
ORD					[oO][rR][dD]
PACK 				[pP][aA][cC][kK]
PACKED				[pP][aA][cC][kK][eE][dD]
PAGE				[pP][aA][gG][eE]
PRED 				[pP][rR][eE][dD]
PROCEDURE			[pP][rR][oO][cC][eE][dD][uU][rR][eE]
PUT					[pP][uU][tT]
READ 				[rR][eE][aA][dD]
READLN				[rR][eE][aA][dD][lL][nN]
RECORD				[rR][eE][cC][oO][rR][dD]
REINTRODUCE			[rR][eE][iI][nN][tT][rR][oO][dD][uU][cC][eE]
RESET				[rR][eE][sS][eE][tT]
REWRITE				[rR][eE][wW][rR][iI][tT][eE]
ROUND				[rR][oO][uU][nN][dD]
SELF 				[sS][eE][lL][fF]
SET					[sS][eE][tT]
SHL					[sS][hH][lL]
SHR					[sS][hH][rR]
SIN 				[sS][iI][nN]
SQR					[sS][qQ][rR]
SQRT				[sS][qQ][rR][tT]
SUCC				[sS][uU][cC][cC]
TEXT				[tT][eE][xX][tT]
TO					[tT][oO]
TRUNC				[tT][rR][uU][nN][cC]
TYPE				[tT][yY][pP][eE]
UNIT 				[uU][nN][iI][tT]
UNPACK				[uU][nN][pP][aA][cC][kK]
WITH				[wW][iI][tT][hH]
WRITE 				[wW][rR][iI][tT][eE]
XOR					[xX][oO][rR]


ID					{word}({word}|{number})*

scalefactor			[eE][+-]?{number}
dotnumber			{DOT}{number}
REALLIT				{number}{dotnumber}?{scalefactor}?

INTLIT				{number}

%%


"(*"|"{"				;	{if(DEBUG) printf("BEGIN COMMENT\n"); BEGIN COMMENT; commentLines=line; commentCols=col+strlen(yytext); }

<COMMENT>"*)"|"}"		;	{if(DEBUG) printf("EXIT COMMENT\n"); BEGIN 0; commentCols+=strlen(yytext); line=commentLines; col=commentCols; }

<COMMENT><<EOF>>		;	{printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN 0; commentCols+=strlen(yytext); line=commentLines; col=commentCols;}

<COMMENT>.				;	{if(DEBUG) printf("TEXT COMMENT\n"); commentCols+=strlen(yytext);}
<COMMENT>"\n"			;	{if(DEBUG) printf("\\n COMMENT\n"); commentLines++; commentCols=1;}




"'"						;	{if(DEBUG) printf("BEGIN STRINGLIT\n"); BEGIN STRINGLIT; readString = strdup(yytext); }

<STRINGLIT>"''"			;	{if(DEBUG) printf("ASPAS STRINGLIT\n"); readString = strdup(strcat(readString, yytext));}
<STRINGLIT>"'"			;	{if(DEBUG) printf("PLICA STRINGLIT\n"); readString = strdup(strcat(readString, yytext)); BEGIN 0; col=col+strlen(readString); yylval.string = strdup(readString); yytext = strdup(readString); return STRING;}

<STRINGLIT>.			;	{if(DEBUG) printf("TEXT STRINGLIT\n"); readString = strdup(strcat(readString, yytext));}
<STRINGLIT>"\n"			;	{printf("Line %d, col %d: unterminated string\n", line, col); BEGIN 0; line++; col=1; yytext = strdup(readString); }
<STRINGLIT><<EOF>>		;	{printf("Line %d, col %d: unterminated string\n", line, col); BEGIN 0; col=col+strlen(readString); yytext = strdup(readString); }




{INTLIT}				; 	{if(DEBUG) printf("INTLIT\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return INTLIT;}
{REALLIT}				; 	{if(DEBUG) printf("REALLIT\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return REALLIT;}


{RESERVED}				;	{if(DEBUG) printf("RESERVED\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return RESERVED;}


{ASSIGN}				; 	{if(DEBUG) printf("ASSIGN\n"); col=col+strlen(yytext); return ASSIGN;}
{BEGIN_token}			; 	{if(DEBUG) printf("BEGIN_token\n"); col=col+strlen(yytext); return BEGIN_token;}
{COLON}					; 	{if(DEBUG) printf("COLON\n"); col=col+strlen(yytext); return ':';}
{COMMA}					; 	{if(DEBUG) printf("COMMA\n"); col=col+strlen(yytext); return ',';}
{DO}					; 	{if(DEBUG) printf("DO\n"); col=col+strlen(yytext); return DO;}
{DOT}					; 	{if(DEBUG) printf("DOT\n"); col=col+strlen(yytext); return '.';}
{ELSE}					; 	{if(DEBUG) printf("ELSE\n"); col=col+strlen(yytext); return ELSE;}
{END}					; 	{if(DEBUG) printf("END\n"); col=col+strlen(yytext); return END;}
{FORWARD}				; 	{if(DEBUG) printf("FORWARD\n"); col=col+strlen(yytext); return FORWARD;}
{FUNCTION}				; 	{if(DEBUG) printf("FUNCTION\n"); col=col+strlen(yytext); return FUNCTION;}
{IF}					; 	{if(DEBUG) printf("IF\n"); col=col+strlen(yytext); return IF;}
{LBRAC}					; 	{if(DEBUG) printf("LBRAC\n"); col=col+strlen(yytext); return '(';}
{NOT}					; 	{if(DEBUG) printf("NOT\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return NOT;}
{OUTPUT}				; 	{if(DEBUG) printf("OUTPUT\n"); col=col+strlen(yytext); return OUTPUT;}
{PARAMSTR}				; 	{if(DEBUG) printf("PARAMSTR\n"); col=col+strlen(yytext); return PARAMSTR;}
{PROGRAM}				; 	{if(DEBUG) printf("PROGRAM\n"); col=col+strlen(yytext); return PROGRAM;}
{RBRAC}					; 	{if(DEBUG) printf("RBRAC\n"); col=col+strlen(yytext); return ')';}
{REPEAT}				; 	{if(DEBUG) printf("REPEAT\n"); col=col+strlen(yytext); return REPEAT;}
{SEMIC}					; 	{if(DEBUG) printf("SEMIC\n"); col=col+strlen(yytext); return ';';}
{THEN}					; 	{if(DEBUG) printf("THEN\n"); col=col+strlen(yytext); return THEN;}
{UNTIL}					; 	{if(DEBUG) printf("UNTIL\n"); col=col+strlen(yytext); return UNTIL;}
{VAL}					; 	{if(DEBUG) printf("VAL\n"); col=col+strlen(yytext); return VAL;}
{VAR}					; 	{if(DEBUG) printf("VAR\n"); col=col+strlen(yytext); return VAR;}
{WHILE}					; 	{if(DEBUG) printf("WHILE\n"); col=col+strlen(yytext); return WHILE;}
{WRITELN}				; 	{if(DEBUG) printf("WRITELN\n"); col=col+strlen(yytext); return WRITELN;}


{AND}					; 	{if(DEBUG) printf("AND\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return AND;}
{OR}					;	{if(DEBUG) printf("OR\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return OR;}
{OP2}					; 	{if(DEBUG) printf("OP2\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return OP2;}
{OP3}					; 	{if(DEBUG) printf("OP3\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return OP3;}
{OP4}					; 	{if(DEBUG) printf("OP4\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return OP4;}


{ID}					; 	{if(DEBUG) printf("ID\n"); col=col+strlen(yytext); yylval.string = strdup(yytext); return ID;}


{WHITESPACE}			;	{col+=strlen(yytext); }
{NEWLINE}				; 	{line++; col=1; }

.						; 	{printf("Line %d, col %d: illegal character (\'%c\')\n", line, col, yytext[0]); col=col+strlen(yytext); }

<<EOF>>					;	{return 0;}

%%

int yywrap(){
	return 1;
}

