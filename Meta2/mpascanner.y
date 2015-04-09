%{

#include<stdio.h>

#include"custom_structures.h"

%}

%union {
	int integer;
	char* string;
	double real;
	node* node_pointer;
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

%token <string> ID
%token <string> STRING
%token <real> REALLIT
%token <integer> INTLIT



%token <string> OP2

%token <string> OR
%token <string> OP3
%left '!'
%left '|'

%left '&'
%token <string> AND
%token <string> OP4

%token <string> NOT
%left '~'


%type <node_pointer> Prog ProgHeading ProgBlock VarPart VarDeclarationList VarDeclaration IDList CommaIDList FuncPart FuncDeclarationList FuncDeclaration FuncHeading FuncIdent FormalParamList FormalParams FuncBlock StatPart CompStat StatList Stat WritelnPList Expr OP ParamList 
%type <node_pointer> VarDeclarationSemic_Repeat CommaID_Repeat FuncDeclaration_Repeat SemicFormalParams_Repeat SemicStat_Repeat IDAssignExpr_Optional WritelnPList_Optional CommaExprString_Repeat OP1_Or_OP2_Or_OP3_Or_OP4 OP3_Or_Not CommaExpr_Repeat

%% 

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = makenode(ProgType, $1, $3, null);} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makenode(ProgHeadingType, $2, null, null);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, null);}
	| 																				{$$ = null;}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, null);}
	|																				{$$ = null;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode(VarDeclarationType, $1, $3, null);} ;

IDList: ID CommaID_Repeat															{$$ = makenode(IDListType, $1, $2, null);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode(CommaIDListType, $2, null, null);} ;
	| 																				{$$ = null;} 
	;

FuncPart: FuncDeclaration_Repeat													{$$ = makenode(FuncPartType, $1, null, null);} ;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat					{$$ = makenode(FuncDeclarationListType, $1, $3, null);} 
	| 																				{$$ = null;} 
	;

FuncDeclaration: FuncHeading ';' FORWARD 											{$$ = makenode(FuncDeclarationType, $1, null, null);} 
	|	FuncIdent ';' FuncBlock														{$$ = makenode(FuncDeclarationType, $1, $3, null);} 
	|	FuncHeading ';' FuncBlock													{$$ = makenode(FuncDeclarationType, $1, $3, null);} 
	;

FuncHeading: FUNCTION ID FormalParamList ':' ID  									{$$ = makenode(FuncHeadingType, $2, $3, $5);} 
	| FUNCTION ID ':' ID  															{$$ = makenode(FuncHeadingType, $2, $4, null);} 
	;

FuncIdent: FUNCTION ID 																{$$ = makenode(FuncIdentType, $2, null, null);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FormalParamsListType, $2, $3, null);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FormalParamsListType, $2, $3, null);} 
	| 																				{$$ = null;} 
	;

FormalParams: VAR IDList ':' ID 													{$$ = makenode(FormalParamsType, $2, $4, null);} 
	| IDList ':' ID 																{$$ = makenode(FormalParamsType, $1, $3, null);} 
	;

FuncBlock: VarPart StatPart															{$$ = makenode(FuncBlockType, $1, $2, null);} ;

StatPart: CompStat 																	{$$ = makenode(StatPartType, $1, null, null);} ;

CompStat: BEGIN_token StatList END													{$$ = makenode(CompStatType, $2, null, null);} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode(StatListType, $1, $2, null);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{$$ = makenode(StatListType, $2, $3, null);} 
	| 																				{$$ = null;} 
	;

Stat: CompStat 																		{$$ = makenode(StatType, $1, null, null);} 
	|	IF Expr THEN Stat ELSE Stat 												{$$ = makenode(StatType, $2, $4, $6);} 
	|	IF Expr THEN Stat 															{$$ = makenode(StatType, $2, $4, null);} 
	|	WHILE Expr DO Stat 															{$$ = makenode(StatType, $2, $4, null);} 
	|	REPEAT StatList UNTIL Expr 													{$$ = makenode(StatType, $2, $4, null);} 
	|	VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 									{$$ = makenode(StatType, $5, $8, null);} 
	|	IDAssignExpr_Optional 														{$$ = makenode(StatType, $1, null, null);} 
	|	WRITELN WritelnPList_Optional 												{$$ = makenode(StatType, $2, null, null);} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode(StatType, $1, $3, null);} 
	| 																				{$$ = null;} 
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WritelnPListType, $1, null, null);} 
	| 																				{$$ = null;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, null);} 
	| '(' STRING CommaExprString_Repeat ')' 										{$$ = makenode(WritelnPListType, $2, $3, null);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, null);}
	| ',' STRING CommaExprString_Repeat 											{$$ = makenode(WritelnPListType, $2, $3, null);}
	| 																				{$$ = null;}
	;


Expr: Expr OP1_Or_OP2_Or_OP3_Or_OP4 Expr 											{$$ = makenode(ExprType, $1, $2, $3);}
	| OP3_Or_Not Expr 																{$$ = makenode(OPType, $1, $2, null);}
	| '(' Expr ')' 																	{$$ = makenode(ExprType, $2, null, null);}
	| INTLIT 																		{$$ = $1;}
	| REALLIT 																		{$$ = $1;}
	| ID ParamList 																	{$$ = makenode(ExprType, $1, $2, null);}
	| ID 					 														{$$ = $1;}
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

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode(ParamListType, $2, $3, null);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode(ExprType, $2, $3, null);}
	| 																				{$$ = null;}
	;

%%
int main(){
	yyparse();
}
