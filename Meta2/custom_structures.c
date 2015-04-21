
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

char* getIndependantStr(nodeType t){
	
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

		default:
			return NULL;

	}

}

char* getLeafStr(nodeType t){

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

char* getStatStr(nodeType t){

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

void printChildrenMiddleFirst(node* cur_node){

	printNode(cur_node->field2);

	incrementDotCounter();

	printNode(cur_node->field1);
	printNode(cur_node->field3);

	decrementDotCounter();

}

void printChildren(node* cur_node){

	printNode(cur_node->field1);
	printNode(cur_node->field2);
	printNode(cur_node->field3);

}

/*
void printStatListElements(node* cur_node){

	node* element = cur_node;

	while( !(element == NULL) ){

		//printf("element addr: %d\n", element);

		// don't print superfluous StatLists 
		
		if( element->type_of_node != StatListType ){
			printNode(element);
		}

		element = element->depth;
	}

}

int depthStatList(node* cur_node){

	node* element = cur_node;
	int d = 0;

	while( !(element == NULL) ){
		
		d++;
		element = element->depth;
	}

	return d;

}
*/

void printNode(node* cur_node) {

	if( cur_node == NULL ){
		return;
	}

	nodeType t = cur_node->type_of_node;
	int d;

	/*
	if(DEBUG_TYPE){
		char* enumString[] = {"ProgType", "ProgHeadingType", "ProgBlockType", "VarPartType", "VarDeclarationListType", "VarDeclarationType", "IDListType", "CommaIDListType", "FuncPartType", "FuncDeclarationListType", "FuncDeclarationType", "FuncDefinitionType", "FuncDefinition2Type", "FuncHeadingType", "FuncIdentType", "FuncParamsListType", "VarParamsType", "ParamsType", "FuncBlockType", "StatPartType", "CompStatType", "StatListType", "EmptyStatListType", "StatType", "IfElseStatType", "WhileStatType", "RepeatStatType", "ValParamStatType", "AssignStatType", "WriteLnStatType", "WritelnPListType", "ExprType", "SimpleExprType", "OPFactorListType", "FactorType", "OPTermListType", "UnaryTermType", "TermType", "ExprListType", "ParamListType", "DoubleType", "IDType", "StringType", "OPType", "UnaryOPType", "IntType", "CallType"};
		printf("[DEBUG] type: %s\n", enumString[t]);
	}
	*/

	switch(t) {

		case ProgType:
			
			dotCounter = 0;

			printf("Program\n");
			
			printChildren(cur_node);
			
			break;

		case ProgHeadingType:
		case ProgBlockType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncDefinitionType:
		case FuncDefinition2Type:
		case ParamsType:

			incrementDotCounter();
			
			printDots();
			printf("%s\n", getIndependantStr(cur_node->type_of_node) );

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncHeadingType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printNode(cur_node->field1);

			incrementDotCounter();

			printDots();
			printf("FuncParams\n");

			decrementDotCounter();

			printNode(cur_node->field2);
			printNode(cur_node->field3);

			break;

		case FuncParamsListType:

			incrementDotCounter();

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncIdentType:
		case VarParamsType:
		case FuncBlockType:
		case StatPartType:
		case CompStatType:
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

		case SimpleExprType:

			// the operator is always printed first
			// don't call printChildren !!

			printChildrenMiddleFirst(cur_node);

			break;

		case ExprType:

			if( cur_node->field2 == NULL && cur_node->field3 == NULL ){

				// print nothing, intermediate node
				// don't even increment dot counter

				printChildren(cur_node);

			}
			else{
			
				// the operator is always printed first
				// don't call printChildren !!

				printChildrenMiddleFirst(cur_node);

			}

			break;

		case FactorType:

			printChildrenMiddleFirst(cur_node);

			break;

		case OPTermListType: 

			// print inner OPTermLists first
				
			if( !(cur_node->field1 == NULL) ){

				printChildrenMiddleFirst(cur_node);
			
			}
			else{

				printChildren(cur_node);
				
			}

			break;

		case VarPartType:

			incrementDotCounter();

			printDots();
			printf("VarPart\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case StatListType:
			
			d = cur_node->depth;//depthStatList(cur_node);

			if(DEBUG)
				printf("Depth: %d\n", d);

			if( d == 1){

				// Don't print StatList if it only has one element, it's not a list
				//printStatListElements(cur_node);
				printChildren(cur_node);

			}
			else if( d == 0 ){

				incrementDotCounter();

				printDots();
				printf("StatList\n");
				
				printChildren(cur_node);

				decrementDotCounter();

			}
			else{

				incrementDotCounter();

				printDots();
				printf("StatList\n");

				//printStatListElements(cur_node);
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
			printf("%s(%s)\n", getLeafStr(cur_node->type_of_node), cur_node->field1 );

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

			char* unary_op_str;

			if( strcasecmp ( "+", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Plus";
			}
			else if( strcasecmp ( "-", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Minus";
			}
			else if( strcasecmp ( "not", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Not";
			}
			else{
				unary_op_str = NULL;
			}

			if( !(unary_op_str == NULL) ){
				printDots();
				printf("%s\n", unary_op_str );
			}

			decrementDotCounter();

			// because we can't find a fucking reason for this not to work
			/*
			if( strcmp ( "Not", unary_op_str ) == 0){
				incrementDotCounter();
			}
			*/

			break;

		case OPType:
		
			incrementDotCounter();

			char* op_str;

			if( strcasecmp ( "and", (char*) cur_node->field1 ) == 0){
				op_str = "Add";
			}
			else if( strcasecmp ( "or", (char*) cur_node->field1 ) == 0){
				op_str = "Or";
			}
			else if( strcasecmp ( "<>", (char*) cur_node->field1 ) == 0){
				op_str = "Neq";
			}
			else if( strcasecmp ( "<=", (char*) cur_node->field1 ) == 0){
				op_str = "Leq";
			}
			else if( strcasecmp ( ">=", (char*) cur_node->field1 ) == 0){
				op_str = "Geq";
			}
			else if( strcasecmp ( "<", (char*) cur_node->field1 ) == 0){
				op_str = "Lt";
			}
			else if( strcasecmp ( ">", (char*) cur_node->field1 ) == 0){
				op_str = "Gt";
			}
			else if( strcasecmp ( "=", (char*) cur_node->field1 ) == 0){
				op_str = "Eq";
			}
			else if( strcasecmp ( "+", (char*) cur_node->field1 ) == 0){
				op_str = "Add";
			}
			else if( strcasecmp ( "-", (char*) cur_node->field1 ) == 0){
				op_str = "Sub";
			}
			else if( strcasecmp ( "*", (char*) cur_node->field1 ) == 0){
				op_str = "Mul";
			}
			else if( strcasecmp ( "/", (char*) cur_node->field1 ) == 0){
				op_str = "RealDiv";
			}
			else if( strcasecmp ( "mod", (char*) cur_node->field1 ) == 0){
				op_str = "Mod";
			}
			else if( strcasecmp ( "div", (char*) cur_node->field1 ) == 0){
				op_str = "Div";
			}
			else{
				op_str = NULL;
			}

			if( !(op_str == NULL) ){
				printDots();
				printf("%s\n", op_str );
			}

			decrementDotCounter();

			break;

		default:
			break;
	}
}


node* makenode(nodeType t, node* f1, node* f2, node* f3){

	if(DEBUG){
		printf("[DEBUG] type: %d\n", t);
	}

	node* new_node = (node*) malloc(sizeof(node));
	new_node->type_of_node = t;

	new_node->field1 = f1;
	new_node->field2 = f2;
	new_node->field3 = f3;
	new_node->depth = 0;

	return new_node;
}

node* makeleafDouble(char* d){
	
	if(DEBUG){
		printf("[DEBUG] double leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = DoubleType;
	leaf->field1 = d;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;

	return leaf;
}

node* makeleafInt(char* i){
	
	if(DEBUG){
		printf("[DEBUG] int leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = IntType;
	leaf->field1 = i;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;

	return leaf;
}

node* makeleafUnaryOP(char* o){

	if(DEBUG){
		printf("[DEBUG] unary op leaf %s\n", o);
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = UnaryOPType;
	leaf->field1 = o;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;
	
	return leaf;
}

node* makeleafOP(char* o){

	if(DEBUG){
		printf("[DEBUG] op leaf %s\n", o);
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = OPType;
	leaf->field1 = o;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;
	
	return leaf;
}

node* makeleafID(char* s){

	if(DEBUG){
		printf("[DEBUG] id leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = IDType;
	leaf->field1 = s;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;
	
	return leaf;
}

node* makeleafString(char* s){

	if(DEBUG){
		printf("[DEBUG] string leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = StringType;
	leaf->field1 = s;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;
	
	return leaf;
}

node* makeleafCall(char* s) {

	if(DEBUG){
		printf("[DEBUG] call leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = CallType;
	leaf->field1 = s;
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	leaf->depth = 0;
	
	return leaf;

}

node* createTree(node* n){

	if(DEBUG){
		printf("[DEBUG] Tree Root\n");
	}

	root = n;
	return root;
}

int isLeaf(node* cur_node){

	nodeType t = cur_node->type_of_node;

	if(t == DoubleType || t == IDType || t == StringType || t == OPType || t == UnaryOPType || t == IntType || t == CallType)
		return 1;

	return 0;
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
