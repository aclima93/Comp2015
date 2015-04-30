

#include "ASTree.h"
#include "STable.h"

int createSymbolTable(node* ASTroot) {

	semanticErrorCounter = 0;

	STroot = makeTable(outerTable);

	table* cur_scope = STroot;

	insertSymbol(makeSymbol("boolean", _type_, constantFlag, "_boolean_", DEFINED), STroot);
	insertSymbol(makeSymbol("integer", _type_, constantFlag, "_integer_", DEFINED), STroot);
	insertSymbol(makeSymbol("real", _type_, constantFlag, "_real_", DEFINED), STroot);
	insertSymbol(makeSymbol("false", _boolean_, constantFlag, "_false_", DEFINED), STroot);
	insertSymbol(makeSymbol("true", _boolean_, constantFlag, "_true_", DEFINED), STroot);
	insertSymbol(makeSymbol("paramcount", _function_, NULLFlag, NULL, DEFINED), STroot);
	insertSymbol(makeSymbol("program", _program_, NULLFlag, NULL, DEFINED), STroot);

	/* f é a tabela da funcao paramcount */
	cur_scope = insertTable(cur_scope, makeTable(functionTable));
	insertSymbol(makeSymbol("paramcount", _integer_, returnFlag, NULL, DEFINED), cur_scope);

	cur_scope = insertTable(cur_scope, makeTable(programTable));

	// start walk through AST, creating tables, inserting symbols and verifying scope visibility and type integrity
	walkASTNode(cur_scope, ASTroot, NULL, NULLFlag);

	return semanticErrorCounter;
}

void walkASTNodeChildren(table* cur_scope, node* cur_node, node* cur_declaration_type, PredefFlag cur_flag) {

	walkASTNode(cur_scope, cur_node->field1, cur_declaration_type, cur_flag);
	walkASTNode(cur_scope, cur_node->field2, cur_declaration_type, cur_flag);
	walkASTNode(cur_scope, cur_node->field3, cur_declaration_type, cur_flag);
}

void walkASTNode(table* cur_scope, node* cur_node, node* cur_declaration_type, PredefFlag cur_flag) {


	if( cur_node == NULL || isLeaf(cur_node) ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	node* IDNode;
	node* returnType;
	symbol* s;
	symbol* sym;
	symbol* lookup_result;

	switch(t) {

		case VarDeclarationType: //Type identifier expected; Cannot write values of type <type>
			/* passar o novo tipo das variáveis que se vão seguir*/
			walkASTNodeChildren(cur_scope, cur_node, cur_node->field2, cur_flag);
			break;

		case VarParamsType:
			/* passar o novo tipo das variáveis que se vão seguir*/
			walkASTNodeChildren(cur_scope, cur_node, cur_node->field2, varparamFlag);
			break;

		case ParamsType:
			/* passar o novo tipo das variáveis que se vão seguir*/
			walkASTNodeChildren(cur_scope, cur_node, cur_node->field2, paramFlag);
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

					s = makeSymbol(name, getPredefTypeFromStr(type_str), cur_flag, NULL, DEFINED);

					insertSymbol(s, cur_scope);
				}

			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case FuncHeadingType:
			
			//procura no cur_scope se a função não está declarada
				// se sim: declara a função & insere as suas variáveis nessa tabela, marcando como definida
				// senão: erro, Errroooooo!

			
			; //very important voodoo magic, because switch case can't start with declaration

			// adicionar funcao ao scope onde estamos
			IDNode = cur_node->field1;
			s = makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, DEFINED);
			lookup_result = lookupSymbol(s, cur_scope);

			if (lookup_result == NULL) {

				insertSymbol(s, cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertTable(cur_scope, makeTable(functionTable));

				returnType = cur_node->field3;
				sym = makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED);

				insertSymbol(sym, cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else {
				//imprimir erro
			}

			break;
			

		case FuncIdentType: // Function Identifier expected

			//procura no cur_scope se a função está declarada & se não está definida
				// se sim a ambas: insere as suas variáveis nessa tabela já declarada e marca como definida
				// senão: erro, Errroooooo!

			
			; //very important voodoo magic, because switch case can't start with declaration


			// adicionar funcao ao scope onde estamos
			IDNode = cur_node->field1;
			s = makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, NOT_DEFINED);
			lookup_result = lookupSymbol(s, cur_scope);

			if (lookup_result == NULL) {

				//mudar para definida
				s->isDefined = DEFINED;

				insertSymbol(s, cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertTable(cur_scope, makeTable(functionTable));

				returnType = cur_node->field3;
				sym = makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED);

				insertSymbol(sym, cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else if ( !(lookup_result->isDefined) ) {

			}
			else {
				//imprimir erro
			}

			break;


		case FuncDeclarationType:
			// declara a função que vem em funcHeading mas marca como não definida



			break;

		case VarPartType:
			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, NULLFlag);
			break;

		case FuncDefinitionType:
		case FuncDefinition2Type:
		case ProgType:
		case FuncPartType:
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
		case SimpleExprType: //Operator <token> cannot be applied to type <type>
		case FactorType:
		case OPTermListType:
		case StatListType:
		case FuncParamsListType2:
		case FuncDeclarationListType:
		case VarDeclarationListType: //Symbol <token> already defined; Symbol <token> not defined
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

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

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

char* getPredefTableStr(PredefTable t) {
	char* str[] = {
		"Outer", "Program", "Function"
	};
	return str[t];
}

table* makeTable(PredefTable t) {

	table* new_table = malloc(sizeof(table));

	new_table->type = t;
	new_table->symbol_variables = NULL;
	new_table->nextTable = NULL;

	return new_table;
}

table* insertTable(table* cur_table, table* new_table){

	//just add it if there are no other tables already declared in this scope
	if(cur_table->nextTable == NULL){
		cur_table->nextTable = new_table;
		return new_table;
	}
	else{
		// delegar a tarefa ao seguinte para adicionar no fim, mantendo a ordem
		return insertTable(cur_table->nextTable, new_table);
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
    return 1;
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

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v, int d){

	symbol* s = malloc(sizeof(symbol));

    s->name = n;
    s->type = t;
    s->flag = f;
    s->value = v;
    s->isDefined = d;

    return s;
}

void insertSymbol(symbol* s, table* t){

	/*
	printf("\n\nSymbol\n");
	printSymbol(s);

	printf("\nBefore insertion\n");
	printTable(t);
	*/

    tsearch(s, &(t->symbol_variables), insert_compare); // if it isn't found with tsearch it is inserted

    /*
	printf("\nAfter insertion\n");
	printTable(t);
	*/
}

symbol* lookupSymbol(symbol* s, table* t){
	return tfind(s, &(t->symbol_variables), lookup_compare); //return NULL if element isn't found
}

void printSymbol(symbol* s){
	
	printf("%s\t%s", strlwr(s->name), getPredefTypeStr(s->type));
	if (s->flag != NULLFlag) {

		printf("\t%s", getPredefFlagStr(s->flag));
		if (s->value != NULL) {

			printf("\t%s", s->value);
		}
	}
	printf("\n");
}

void printTable( table* t){

	printf("===== %s Symbol Table =====\n", getPredefTableStr(t->type));
    twalk(t->symbol_variables, walker); // prints all nodes in inorder
}

void printSymbolTables( table* root_table ){
	
	table* cur_table = root_table;

	while( cur_table != NULL ){
		printTable(cur_table);
		cur_table = cur_table->nextTable;
        if(cur_table != NULL)
            printf("\n");
	}
}

char* strlwr(char* str){
	int i;
	int len = strlen(str);
	char* lowered = malloc( sizeof(char) * len );

	for(i=0; i<len; i++){
		lowered[i] = tolower((unsigned char) str[i]);
	}
	return lowered;
}


void printErrorLineCol(int l, int c) {
	semanticErrorCounter++;
	printf("Line %d, col %d: ", l, c);
} 

void printTypeError(char* type) {
	printf("Cannot write values of type %s\n", type);
}

void printFunctionIDError() {
	printf("Function identifier expected.\n");
}

void printIncompatibleTypeCallFunctionError(int num, char* functionStr, char* gotType, char* expectedType) {
	printf("Incompatible type for argument %d in call to function %s (got %s, expected %s)\n", num, functionStr, gotType, expectedType);
}

void printIncompatibleTypeAssignmentError(char* tokenStr, char* gotType, char* expectedType) {
	printf("Incompatible type in assignment to %s (got %s, expected %s)\n", tokenStr, gotType, expectedType);
}

void printIncompatibleTypeStatementError(char* statementStr, char* gotType, char* expectedType) {
	printf("Incompatible type in %s statement (got %s, expected %s)\n", statementStr, gotType, expectedType);
}

void printOperatorTypeError(char* tokenStr, char* type) {
	printf("Operator %s cannot be applied to type %s\n", tokenStr, type);
}

void printOperatorTypesError(char* leftTokenStr, char* righttTokenStr, char* type) {
	printf("Operator %s cannot be applied to types %s, %s\n", leftTokenStr, righttTokenStr, type);
}

void printSymbolAlreadyDefinedError(char* tokenStr) {
	printf("Symbol %s already defined\n", tokenStr);
}

void printSymbolNotDefinedError(char* tokenStr) {
	printf("Symbol %s not defined\n", tokenStr);
}

void printTypeIdentifierExpectedError() {
	printf("Type identifier expected\n");
}

void printVariableIdentifierExpectedError() {
	printf("Variable identifier expected\n");
}

void printWrongNumberCallFunctionError(char* tokenStr, int gotNArgs, int expectedNArgs) {
	printf("Wrong number of arguments in call to function %s (got %d, expected %d)\n", tokenStr, gotNArgs, expectedNArgs);
}




