

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
	STroot->nextTable = f;


	insertSymbol(makeSymbol("paramcount", _integer_, returnFlag, NULL), f);
	

	table* p = makeTable(programTable);
	f->nextTable = p;
	

	walkAST(p, ASTroot, NULL);


	return semanticErrorCounter;
}

void walkAST(table* cur_scope, node* cur_node, node* cur_declaration_type) {


	if( cur_node == NULL){
		return;
	}

	NodeType t = cur_node->type_of_node;

	int d;
	char* name;
	char* type_str;

	switch(t) {

		case VarDeclarationType:
		case VarParamsType:
		case ParamsType:

			/* guardar cur_node->field2 numa variavel global que e cur_declaration_type */
			walkAST(cur_scope, cur_node->field1, cur_node->field2);
			walkAST(cur_scope, cur_node->field2, cur_node->field2);
			walkAST(cur_scope, cur_node->field1, cur_node->field2);

			break;

		case IDListType:
		case CommaIDListType:

			/* pegar em cur_node->field1 e criar um simbolo em cur_scope do tipo cur_declaration_type */
			if (cur_node->field1 != NULL) {

				//get name from id node
				node* variable = cur_node->field1;
				name = variable->field1;

				//get type string from current type of declarations
				if (cur_declaration_type != NULL) {
					type_str = cur_declaration_type->field1;

					symbol* s = makeSymbol(name, getPredefTypeFromStr(type_str), NULLFlag, NULL);

					insertSymbol(s, cur_scope);
				}

			}

			walkAST(cur_scope, cur_node->field1, cur_declaration_type);
			walkAST(cur_scope, cur_node->field2, cur_declaration_type);
			walkAST(cur_scope, cur_node->field3, cur_declaration_type);

			break;

		case FuncHeadingType:
		case FuncIdentType:

			/* adicionar funcao ao scope onde estamos */
			name = cur_node->field1;
			symbol *s = makeSymbol(name, _function_, NULLFlag, NULL);
			insertSymbol(s, cur_scope);

			/* criar tabela de simbolos (scope) para a nova funcao */
			cur_scope->nextTable = makeTable(functionTable);
			table* new_table = cur_scope->nextTable;

			symbol* sy;
			if (cur_node->field3 != NULL) {
				char* returnTypeStr = cur_node->field3;
				sy = makeSymbol(cur_node->field1, getPredefTypeFromStr(returnTypeStr), returnFlag, NULL);
			}
			else
				sy = makeSymbol(cur_node->field1, _NULL_, NULLFlag, NULL);	

			insertSymbol(sy, new_table);

			walkAST(new_table, cur_node->field1, cur_declaration_type);
			walkAST(new_table, cur_node->field2, cur_declaration_type);
			walkAST(new_table, cur_node->field3, cur_declaration_type);

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

			walkAST(cur_scope, cur_node->field1, cur_declaration_type);
			walkAST(cur_scope, cur_node->field2, cur_declaration_type);
			walkAST(cur_scope, cur_node->field3, cur_declaration_type);

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
		"_boolean_", "_integer_", "_real_", "_function_", "_program_", "_type_", "_true_", "_false_"
	};
	return str[t];
}

char* getPredefFlagStr(PredefFlag f) {
	char* str[] = {
		"constant", "return", "param", "varparam"
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
  symbol *f;
  f = *(symbol **)node;

   switch (which) {

		case preorder:
		case endorder:
		   break;
	
		case leaf:
		case postorder:
		   printf("%s\t%s", f->name, getPredefTypeStr(f->type));
		   if (f->flag != NULLFlag) {
		   		printf("\t%s", getPredefFlagStr(f->flag));
		   		if (f->value != NULL) {
		   			printf("\t%s", f->value);
		   		}
		   }
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
	void* table = t->symbol_variables;
    tsearch(s, &table, insert_compare); // if it isn't found with tsearch it is inserted
}

symbol* lookupSymbol(symbol* s, table* t){
	void* table = t->symbol_variables;
	return tfind(s, &table, lookup_compare); //return NULL if element isn't found
}

void printTable( table* t){
	void* table = t->symbol_variables;
    twalk(table, walker); // prints all nodes in inorder
}








