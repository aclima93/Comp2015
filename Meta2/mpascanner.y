%{

#include<stdio.h>
%}

%token ASSIGN
%token BEGIN
%token DO
%token ELSE
%token END
%token FORWARD
%token FUNCTION
%token IF
%token OUTPUT
%token PARAMSTR
%token PROGRAM
%token RBRAC
%token REPEAT
%token THEN
%token UNTIL
%token VAL
%token VAR
%token WHILE
%token WRITELN
%token RESERVED
%token ID
%token REALLIT
%token INTLIT



%token OP2

%token OR
%token OP3
%left '!'
%left '|'

%left '&'
%token AND
%token OP4

%token NOT
%left '~'


%% 

Prog:  ProgHeading ';' ProgBlock '.';

ProgHeading: PROGRAM ID '(' OUTPUT ')';

ProgBlock: VarPart FuncPart StatPart;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 
	| ;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat
	| ;

VarDeclaration: IDList ':' ID;

IDList: ID CommaID_Repeat;

CommaID_Repeat: ',' ID CommaID_Repeat
	| ;

FuncPart: FuncDeclaration_Repeat;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat
	| ;

FuncDeclaration: FuncHeading ';' FORWARD 
	|	FuncIdent ';' FuncBlock
	|	FuncHeading ';' FuncBlock
	;

FuncHeading: FUNCTION ID FormalParamList_Optional ':' ID;

FuncIdent: FUNCTION ID;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')';

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat
	| ;

FormalParamList_Optional: FormalParamList 
	| ;

FormalParams: VAR_Optional IDList ':' ID;

VAR_Optional: VAR 
	| ;

FuncBlock: VarPart StatPart;

StatPart: CompStat;

CompStat: BEGIN StatList END;

StatList: Stat SemicStat_Repeat;

SemicStat_Repeat: ';' Stat SemicStat_Repeat
	| ;

Stat: CompStat
	|	IF Expr THEN Stat ElseStat_Optional
	|	WHILE Expr DO Stat
	|	REPEAT StatList UNTIL Expr
	|	VAL '(' PARAMSTR '(' Expr ')' ',' ID ')'
	|	IDAssignExpr_Optional
	|	WRITELN WritelnPList_Optional
	;

ElseStat_Optional: ELSE Stat
	| ;

IDAssignExpr_Optional: ID ASSIGN Expr
	| ;

WritelnPList_Optional: WritelnPList 
	| ;

WritelnPList: '(' Expr_Or_String CommaExprString_Repeat ')';

Expr_Or_String: Expr | String;

CommaExprString_Repeat: ',' Expr_Or_String CommaExprString_Repeat
	| ;


Expr: Expr OP1_Or_OP2_Or_OP3_Or_OP4 Expr
	|	OP3_Or_Not Expr
	|	'(' Expr ')'
	|	INTLIT | REALLIT
	|	ID ParamList_Optional
	;

OP1_Or_OP2_Or_OP3_Or_OP4: AND | OR
	| OP2
	| OP3
	| OP4
	; 

OP3_Or_Not: OP3 | NOT;

ParamList_Optional: ParamList
	| ;

ParamList: '(' Expr CommaExpr_Repeat ')' ;

CommaExpr_Repeat: COMMA Expr CommaExpr_Repeat
	| ;

%%
int main(){
	yyparse();
}
