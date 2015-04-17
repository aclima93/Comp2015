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

%token <string> OP2
%token <string> OR
%token <string> OP3
%token <string> AND
%token <string> OP4
%token <string> NOT

%right THEN
%right ELSE

%nonassoc OP2
%nonassoc OR
%left OP3
%nonassoc AND
%left OP4
%nonassoc NOT


%type <node_pointer> Prog ProgHeading ProgBlock VarPart VarDeclaration IDList FuncPart FuncDeclaration FuncHeading FuncIdent FormalParamList FormalParams FuncBlock StatPart CompStat StatList Stat WritelnPList Expr SimpleExpr Term Factor ParamList 
%type <node_pointer> VarDeclarationSemic_Repeat CommaID_Repeat FuncDeclaration_Repeat SemicFormalParams_Repeat SemicStat_Repeat IDAssignExpr_Optional WritelnPList_Optional CommaExprString_Repeat CommaExpr_Repeat OPTerm_Repeat OPFactor_Repeat

%% 

Prog:  ProgHeading ';' ProgBlock '.' 												{$$ = createTree(makenode(ProgType, $1, $3, NULL));} ;

ProgHeading: PROGRAM ID '(' OUTPUT ')' 												{$$ = makenode(ProgHeadingType, makeleafID($2), NULL, NULL);} ;

ProgBlock: VarPart FuncPart StatPart 												{$$ = makenode(ProgBlockType, $1, $2, $3);} ;

VarPart: VAR VarDeclaration ';' VarDeclarationSemic_Repeat 							{$$ = makenode(VarPartType, $2, $4, NULL);}
	| 																				{$$ = NULL;}
	;

VarDeclarationSemic_Repeat: VarDeclaration ';' VarDeclarationSemic_Repeat			{$$ = makenode(VarDeclarationListType, $1, $3, NULL);}
	|																				{$$ = NULL;} 
	;

VarDeclaration: IDList ':' ID														{$$ = makenode(VarDeclarationType, $1, makeleafID($3), NULL);} ;

IDList: ID CommaID_Repeat															{$$ = makenode(IDListType, makeleafID($1), $2, NULL);} ;

CommaID_Repeat: ',' ID CommaID_Repeat												{$$ = makenode(CommaIDListType, makeleafID($2), $3, NULL);} ;
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

FuncHeading: FUNCTION ID FormalParamList ':' ID  									{$$ = makenode(FuncHeadingType, makeleafID($2), $3, makeleafID($5));} 
	| FUNCTION ID ':' ID  															{$$ = makenode(FuncHeadingType, makeleafID($2), makeleafID($4), NULL);} 
	;

FuncIdent: FUNCTION ID 																{$$ = makenode(FuncIdentType, makeleafID($2), NULL, NULL);} ;

FormalParamList: '(' FormalParams SemicFormalParams_Repeat ')'						{$$ = makenode(FuncParamsListType, $2, $3, NULL);} ;

SemicFormalParams_Repeat: ';' FormalParams SemicFormalParams_Repeat					{$$ = makenode(FuncParamsListType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

FormalParams: VAR IDList ':' ID 													{$$ = makenode(VarParamsType, $2, makeleafID($4), NULL);} 
	| IDList ':' ID 																{$$ = makenode(ParamsType, $1, makeleafID($3), NULL);} 
	;

FuncBlock: VarPart StatPart															{$$ = makenode(FuncBlockType, $1, $2, NULL);} ;

StatPart: CompStat 																	{$$ = makenode(StatPartType, $1, NULL, NULL);} ;

CompStat: BEGIN_token StatList END													{$$ = makenode(CompStatType, $2, NULL, NULL);} ;

StatList: Stat SemicStat_Repeat 													{$$ = makenode(StatListType, $1, $2, NULL);} ;

SemicStat_Repeat: ';' Stat SemicStat_Repeat 										{$$ = makenode(StatType, $2, $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

Stat: CompStat 																		{$$ = makenode(StatType, $1, NULL, NULL);} 
	|	IF Expr THEN Stat ELSE Stat 												{$$ = makenode(IfElseStatType, $2, $4, $6);} 
	|	IF Expr THEN Stat 															{$$ = makenode(IfElseStatType, $2, $4, makenode(StatListType, NULL, NULL, NULL));} 
	|	WHILE Expr DO Stat 															{$$ = makenode(WhileStatType, $2, $4, NULL);} 
	|	REPEAT StatList UNTIL Expr 													{$$ = makenode(RepeatStatType, $2, $4, NULL);} 
	|	VAL '(' PARAMSTR '(' Expr ')' ',' ID ')' 									{$$ = makenode(ValParamStatType, $5, makeleafID($8), NULL);} 
	|	IDAssignExpr_Optional 														{$$ = makenode(StatType, $1, NULL, NULL);} 
	|	WRITELN WritelnPList_Optional 												{$$ = makenode(StatType, $2, NULL, NULL);} 
	;

IDAssignExpr_Optional: ID ASSIGN Expr 												{$$ = makenode(AssignStatType, makeleafID($1), $3, NULL);} 
	| 																				{$$ = NULL;} 
	;

WritelnPList_Optional: WritelnPList 												{$$ = makenode(WriteLnStatType, $1, NULL, NULL);} 
	| 																				{$$ = NULL;}
	;

WritelnPList: '(' Expr CommaExprString_Repeat ')' 									{$$ = makenode(WritelnPListType, $2, $3, NULL);} 
	| '(' STRING CommaExprString_Repeat ')' 										{$$ = makenode(WritelnPListType, makeleafString($2), $3, NULL);} 
	;

CommaExprString_Repeat: ',' Expr CommaExprString_Repeat 							{$$ = makenode(WritelnPListType, $2, $3, NULL);}
	| ',' STRING CommaExprString_Repeat 											{$$ = makenode(WritelnPListType, makeleafString($2), $3, NULL);}
	| 																				{$$ = NULL;}
	;

Expr: SimpleExpr 																	{$$ = makenode(ExprType, $1, NULL, NULL);}
	| SimpleExpr OP2 SimpleExpr 													{$$ = makenode(ExprType, $1, makeleafOP($2), $3);}
	;

SimpleExpr: OP3 Term OPTerm_Repeat													{$$ = makenode(SimpleExprType, makeleafUnaryOP($1), $2, $3);} 
	| Term OPTerm_Repeat															{$$ = makenode(SimpleExprType, NULL, $1, $2);}
	;

OPTerm_Repeat: OP3 Term OPTerm_Repeat												{$$ = makenode(OPTermListType, makeleafOP($1), $2, $3);} 
	| OR Term OPTerm_Repeat															{$$ = makenode(OPTermListType, makeleafOP($1), $2, $3);} 
	| 																				{$$ = NULL;}
	;

Term: Factor OPFactor_Repeat														{$$ = makenode(TermType, $1, $2, NULL);} ;

OPFactor_Repeat: OP4 Factor OPFactor_Repeat											{$$ = makenode(OPFactorListType, makeleafOP($1), $2, $3);}
	| AND Factor OPFactor_Repeat													{$$ = makenode(OPFactorListType, makeleafOP($1), $2, $3);}
	|																				{$$ = NULL;}
	;

Factor: NOT Factor																	{$$ = makenode(FactorType, NULL, makeleafUnaryOP($1), $2);}
	| '(' Expr ')' 																	{$$ = makenode(FactorType, NULL, $2, NULL);}
	| INTLIT 																		{$$ = makeleafInt($1);}
	| REALLIT 																		{$$ = makeleafDouble($1);}
	| ID ParamList 																	{$$ = makenode(FactorType, NULL, makeleafCall($1), $2);}
	| ID 					 														{$$ = makeleafID($1);}
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

    if(printTree){
		printNode(root);
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



