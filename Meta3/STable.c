

#include "ASTree.h"
#include "STable.h"

int createSymbolTable(node* ASTroot) {

	semanticErrorCounter = 0;

	// tabela do outer scope
	STroot = makeTable(outerTable);

	insertSymbol(makeSymbol("boolean", _type_, constantFlag, "_boolean_", DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("integer", _type_, constantFlag, "_integer_", DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("real", _type_, constantFlag, "_real_", DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("false", _boolean_, constantFlag, "_false_", DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("true", _boolean_, constantFlag, "_true_", DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("paramcount", _function_, NULLFlag, NULL, DEFINED, STroot), STroot);
	insertSymbol(makeSymbol("program", _program_, NULLFlag, NULL, DEFINED, STroot), STroot);

	// tabela da funcao paramcount
	table* paramcount_scope = insertChildTable(STroot, makeTable(functionTable));
	insertSymbol(makeSymbol("paramcount", _integer_, returnFlag, NULL, DEFINED, paramcount_scope), paramcount_scope);

	// tabela do program
	table* program_scope = insertChildTable(STroot, makeTable(programTable));

	// starting at program table:
	// walk through AST, creating tables, inserting symbols and verifying scope visibility and type integrity
	walkASTNode(program_scope, ASTroot, NULL, NULLFlag);

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

	node* temp;
	node* IDNode;
	node* returnType;
	symbol* s;
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

					s = makeSymbol(name, getPredefTypeFromStr(type_str), cur_flag, NULL, DEFINED, cur_scope);

					insertSymbol(s, cur_scope);
				}

			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;


		case FuncDeclarationType:
			// declara a função que vem em funcHeading mas marca como não definida

			; //very important voodoo magic, because switch case can't start with declaration

			// adicionar funcao ao scope onde estamos
			temp = cur_node->field1;
			IDNode = temp->field1;
			s = makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, NOT_DEFINED, cur_scope);
			lookup_result = lookupSymbol(s, cur_scope);

			if (lookup_result == NULL) {

				// insere o símbolo que representa a tabela mas marcado como não definida
				insertSymbol(s, cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else {
				//imprimir erro
			}

			break;

		case FuncDefinition2Type:
			
			//procura no cur_scope se a função não está declarada
				// se não estiver declarada: declara a função & insere as suas variáveis nessa tabela, marcando como definida
				// senão: erro, Errroooooo!

			
			; //very important voodoo magic, because switch case can't start with declaration

			// adicionar funcao ao scope onde estamos
			temp = cur_node->field1;
			IDNode = temp->field1;
			s = makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, NOT_DEFINED, cur_scope);
			lookup_result = lookupSymbol(s, cur_scope);

			if (lookup_result == NULL) {

				//imprimir erro
			}
			else {

				lookup_result->isDefined = DEFINED;
				//insertSymbol(s, cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				//cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				//insertSymbol(makeSymbol(IDNode->field1, _NULL_, returnFlag, NULL, DEFINED), cur_scope);
				printf("\nEstou aqui");
				printSymbol(lookup_result);
				walkASTNodeChildren(lookup_result->declarationScope, cur_node, cur_declaration_type, cur_flag);
			}

			break;
			


		case FuncDefinitionType: // Function Identifier expected

			//procura no cur_scope se a função está declarada & se não está definida
				// se está declarada e não está definida : insere as suas variáveis nessa tabela já declarada e marca como definida
				// senão: erro, Errroooooo!

			
			; //very important voodoo magic, because switch case can't start with declaration


			// adicionar funcao ao scope onde estamos
			temp = cur_node->field1;
			IDNode = temp->field1;
			s = makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, NOT_DEFINED, cur_scope);
			lookup_result = lookupSymbol(s, cur_scope);

			if (lookup_result == NULL) {

				//mudar estado da função para definida
				s->isDefined = DEFINED;

				insertSymbol(s, cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else if ( !(lookup_result->isDefined) ) {

				//mudar estado da função _existente_ para definida
				lookup_result->isDefined = DEFINED;

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			}
			else {
				//imprimir erro
			}

			break;

		case VarPartType:

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, NULLFlag);
			break;

		case FuncIdentType:
		case FuncHeadingType:
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
		"_boolean_", "_integer_", "_real_", "_function_", "_program_", "_type_", "_true_", "_false_", "This cannot show!"
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
	new_table->nextSiblingTable = NULL;
	new_table->childrenTableList = NULL;
	new_table->parentTable = NULL;

	return new_table;
}

table* insertSiblingTable(table* cur_table, table* new_table){

	//just add it if there are no other tables already declared in this scope
	if(cur_table->nextSiblingTable == NULL){
		cur_table->nextSiblingTable = new_table;
		new_table->parentTable = cur_table->parentTable;
		return new_table;
	}
	else{
		// delegar a tarefa ao seguinte para adicionar no fim, mantendo a ordem
		return insertSiblingTable(cur_table->nextSiblingTable, new_table);
	}
}

table* insertChildTable(table* cur_table, table* new_table){

	//just add it if there are no children already declared in the scope
	if(cur_table->childrenTableList == NULL){
		cur_table->childrenTableList = new_table;
		new_table->parentTable = cur_table;
		return new_table;
	}
	else{
		// delegar a tarefa de adicionar os seus irmaos ao filho
		return insertSiblingTable(cur_table->childrenTableList, new_table);
	}
}

int lookup_compare(const void* l, const void* r){
	// compare normaly
    const symbol* lm = l;
    const symbol* lr = r;
    return strcasecmp(lm->name, lr->name);
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

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v, int d, table* scope){

	symbol* s = malloc(sizeof(symbol));

    s->name = n;
    s->type = t;
    s->flag = f;
    s->value = v;
    s->isDefined = d;
	s->declarationScope = scope;

    return s;
}

void insertSymbol(symbol* s, table* t){

	if(INSERTION_DEBUG){
		printf("\n\n\n\nSymbol\n");
		printSymbol(s);

		printf("\nBefore insertion\n");
		printTable(t);
	}
	

    tsearch(s, &(t->symbol_variables), insert_compare); // if it isn't found with tsearch it is inserted

    if(INSERTION_DEBUG){
		printf("\nAfter insertion\n");
		printTable(t);
	}
	
}

void printSymbolDebug(symbol* node) {
	printf("No %p\n", node);

	printf("%s\n", node->name);
	printf("%s\n", getPredefTypeStr(node->type));
	printf("%s\n", getPredefFlagStr(node->flag));
	printf("%s\n", node->value);
	printf("%d\n", node->isDefined);
	printf("%p\n", node->declarationScope);
}

symbol* lookupSymbol(symbol* s, table* t){

	symbol* node = tfind(&s, &(t->symbol_variables), lookup_compare); //return NULL if element isn't found
	if (node == NULL)
		return NULL;
	else{

		printf("Searching\n");
		printSymbolDebug(s);
		printf("Got\n");
		printSymbolDebug(node);

		return node;
	}
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

void printSiblings(table* cur_table){

	while( cur_table != NULL ){

		// se o irmão existe separa-o do anterior por um "\n", assim só a última tabela não é seguida de um \n
		printf("\n");

		printTable(cur_table);
		printSiblings(cur_table->childrenTableList);

		cur_table = cur_table->nextSiblingTable;
	}
}

void printAllSymbolTables( table* root_table ){
	
    if(INSERTION_DEBUG){
    	printf("\n\n\n-------------LOLITOS--------------\n\n\n");
    }

	printTable(root_table);

	// imprime os irmãos (que são inexistentes em milipascal)
	printSiblings(root_table->nextSiblingTable);

	// imprime os filhos da outer table
	printSiblings(root_table->childrenTableList);
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




