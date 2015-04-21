%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "custom_structures.h"

void yyerror(char *s);

extern char* yytext;
extern int yyleng;

extern int line;
extern int col;

%}

%union {
	char* string;
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
%token <string> REALLIT
%token <string> INTLIT

%token <string> OP2
%token <string> OR
%token <string> OP3
%token <string> AND
%token <string> OP4
%token <string> NOT

%right THEN
%right ELSE

%left OP2
%left OR OP3
%left AND OP4
%right NOT
%left '(' ')'
%right ASSIGN


%type <node_pointer> Prog ProgHeading ProgBlock VarPart VarDeclaration IDList FuncPart FuncDeclaration FuncHeading FuncIdent FormalParamList FormalParams FuncBlock StatPart CompStat StatList Stat WritelnPList Expr SimpleExpr Term Factor ParamList 
%type <node_pointer> VarDeclarationSemic_Repeat CommaID_Repeat FuncDeclaration_Repeat SemicFormalParams_Repeat SemicStat_Repeat IDAssignExpr_Optional WritelnPList_Optional CommaExprString_Repeat CommaExpr_Repeat 

%% 

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = createTree(makenode(ProgType, $1, $3, NULL));} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makeleaf(IDType, $2);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, NULL);}
	| 																				{$$ = makenode(VarPartType, NULL, NULL, NULL);}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, NULL);}
	|																				{$$ = NULL;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode(VarDeclarationType, $1, makeleaf(IDType, $3), NULL);} ;

IDList: ID CommaID_Repeat															{$$ = makenode(IDListType, makeleaf(IDType, $1), $2, NULL);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode(CommaIDListType, makeleaf(IDType, $2), $3, NULL);} ;
	| 																				{$$ = NULL;} 
	;

FuncPart: FuncDeclaration_Repeat													{$$ = makenode(FuncPartType, $1, NULL, NULL);} ;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat					{$$ = makenode(FuncDeclarationListType, $1, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

FuncDeclaration: FuncHeading ';' FORWARD 											{$$ = makenode(FuncDeclarationType, $1, NULL, NULL);} 
	|	FuncIdent ';' FuncBlock														{$$ = makenode(FuncDefinition2Type, $1, $3, NULL);} 
	|	FuncHeading ';' FuncBlock													{$$ = makenode(FuncDefinitionType, $1, $3, NULL);} 
	;

FuncHeading: FUNCTION ID FormalParamList ':' ID  									{$$ = makenode(FuncHeadingType, makeleaf(IDType, $2), $3, makeleaf(IDType, $5));} 
	| FUNCTION ID ':' ID  															{$$ = makenode(FuncHeadingType, makeleaf(IDType, $2), makeleaf(IDType, $4), makenode(FuncParamsListType, NULL, NULL, NULL));} 
	;

FuncIdent: FUNCTION ID 																{$$ = makenode(FuncIdentType, makeleaf(IDType, $2), NULL, NULL);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FuncParamsListType, $2, $3, NULL);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FuncParamsListType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

FormalParams: VAR IDList ':' ID 													{$$ = makenode(VarParamsType, $2, makeleaf(IDType, $4), NULL);} 
	| IDList ':' ID 																{$$ = makenode(ParamsType, $1, makeleaf(IDType, $3), NULL);} 
	;

FuncBlock: VarPart StatPart															{$$ = makenode(FuncBlockType, $1, $2, NULL);} ;

StatPart: CompStat 																	{$$ = $1;} ;

CompStat: BEGIN_token StatList END													{$$ = $2;} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode(StatListType, $1, $2, NULL);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{$$ = makenode(StatType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

Stat: CompStat 																		{$$ = $1;} 
	| IF Expr THEN Stat ELSE Stat 													{$$ = makenode(IfElseStatType, $2, $4, $6);} 
	| IF Expr THEN Stat 															{$$ = makenode(IfElseStatType, $2, $4, makenode(StatListType, NULL, NULL, NULL));} 
	| WHILE Expr DO Stat 															{
																						if($4 == NULL){
																							$4 = makenode(StatListType, NULL, NULL, NULL);
																						}
																						$$ = makenode(WhileStatType, $2, $4, NULL);
																					} 
	| REPEAT StatList UNTIL Expr 													{$$ = makenode(RepeatStatType, $2, $4, NULL);} 
	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 										{$$ = makenode(ValParamStatType, $5, makeleaf(IDType, $8), NULL);} 
	| IDAssignExpr_Optional 														{$$ = $1;} 
	| WRITELN WritelnPList_Optional 												{$$ = $2;} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode(AssignStatType, makeleaf(IDType, $1), $3, NULL);} 
	| 																				{$$ = NULL;}
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WriteLnStatType, $1, NULL, NULL);} 
	| 																				{$$ = NULL;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL);} 
	| '(' STRING CommaExprString_Repeat ')' 										{$$ = makenode(WritelnPListType, makeleaf(StringType, $2), $3, NULL);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, NULL);}
	| ',' STRING CommaExprString_Repeat 											{$$ = makenode(WritelnPListType, makeleaf(StringType, $2), $3, NULL);}
	| 																				{$$ = NULL;}
	;

Expr: SimpleExpr 																	{$$ = makenode(ExprType, $1, NULL, NULL);}
	| SimpleExpr OP2 SimpleExpr 													{$$ = makenode(ExprType, $1, makeleaf(OPType, $2), $3);}
	;

SimpleExpr: SimpleExpr OP3 Term														{$$ = makenode(SimpleExprType, $1, makeleaf(OPType, $2), $3);} 
	| SimpleExpr OR Term															{$$ = makenode(SimpleExprType, $1, makeleaf(OPType, $2), $3);}
	| OP3 Term 																		{$$ = makenode(SimpleExprType, NULL, makeleaf(UnaryOPType, $1), $2);}
	| Term 																			{$$ = $1;}
	;

Term: Term OP4 Term 																{$$ = makenode(OPTermListType, $1, makeleaf(OPType, $2), $3);}
	| Term AND Term 																{$$ = makenode(OPTermListType, $1, makeleaf(OPType, $2), $3);}
	| Factor 																		{$$ = $1;}
	;

Factor: NOT Factor																	{$$ = makenode(FactorType, NULL, makeleaf(UnaryOPType, $1), $2);}
	| '(' Expr ')' 																	{$$ = $2;}
	| INTLIT 																		{$$ = makeleaf(IntType, $1);}
	| REALLIT 																		{$$ = makeleaf(DoubleType, $1);}
	| ID ParamList 																	{$$ = makenode(FactorType, NULL, makeleaf(CallType, $1), $2);}
	| ID 					 														{$$ = makeleaf(IDType, $1);}
	;

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode(ParamListType, $2, $3, NULL);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode(ExprListType, $2, $3, NULL);}
	| 																				{$$ = NULL;}
	;

%%

int main(int argc, char** args){

	errorCounter = 0;

	yyparse();
	
	// terminate program if any errors where found
	if(errorCounter)
		return 0;

    // checks which flags were requested
	char c;
	int i;
	for(i = 1; i < argc; i++) {

		c = getopt(argc, args, "st");

		switch(c){

			case 't':

				printTree = 1;
	      		break;
	        
			case 's':

				printSymbolTable = 1;
	        	break;

			default:
	    		break;
		}
	}

	//remove useless consecutive StatLists 
	cleanStatLists(root);

    if(printTree){
		printNode(root, ProgType);
    }
	
	if(printSymbolTable){
		// print the symbol table here
	}

	freeNode(root);

	return 0;
}

void yyerror(char *s) {

     printf ("Line %d, col %d: %s: %s\n", line, (int)(col-strlen(yytext)), s, yytext);
     errorCounter++;

}



