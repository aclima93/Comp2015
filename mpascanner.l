%{

%}

word				[a-zA-Z]+
number				[0-9]+

ID					{word}([{word}{number}])*
INTLIT				{number}
REALLIT				{INTLIT}"."?(e[-+]{INTLIT})
STRING				'.'

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
