%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ASTree.h"
#include "STable.h"

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


%type <node_pointer> OP2Token 
%type <node_pointer> ORToken OP3Token UnaryOP3Token 
%type <node_pointer> ANDToken OP4Token 
%type <node_pointer> UnaryNOTToken 


%type <node_pointer> IDToken StringToken RealLitToken IntLitToken IDCallToken
%type <node_pointer> Prog ProgHeading ProgBlock VarPart VarDeclaration IDList FuncPart FuncDeclaration FuncHeading FuncIdent FormalParamList FormalParams FuncBlock StatPart CompStat StatList Stat WritelnPList Expr SimpleExpr Term Factor ParamList 
%type <node_pointer> VarDeclarationSemic_Repeat CommaID_Repeat FuncDeclaration_Repeat SemicFormalParams_Repeat SemicStat_Repeat IDAssignExpr_Optional WritelnPList_Optional CommaExprString_Repeat CommaExpr_Repeat 

%% 

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = createTree(makenode(ProgType, $1, $3, NULL, line, col));} ;

ProgHeading: PROGRAM IDToken '(' OUTPUT ')' 										{$$ = $2;} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3, line, col);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, NULL, line, col);}
	| 																				{$$ = makenode(VarPartType, NULL, NULL, NULL, line, col);}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, NULL, line, col);}
	|																				{$$ = NULL;} 
	;

VarDeclaration: IDList ':' IDToken													{$$ = makenode(VarDeclarationType, $1, $3, NULL, line, col);} ;

IDList: IDToken CommaID_Repeat														{$$ = makenode(IDListType, $1, $2, NULL, line, col);} ;

CommaID_Repeat: ',' IDToken CommaID_Repeat											{$$ = makenode(CommaIDListType, $2, $3, NULL, line, col);} ;
	| 																				{$$ = NULL;} 
	;

FuncPart: FuncDeclaration_Repeat													{$$ = makenode(FuncPartType, $1, NULL, NULL, line, col);} ;

FuncDeclaration_Repeat: FuncDeclaration ';' FuncDeclaration_Repeat					{$$ = makenode(FuncDeclarationListType, $1, $3, NULL, line, col);} 
	| 																				{$$ = NULL;} 
	;

FuncDeclaration: FuncHeading ';' FORWARD 											{$$ = makenode(FuncDeclarationType, $1, NULL, NULL, line, col);} 
	|	FuncIdent ';' FuncBlock														{$$ = makenode(FuncDefinition2Type, $1, $3, NULL, line, col);} 
	|	FuncHeading ';' FuncBlock													{$$ = makenode(FuncDefinitionType, $1, $3, NULL, line, col);} 
	;

FuncHeading: FUNCTION IDToken FormalParamList ':' IDToken  							{$$ = makenode(FuncHeadingType, $2, $3, $5, line, col);} 
	| FUNCTION IDToken ':' IDToken  												{$$ = makenode(FuncHeadingType, $2, makenode(FuncParamsListType, NULL, NULL, NULL, line, col), $4, line, col);} 
	;

FuncIdent: FUNCTION IDToken 														{$$ = makenode(FuncIdentType, $2, NULL, NULL, line, col);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FuncParamsListType, $2, $3, NULL, line, col);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FuncParamsListType2, $2, $3, NULL, line, col);} 
	| 																				{$$ = NULL;} 
	;

FormalParams: VAR IDList ':' IDToken 												{$$ = makenode(VarParamsType, $2, $4, NULL, line, col);} 
	| IDList ':' IDToken 															{$$ = makenode(ParamsType, $1, $3, NULL, line, col);} 
	;

FuncBlock: VarPart StatPart															{$$ = makenode(FuncBlockType, $1, $2, NULL, line, col);} ;

StatPart: CompStat 																	{$$ = $1;} ;

CompStat: BEGIN_token StatList END													{$$ = makenode(CompStatType, $2, NULL, NULL, line, col);} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode(StatListType, $1, $2, NULL, line, col);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{
																						if($3 != NULL)
																							$$ = makenode(StatType, $2, $3, NULL, line, col);
																						else
																							$$ = $2;
																					} 
	| 																				{$$ = NULL;} 
	;

Stat: CompStat 																		{$$ = $1;} 
	| IF Expr THEN Stat ELSE Stat 													{$$ = makenode(IfElseStatType, $2, $4, $6, line, col);} 
	| IF Expr THEN Stat 															{$$ = makenode(IfElseStatType, $2, $4, makenode(StatListType, NULL, NULL, NULL, line, col), line, col);} 
	| WHILE Expr DO Stat 															{
																						if($4 == NULL){
																							$4 = makenode(StatListType, NULL, NULL, NULL, line, col);
																						}
																						$$ = makenode(WhileStatType, $2, $4, NULL, line, col);
																					} 
	| REPEAT StatList UNTIL Expr 													{$$ = makenode(RepeatStatType, $2, $4, NULL, line, col);} 
	| VAL '(' PARAMSTR '(' Expr ')' ',' IDToken ')' 								{$$ = makenode(ValParamStatType, $5, $8, NULL, line, col);} 
	| IDAssignExpr_Optional 														{$$ = $1;} 
	| WRITELN WritelnPList_Optional 												{$$ = $2;} 
	;

IDAssignExpr_Optional: IDToken ASSIGN Expr 											{$$ = makenode(AssignStatType, $1, $3, NULL, line, col);} 
	| 																				{$$ = NULL;}
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WriteLnStatType, $1, NULL, NULL, line, col);} 
	| 																				{$$ = NULL;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL, line, col);} 
	| '(' StringToken CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL, line, col);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, NULL, line, col);}
	| ',' StringToken CommaExprString_Repeat 										{$$ = makenode(WritelnPListType, $2, $3, NULL, line, col);}
	| 																				{$$ = NULL;}
	;

Expr: SimpleExpr 																	{$$ = makenode(ExprType, NULL, $1, NULL, line, col);}
	| SimpleExpr OP2Token SimpleExpr 												{$$ = makenode(ExprType, $1, $2, $3, line, col);}
	;

SimpleExpr: SimpleExpr OP3Token Term												{$$ = makenode(SimpleExprType, $1, $2, $3, line, col);} 
	| SimpleExpr ORToken Term														{$$ = makenode(SimpleExprType, $1, $2, $3, line, col);}
	| UnaryOP3Token Term 															{$$ = makenode(SimpleExprType, NULL, $1, $2, line, col);}
	| Term 																			{$$ = $1;}
	;

Term: Term OP4Token Term 															{$$ = makenode(OPTermListType, $1, $2, $3, line, col);}
	| Term ANDToken Term 															{$$ = makenode(OPTermListType, $1, $2, $3, line, col);}
	| Factor 																		{$$ = $1;}
	;

Factor: UnaryNOTToken Factor														{$$ = makenode(FactorType, NULL, $1, $2, line, col);}
	| '(' Expr ')' 																	{$$ = $2;}
	| IntLitToken 																	{$$ = $1;}
	| RealLitToken 																	{$$ = $1;}
	| IDCallToken ParamList 														{$$ = makenode(FactorType, NULL, $1, $2, line, col);}
	| IDToken 					 													{$$ = $1;}
	;

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode(ParamListType, $2, $3, NULL, line, col);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode(ExprListType, $2, $3, NULL, line, col);}
	| 																				{$$ = NULL;}
	;


IDToken: ID 																		{$$ = makeleaf(IDType, $1, line, col);} ;
StringToken: STRING 																{$$ = makeleaf(StringType, $1, line, col);} ;
RealLitToken: REALLIT 																{$$ = makeleaf(DoubleType, $1, line, col);} ;
IntLitToken: INTLIT 																{$$ = makeleaf(IntType, $1, line, col);} ;

IDCallToken: ID 																	{$$ = makeleaf(CallType, $1, line, col);} ;

ANDToken: AND																		{$$ = makeleaf(OPType, $1, line, col);} ;
OP4Token: OP4 																		{$$ = makeleaf(OPType, $1, line, col);} ;
ORToken: OR 																		{$$ = makeleaf(OPType, $1, line, col);} ;
OP3Token: OP3 																		{$$ = makeleaf(OPType, $1, line, col);} ;
OP2Token: OP2 																		{$$ = makeleaf(OPType, $1, line, col);} ;

UnaryNOTToken: NOT																	{$$ = makeleaf(UnaryOPType, $1, line, col);} ;
UnaryOP3Token: OP3 																	{$$ = makeleaf(UnaryOPType, $1, line, col);} ;

%%

int main(int argc, char** args){

	errorCounter = 0;

	// read input and create Abstract Syntax Tree
	yyparse();

    // create Symbol Table
    errorCounter += createSymbolTable(ASTroot);
	
	// terminate program if any errors were found
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

    if(printTree){
    	// print AST recursively, starting from root node
		printNode(ASTroot, ProgType);
    }
	
	// mandatory, as per request
    if( printTree && printSymbolTable ){
    	printf("\n");
    }

	if(printSymbolTable){
    	// print ST recursively, by declaration order
		printSymbolTables( STroot );
	}

	// free all nodes in AST
	freeNode(ASTroot);

	return 0;
}

void yyerror(char *s) {

     printf ("Line %d, col %d: %s: %s\n", line, (int)(col-strlen(yytext)), s, yytext);
     errorCounter++;

}



