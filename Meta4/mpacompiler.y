%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ASTree.h"
#include "STable.h"
#include "LLVMCode.h"

void yyerror(char *s);

extern char* yytext;
extern int yyleng;

extern int line;
extern int col;

%}

%union {
	tokenInfo* info;
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

%token <info> ID
%token <info> STRING
%token <info> REALLIT
%token <info> INTLIT

%token <info> OP2
%token <info> OR
%token <info> OP3
%token <info> AND
%token <info> OP4
%token <info> NOT

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

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = createTree(makenode(ProgType, $1, $3, NULL, line, col));} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makeleaf(IDType, ($2)->string, ($2)->line, ($2)->col);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3, line, col);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, NULL, line, col);}
	| 																				{$$ = makenode(VarPartType, NULL, NULL, NULL, line, col);}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, NULL, line, col);}
	|																				{$$ = NULL;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode(VarDeclarationType, $1, makeleaf(IDType, ($3)->string, ($3)->line, ($3)->col), NULL, line, col);} ;

IDList: ID CommaID_Repeat															{$$ = makenode(IDListType, makeleaf(IDType, ($1)->string, ($1)->line, ($1)->col), $2, NULL, line, col);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode(CommaIDListType, makeleaf(IDType, ($2)->string, ($2)->line, ($2)->col), $3, NULL, line, col);} ;
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

FuncHeading: FUNCTION ID FormalParamList ':' ID  									{$$ = makenode(FuncHeadingType, makeleaf(IDType, ($2)->string, ($2)->line, ($2)->col), $3, makeleaf(IDType, ($5)->string, ($5)->line, ($5)->col), line, col);} 
	| FUNCTION ID ':' ID  															{$$ = makenode(FuncHeadingType, makeleaf(IDType, ($2)->string, ($2)->line, ($2)->col), makenode(FuncParamsListType, NULL, NULL, NULL, line, col), makeleaf(IDType, ($4)->string, ($4)->line, ($4)->col), line, col);} 
	;

FuncIdent: FUNCTION ID 																{$$ = makenode(FuncIdentType, makeleaf(IDType, ($2)->string, ($2)->line, ($2)->col), NULL, NULL, line, col);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FuncParamsListType, $2, $3, NULL, line, col);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FuncParamsListType2, $2, $3, NULL, line, col);} 
	| 																				{$$ = NULL;} 
	;

FormalParams: VAR IDList ':' ID 													{$$ = makenode(VarParamsType, $2, makeleaf(IDType, ($4)->string, ($4)->line, ($4)->col), NULL, line, col);} 
	| IDList ':' ID 																{$$ = makenode(ParamsType, $1, makeleaf(IDType, ($3)->string, ($3)->line, ($3)->col), NULL, line, col);} 
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
	| VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 										{$$ = makenode(ValParamStatType, $5, makeleaf(IDType, ($8)->string, ($8)->line, ($8)->col), NULL, line, col);} 
	| IDAssignExpr_Optional 														{$$ = $1;} 
	| WRITELN WritelnPList_Optional 												{$$ = $2;} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode(AssignStatType, makeleaf(IDType, ($1)->string, ($1)->line, ($1)->col), $3, NULL, ($1)->line, ($1)->col);} 
	| 																				{$$ = NULL;}
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WriteLnStatType, $1, NULL, NULL, ($1)->line, ($1)->col);} 
	| 																				{$$ = NULL;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL, ($2)->line, ($2)->col);} 
	| '(' STRING CommaExprString_Repeat ')' 										{$$ = makenode(WritelnPListType, makeleaf(StringType, ($2)->string, ($2)->line, ($2)->col), $3, NULL, ($2)->line, ($2)->col);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, NULL, ($2)->line, ($2)->col);}
	| ',' STRING CommaExprString_Repeat 											{$$ = makenode(WritelnPListType, makeleaf(StringType, ($2)->string, ($2)->line, ($2)->col), $3, NULL, ($2)->line, ($2)->col);}
	| 																				{$$ = NULL;}
	;

Expr: SimpleExpr 																	{$$ = makenode(ExprType, NULL, $1, NULL, ($1)->line, ($1)->col);}
	| SimpleExpr OP2 SimpleExpr 													{$$ = makenode(ExprType, $1, makeleaf(OPType, ($2)->string, ($2)->line, ($2)->col), $3, ($2)->line, ($2)->col);}
	;

SimpleExpr: SimpleExpr OP3 Term														{$$ = makenode(SimpleExprType, $1, makeleaf(OPType, ($2)->string, ($2)->line, ($2)->col), $3, ($2)->line, ($2)->col);} 
	| SimpleExpr OR Term															{$$ = makenode(SimpleExprType, $1, makeleaf(OPType, ($2)->string, ($2)->line, ($2)->col), $3, ($2)->line, ($2)->col);}
	| OP3 Term 																		{$$ = makenode(SimpleExprType, NULL, makeleaf(UnaryOPType, ($1)->string, ($1)->line, ($1)->col), $2, ($1)->line, ($1)->col);}
	| Term 																			{$$ = $1;}
	;

Term: Term OP4 Term 																{$$ = makenode(OPTermListType, $1, makeleaf(OPType, ($2)->string, ($2)->line, ($2)->col), $3, ($2)->line, ($2)->col);}
	| Term AND Term 																{$$ = makenode(OPTermListType, $1, makeleaf(OPType, ($2)->string, ($2)->line, ($2)->col), $3, ($2)->line, ($2)->col);}
	| Factor 																		{$$ = $1;}
	;

Factor: NOT Factor																	{$$ = makenode(FactorType, NULL, makeleaf(UnaryOPType, ($1)->string, ($1)->line, ($1)->col), $2, ($1)->line, ($1)->col);}
	| '(' Expr ')' 																	{$$ = $2;}
	| INTLIT 																		{$$ = makeleaf(IntType, ($1)->string, ($1)->line, ($1)->col);}
	| REALLIT 																		{$$ = makeleaf(DoubleType, ($1)->string, ($1)->line, ($1)->col);}
	| ID ParamList 																	{$$ = makenode(FactorType, NULL, makeleaf(CallType, ($1)->string, ($1)->line, ($1)->col), $2, ($1)->line, ($1)->col);}
	| ID 					 														{$$ = makeleaf(IDType, ($1)->string, ($1)->line, ($1)->col);}
	;

ParamList: '(' Expr CommaExpr_Repeat ')' 											{$$ = makenode(ParamListType, $2, $3, NULL, line, col);} ;

CommaExpr_Repeat: ',' Expr CommaExpr_Repeat 										{$$ = makenode(ExprListType, $2, $3, NULL, line, col);}
	| 																				{$$ = NULL;}
	;

%%

int main(int argc, char** args){

	errorCounter = 0;

	// read input and create Abstract Syntax Tree
	yyparse();


	if(errorCounter && !IGNORE_ERROR_COUNTER)
		return 0;

    // create Symbol Table
    errorCounter += createSymbolTable(ASTroot);
	

	// terminate program if any errors were found
	if(errorCounter && !IGNORE_ERROR_COUNTER)
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
		printAllSymbolTables( STroot );
	}

	if( !printTree && !printSymbolTable ){
		// only generate IR LLVM if no errors were found (checked beforehand) AND no printing flags were activated
		printLLVM( ASTroot );
	}

	// free all nodes in AST
	freeNode(ASTroot);
	freeSymbolTable(STroot);

	return 0;
}

void yyerror(char *s) {

     printf ("Line %d, col %d: %s: %s\n", line, (int)(col-strlen(yytext)), s, yytext);
     errorCounter++;

}



