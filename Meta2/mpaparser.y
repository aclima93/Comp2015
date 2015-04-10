%{

#include<stdio.h>
#include <stdlib.h>

#include "custom_structures.h"

%}

%union {
	int integer;
	char* string;
	double real;
	node* node_pointer;
}


%token FuncDeclarationList
%token VarDeclarationList
%token OP
%token CommaIDList

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
%token <string> AND
%token <string> OP4
%token <string> NOT

%right THEN
%right ELSE

%left OP2
%left OR
%left OP3
%left AND
%left OP4
%left NOT


%type <node_pointer> Prog ProgHeading ProgBlock VarPart VarDeclarationList VarDeclaration IDList CommaIDList FuncPart FuncDeclarationList FuncDeclaration FuncHeading FuncIdent FormalParamList FormalParams FuncBlock StatPart CompStat StatList Stat WritelnPList Expr OP ParamList 
%type <node_pointer> VarDeclarationSemic_Repeat CommaID_Repeat FuncDeclaration_Repeat SemicFormalParams_Repeat SemicStat_Repeat IDAssignExpr_Optional WritelnPList_Optional CommaExprString_Repeat CommaExpr_Repeat

%% 

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = makenode(ProgType, $1, $3, NULL);} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makenode(ProgHeadingType, makeleafString($2), NULL, NULL);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, NULL);}
	| 																				{$$ = NULL;}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, NULL);}
	|																				{$$ = NULL;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode(VarDeclarationType, $1, makeleafString($3), NULL);} ;

IDList: ID CommaID_Repeat															{$$ = makenode(IDListType, makeleafString($1), $2, NULL);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode(CommaIDListType, makeleafString($2), NULL, NULL);} ;
	| 																				{$$ = NULL;} 
	;

FuncPart: FuncDeclaration_Repeat													{$$ = makenode(FuncPartType, $1, NULL, NULL);} ;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat					{$$ = makenode(FuncDeclarationListType, $1, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

FuncDeclaration: FuncHeading ';' FORWARD 											{$$ = makenode(FuncDeclarationType, $1, NULL, NULL);} 
	|	FuncIdent ';' FuncBlock														{$$ = makenode(FuncDeclarationType, $1, $3, NULL);} 
	|	FuncHeading ';' FuncBlock													{$$ = makenode(FuncDeclarationType, $1, $3, NULL);} 
	;

FuncHeading: FUNCTION ID FormalParamList ':' ID  									{$$ = makenode(FuncHeadingType, makeleafString($2), $3, makeleafString($5));} 
	| FUNCTION ID ':' ID  															{$$ = makenode(FuncHeadingType, makeleafString($2), makeleafString($4), NULL);} 
	;

FuncIdent: FUNCTION ID 																{$$ = makenode(FuncIdentType, makeleafString($2), NULL, NULL);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FormalParamsListType, $2, $3, NULL);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FormalParamsListType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

FormalParams: VAR IDList ':' ID 													{$$ = makenode(FormalParamsType, $2, makeleafString($4), NULL);} 
	| IDList ':' ID 																{$$ = makenode(FormalParamsType, $1, makeleafString($3), NULL);} 
	;

FuncBlock: VarPart StatPart															{$$ = makenode(FuncBlockType, $1, $2, NULL);} ;

StatPart: CompStat 																	{$$ = makenode(StatPartType, $1, NULL, NULL);} ;

CompStat: BEGIN_token StatList END													{$$ = makenode(CompStatType, $2, NULL, NULL);} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode(StatListType, $1, $2, NULL);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{$$ = makenode(StatListType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

Stat: CompStat 																		{$$ = makenode(StatType, $1, NULL, NULL);} 
	|	IF Expr THEN Stat ELSE Stat 												{$$ = makenode(StatType, $2, $4, $6);} 
	|	IF Expr THEN Stat 															{$$ = makenode(StatType, $2, $4, NULL);} 
	|	WHILE Expr DO Stat 															{$$ = makenode(StatType, $2, $4, NULL);} 
	|	REPEAT StatList UNTIL Expr 													{$$ = makenode(StatType, $2, $4, NULL);} 
	|	VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 									{$$ = makenode(StatType, $5, makeleafString($8), NULL);} 
	|	IDAssignExpr_Optional 														{$$ = makenode(StatType, $1, NULL, NULL);} 
	|	WRITELN WritelnPList_Optional 												{$$ = makenode(StatType, $2, NULL, NULL);} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode(StatType, makeleafString($1), $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WritelnPListType, $1, NULL, NULL);} 
	| 																				{$$ = NULL;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL);} 
	| '(' STRING CommaExprString_Repeat ')' 										{$$ = makenode(WritelnPListType, makeleafString($2), $3, NULL);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, NULL);}
	| ',' STRING CommaExprString_Repeat 											{$$ = makenode(WritelnPListType, makeleafString($2), $3, NULL);}
	| 																				{$$ = NULL;}
	;


Expr: Expr AND Expr 																{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	| Expr OR Expr 																	{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	| Expr OP2 Expr 																{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	| Expr OP3 Expr 																{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	| Expr OP4 Expr 																{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	| OP3 Expr 																		{$$ = makenode(ExprType, makeleafOP($1), $2, NULL);}
	| NOT Expr 																		{$$ = makenode(ExprType, makeleafOP($1), $2, NULL);}
	| '(' Expr ')' 																	{$$ = makenode(ExprType, $2, NULL, NULL);}
	| INTLIT 																		{$$ = makeleafInt($1);}
	| REALLIT 																		{$$ = makeleafDouble($1);}
	| ID ParamList 																	{$$ = makenode(ExprType, makeleafString($1), $2, NULL);}
	| ID 					 														{$$ = makeleafString($1);}
	;

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode(ParamListType, $2, $3, NULL);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode(ExprType, $2, $3, NULL);}
	| 																				{$$ = NULL;}
	;

%%
int main(){
	yyparse();
}
