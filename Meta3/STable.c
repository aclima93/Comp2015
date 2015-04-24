

#include "ASTree.h"
#include "STable.h"

int createSymbolTable(node* ASTroot) {

	STroot = malloc(sizeof(table));
	semanticErrorCounter=0;

	walkAST(STroot, ASTroot);

	return semanticErrorCounter;
}

void walkAST(table* cur_scope, node* cur_node) {


	if( cur_node == NULL ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	int d;

	switch(t) {

		case ProgType:
		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncDefinitionType:
		case FuncDefinition2Type:
		case ParamsType:
		case VarPartType:
		case VarParamsType:
		case FuncHeadingType:
		case FuncParamsListType:
		case ProgBlockType:
		case FuncIdentType:
		case FuncBlockType:
		case StatType:
		case IfElseStatType:
		case RepeatStatType:
		case WhileStatType:
		case ValParamStatType:
		case AssignStatType:
		case WriteLnStatType:
		case ExprType:
		case SimpleExprType:
		case FactorType:
		case OPTermListType:
		case StatListType:
		case FuncParamsListType2:
		case FuncDeclarationListType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case CompStatType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:
		case DoubleType:
		case IntType:
		case IDType:
		case StringType:
		case CallType:
		case UnaryOPType:
		case OPType:


		default:
			break;
	}
}


int lookup_compare(const void* l, const void* r){
	// compare normaly
    const symbol* lm = l;
    const symbol* lr = r;
    return strcmp(lm->name, lr->name);
}

int insert_compare(const void* l, const void* r){
    // always insert at the end, preserving insertion order
    return -1;
}

void walker(const void *node, const VISIT which, const int depth) {
  symbol *f;
  f = *(symbol **)node;

   switch (which) {

		case preorder:
		case endorder:
		   break;
	
		case leaf:
		case postorder:
		   printf("%s\t%s", f->name, f->type);
		   if (f->flag != NULL) {
		   		printf("\t%s", f->flag);
		   		if (f->value != NULL) {
		   			printf("\t%s", f->value);
		   		}
		   }
		   break;
   }
}

symbol makeSymbol(char* n, PredefType t, PredefFlag f, char* v){

	symbol* s = malloc(sizeof(symbol));

    s->name = n;
    s->type = t;
    s->flag = f;
    s->value = v;

    return s;
}

void insertSymbol(symbol* s, void* table){
    tsearch(s, &table, insert_compare); // if it isn't found with tsearch it is inserted
}

symbol lookupSymbol(symbol* s, void* table){
	return tfind(s, &table, lookup_compare); //return NULL if element isn't found
}

void printTable(void* table){
    twalk(table, walker); // prints all nodes in inorder
}








