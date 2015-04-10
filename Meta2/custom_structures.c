
#include "custom_structures.h"

node* makenode(nodeType t, node* f1, node* f2, node* f3){
	return NULL;
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