
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

void printNode(node* cur_node) {

	nodeType t = cur_node->type_of_node;

	switch(t) {

		case ProgType:
			
			dotCounter = 0;
			printf("Program\n");
			printNode(cur_node->field1);
			printNode(cur_node->field2);
			
			break;

		case ProgHeadingType:
			
			incrementDotCounter();
			printDots();
			printf("ID(%s)\n", (cur_node->field1)->field1);
			decrementDotCounter();
			
			break;


		case ProgBlockType:

			printDots();
			printf("VarPart");
			if (cur_node->field1 != NULL) {
				printNode(cur_node->field1);
			}

			printDots();
			printf("FuncPart");
			if (cur_node->field2 != NULL) {
				printNode(cur_node->field2);
			}

			printDots();
			printf("StatList");
			if (cur_node->field3 != NULL) {
				printNode(cur_node->field3);
			}

			break;

		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncHeadingType:
		case FuncIdentType:
		case FormalParamsType:
		case FuncBlockType:
		case StatPartType:
		case CompStatType:
		case StatType:
		case ExprType:
		case VarPartType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case FuncDeclarationListType:
		case FormalParamsListType:
		case StatListType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:
	}
}


node* makenode(nodeType t, node* f1, node* f2, node* f3){

	node* new_node = malloc(sizeof(node*));
	new_node->type_of_node = t;

	switch (t) {

		case ProgType:
		case ProgHeadingType:
		case ProgBlockType:
		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncHeadingType:
		case FuncIdentType:
		case FormalParamsType:
		case FuncBlockType:
		case StatPartType:
		case CompStatType:
		case StatType:
		case ExprType:

			new_node->field1 = f1;
			new_node->field2 = f2;
			new_node->field3 = f3;
			break;

		case VarPartType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case FuncDeclarationListType:
		case FormalParamsListType:
		case StatListType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:

			f1->next = f2;

			new_node->field1 = f1;
			new_node->field2 = NULL;
			new_node->field3 = NULL;
			break;

		default:
			return NULL;
	}



	return new_node;
}

node* makeleafInt(int* i){
	
	node* leaf = malloc(sizeof(node*));
	
	leaf->type_of_node = IntType;
	leaf->field1 = i;
	leaf->field2 = NULL;
	leaf->field3 = NULL;

	return leaf;
}

node* makeleafOP(char* o){

	node* leaf = malloc(sizeof(node*));
	
	leaf->type_of_node = OPType;
	strcpy(leaf->field1, o);
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	
	return leaf;
}

node* makeleafString(char* s){

	node* leaf = malloc(sizeof(node*));
	
	leaf->type_of_node = StringType;
	strcpy(leaf->field1, s);
	leaf->field2 = NULL;
	leaf->field3 = NULL;
	
	return leaf;
}

node* makeleafDouble(double* d){
	
	node* leaf = malloc(sizeof(node*));
	
	leaf->type_of_node = DoubleType;
	leaf->field1 = d;
	leaf->field2 = NULL;
	leaf->field3 = NULL;

	return leaf;
}