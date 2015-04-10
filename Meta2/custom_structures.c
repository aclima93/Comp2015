
#include "custom_structures.h"

node* makenode(nodeType t, node* f1, node* f2, node* f3){

	node* new_node = malloc(sizeof(node*));
	leaf->type_of_node = t;

	switch (t) {

		case ProgType:
		case ProgHeadingType:
		case ProgBlockType:
		case VarDeclarationType:

			leaf->field1 = f1;
			leaf->field2 = f2;
			leaf->field3 = f3;
			break;

		case VarPartType:
		case VarDeclarationListType:
		case IDListType:

			f1->next = f2;

			leaf->field1 = f1;
			leaf->field2 = NULL;
			leaf->field3 = NULL;
			break;

		case CommaIDListType:

		break;

		case FuncPartType:

		break;

		case FuncDeclarationListType:

		break;

		case FuncDeclarationType:

		break;

		case FuncHeadingType:

		break;

		case FuncIdentType:

		break;

		case FormalParamsListType:

		break;

		case FormalParamsType:

		break;

		case FuncBlockType:

		break;

		case StatPartType:

		break;

		case CompStatType:

		break;

		case StatListType:

		break;

		case StatType:

		break;

		case WritelnPListType:

		break;

		case ExprType:

		break;

		case OPType:

		break;

		case IntType:

		break;

		case StringType:

		break;

		case DoubleType:

		break;

		case ParamListType:

		break;

		default:
			return NULL;
	}



	return new_node;
}

node* makeleafInt(int i){
	
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

node* makeleafDouble(double d){
	node* leaf = malloc(sizeof(node*));
	
	leaf->type_of_node = DoubleType;
	leaf->field1 = d;
	leaf->field2 = NULL;
	leaf->field3 = NULL;

	return leaf;
}