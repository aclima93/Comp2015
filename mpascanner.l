%{

#include <stdio.h>
#include <stdlib.h>

int line = 1;
int col = 1;

%}

word				[a-zA-Z]+
number				[0-9]+

NEWLINE				\n
WHITESPACE			[ \t\r]+

ASSIGN				":="
BEGIN				[bB][eE][gG][iI][nN]
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


RESERVED			{ABSOLUTE}|{ARRAY}|{ASM}|{CASE}|{CONST}|{CONSTRUCTOR}|{DESTRUCTOR}|{DISPOSE}|{DOWNTO}|{EXIT}|{FILE}|{FOR}|{GOTO}|{IMPLEMENTATION}|{IN}|{INHERITED}|{INLINE}|{INTERFACE}|{LABEL}|{NEW}|{NIL}|{OBJECT}|{OF}|{OPERATOR}|{PACKED}|{PROCEDURE}|{RECORD}|{REINTRODUCE}|{SELF}|{SET}|{SHL}|{SHR}|{STRING}|{TO}|{TYPE}|{UNIT}|{USES}|{WITH}|{XOR}
ABSOLUTE			[aA][bB][sS][oO][lL][uU][tT][eE]
ARRAY				[aA][rR][rR][aA][yY]
ASM					[aA][sS][mM]
CASE				[cC][aA][sS][eE]
CONST				[cC][oO][nN][sS][tT]
CONSTRUCTOR			[cC][oO][nN][sS][tT][rR][uU][cC][tT][oO][rR]
DESTRUCTOR			[dD][eE][sS][tT][rR][uU][cC][tT][oO][rR]
DISPOSE				[dD][iI][sS][pP][oO][sS][eE]
DOWNTO				[dD][oO][wW][nN][tT][oO]
EXIT				[eE][xX][iI][tT]
FILE				[fF][iI][lL][eE]
FOR   				[fF][oO][rR]
GOTO				[gG][oO][tT][oO]
IMPLEMENTATION		[iI][mM][pP][lL][eE][mM][eE][nN[tT][aA][tT][iI][oO][nN]
IN 					[iI][nN]
INHERITED			[iI][nN][hH][eE][rR][iI][tT][eE][dD]
INLINE				[iI][nN][lL][iI][nN][eE]
INTERFACE			[iI][nN][tT][eE][rR][fF][aA][cC][eE]
LABEL				[lL][aA][bB][eE][lL]
NEW					[nN][eE][wW]
NIL					[nN][iI][lL]
OBJECT				[oO][bB][jJ][eE][cC][tT]
OF					[oO][fF]
OPERATOR			[oO][pP][eE][rR][aA][tT][oO][rR]
PACKED				[pP][aA][cC][kK][eE][dD]
PROCEDURE			[pP][rR][oO][cC][eE][dD][uU][rR][eE]
RECORD				[rR][eE][cC][oO][rR][dD]
REINTRODUCE			[rR][eE][iI][nN][tT][rR][oO][dD][uU][cC][eE]
SELF 				[sS][eE][lL][fF]
SET					[sS][eE][tT]
SHL					[sS][hH][lL]
SHR					[sS][hH][rR]
STRING				[sS][tT][rR][iI][nN][gG]
TO					[tT][oO]
TYPE				[tT][yY][pP][eE]
UNIT 				[uU][nN][iI][tT]
USES				[uU][sS][eE][sS]
WITH				[wW][iI][tT][hH]
XOR					[xX][oO][rR]


ID					{word}([{word}{number}])*
INTLIT				{number}
REALLIT				{INTLIT}"."?(e[+-]{INTLIT})
STRINGLIT			'.'


%%


{INTLIT}				; 	{printf("INTLIT(%s)\n", yytext); col=col+yyleng;}
{REALLIT}				; 	{printf("REALLIT(%s)\n", yytext); col=col+yyleng;}
{STRINGLIT}				; 	{printf("STRING(%s)\n", yytext); col=col+yyleng;}

{ASSIGN}				; 	{printf("ASSIGN\n"); col=col+yyleng;}
{BEGIN}					; 	{printf("BEGIN\n"); col=col+yyleng;}
{COLON}					; 	{printf("COLON\n"); col=col+yyleng;}
{COMMA}					; 	{printf("COMMA\n"); col=col+yyleng;}
{DO}					; 	{printf("DO\n\n"); col=col+yyleng;}
{DOT}					; 	{printf("DOT\n"); col=col+yyleng;}
{ELSE}					; 	{printf("ELSE\n"); col=col+yyleng;}
{END}					; 	{printf("END\n"); col=col+yyleng;}
{FORWARD}				; 	{printf("FORWARD\n"); col=col+yyleng;}
{FUNCTION}				; 	{printf("FUNCTION\n"); col=col+yyleng;}
{IF}					; 	{printf("IF\n"); col=col+yyleng;}
{LBRAC}					; 	{printf("LBRAC\n"); col=col+yyleng;}
{NOT}					; 	{printf("NOT\n"); col=col+yyleng;}
{OUTPUT}				; 	{printf("OUTPUT\n"); col=col+yyleng;}
{PARAMSTR}				; 	{printf("PARAMSTR\n"); col=col+yyleng;}
{PROGRAM}				; 	{printf("PROGRAM\n"); col=col+yyleng;}
{RBRAC}					; 	{printf("RBRAC\n"); col=col+yyleng;}
{REPEAT}				; 	{printf("REPEAT\n"); col=col+yyleng;}
{SEMIC}					; 	{printf("SEMIC\n"); col=col+yyleng;}
{THEN}					; 	{printf("THEN\n"); col=col+yyleng;}
{UNTIL}					; 	{printf("UNTIL\n"); col=col+yyleng;}
{VAL}					; 	{printf("VAL\n"); col=col+yyleng;}
{VAR}					; 	{printf("VAR\n"); col=col+yyleng;}
{WHILE}					; 	{printf("WHILE\n"); col=col+yyleng;}
{WRITELN}				; 	{printf("WRITELN\n"); col=col+yyleng;}

{OP1}					; 	{printf("OP1(%s)\n", yytext); col=col+yyleng;}
{OP2}					; 	{printf("OP2(%s)\n", yytext); col=col+yyleng;}
{OP3}					; 	{printf("OP3(%s)\n", yytext); col=col+yyleng;}
{OP4}					; 	{printf("OP4(%s)\n", yytext); col=col+yyleng;}

{ID}					; 	{printf("ID(%s)\n", yytext); col=col+yyleng;}

{WHITESPACE}			;	{col=col+yyleng;}
{NEWLINE}				; 	{line++; col=1;}

.						; 	{printf("Line %d, col %d: illegal character (\'%c\')\n", line, col, yytext[0]); ; col=col+yyleng;}


%%

int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
