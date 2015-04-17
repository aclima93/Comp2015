
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

int returnSonIfAlsoOfType(nodeType parent_type, nodeType parent_child_type, node* parent_child){

	if (parent_child == NULL){
		return 0;
	}

	// if parent child is of the same type as parent return it's child

	if( parent_child_type == parent_type ){

		if( !( parent_child->field1 == NULL ) )
			return 1;

	}

	// else, keep the structure

	return 0;

}

void cleanUselessNodes(node* cur_node){

	if (cur_node == NULL ){
		return ;
	}

	cleanUselessNodes(cur_node->field1);
	cleanUselessNodes(cur_node->field2);
	cleanUselessNodes(cur_node->field3);

	nodeType t = cur_node->type_of_node;
	nodeType t_child;

	if( t == StatListType ){


		if( !( cur_node->field1 == NULL ) ){

			t_child = ((node*)(cur_node->field1))->type_of_node;

			if( returnSonIfAlsoOfType( t, t_child, cur_node->field1) ){
				cur_node->field1 = ((node*)(cur_node->field1))->field1;
			}
		}


		if( !( cur_node->field2 == NULL ) ){

			t_child = ((node*)(cur_node->field2))->type_of_node;

			if( returnSonIfAlsoOfType( t, t_child, cur_node->field2) ){
				cur_node->field2 = ((node*)(cur_node->field2))->field1;
			}
		}


		if( !( cur_node->field3 == NULL ) ){

			t_child = ((node*)(cur_node->field3))->type_of_node;

			if( returnSonIfAlsoOfType( t, t_child, cur_node->field3) ){
				cur_node->field3 = ((node*)(cur_node->field3))->field1;
			}

		}

	}

	// Do the same for the children. Won't any one please think of the children?
}

char* getStatStr(nodeType t){

	switch (t){
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

void printChildren(node* cur_node){

	printNode(cur_node->field1);
	printNode(cur_node->field2);
	printNode(cur_node->field3);

}

void printNode(node* cur_node) {

	if (cur_node == NULL){
		return;
	}

	nodeType t = cur_node->type_of_node;

	if(DEBUG_TYPE){
		char* enumString[] = {"ProgType", "ProgHeadingType", "ProgBlockType", "VarPartType", "VarDeclarationListType", "VarDeclarationType", "IDListType", "CommaIDListType", "FuncPartType", "FuncDeclarationListType", "FuncDeclarationType", "FuncDefinitionType", "FuncDefinition2Type", "FuncHeadingType", "FuncIdentType", "FuncParamsListType", "VarParamsType", "ParamsType", "FuncBlockType", "StatPartType", "CompStatType", "StatListType", "EmptyStatListType", "StatType", "IfElseStatType", "WhileStatType", "RepeatStatType", "ValParamStatType", "AssignStatType", "WriteLnStatType", "WritelnPListType", "ExprType", "SimpleExprType", "OPFactorListType", "FactorType", "OPTermListType", "UnaryTermType", "TermType", "ExprListType", "ParamListType", "DoubleType", "IDType", "StringType", "OPType", "UnaryOPType", "IntType", "CallType"};
		printf("[DEBUG] type: %s\n", enumString[t]);
	}

	switch(t) {

		case ProgType:
			
			dotCounter = 0;

			printf("Program\n");
			
			printChildren(cur_node);
			
			break;

		case ProgHeadingType:
			
			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);
			
			break;


		case ProgBlockType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case VarDeclarationType:

			incrementDotCounter();

			printDots();
			printf("VarDecl\n");
			
			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncPartType:

			incrementDotCounter();

			printDots();
			printf("FuncPart\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncDeclarationType:

			incrementDotCounter();
			
			printDots();
			printf("FuncDecl\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncDefinitionType:

			incrementDotCounter();
			
			printDots();
			printf("FuncDef\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncDefinition2Type:

			incrementDotCounter();
			
			printDots();
			printf("FuncDef2\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncIdentType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printNode(cur_node->field1);
			printNode(cur_node->field2);
			printNode(cur_node->field3);

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

		case VarParamsType:
			
			printChildren(cur_node);

			break;

		case ParamsType:
			
			incrementDotCounter();

			printDots();
			printf("Params\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case FuncBlockType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;


		case StatPartType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case CompStatType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case EmptyStatListType:

			incrementDotCounter();

			printDots();
			printf("StatList\n");
			
			decrementDotCounter();

			break;

		case IfElseStatType:

			incrementDotCounter();

			char* ifelse_stat_str = getStatStr(t);

			if( !(ifelse_stat_str == NULL) ){
				printDots();
				printf("%s\n", ifelse_stat_str);
			}

			// always print the Expr in if

			printNode(cur_node->field1);

			printNode(cur_node->field2);

			printNode(cur_node->field3);

			decrementDotCounter();

			break;

		case RepeatStatType:

			/*
			// TODO: este vai dar bode no Stalist

			incrementDotCounter();

			char* repeat_stat_str = getStatStr(t);

			if( !(repeat_stat_str == NULL) ){
				printDots();
				printf("%s\n", repeat_stat_str);
			}

			// if any of the statements is empty print "StatList"

			if( !( ((node*)(cur_node->field1))->field1 == NULL) ){
				printNode(cur_node->field1);
			}
			else{

				incrementDotCounter();

				printDots();
				printf("StatList\n");
				
				decrementDotCounter();
			}

			printNode(cur_node->field2);

			decrementDotCounter();

			break;
			*/


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

		case StatType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printChildren(cur_node);

			break;

		case SimpleExprType:
		case ExprType:

			if( cur_node->field2 == NULL && cur_node->field3 == NULL ){

				// print nothing, intermediate node
				// don't even increment dot counter

				printChildren(cur_node);

			}
			else{
			
				// the operator is always printed first
				// don't call printChildren !!

				printNode(cur_node->field2);

				incrementDotCounter();

				printNode(cur_node->field1);

				printNode(cur_node->field3);
				
				decrementDotCounter();

			}

			break;

		case UnaryTermType:

			// print inner OPTermLists first
				
			if( !(cur_node->field2 == NULL) ){

				printNode(cur_node->field2);

				incrementDotCounter();

				printNode(cur_node->field1);

				printNode(cur_node->field3);
				
				decrementDotCounter();		
			
			}
			else{

				printChildren(cur_node);
				
			}

			break;

		case FactorType:
		case OPFactorListType:
		case OPTermListType: 

			// print inner OPTermLists first
				
			if( !(cur_node->field1 == NULL) ){

				printNode(cur_node->field2);

				incrementDotCounter();

				printNode(cur_node->field1);

				printNode(cur_node->field3);
				
				decrementDotCounter();		
			
			}
			else{

				printChildren(cur_node);
				
			}

			break;

		case TermType:

			printChildren(cur_node);

			break;

		case VarPartType:

			incrementDotCounter();

			printDots();
			printf("VarPart\n");

			printChildren(cur_node);

			decrementDotCounter();

			break;

		case StatListType:

			if( !(cur_node->field2 == NULL) ){

				incrementDotCounter();

				printDots();
				printf("StatList\n");

				printChildren(cur_node);
				
				decrementDotCounter();
			}
			else{

				// Don't print StatList if it only has one element, it's not a list

				printChildren(cur_node);
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

			incrementDotCounter();

			double* double_ptr = cur_node->field1;

			printDots();
			printf("RealLit(%lf)\n", double_ptr );

			decrementDotCounter();
		
			break;

		case IntType:

			incrementDotCounter();

			int* int_ptr = cur_node->field1;

			printDots();
			printf("IntLit(%d)\n", int_ptr );

			decrementDotCounter();

			break;

		case IDType:

			incrementDotCounter();

			printDots();
			printf("Id(%s)\n", (char*) cur_node->field1);

			decrementDotCounter();
		
			break;

		case StringType:

			incrementDotCounter();

			printDots();
			printf("String(%s)\n", (char*) cur_node->field1);

			decrementDotCounter();
		
			break;

		case CallType:

			incrementDotCounter();

			printDots();
			printf("Call\n");

			printChildren(cur_node);

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
				op_str = "Div";
			}
			else if( strcasecmp ( "mod", (char*) cur_node->field1 ) == 0){
				op_str = "Mod";
			}
			else if( strcasecmp ( "div", (char*) cur_node->field1 ) == 0){
				op_str = "RealDiv";
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

	return new_node;
}

node* makeleafDouble(double d){
	
	if(DEBUG){
		printf("[DEBUG] double leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = DoubleType;

	memcpy(&leaf->field1, &d, sizeof d);
	leaf->field2 = NULL;
	leaf->field3 = NULL;

	return leaf;
}

node* makeleafInt(int i){
	
	if(DEBUG){
		printf("[DEBUG] int leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = IntType;

	memcpy(&leaf->field1, &i, sizeof i);
	leaf->field2 = NULL;
	leaf->field3 = NULL;

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
