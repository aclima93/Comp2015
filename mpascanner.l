%{

%}

word				[a-zA-Z]+
number				[0-9]+

ID					{word}([{word}{number}])*
INTLIT				{number}
REALLIT				{INTLIT}"."?(e[-+]{INTLIT})
STRINGLIT			'.'

ASSIGN				:=
BEGIN				[bB][eE][gG][iI][nN]
COLON				:
COMMA				,
DO					[dD][oO]
DOT					"."
ELSE				[eE][lL][sS][eE]
END					[eE][nN][dD]
FORWARD				[fF][oO][rR][wW][aA][rR][dD]
FUNCTION			[fF][uU][nN][cC][tT][iI][oO][nN]
IF					[iI][fF]
LBRAC				(
NOT					[nN][oO][tT]
OUTPUT				[oO][uU][tT][pP][uU][tT]
PARAMSTR			[pP][aA][rR][aA][mM][sS][tT][rR]
PROGRAM				[pP][rR][oO][gG][rR][aA][mM]
RBRAC				)
REPEAT				[rR][eE][pP][eE][aA][tT]
SEMIC				;
THEN				[tT][hH][eE][nN]
UNTIL				[uU][nN][tT][iI][lL]
VAL					[vV][aA][lL]
VAR					[vV][aA][rR]
WHILE				[wW][hH][iI][lL][eE]
WRITELN				[wW][rR][iI][tT][eE][lL][nN]
OP1					[([aA][nN][dD])|([oO][rR])]
OP2					[<|>|=|"<>"|"<="|">="]
OP3					[+-]
OP4					[*|/|([mM][oO][dD])|([dD][iI][vV])]


RESERVED			[|]
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


%%
{email}					;		{printf("%s, ", yytext);}
.						; 		{;}
\n						; 		{;}
%%
int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}
