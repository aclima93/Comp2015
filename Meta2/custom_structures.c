
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

	if (cur_node == NULL){
		return;
	}

	node* next_node = cur_node;

	while(next_node != NULL) {

		printDots();
		printNode(next_node->field1);

		next_node = (node*) next_node->next;
	}
	
}

void printNode(node* cur_node) {

	if (cur_node == NULL){
		return;
	}

	nodeType t = cur_node->type_of_node;

	if(DEBUG){
		printf("[DEBUG] type: %d\n", t);
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

			incrementDotCounter();

			printDots();
			printf("VarPart\n");
			printNode(cur_node->field1);
			
			printDots();
			printf("FuncPart\n");
			printNode(cur_node->field2);
		
			printDots();
			printf("StatList\n");
			printNode(cur_node->field3);
	
			decrementDotCounter();

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
			printNode(cur_node->field2);

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

			if (((node*)(cur_node->field1))->type_of_node == WritelnPListType) {
				printList(cur_node->field1);
				break;
			}

			if (((node*)(cur_node->field1))->type_of_node == StatListType) {
				printList(cur_node->field1);
				printNode(cur_node->field2);
				break;
			}

			printNode(cur_node->field1);
			printNode(cur_node->field2);
			printNode(cur_node->field3);

			decrementDotCounter();

			break;

		case ExprType:

			incrementDotCounter();

			printNode(cur_node->field1);
			printNode(cur_node->field2);
			printNode(cur_node->field3);
			
			decrementDotCounter();

			break;

		case VarPartType:

			incrementDotCounter();

			printNode(cur_node->field1);
			printNode(cur_node->field2);
			printNode(cur_node->field3);

			decrementDotCounter();

			/*
			incrementDotCounter();
			printList(cur_node->field1);
			decrementDotCounter();
			*/

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

			//incrementDotCounter();

			printList(cur_node->field1);

			//decrementDotCounter();

			break;

		case DoubleType:

			printDots();
			printf("RealLit(%lf)\n", (double) ( *( (double*) cur_node->field1) ) );
		
			break;

		case StringType:

			printDots();
			printf("ID(%s)\n", (char*) cur_node->field1);
		
			break;

		case IntType:
		
			printDots();
			printf("IntLit(%d)\n", (int) ( *( (int*) cur_node->field1) ) );
		
			break;

		case UnaryOPType:

			printDots();

			char* unary_op_str;

			if( strcasecmp ( "+", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Plus";
			}
			else if( strcasecmp ( "-", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Minus";
			}
			else if( strcasecmp ( "!", (char*) cur_node->field1 ) == 0){
				unary_op_str = "Not";
			}

			printf("%s\n", unary_op_str );
			break;

		case OPType:
		
			printDots();

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

			printf("%s\n", op_str );
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
			new_node->next = NULL;

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
			new_node->next = f1;
			
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
	
	if(DEBUG){
		printf("[DEBUG] int leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = IntType;
	leaf->field1 = i;
	leaf->field2 = NULL;
	leaf->field3 = NULL;

	return leaf;
}

node* makeleafUnaryOP(char* o){

	if(DEBUG){
		printf("[DEBUG] unary op leaf\n");
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
		printf("[DEBUG] op leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = OPType;
	leaf->field1 = o;
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

node* makeleafDouble(double* d){
	
	if(DEBUG){
		printf("[DEBUG] double leaf\n");
	}

	node* leaf = (node*) malloc(sizeof(node));
	
	leaf->type_of_node = DoubleType;
	leaf->field1 = d;
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

void freeNode(node* cur_node) {

	if (cur_node == NULL)
		return;

	freeNode(cur_node->field1);
	freeNode(cur_node->field2);
	freeNode(cur_node->field3);
	freeNode(cur_node->next);

}
