
#include "custom_structures.h"

void incrementDotCounter() {
	dotCounter+=2;
}

void decrementDotCounter() {
	dotCounter-=2;
}

void printDots() {
	int i=0;
	while(i<dotCounter) {
		printf(".");
		i++;
	}
}

void printChildrenMiddleFirst(node* cur_node){

	printNode(cur_node->field2, cur_node->type_of_node);

	incrementDotCounter();

	printNode(cur_node->field1, cur_node->type_of_node);
	printNode(cur_node->field3, cur_node->type_of_node);

	decrementDotCounter();

}

void printChildren(node* cur_node){

	printNode(cur_node->field1, cur_node->type_of_node);
	printNode(cur_node->field2, cur_node->type_of_node);
	printNode(cur_node->field3, cur_node->type_of_node);

}


// recursive function to print the AST, one node at a time

void printNode(node* cur_node, NodeType lastNodeType) {

	if( cur_node == NULL ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	int d;

	switch(t) {

		case ProgType:
			
			dotCounter = 0;

			printf("Program\n");
			
			printChildren(cur_node);
			
			break;

		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncDefinitionType:
		case FuncDefinition2Type:
		case ParamsType:
		case VarPartType:

			incrementDotCounter();
			
			printDots();
			printf("%s\n", getIndependantStr(t) );

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncHeadingType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printNode(cur_node->field1, t);

			incrementDotCounter();

			printDots();
			printf("FuncParams\n");

			decrementDotCounter();

			printNode(cur_node->field2, t);
			printNode(cur_node->field3, t);

			break;

		case FuncParamsListType:

			incrementDotCounter();

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case ProgBlockType:
		case FuncIdentType:
		case VarParamsType:
		case FuncBlockType:
		case StatType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case IfElseStatType:

			incrementDotCounter();

			char* ifelse_stat_str = getStatStr(t);

			if( !(ifelse_stat_str == NULL) ){
				printDots();
				printf("%s\n", ifelse_stat_str);
			}

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case RepeatStatType:
		case WhileStatType:
		case ValParamStatType:
		case AssignStatType:
		case WriteLnStatType:

			incrementDotCounter();

			char* stat_str = getStatStr(t);

			if( !(stat_str == NULL) ){
				printDots();
				printf("%s\n", stat_str);
			}

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case ExprType:

			if( cur_node->field2 == NULL && cur_node->field3 == NULL ){

				printChildren(cur_node);

			}
			else{
			
				// the operator is always printed first
				// don't call printChildren !!

				printChildrenMiddleFirst(cur_node);

			}

			break;

		case SimpleExprType:
		case FactorType:
		case OPTermListType: 

			// the operator is always printed first
			// don't call printChildren !!

			printChildrenMiddleFirst(cur_node);

			break;

		case StatListType:
			
			d = cur_node->numStats;
			
			if(DEBUG)
				printf("Depth: %d\n", d);
			

			// Don't print StatList if it only has one statement (it's not a real list...) 
			// or if the last node was also a StatList 
			if( d == 1 || lastNodeType == StatListType){

				printChildren(cur_node);

			}
			else if( d == 0 ){

				incrementDotCounter();

				printDots();
				printf("StatList\n");

				decrementDotCounter();

			}
			else{

				incrementDotCounter();

				printDots();
				printf("StatList\n");

				printChildren(cur_node);
				
				decrementDotCounter();
			}

			break;

		case FuncDeclarationListType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:

			// print nothing, intermediate node
			// don't even increment dot counter
			// all members are the same "depth"

			printChildren(cur_node);

			break;

		case DoubleType:
		case IntType:
		case IDType:
		case StringType:

			incrementDotCounter();

			printDots();
			printf("%s(%s)\n", getLeafStr(t), cur_node->field1 );

			decrementDotCounter();
		
			break;

		case CallType:

			incrementDotCounter();

			printDots();
			printf("Call\n");

			incrementDotCounter();
			printDots();
			printf("Id(%s)\n", (char*) cur_node->field1);
			decrementDotCounter();

			decrementDotCounter();

			break;

		case UnaryOPType:

			incrementDotCounter();

			printDots();
			printf("%s\n", getUnaryOPStr(cur_node->field1) );

			decrementDotCounter();

			break;

		case OPType:
		
			incrementDotCounter();

			printDots();
			printf("%s\n", getOPStr(cur_node->field1) );

			decrementDotCounter();

			break;

		default:
			break;
	}
}

int getNodeDepth(node* n){

	if( n == NULL)
		return 0;

	NodeType t = n->type_of_node;

	if( t == StatType || t == StatListType || t == IfElseStatType || t == RepeatStatType || t == WhileStatType || t == ValParamStatType || t == AssignStatType || t == WriteLnStatType )
		return 1;

	return 0;
}

node* makenode(NodeType t, node* f1, node* f2, node* f3){

	if(DEBUG){

		printf("\n\n[DEBUG] type: %s\n", getNodeTypeStr(t));

		if( t == StatListType ){

			if(f1 != NULL)
				printf("f1 type %s\n", getNodeTypeStr(f1->type_of_node));
			if(f2 != NULL)
				printf("f2 type %s\n", getNodeTypeStr(f2->type_of_node));
			if(f3 != NULL)
				printf("f3 type %s\n", getNodeTypeStr(f3->type_of_node));
		}
	}

	node* new_node = (node*) malloc(sizeof(node));
	new_node->type_of_node = t;

	new_node->field1 = f1;
	new_node->field2 = f2;
	new_node->field3 = f3;

	new_node->numStats = getNodeDepth(f1) + getNodeDepth(f2) + getNodeDepth(f3);



	return new_node;
}

node* makeleaf(NodeType t, char* str){

	node* leaf = (node*) malloc(sizeof(node));	

	leaf->type_of_node = t;
	leaf->field1 = str;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->numStats = 0;

	return leaf;
}

node* createTree(node* n){

	root = n;
	return root;
}

int isLeaf(node* cur_node){

	NodeType t = cur_node->type_of_node;

	if(t == DoubleType || t == IDType || t == StringType || t == OPType || t == UnaryOPType || t == IntType || t == CallType)
		return 1;

	return 0;
}

void cleanStatLists(node* cur_node){

	if( cur_node == NULL || isLeaf(cur_node) )
		return;

	if( cur_node->type_of_node == StatListType ){

		int statListChildren = 0;

		if (cur_node->field1 != NULL && ((node*)(cur_node->field1))->type_of_node == StatListType)
		{
			statListChildren++;
		}
		if (cur_node->field2 != NULL && ((node*)(cur_node->field2))->type_of_node == StatListType)
		{
			statListChildren++;
		}
		if (cur_node->field3 != NULL && ((node*)(cur_node->field3))->type_of_node == StatListType)
		{
			statListChildren++;
		}

		// we can do this if the the parent only has one child and it is of type StatList as well
		if (statListChildren == 1){

			node* temp_ref = NULL;

			// copy grandchildren, free child afterwards

			if (cur_node->field1 != NULL && ((node*)(cur_node->field1))->type_of_node == StatListType){

				temp_ref = cur_node->field1;
			}
			else if (cur_node->field2 != NULL && ((node*)(cur_node->field2))->type_of_node == StatListType){

				temp_ref = cur_node->field2;
			}
			else if (cur_node->field3 != NULL && ((node*)(cur_node->field3))->type_of_node == StatListType){

				temp_ref = cur_node->field3;
			}

			if( temp_ref != NULL){
				cur_node->field1 = temp_ref->field1;
				cur_node->field2 = temp_ref->field2;
				cur_node->field3 = temp_ref->field3;
			}

			free(temp_ref);
		}

	}

	cleanStatLists(cur_node->field1);
	cleanStatLists(cur_node->field2);
	cleanStatLists(cur_node->field3);


}

void freeNode(node* cur_node) {

	if (cur_node == NULL)
		return;

	// Dont' free these sub nodes because they weren't allocated dynamically
	if( !isLeaf(cur_node) ){

		freeNode(cur_node->field1);
		freeNode(cur_node->field2);
		freeNode(cur_node->field3);
	}

	free(cur_node);

}


/*
 * Functions that fetch strings for output & debug
 */

char* getNodeTypeStr(NodeType t){

	char* str[] = 
	{
	"ProgType", "ProgBlockType", "VarPartType", "VarDeclarationListType", "VarDeclarationType", "IDListType", "CommaIDListType", "FuncPartType", 
	"FuncDeclarationListType", "FuncDeclarationType", "FuncDefinitionType", "FuncDefinition2Type", "FuncHeadingType", "FuncIdentType", "FuncParamsListType", "VarParamsType",
	 "ParamsType", "FuncBlockType", "StatListType", "StatType", "IfElseStatType", "WhileStatType", "RepeatStatType", "ValParamStatType", "AssignStatType", 
	 "WriteLnStatType", "WritelnPListType", "ExprType", "SimpleExprType", "OPFactorListType", "FactorType", "OPTermListType", "UnaryTermType", "TermType", "ExprListType", "ParamListType", 
	 "DoubleType", "IDType", "StringType", "OPType", "UnaryOPType", "IntType", "CallType"
	};

	return str[t];
}

char* getIndependantStr(NodeType t){
	
	switch(t){
		case VarDeclarationType:
			return "VarDecl";

		case FuncPartType:
			return "FuncPart";

		case FuncDeclarationType:
			return "FuncDecl";

		case FuncDefinitionType:
			return "FuncDef";

		case FuncDefinition2Type:
			return "FuncDef2";

		case ParamsType:
			return "Params";

		case VarPartType:
			return "VarPart";

		default:
			return NULL;

	}

}

char* getLeafStr(NodeType t){

	switch(t){
		case DoubleType:
			return "RealLit";

		case IntType:
			return "IntLit";

		case IDType:
			return "Id";

		case StringType:
			return "String";

		default:
			return NULL;
	}
}

char* getStatStr(NodeType t){

	switch(t){
		case IfElseStatType:
			return "IfElse";

		case WhileStatType:
			return "While";
		
		case RepeatStatType:
			return "Repeat";
		
		case ValParamStatType:
			return "ValParam";
		
		case AssignStatType:
			return "Assign";
		
		case WriteLnStatType:
			return "WriteLn";

		default:
			return NULL;

	}
}

char* getUnaryOPStr(char* str){

	if( strcasecmp ( "+", str ) == 0){
		return "Plus";
	}
	else if( strcasecmp ( "-", str ) == 0){
		return "Minus";
	}
	else if( strcasecmp ( "not", str ) == 0){
		return "Not";
	}
	else{
		return NULL;
	}
}

char* getOPStr(char* str){

	if( strcasecmp ( "and", str ) == 0){
		return "Add";
	}
	else if( strcasecmp ( "or", str ) == 0){
		return "Or";
	}
	else if( strcasecmp ( "<>", str ) == 0){
		return "Neq";
	}
	else if( strcasecmp ( "<=", str ) == 0){
		return "Leq";
	}
	else if( strcasecmp ( ">=", str ) == 0){
		return "Geq";
	}
	else if( strcasecmp ( "<", str ) == 0){
		return "Lt";
	}
	else if( strcasecmp ( ">", str ) == 0){
		return "Gt";
	}
	else if( strcasecmp ( "=", str ) == 0){
		return "Eq";
	}
	else if( strcasecmp ( "+", str ) == 0){
		return "Add";
	}
	else if( strcasecmp ( "-", str ) == 0){
		return "Sub";
	}
	else if( strcasecmp ( "*", str ) == 0){
		return "Mul";
	}
	else if( strcasecmp ( "/", str ) == 0){
		return "RealDiv";
	}
	else if( strcasecmp ( "mod", str ) == 0){
		return "Mod";
	}
	else if( strcasecmp ( "div", str ) == 0){
		return "Div";
	}
	else{
		return NULL;
	}
}

