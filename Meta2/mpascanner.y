%{

#include<stdio.h>

%}

%union {
	int integer;
	char* string;
	double real;
}


%token ASSIGN
%token BEGIN_token
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

%token <string> ID
%token <string> STRING
%token <real> REALLIT
%token <integer> INTLIT



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

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = makenode("Prog", $1, $3, null);} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makenode("ProgHeading", $2, null, null);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode("ProgBlock", $1, $2, $3);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode("VarPart", $2, $4, null);}
	| 																				{$$ = null;}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode("VarDeclarationList", $1, $3, null);}
	|																				{$$ = null;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode("VarDeclaration", $1, $3, null);} ;

IDList: ID CommaID_Repeat															{$$ = makenode("IDList", $1, $2, null);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode("CommaIDList", $2, null, null);} ;
	| 																				{$$ = null;} 
	;

FuncPart: FuncDeclaration_Repeat													{$$ = makenode("FuncPart", $1, null, null);} ;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat					{$$ = makenode("FuncDeclarationList", $1, $3, null);} 
	| 																				{$$ = null;} 
	;

FuncDeclaration: FuncHeading ';' FORWARD 											{$$ = makenode("FuncDeclaration", $1, null, null);} 
	|	FuncIdent ';' FuncBlock														{$$ = makenode("FuncDeclaration", $1, $3, null);} 
	|	FuncHeading ';' FuncBlock													{$$ = makenode("FuncDeclaration", $1, $3, null);} 
	;

FuncHeading: FUNCTION ID FormalParamList_Optional ':' ID  							{$$ = makenode("FuncHeading", $2, $3, $5);} ;

FuncIdent: FUNCTION ID 																{$$ = makenode("FuncIdent", $2, null, null);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode("FormalParamsList", $2, $3, null);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode("FormalParamsList", $2, null, null);} 
	| 																				{$$ = null;} 
	;

FormalParamList_Optional: FormalParamList 											{$$ = makenode("FormalParamsList", $1, null, null);} 
	| 																				{$$ = null;}
	;

FormalParams: VAR_Optional IDList ':' ID 											{$$ = makenode("FormalParams", $2, $4, null);} ;

VAR_Optional: VAR 
	| 
	;

FuncBlock: VarPart StatPart															{$$ = makenode("FuncBlock", $1, $2, null);} ;

StatPart: CompStat 																	{$$ = makenode("StatPart", $1, null, null);} ;

CompStat: BEGIN_token StatList END													{$$ = makenode("CompStat", $2, null, null);} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode("StatList", $1, $2, null);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{$$ = makenode("StatList", $2, $3, null);} 
	| 																				{$$ = null;} 
	;

Stat: CompStat 																		{$$ = makenode("Stat", $1, null, null);} 
	|	IF Expr THEN Stat ElseStat_Optional 										{$$ = makenode("Stat", $2, $4, $5);} 
	|	WHILE Expr DO Stat 															{$$ = makenode("Stat", $2, $4, null);} 
	|	REPEAT StatList UNTIL Expr 													{$$ = makenode("Stat", $2, $4, null);} 
	|	VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 									{$$ = makenode("Stat", $5, $8, null);} 
	|	IDAssignExpr_Optional 														{$$ = makenode("Stat", $1, null, null);} 
	|	WRITELN WritelnPList_Optional 												{$$ = makenode("Stat", $2, null, null);} 
	;

ElseStat_Optional: ELSE Stat 														{$$ = makenode("Stat", $2, null, null);} 
	| 																				{$$ = null;} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode("Stat", $1, $3, null);} 
	| 																				{$$ = null;} 
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode("WritelnPList", $1, null, null);} 
	| 																				{$$ = null;}
	;

WritelnPList: '(' Expr_Or_String CommaExprString_Repeat ')' 						{$$ = makenode("WritelnPList", $2, $3, null);} ;

Expr_Or_String: Expr 																{$$ = makenode("Expr", $1, null, null);}
	| STRING 																		{$$ = $1;} 
	;

CommaExprString_Repeat: ',' Expr_Or_String CommaExprString_Repeat 					{$$ = makenode("Expr_Or_String", $2, $3, null);}
	| 																				{$$ = null;}
	;


Expr: Expr OP1_Or_OP2_Or_OP3_Or_OP4 Expr 											{$$ = makenode("Expr", $1, $2, $3);}
	| OP3_Or_Not Expr 																{$$ = makenode("OP", $1, $2, null);}
	| '(' Expr ')' 																	{$$ = makenode("Expr", $2, null, null);}
	| INTLIT 																		{$$ = $1;}
	| REALLIT 																		{$$ = $1;}
	| ID ParamList_Optional 														{$$ = makenode("Expr", $1, $2, null);}
	;

OP1_Or_OP2_Or_OP3_Or_OP4: AND 														{$$ = $1;}
	| OR 																			{$$ = $1;}
	| OP2 																			{$$ = $1;}
	| OP3 																			{$$ = $1;}
	| OP4 																			{$$ = $1;}
	; 

OP3_Or_Not: OP3 																	{$$ = $1;}
	| NOT 																			{$$ = $1;}
	;

ParamList_Optional: ParamList 														{$$ = makenode("ParamList", $1, null, null);}
	| 																				{$$ = null;}
	;

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode("ParamList", $2, $3, null);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode("Expr", $2, $3, null);}
	| 																				{$$ = null;}
	;

%%
int main(){
	yyparse();
}
