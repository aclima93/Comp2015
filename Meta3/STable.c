

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

	// stop if one error has been found
	if( !DISABLE_ERRORS && semanticErrorCounter){
		return;
	}

	if( cur_node == NULL || isLeaf(cur_node) ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	node* temp;
	node* IDNode;
	node* expr_node;
	PredefType expr_type, type1, type2;
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

					lookup_result = searchForSymbolInRelevantScopes(variable->field1, cur_scope);

					if (lookup_result == NULL) {

						char* type_str = cur_declaration_type->field1;
						insertSymbol(makeSymbol(name, getPredefTypeFromStr(type_str), cur_flag, NULL, DEFINED, cur_scope), cur_scope);
					}
					else {
						printErrorLineCol(variable->line, variable->col, printSymbolAlreadyDefinedError(name));
					}

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
			lookup_result = lookupSymbol(IDNode->field1, cur_scope);

			if (lookup_result == NULL) {

				// insere o símbolo que representa a tabela mas marcado como não definida
				insertSymbol(makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, NOT_DEFINED, cur_scope), cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else {
				//TODO
				//imprimir erro
				// encontrou uma função com o mesmo nome
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
			lookup_result = lookupSymbol(IDNode->field1, cur_scope);

			if (lookup_result == NULL) {
				//TODO
				//imprimir erro

			}
			else {

				lookup_result->isDefined = DEFINED;

				// nao e preciso criar o simbolo que representa a tabela, nem a tabela, porque assumimos que ja foram declarados, apenas falta definir
			
				cur_scope = getFuncScope(IDNode->field1, cur_scope);

				if(cur_scope == NULL){
					//TODO
					//imprimir erro
					// não encontrou a função pré declarada
				}

				//walkASTNodeChildren(lookup_result->declarationScope, cur_node, cur_declaration_type, cur_flag);
				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
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
			lookup_result = lookupSymbol(IDNode->field1, cur_scope);

			if (lookup_result == NULL) {

				insertSymbol(makeSymbol(IDNode->field1, _function_, NULLFlag, NULL, DEFINED, cur_scope), cur_scope);

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);
			}
			else if ( lookup_result->isDefined == NOT_DEFINED ) {

				//mudar estado da função _existente_ para definida
				lookup_result->isDefined = DEFINED;

				// criar tabela de simbolos (scope) para a nova funcao
				cur_scope = insertChildTable(cur_scope, makeTable(functionTable));

				returnType = temp->field3;

				insertSymbol(makeSymbol(IDNode->field1, getPredefTypeFromStr(returnType->field1), returnFlag, NULL, DEFINED, cur_scope), cur_scope);

				walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			}
			else {
				//TODO
				//imprimir erro
			}

			break;

		case VarPartType:

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, NULLFlag);
			break;

		case IDType:

			lookup_result = searchForSymbolInRelevantScopes(cur_node->field1, cur_scope);

			if (lookup_result == NULL) {
				printErrorLineCol(cur_node->line, cur_node->col, printSymbolNotDefinedError(cur_node->field1));
			}

			break;


		case ExprType:
		case SimpleExprType: //Operator <token> cannot be applied to type <type>
		case FactorType:
		case OPTermListType:

			// check for type matching errors between operators and operands
			getPredefTypeOfNode(cur_node, cur_scope);
			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case IfElseStatType:

			;
			expr_node = cur_node->field1;
			expr_type = getPredefTypeOfNode(expr_node, cur_scope);

			// têm de verificar se a Expr se resolve em booleano
			if( expr_type != _boolean_ ){
				// imprimir erro
				printErrorLineCol(expr_node->line, expr_node->col, printIncompatibleTypeStatementError("IfElse", getPredefTypeStr(expr_type), "_boolean_") );
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case WhileStatType:
			
			expr_node = cur_node->field1;
			expr_type = getPredefTypeOfNode(expr_node, cur_scope);

			// têm de verificar se a Expr se resolve em booleano
			if( expr_type != _boolean_ ){
				// imprimir erro
				printErrorLineCol(expr_node->line, expr_node->col, printIncompatibleTypeStatementError("While", getPredefTypeStr(expr_type), "_boolean_") );
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case RepeatStatType:
			
			expr_node = cur_node->field2;
			expr_type = getPredefTypeOfNode(expr_node, cur_scope);

			// têm de verificar se a Expr se resolve em booleano
			if( expr_type != _boolean_ ){
				// imprimir erro
				printErrorLineCol(expr_node->line, expr_node->col, printIncompatibleTypeStatementError("Repeat", getPredefTypeStr(expr_type), "_boolean_") );
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case ValParamStatType:
			
			expr_node = cur_node->field1;
			expr_type = getPredefTypeOfNode(expr_node, cur_scope);

			// têm de verificar se a Expr se resolve em inteiro
			if( expr_type != _integer_ ){
				// imprimir erro
				printErrorLineCol(expr_node->line, expr_node->col, printIncompatibleTypeStatementError("ValParam", getPredefTypeStr(expr_type), "_integer_") );
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case AssignStatType:

			IDNode = cur_node->field1;
			type1 = getPredefTypeOfNode(IDNode, cur_scope);
			type2 = getPredefTypeOfNode(cur_node->field2, cur_scope);


			// tem de verificar se o tipo da direita é o mesmo do tipo da esquerda
			if( type1 != type2 ){
				// imprimir erro
				printErrorLineCol(IDNode->line, IDNode->col, printIncompatibleTypeAssignmentError(IDNode->field1, getPredefTypeStr(type1), getPredefTypeStr(type2)) );
			}
			
			
			lookup_result = searchForSymbolInRelevantScopes(IDNode->field1, cur_scope);

			// erro de atribuição a field 1 se for um const nas tabelas relevantes
			if( lookup_result != NULL && lookup_result->flag == constantFlag ){
				// imprimir erro
				printErrorLineCol(IDNode->line, IDNode->col, printVariableIdentifierExpectedError() );
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case WritelnPListType:

			// tem de veificar se é um integer, real, bool ou string

			; //very important voodoo magic, because switch case can't start with declaration

			PredefType f1 = getPredefTypeOfNode(cur_node->field1, cur_scope);
			PredefType f2 = getPredefTypeOfNode(cur_node->field2, cur_scope);
			
			if( !( isValidWriteLnArgument(f1) ) ){
				//TODO
				// imprimir erro ?
			}
			
			if( !( isValidWriteLnArgument(f2) ) ){
				//TODO
				// imprimir erro ?
			}

			walkASTNodeChildren(cur_scope, cur_node, cur_declaration_type, cur_flag);

			break;

		case ParamListType:
		case ExprListType:
		case FuncIdentType:
		case FuncHeadingType:
		case ProgType:
		case FuncPartType:
		case FuncParamsListType:
		case ProgBlockType:
		case FuncBlockType:
		case StatType:
		case WriteLnStatType:
		case StatListType:
		case FuncParamsListType2:
		case FuncDeclarationListType:
		case VarDeclarationListType: //Symbol <token> already defined; Symbol <token> not defined
		case CompStatType:
		case DoubleType:
		case IntType:
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
		"_boolean_", "_integer_", "_real_", "_function_", "_program_", "_type_", "_true_", "_false_", "_string_", "This cannot show!"
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
	//TODO find a way to preserve insertion order and order by name
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

	printf("Node address: %p\n", node);
	printf("%s\n", node->name);
	printf("%s\n", getPredefTypeStr(node->type));
	printf("%s\n", getPredefFlagStr(node->flag));
	printf("%s\n", node->value);
	printf("%d\n", node->isDefined);
	printf("%p\n", node->declarationScope);
}

table* getFuncScope(char *key, table* cur_scope) {

	if (lookupSymbol(key, cur_scope) == NULL) {
		return NULL;
	}
	else {
		cur_scope = cur_scope->childrenTableList;
		while(cur_scope != NULL && lookupSymbol(key, cur_scope) == NULL) {
			cur_scope = cur_scope->nextSiblingTable;
		}
		return cur_scope;
	}
}

symbol* lookupSymbol(char* key, table* t){

	symbol* s = makeSymbol(key, _NULL_, NULLFlag, NULL, DEFINED, NULL); // only the name matters in lookup_compare

	void* node = tfind(s, &(t->symbol_variables), lookup_compare); //return NULL if element isn't found 

	if (node == NULL){
		return NULL;
	}
	else{

		if(LOOKUP_DEBUG){
			printf("\n--------\n");
			printTable(t);
			printf("Searching\n");
			printf("%s\n", key);
			printf("Got\n");
			printSymbolDebug( (*(symbol**)node) );
		}
		return (*(symbol**)node);
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
    	printf("\n\n\n-------------LOLITOS DEBUGZITO--------------\n\n\n");
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

/*
 * Error functions
 */

int isValidWriteLnArgument(PredefType p){

	// WriteLn can only print these types of variables
	if( p == _integer_ || p == _boolean_ || p == _real_ || p == _string_ ){
		return 1;
	}
	return 0;
}

PredefType outcomeOfOperation(char* op, PredefType leftType, PredefType rightType) {
 	if (strcasecmp(op, "+") == 0 || strcasecmp(op, "-") == 0 || strcasecmp(op, "*") == 0) {
 		
 		// integer/real with integer/real
		if ( leftType == _integer_ && leftType == _integer_)
			return _integer_;
		else if ( (leftType == _integer_ || leftType == _real_) && (rightType == _integer_ || rightType == _real_) )
			return _real_;
 	}
 	else if (strcasecmp(op, "/") == 0)
 		return _real_;

 	else if (strcasecmp(op, "div") == 0 || strcasecmp(op, "mod") == 0) {
 		return _integer_;
 	}
 	else if (strcasecmp(op, ">") == 0 || strcasecmp(op, "<=") == 0 
 		  || strcasecmp(op, ">=") == 0 || strcasecmp(op, "<") == 0  
 		  || strcasecmp(op, "<>") == 0 || strcasecmp(op, "=") == 0 ) {
 			return _boolean_;
 	}

 	return _NULL_;
}

int isValidOperation(char* op, PredefType leftType, PredefType rightType){

 	if (strcasecmp(op, "+") == 0 || strcasecmp(op, "-") == 0 || strcasecmp(op, "*") == 0 || strcasecmp(op, "/") == 0) {
 		// integer/real with integer/real
 		if ( (leftType == _integer_ || leftType == _real_) && (rightType == _integer_ || rightType == _real_) ) {
 			return 1;
 		}
 	}
 	else if (strcasecmp(op, "div") == 0 || strcasecmp(op, "mod") == 0) {
 		if ( (leftType == _integer_ ) && (rightType == _integer_) ) {
 			return 1;
 		}
 	}
 	else if (strcasecmp(op, ">") == 0 || strcasecmp(op, "<=") == 0 || strcasecmp(op, ">=") == 0 || strcasecmp(op, "<") == 0)   {
 		if ((leftType == _integer_  && rightType == _integer_) || (leftType == _real_  && rightType == _real_) ) {
 			return 1;
 		}
 	}
 	else if ((strcasecmp(op, "<>") == 0 || strcasecmp(op, "=") == 0) ) {
 		if (leftType ==  rightType) {
 			return 1;
 		}
 	}

 	return 0;
}

PredefType outcomeOfUnaryOperation(char* op, PredefType rightType){

	// because unary operators don't change the type, only the value
	return rightType;
}

int isValidUnaryOperation(char* op, PredefType rightType){

	if( strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ){
		if ( rightType == _integer_ || rightType == _real_ ){
			return 1;
		}
	}
	else if( strcmp(op, "!") == 0 ){ 
		if( rightType == _boolean_ ){
			return 1;
		}
	}

	return 0;
}

PredefType getPredefTypeOfExpr(node* cur_node, table* cur_scope){

	if( cur_node->field1 != NULL && cur_node ->field3 != NULL ){
		
		PredefType leftType = getPredefTypeOfNode(cur_node->field1, cur_scope);
		PredefType rightType = getPredefTypeOfNode(cur_node->field3, cur_scope);

		node* op = cur_node->field2;

		if( !(isValidOperation(op->field1, leftType, rightType))){

			//imprimir erro
			printErrorLineCol(op->line, op->col, printOperatorTypesError(op->field1, getPredefTypeStr(leftType), getPredefTypeStr(rightType)) );
		}

		return outcomeOfOperation(op->field1, leftType, rightType);

	}
	else{
		// retorna o tipo da SimpleExpr que tem
		return getPredefTypeOfNode(cur_node->field2, cur_scope);
	}
}

PredefType getPredefTypeOfSimpleExpr(node* cur_node, table* cur_scope){

	node* op = cur_node->field2;
	PredefType leftType;
	PredefType rightType;
	
	if( cur_node->field1 != NULL ){
		
		leftType = getPredefTypeOfNode(cur_node->field1, cur_scope);
		rightType = getPredefTypeOfNode(cur_node->field3, cur_scope);

		if( !(isValidOperation(op->field1, leftType, rightType)) ){

			//imprimir erro
			printErrorLineCol(op->line, op->col, printOperatorTypesError(op->field1, getPredefTypeStr(leftType), getPredefTypeStr(rightType)) );
		}

		return outcomeOfOperation(op->field1, leftType, rightType);

	}
	else{
		//só tem um operando à direita, é uma operação unária

		// retorna o tipo da Term que tem
		rightType = getPredefTypeOfNode(cur_node->field3, cur_scope);

		if( !( isValidUnaryOperation(op->field1, rightType) ) ){

			printErrorLineCol(op->line, op->col, printOperatorTypeError(op->field1, getPredefTypeStr(rightType)) );
		}

		return outcomeOfUnaryOperation(op->field1, rightType);
	}
}

PredefType getPredefTypeOfTerm(node* cur_node, table* cur_scope){

	node* op = cur_node->field2;
	PredefType leftType = getPredefTypeOfNode(cur_node->field1, cur_scope);
	PredefType rightType = getPredefTypeOfNode(cur_node->field3, cur_scope);

	if( !(isValidOperation(op->field1, leftType, rightType)) ){

		//imprimir erro
		printErrorLineCol(op->line, op->col, printOperatorTypesError(op->field1, getPredefTypeStr(leftType), getPredefTypeStr(rightType)) );
	}

	return outcomeOfOperation(op->field1, leftType, rightType);
}

PredefType getPredefTypeOfFactor(node* cur_node, table* cur_scope){

	node* op = cur_node->field2;
	PredefType leftType;
	PredefType rightType;

	if( op->type_of_node == CallType ){ // function call

		ExprPredefTypeList* cur_expectedExpr;
		ExprPredefTypeList* cur_gotExpr;
		symbol* lookup_result;


		if(FUNCTION_CALL_DEBUG){
			printf("\n---------\nCurrent Scope\n");
			printTable(cur_scope);
		}

		// check function id in current scope and scopes above it 

		lookup_result = searchForSymbolInRelevantScopes(op->field1, cur_scope);

		if (lookup_result == NULL) {
			//printErrorLineCol(op->line, op->col, printSymbolNotDefinedError(op->field1));
			printErrorLineCol(op->line, op->col, printFunctionIDError());
			return _NULL_; // no function return type because the function doesn't exist
		}

		if(FUNCTION_CALL_DEBUG){
			printf("\n---------\nFunction %s in Function Call\n", lookup_result->name);
			printSymbolDebug(lookup_result);
		}

		// get function scope (good thing each symbol has a reference to its declaration scope)
		table* func_scope = getFuncScope(op->field1, lookup_result->declarationScope);

		if(FUNCTION_CALL_DEBUG){
			printf("\n---------\nScope of Function %s in Function Call\n", lookup_result->name);
			printTable(func_scope);
		}


		// check number of arguments and Types in ArgumentList

		ExprPredefTypeList* expectedExprTypes = getPredefTypesOfParamList(func_scope); // expected type list
		int numExpectedArgs = countNumElements(expectedExprTypes); // count number of arguments in expected List

		ExprPredefTypeList* gotExprTypes = getPredefTypesOfExprList(cur_node, cur_scope); // gotten type list
		int numGottenArgs = countNumElements(gotExprTypes); // count number of arguments in gotten List

		if( numGottenArgs != numExpectedArgs ){
			// imprimir erro
			printErrorLineCol(op->line, op->col, printWrongNumberCallFunctionError(op->field1, numGottenArgs, numExpectedArgs));
			return _NULL_;
		}

		// compare gotten types and expected types
		cur_gotExpr = gotExprTypes;
		cur_expectedExpr = expectedExprTypes;
		int num = 1;

		while( cur_gotExpr != NULL && cur_expectedExpr != NULL ){

			if( cur_gotExpr->type != cur_expectedExpr->type ){
				// printIncompatibleTypeCallFunctionError(int num, char* functionStr, char* gotType, char* expectedType)
				printErrorLineCol(op->line, op->col, printIncompatibleTypeCallFunctionError(num, op->field1, getPredefTypeStr(cur_gotExpr->type), getPredefTypeStr(cur_expectedExpr->type) ) );
				return _NULL_;
			}

			num++;
			cur_gotExpr = cur_gotExpr->next;
			cur_expectedExpr = cur_expectedExpr->next;
		}

		// return type of func
		lookup_result = lookupSymbol(op->field1, func_scope);
		if( lookup_result != NULL && lookup_result->flag == returnFlag )
			return lookup_result->type;

		return _NULL_;

	}
	else{ // UnaryOPType

		rightType = getPredefTypeOfNode(cur_node->field3, cur_scope);

		if( !( isValidUnaryOperation(op->field1, rightType) ) ){

			printErrorLineCol(op->line, op->col, printOperatorTypeError(op->field1, getPredefTypeStr(rightType)) );
		}

		return outcomeOfUnaryOperation(op->field1, rightType);
	}

}

void addSymbolToParamList(symbol* s){

	if( s == NULL )
		return ;

	// create new element and add to end of list
	ExprPredefTypeList* new_element = malloc( sizeof(ExprPredefTypeList) );
	new_element->type = s->type;
	new_element->next = NULL;

	if( paramSymbolList == NULL ){
		paramSymbolList = new_element;
		return ;
	}

	ExprPredefTypeList* temp = paramSymbolList;

	while( temp->next != NULL ){
		temp = temp->next;
	}

	temp->next = new_element;
}

void param_walker(const void *node, const VISIT which, const int depth) {

  symbol *s;
  s = *(symbol **)node;

   switch (which) {

		case preorder:
		case endorder:
		   break;
	
		case leaf:
		case postorder:
			if( s->flag == paramFlag || s->flag == varparamFlag){
				addSymbolToParamList(s);
			}
			break;
   }
}

int countNumElements(ExprPredefTypeList* exprTypes){
	ExprPredefTypeList* cur_expr = exprTypes;
	int numElements = 0;

	while( cur_expr != NULL ){
		numElements++;
		cur_expr = cur_expr->next;
	}

	return numElements;
}

ExprPredefTypeList* getPredefTypesOfParamList(table* func_scope){
	//TODO
	// return list of types of param symbols for this function
	paramSymbolList = NULL; // this should eb a deallocation, but the'res no time for fancy stuff right now
	twalk(func_scope->symbol_variables, param_walker); // fetch all types of function parameters
	return paramSymbolList;
}

ExprPredefTypeList* getPredefTypesOfExprList(node* cur_node, table* cur_scope){

	if( cur_node == NULL )
		return NULL;

	ExprPredefTypeList* exprTypes = malloc( sizeof(ExprPredefTypeList) );
	
	exprTypes->type = getPredefTypeOfNode(cur_node->field1, cur_scope);
	exprTypes->next = getPredefTypesOfExprList(cur_node->field2, cur_scope);

	return exprTypes; // return list of gotten types of arguments in function call

}

PredefType getPredefTypeOfNode(node* cur_node, table* cur_scope){

	if(cur_node == NULL)
		return _NULL_;

	// cur_node can be a terminal (ID, INTLIT, REALLIT, STRING ), Expr, SimpleExpr, Term, Factor
	// resolve the underlying type and return it

	if( cur_node->type_of_node == ExprType ){
		return getPredefTypeOfExpr(cur_node, cur_scope);
	}
	else if( cur_node->type_of_node == SimpleExprType ){
		return getPredefTypeOfSimpleExpr(cur_node, cur_scope);
	}
	else if ( cur_node->type_of_node == OPTermListType ){
		return getPredefTypeOfTerm(cur_node, cur_scope);
	}
	else if( cur_node->type_of_node == FactorType ){
		return getPredefTypeOfFactor(cur_node, cur_scope);
	}
	else if( cur_node->type_of_node == IDType ){
		return searchForTypeOfSymbolInRelevantScopes(cur_node, cur_scope);
	}
	else if( cur_node->type_of_node == IntType ){
		return _integer_;
	}
	else if( cur_node->type_of_node == DoubleType ){
		return _real_;
	}
	else if( cur_node->type_of_node == StringType ){
		return _string_;
	}

	return _NULL_;
}

PredefType searchForTypeOfSymbolInRelevantScopes(node* cur_node, table* cur_scope){

	// check cur_scope and upper scopes for symbol declaration in symbol tables
	// -- issue warning if not declared in any
	// -- else: return type in table

	symbol* lookup_result = NULL;

	while( cur_scope != NULL && lookup_result == NULL ){
		lookup_result = lookupSymbol(cur_node->field1, cur_scope);
		cur_scope = cur_scope->parentTable; //check for outer table
	}

	if (lookup_result == NULL) {
		printErrorLineCol(cur_node->line, cur_node->col, printSymbolNotDefinedError(cur_node->field1) );
		return _NULL_;
	}

	return lookup_result->type;
}

symbol* searchForSymbolInRelevantScopes(char* key, table* cur_scope){

	// check cur_scope and upper scopes for symbol declaration in symbol tables

	symbol* lookup_result = NULL;
	table* upper_scope = cur_scope;

	while( upper_scope != NULL ){

		lookup_result = lookupSymbol(key, upper_scope);
		
		if( LOOKUP_UPPER_SCOPES_DEBUG ){

			if( upper_scope != NULL ){
				printf("\n\nLooking for %s in Scope\n", key);
				printTable(upper_scope);
			}

			if( lookup_result != NULL ){
				printf("\n\nSymbol Found\n");
				printSymbolDebug(lookup_result);
			}
		}

		upper_scope = upper_scope->parentTable; //check for outer table

		if(lookup_result != NULL)
			return lookup_result;

	}

	return lookup_result;
}

void printErrorLineCol(int l, int c, char* errorStr) {

	if(DISABLE_ERRORS)
		return ;

	// stop if one error has been found
	if(semanticErrorCounter){
		semanticErrorCounter++;
		return ;
	}
	else{
		semanticErrorCounter++;
		printf("Line %d, col %d: %s", l, c, errorStr);
	}
} 

char* printTypeError(char* type) {
	char* errorStr = malloc(sizeof(char) * ( strlen("Cannot write values of type \n") + strlen(type) ) );
	sprintf(errorStr, "Cannot write values of type %s\n", type);
	return errorStr;
}

char* printFunctionIDError() {
	int len = strlen("Function identifier expected.\n");
	char* errorStr = malloc(sizeof(char) * len );
	sprintf(errorStr, "Function identifier expected.\n");
	return errorStr;
}

char* printIncompatibleTypeCallFunctionError(int num, char* functionStr, char* gotType, char* expectedType) {
	int len = 0;
	len += MAX_INT_LEN;
	len += strlen("Incompatible type for argument  in call to function  (got , expected )\n");
	len += strlen(functionStr) + strlen(gotType) + strlen(expectedType);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Incompatible type for argument %d in call to function %s (got %s, expected %s)\n", num, functionStr, gotType, expectedType);
	return errorStr;
}

char* printIncompatibleTypeAssignmentError(char* tokenStr, char* gotType, char* expectedType) {
	int len = 0;
	len += strlen("Incompatible type in assignment to  (got , expected )\n");
	len += strlen(tokenStr) + strlen(gotType) + strlen(expectedType);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Incompatible type in assignment to %s (got %s, expected %s)\n", tokenStr, gotType, expectedType);
	return errorStr;
}

char* printIncompatibleTypeStatementError(char* statementStr, char* gotType, char* expectedType) {
	int len = 0;
	len += strlen("Incompatible type in  statement (got , expected )\n");
	len += strlen(statementStr) + strlen(gotType) + strlen(expectedType);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Incompatible type in %s statement (got %s, expected %s)\n", statementStr, gotType, expectedType);
	return errorStr;
}

char* printOperatorTypeError(char* op, char* type) {
	int len = 0;
	len += strlen("Operator  cannot be applied to type \n");
	len += strlen(op) + strlen(type);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Operator %s cannot be applied to type %s\n", op, type);
	return errorStr;
}

char* printOperatorTypesError(char* op, char* leftType, char* rightType) {
	int len = 0;
	len += strlen("Operator  cannot be applied to types , \n");
	len += strlen(op) + strlen(leftType) + strlen(rightType);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Operator %s cannot be applied to types %s, %s\n", op, leftType, rightType);
	return errorStr;
}

char* printSymbolAlreadyDefinedError(char* tokenStr) {
	int len = 0;
	len += strlen("Symbol  already defined\n");
	len += strlen(tokenStr);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Symbol %s already defined\n", tokenStr);
	return errorStr;
}

char* printSymbolNotDefinedError(char* tokenStr) {
	int len = 0;
	len += strlen("Symbol  not defined\n");
	len += strlen(tokenStr);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Symbol %s not defined\n", tokenStr);
	return errorStr;
}

char* printTypeIdentifierExpectedError() {
	int len = strlen("Type identifier expected\n");
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Type identifier expected\n");
	return errorStr;
}

char* printVariableIdentifierExpectedError() {
	int len = strlen("Variable identifier expected\n");
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Variable identifier expected\n");
	return errorStr;
}

char* printWrongNumberCallFunctionError(char* tokenStr, int gotNArgs, int expectedNArgs) {
	int len = 0;
	len += MAX_INT_LEN * 2;
	len += strlen("Wrong number of arguments in call to function  (got , expected )\n");
	len += strlen(tokenStr);
	char* errorStr = malloc(sizeof(char) * len);
	sprintf(errorStr, "Wrong number of arguments in call to function %s (got %d, expected %d)\n", tokenStr, gotNArgs, expectedNArgs);
	return errorStr;
}




