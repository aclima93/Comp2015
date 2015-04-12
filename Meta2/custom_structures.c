
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

void printList(node* cur_node) {
	node* next_node = ((node*)(cur_node->field1))->next;

	while(next_node != NULL) {
		printDots();
		printNode(next_node->field1);
		next_node = ((node*)(next_node->field1))->next;
	}
}

void printNode(node* cur_node) {

	nodeType t = cur_node->type_of_node;

	if(DEBUG){
		printf("[DEBUG] type: %d", t);
	}

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
			printNode(cur_node->field1);
			decrementDotCounter();
			
			break;


		case ProgBlockType:

			printDots();
			printf("VarPart\n");
			if (cur_node->field1 != NULL) {
				printNode(cur_node->field1);
			}

			printDots();
			printf("FuncPart\n");
			if (cur_node->field2 != NULL) {
				printNode(cur_node->field2);
			}

			printDots();
			printf("StatList\n");
			if (cur_node->field3 != NULL) {
				printNode(cur_node->field3);
			}

			break;

		case VarDeclarationType:

			incrementDotCounter();
			printDots();
			printf("VarDecl\n");
			
			incrementDotCounter();
			printDots();
			printNode(cur_node->field1);

			node* next_node = ((node*)(cur_node->field1))->next;

			printList(cur_node);

			printDots();
			printNode(cur_node->field2);

			decrementDotCounter();

			decrementDotCounter();

			break;

		case FuncPartType:
			incrementDotCounter();
			printDots();
			printf("FuncPart\n");
			printNode(cur_node->field1);
			decrementDotCounter();
			break;

		case FuncDeclarationType:

			incrementDotCounter();
			
			printNode(cur_node->field1);

			if (cur_node->field2!=NULL) {
				printNode(cur_node->field2);
			}

			decrementDotCounter();

			break;


		case FuncHeadingType:

			incrementDotCounter();
			

			printNode(cur_node->field1);
			if (cur_node->field3 !=NULL) {
				printList(cur_node->field2);
				printNode(cur_node->field3);
			}
			else {
				printNode(cur_node->field2);
			}

			decrementDotCounter();

			break;

		case FuncIdentType:
			incrementDotCounter();

			printNode(cur_node->field1);
			
			decrementDotCounter();

			break;

		case FormalParamsType:
			incrementDotCounter();
			
			printList(cur_node->field1);
			printNode(cur_node->field2);
			decrementDotCounter();

			break;

		case FuncBlockType:
			incrementDotCounter();
			
			printNode(cur_node->field1);
			printNode(cur_node->field2);
			decrementDotCounter();

			break;


		case StatPartType:
			incrementDotCounter();
			
			printList(cur_node->field1);

			decrementDotCounter();

			break;

		case CompStatType:
			incrementDotCounter();
			
			printList(cur_node->field1);
			decrementDotCounter();

			break;

		case StatType:
			incrementDotCounter();
			if ((cur_node->field1)->type_of_node == WritelnPListType) {
				printList(cur_node->field1);
				break;
			}

			if ((cur_node->field1)->type_of_node == StatListType) {
				printList(cur_node->field1);
				printNode(cur_node->field2);
				break;
			}

			printNode(cur_node->field1);
			if (cur_node->field2 != NULL)
				printNode(cur_node->field2);

			if (cur_node->field3 !=NULL) {
				printNode(cur_node->field3);
			}
			decrementDotCounter();

			break;
		case ExprType:
			incrementDotCounter();

			printNode(cur_node->field1);
			if (cur_node->field2 != NULL)
				printNode(cur_node->field2);

			if (cur_node->field3 !=NULL) {
				printNode(cur_node->field3);
			}
			decrementDotCounter();

			break;


		case VarPartType:
			incrementDotCounter();

			printList(cur_node->field1);
			decrementDotCounter();

			break;

		
		case FuncDeclarationListType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case FormalParamsListType:
		case StatListType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:

			incrementDotCounter();

			printList(cur_node->field1);
			decrementDotCounter();

			break;


		case DoubleType:
			printDots();
			//FIXME: fix this shit, yo
			//printf("ID(%lf)\n", (double) cur_node->field1);
			break;

		case StringType:
			printDots();
			printf("ID(%s)\n", (char*) cur_node->field1);
			break;

		case IntType:
			printDots();
			printf("ID(%d)\n", (int) cur_node->field1);
			break;

		case OPType:
			break;

		default:
			// do nothing, bro
			break;
	}
}


node* makenode(nodeType t, node* f1, node* f2, node* f3){

	node* new_node = malloc(sizeof(node*));
	new_node->type_of_node = t;

	if(DEBUG){
		printf("[DEBUG] type: %d", t);
	}

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


		case DoubleType:
		case StringType:
		case OPType:
		case IntType:
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

node* createTree(node* n){

	if(DEBUG){
		printf("[DEBUG] type: %d", n->type_of_node);
	}

	root = n;
	return root;
}
