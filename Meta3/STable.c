

#include "ASTree.h"
#include "STable.h"

int createSymbolTable(node* ASTroot) {

	semanticErrorCounter = 0;

	STroot = makeTable(outerTable);

	insertSymbol(makeSymbol("boolean", _type_, constantFlag, "_boolean_"), STroot);
	insertSymbol(makeSymbol("integer", _type_, constantFlag, "_integer_"), STroot);
	insertSymbol(makeSymbol("real", _type_, constantFlag, "_real_"), STroot);
	insertSymbol(makeSymbol("false", _boolean_, constantFlag, "_false_"), STroot);
	insertSymbol(makeSymbol("true", _boolean_, constantFlag, "_true_"), STroot);
	insertSymbol(makeSymbol("paramcount", _function_, NULLFlag, NULL), STroot);
	insertSymbol(makeSymbol("program", _program_, NULLFlag, NULL), STroot);

	/* f é a tabela da funcao paramcount */
	table* f = makeTable(functionTable);
	insertSymbol(makeSymbol("paramcount", _integer_, returnFlag, NULL), f);
	STroot->nextTable = f;	

	table* p = makeTable(programTable);
	f->nextTable = p;

	// start walk through AST, creating tables, inserting symbols and verifying scope visibility and type integrity
	walkASTNode(p, ASTroot, NULL);

	return semanticErrorCounter;
}

void walkASTNodeChildren(table* cur_scope, node* cur_node, node* cur_declaration_type) {

	walkASTNode(cur_scope, cur_node->field1, cur_declaration_type);
	walkASTNode(cur_scope, cur_node->field2, cur_declaration_type);
	walkASTNode(cur_scope, cur_node->field3, cur_declaration_type);
}

void walkASTNode(table* cur_scope, node* cur_node, node* cur_declaration_type) {


	if( cur_node == NULL || isLeaf(cur_node) ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	switch(t) {

		case VarDeclarationType:
		case VarParamsType:
		case ParamsType:

			/* passar o novo tipo das variáveis que se vão seguir*/
			walkASTNodeChildren(cur_scope, cur_node, cur_node->field2);

			break;

		case IDListType:
		case CommaIDListType:

			/* pegar em cur_node->field1 e criar um simbolo em cur_scope do tipo cur_declaration_type */
			if (cur_node->field1 != NULL) {

				//get name from id node
				node* variable = cur_node->field1;
				char* name = variable->field1;

				//get type string from current type of declarations
				if (cur_declaration_type != NULL) {
					char* type_str = cur_declaration_type->field1;

					symbol* s = makeSymbol(name, getPredefTypeFromStr(type_str), NULLFlag, NULL);

					insertSymbol(s, cur_scope);
				}

			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type);

			break;

		case FuncHeadingType:
		case FuncIdentType:

			/* adicionar funcao ao scope onde estamos */
			if( cur_node->field1 != NULL){
				symbol *s = makeSymbol(cur_node->field1, _function_, NULLFlag, NULL);
				insertSymbol(s, cur_scope);
			}

			/* criar tabela de simbolos (scope) para a nova funcao */
			cur_scope->nextTable = makeTable(functionTable);
			table* new_table = cur_scope->nextTable;

			symbol* sym;
			if (cur_node->field3 != NULL) {
				char* returnTypeStr = cur_node->field3;
				sym = makeSymbol(cur_node->field1, getPredefTypeFromStr(returnTypeStr), returnFlag, NULL);
			}
			else{
				sym = makeSymbol(cur_node->field1, _NULL_, NULLFlag, NULL);	
			}

			insertSymbol(sym, new_table);

			walkASTNodeChildren(new_table, cur_node, cur_declaration_type);

			break;


		case ProgType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncDefinitionType:
		case FuncDefinition2Type:
		case VarPartType:
		case FuncParamsListType:
		case ProgBlockType:
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

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type);

			break;
	}
}


PredefType getPredefTypeFromStr(char* t) {
	if(strcasecmp(t,"boolean" ) == 0)
		return _boolean_;
	else if(strcasecmp(t,"integer" ) == 0)
		return _integer_;
	else if(strcasecmp(t,"real" ) == 0)
		return _real_;
	else if(strcasecmp(t,"true" ) == 0)
		return _true_;
	else if(strcasecmp(t,"false" ) == 0)
		return _false_;
	else
		return _NULL_;
}

char* getPredefTypeStr(PredefType t) {
	char* str[] = {
		"_boolean_", "_integer_", "_real_", "_function_", "_program_", "_type_", "_true_", "_false_", NULL
	};
	return str[t];
}

char* getPredefFlagStr(PredefFlag f) {
	char* str[] = {
		"constant", "return", "param", "varparam", NULL
	};
	return str[f];
}

 table* makeTable(PredefTable t) {

 	table* new_table = malloc(sizeof(table));

 	new_table->type = t;
 	new_table->symbol_variables = NULL;
 	new_table->nextTable = NULL;

 	return new_table;
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

  symbol *s;
  s = *(symbol **)node;

   switch (which) {

		case preorder:
		case endorder:
		   break;
	
		case leaf:
		case postorder:
			printSymbol(s);
			break;
   }
}

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v){

	symbol* s = malloc(sizeof(symbol));

    s->name = n;
    s->type = t;
    s->flag = f;
    s->value = v;

    return s;
}

void insertSymbol(symbol* s, table* t){

	printf("\n\nSymbol\n");
	printSymbol(s);

	printf("\nBefore insertion\n");
	printTable(t);

	void* table = t->symbol_variables;
    tsearch(s, &table, insert_compare); // if it isn't found with tsearch it is inserted

	printf("\nAfter insertion\n");
	printTable(t);
}

symbol* lookupSymbol(symbol* s, table* t){
	void* table = t->symbol_variables;
	return tfind(s, &table, lookup_compare); //return NULL if element isn't found
}

void printSymbol(symbol* s){
	
	printf("%s\t%s", s->name, getPredefTypeStr(s->type));
	if (s->flag != NULLFlag) {

		printf("\t%s", getPredefFlagStr(s->flag));
		if (s->value != NULL) {

			printf("\t%s", s->value);
		}
	}
	printf("\n");
}

void printTable( table* t){
	void* table = t->symbol_variables;

	/*
	printf("%p\n", t);
	printf("%p\n\n", table);
	*/

    twalk(table, walker); // prints all nodes in inorder
}

void printSymbolTables( table* root_table ){
	
	table* cur_table = root_table;

	while( cur_table != NULL ){
		printTable(cur_table);
		cur_table = cur_table->nextTable;
	}
}







