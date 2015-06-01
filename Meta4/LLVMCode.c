


#include "LLVMCode.h"


void printLLVM(node* ast_root){

	localVarCounter = 1;
	labelCounter = 1;

	printLLVMHeader();

	printLLVMCode(ast_root);
}

void printLLVMHeader(){

	// helper functions
    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*) nounwind readonly\n");
    printf("\n\n");

	// global variables used for printing values 
	// --- booleans "TRUE" and "FALSE"
	// --- integer and real literals
	printf("@str.int_lit = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
	printf("@str.real_lit = private unnamed_addr constant [8 x i8] c\"%%f.12E\\0A\\00\"\n");
    printf("@str.false = private unnamed_addr constant [7 x i8] c\"FALSE\\0A\\00\"\n");
    printf("@str.true = private unnamed_addr constant [6 x i8] c\"TRUE\\0A\\00\"\n");
    printf("@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8]* @str.true, i32 0, i32 0)]\n");
    printf("\n\n");
}

void printLLVMCodeChildren(node* cur_node){

	printLLVMCode(cur_node->field1);
	printLLVMCode(cur_node->field2);
	printLLVMCode(cur_node->field3);
}

void printLLVMCode(node* cur_node){

	if( cur_node == NULL || isLeaf(cur_node) ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	switch(t) {

		case ProgType:
			
			; // very importnt voodoo magic ;)

			//
			// print the functions in FuncPart first so we can refference them in main
			node* progBlock = cur_node->field2;
			printLLVMCode(progBlock->field2);

			//
			// create a function stub for LLVM's main function from the program's VarPart and StatPart

			// change the title to "main" and add a return type
			node* progID = cur_node->field1;
			strcpy(progID->field1, "main");
			node* progFuncHeading = makenode(FuncHeadingType, progID, NULL, NULL, -1, -1);

			// "glue" the VarPart and StatPart nodes together so that they can be called with generateLLVMFunction()
			node* progFuncBlock = makenode(FuncDefinitionType, progBlock->field1, progBlock->field3, NULL, -1, -1);

			// print LLVM's main function and its body
			node* mainFuncNode = makenode(FuncDefinitionType, progFuncHeading, progFuncBlock, NULL, -1, -1);
			generateLLVMFunction(mainFuncNode);

			break;

		case ProgBlockType:

			printLLVMCodeChildren(cur_node);

			/*
			// print the functions first so we can refference them
			printLLVMCode(cur_node->field2);

			// pinrt LLVM's main function and its body
			generateLLVMMainFunction(cur_node->field1, cur_node->field1);
			*/

			break;

		case FuncDeclarationListType:

			generateLLVMFunction(cur_node->field1);
			printLLVMCode(cur_node->field2);

			break;

		default:
			printLLVMCodeChildren(cur_node);
			break;
	}

}

void generateLLVMFunction(node* funcNode){

	// we can't define the function in LLVM with just a declaration, wait for the actual definition later on
	if( funcNode->field2 == NULL )
		return;

    localVarCounter = 1;

    // "regular" function declaration and definition
    if( funcNode->type_of_node == FuncDefinitionType){

    	node* funcHeading = funcNode->field1;
    	node* funcBlock = funcNode->field2;

	    node* funcReturnType = funcHeading->field3;
	    node* funcID = funcHeading->field1;

	    // function header
	    if( strcmp(funcID->field1, "main") == 0){
		    printf("define void @%s(", funcID->field1);
		}
		else{
		    printf("define %s @%s(", getLLVMTypeStrFromNodeStr(funcReturnType->field1), funcID->field1);
		}

	    // function parameters (quadratic complexity!)
	    generateLLVMFunctionParameters(funcHeading->field2);

	    // begin function definition
	    printf(")\n{\n");

	    /*
	    //Save arguments to stack
	    table* localTable = getLocalTable(funcID->field1);

	    symbol* aux3 = localTable->entries;
	    while( aux3 != NULL){
	        if(aux3->isParam){

	            printf("\t%%%s = alloca %s\n", aux3->id, getLLVMTypeStr(aux3->type_of_node));
	            printf("\tstore %s %%%s.param, %s* %%%s\n", getLLVMTypeStr(aux3->type_of_node), aux3->id, getLLVMTypeStr(aux3->type_of_node), aux3->id);
	        }
	        aux3 = aux3->nextSymbol;
	    }
	    */

	    //Generate variable definition code
	    node* varPart = funcBlock->field1;

	    while( varPart != NULL){

	    	if( varPart->field1 != NULL){
		        generateLLVMLocalVar(varPart->field1);
	    	}
	        varPart = varPart->field2;
	    }

	    //Generate statements part code
	    node* compStat = funcBlock->field2;
	    generateLLVMStatementList(compStat->field1);
	    

	    //Add a default return
	    if( strcmp(funcID->field1, "main") == 0 ){
	    	printf("\tret void\n");
	    }
	    else{
	    	printf("\tret %s 0\n", getLLVMTypeStrFromNodeStr(funcReturnType->field1));
	    }

	    // close function definition
	    printf("}\n\n");

	}
}

void generateLLVMFunctionParameters(node* formalParamList){

    node* formalParams;
	node* formalParamsIDList;
	node* formalParamsIDListType;
	char* formalParamsIDListTypeStr;
	node* formalParamID;
	char firstFormalParam = 1;

    while( formalParamList != NULL){

    	formalParams = formalParamList->field1;
    	formalParamsIDList = formalParams->field1;
    	formalParamsIDListType = formalParams->field2;
    	formalParamsIDListTypeStr = getLLVMTypeStrFromNodeStr(formalParamsIDListType->field1);

    	while( formalParamsIDList != NULL ){

    		formalParamID = formalParamsIDList->field1;
        	if(firstFormalParam){
        		firstFormalParam = 0;
        		printf("%s %%%s.param", formalParamsIDListTypeStr, formalParamID->field1);
        	}
        	else{
	        	printf(", %s %%%s.param", formalParamsIDListTypeStr, formalParamID->field1);
	        }
        	formalParamsIDList = formalParamsIDList->field2;
        }

        formalParamList = formalParamList->field2;
    }
}

void generateLLVMLocalVar(node* varDeclarationNode){

    node* IDList = varDeclarationNode->field1;
    node* IDListType = varDeclarationNode->field2;
    char* llvmType = getLLVMTypeStrFromNode(IDListType);
    node* IDNode;

    while( IDList != NULL){

    	IDNode = IDList->field1;
        printf("\t%%%s = alloca %s\n", IDNode->field1, llvmType);
        IDList = IDList->field2;
    }

    printf("\n");
}

void generateLLVMStatementList(node* statementList){

    while( statementList != NULL){

        generateLLVMStatement(statementList->field1);
        statementList = statementList->field2;
    }
}

void generateLLVMStatement(node* statement){

	if(statement == NULL)
		return ;

    if(statement->type_of_node == CompStatType){

        generateLLVMStatementList(statement->field1);
    }
    else if(statement->type_of_node == IfElseStatType){

    	// new label, increment counter
        int labelNum = getAndIncrementLabelCounter();

        LLVMReturnReff returnReff = generateLLVMExpression(statement->field1);

        printf("\tbr i1 %%%d, label %%if.then%d, label %%if.else%d\n\n", returnReff.returnVarNum, labelNum, labelNum);

        printf("if.then%d:\n", labelNum);
        generateLLVMStatement(statement->field2);
        printf("\tbr label %%if.end%d\n\n", labelNum);

        printf("if.else%d:\n", labelNum);
        generateLLVMStatement(statement->field3);
        printf("\tbr label %%if.end%d\n\n", labelNum);

        printf("if.end%d:\n", labelNum);

    }
    else if(statement->type_of_node == WhileStatType){

		// new label, increment counter
        int labelNum = labelNum++;

        printf("\tbr label %%while.start%d\n\n", labelNum);

        printf("while.start%d:\n", labelNum);
        
		LLVMReturnReff returnReff = generateLLVMExpression(statement->field1);
        
        printf("\tbr i1 %%%d, label %%while.do%d, label %%while.end%d\n\n", returnReff.returnVarNum, labelNum, labelNum);

        printf("while.do%d:\n", labelNum);

        generateLLVMStatement(statement->field2);

        printf("\tbr label %%while.start%d\n", labelNum);

        printf("\nwhile.end%d:\n", labelNum);
    }
    else if(statement->type_of_node == WriteLnStatType){

    	// percorrer a lista de argumentos da chamda ao writeln e imprimi-los

        LLVMReturnReff ret;

        while( statement != NULL ){

	        ret = generateLLVMExpression(statement->field1);

	        if(ret.returnVarType == llvm_i32){

	            printf("\tcall i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @str.d, i32 0, i32 0), i32 %%%d)\n\n", ret.returnVarNum);
	        }
	        else if(ret.returnVarType == llvm_i1){

	            printf("\t%%%d = zext i1 %%%d to i32\n", getAndIncrementLocalVarCounter(), ret.returnVarNum);
	            printf("\t%%%d = getelementptr inbounds [2 x i8*]* @str.bools, i32 0, i32 %%%d\n", getAndIncrementLocalVarCounter(), localVarCounter -1);
	            printf("\t%%%d = load i8** %%%d\n", getAndIncrementLocalVarCounter(), localVarCounter -1);
	            printf("\tcall i32 (i8*, ...)* @printf(i8* %%%d)\n\n", localVarCounter -1);
	        }
	        else if(ret.returnVarType == llvm_double){
	        	/*
	        	// TODO how do i print a double in LLVM ?
	        	printf("\tcall i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @str.d, i32 0, i32 0), i32 %%%d)\n\n", ret.returnVarNum);
	        	*/
	        }

	        getAndIncrementLocalVarCounter();
	        statement = statement->field2;
	    }
    }
}

LLVMReturnReff printLLVMExpression(node* expr, LLVMReturnReff leftExpr, LLVMReturnReff rightExpr, char* operation){

    LLVMReturnReff returnValue;
    char* llvmType = getLLVMTypeStr(leftExpr.returnVarType);

    returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    returnValue.returnVarType = leftExpr.returnVarType;

    printf("\t%%%d = %s %s %%%d, %%%d\n\n", returnValue.returnVarNum, operation, llvmType, leftExpr.returnVarNum, rightExpr.returnVarNum);

    return returnValue;
}

LLVMReturnReff generateLLVMExpression(node* expr){

    LLVMReturnReff returnValue;
    LLVMReturnReff leftExprId, rightExprId;

    if(expr->type_of_node == OPType){

        returnValue = printOPLLVMCode(expr);
    }
    else if(expr->type_of_node == UnaryOPType){

        returnValue = printUnaryOPLLVMCode(expr);
    }
    /*
    else if(expr->type_of_node == IDType){

        char llvmType[MAX_LLVM_TYPE_SIZE];
        Type idType = getSymbolFromLocal(expr->idOrLit);

        returnValue.returnVarNum = getAndIncrementLocalVarCounter();

        if(idType != -1)
        {
            getLLVMTypeStr(leftExpr.idType);
            printf("\t%%%d = load %s* %%%s\n\n", returnValue.returnVarNum, llvmType, expr->idOrLit);
        }
        else
        {
            idType = getSymbolFromGlobal(expr->idOrLit);
            getLLVMTypeStr(leftExpr.idType);
            printf("\t%%%d = load %s* @%s\n\n", returnValue.returnVarNum, llvmType, expr->idOrLit);
        }

        returnValue.returnVarType = idType;
    }
    */
    else if(expr->type_of_node == IntType){

		returnValue.returnVarNum = getAndIncrementLocalVarCounter();
        printf("\t%%%d = add i32 0, %d\n", returnValue.returnVarNum, atoi(expr->field1));
        returnValue.returnVarType = llvm_i32;
    }
    else if(expr->type_of_node == DoubleType){

		returnValue.returnVarNum = getAndIncrementLocalVarCounter();
		double d;
		sscanf(expr->field1, "%lf", &d);
        printf("\t%%%d = add double 0, %f.12E\n", returnValue.returnVarNum, d);
        returnValue.returnVarType = llvm_double;
    }
    /*
    else if(expr->type_of_node == BOOLLIT_T)
    {
        if(strcmp(expr->idOrLit, "true") == 0) {
            printf("\t%%%d = add i1 0, 1\n", localVarCounter);
        }
        else {
            printf("\t%%%d = add i1 0, 0\n", localVarCounter);
        }        
        returnValue.returnVarNum = getAndIncrementLocalVarCounter();
        returnValue.returnVarType = llvm_i1;
    }
	*/
	/*
    else if(expr->type_of_node == CallType){

        char llvmType[MAX_LLVM_TYPE_SIZE];
        Type methodType = getMethodFromGlobal(expr->idOrLit);
        getLLVMTypeStr(leftExpr.methodType);

        //Count the amount of parameters
        int nParams = 0;
        ArgsList* aux = expr->argsList;
        for(; aux != NULL; aux = aux->next)
            nParams++;

        LLVMReturnReff* args = (LLVMReturnReff*) malloc(nParams * sizeof(LLVMReturnReff));

        int i;
        for(i=0, aux = expr->argsList; aux != NULL; aux = aux->next, i++)
            args[i] = generateLLVMExpression(aux->expr);

        printf("\t%%%d = call %s @%s(", getAndIncrementLocalVarCounter(), llvmType, expr->idOrLit);
        aux = expr->argsList;
        if(aux != NULL)
        {
            getLLVMTypeStr(leftExpr.args[0].type);
            printf("%s %%%d", llvmType, args[0].returnVarNum);
            aux = aux->next;
        }
        for(i=1 ; aux != NULL; aux = aux->next, i++)
        {
            getLLVMTypeStr(leftExpr.args[i].type);
            printf(", %s %%%d", llvmType, args[i].returnVarNum);
        }

        printf(")\n");

        free(args);

        returnValue.returnVarNum = localVarCounter -1;
        returnValue.returnVarType = methodType;
    }
    */

    return returnValue;
}

LLVMReturnReff printUnaryOPLLVMCode(node* expr){

	node* op_expr = expr->field2;
	char* op_str = op_expr->field1;

	LLVMReturnReff returnValue;
    LLVMReturnReff exprId;

    exprId = generateLLVMExpression(expr->field3);
    returnValue.returnVarNum = getAndIncrementLocalVarCounter();

	if( strcasecmp ( "+", op_str ) == 0){

        printf("\t%%%d = add %s 0, %%%d\n\n", returnValue.returnVarNum, getLLVMTypeStr(exprId.returnVarType), exprId.returnVarNum);
    }
	else if( strcasecmp ( "-", op_str ) == 0){

        printf("\t%%%d = sub %s 0, %%%d\n\n", returnValue.returnVarNum, getLLVMTypeStr(exprId.returnVarType), exprId.returnVarNum);
    }
	else if( strcasecmp ( "not", op_str ) == 0){

        printf("\t%%%d = icmp ne i1 %%%d, 0\n", returnValue.returnVarNum, exprId.returnVarNum);
        printf("\t%%%d = xor i1 %%%d, true\n\n", localVarCounter, returnValue.returnVarNum);
        returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    }

	returnValue.returnVarType = exprId.returnVarType;

    return returnValue;
}

LLVMReturnReff printOPLLVMCode(node* expr){

	node* op_expr = expr->field2;
	char* op_str = op_expr->field1;

	// new label, increment counter
    int labelNum = getAndIncrementLabelCounter();
	LLVMReturnReff returnValue;

	int resVarNumber = getAndIncrementLocalVarCounter();
	LLVMReturnReff leftExpr = generateLLVMExpression(expr->field1);
	LLVMReturnReff rightExpr = generateLLVMExpression(expr->field3);

	LLVMType exprType = getLLVMTypeToUseInOP(op_str, leftExpr.returnVarNum, rightExpr.returnVarNum);

	if( strcasecmp ( "and", op_str ) == 0){

        //res = a
        printf("\t%%%d = alloca i1\n", resVarNumber);
        printf("\tstore i1 %%%d, i1* %%%d\n", leftExpr.returnVarNum, resVarNumber);

        //if(a)
        printf("\t%%%d = icmp eq i1 1, %%%d\n", getAndIncrementLocalVarCounter(), leftExpr.returnVarNum);
        printf("\tbr i1 %%%d, label %%and.do%d, label %%and.end%d\n\n", localVarCounter -1, labelNum, labelNum);

        //res = a
        printf("and.do%d:\n", labelNum);
        printf("\tstore i1 %%%d, i1* %%%d\n", rightExpr.returnVarNum, resVarNumber);
        printf("\tbr label %%and.end%d\n\n", labelNum);

        printf("and.end%d:", labelNum);
        printf("%%%d = load i1* %%%d\n", getAndIncrementLocalVarCounter(), resVarNumber);

        returnValue.returnVarNum = localVarCounter -1;
        returnValue.returnVarType = llvm_i1;

	}
	else if( strcasecmp ( "or", op_str ) == 0){

	    //res = a
	    printf("\t%%%d = alloca i1\n", resVarNumber);
	    printf("\tstore i1 %%%d, i1* %%%d\n", leftExpr.returnVarNum, resVarNumber);

	    //if(!a)
	    printf("\t%%%d = icmp eq i1 0, %%%d\n", getAndIncrementLocalVarCounter(), leftExpr.returnVarNum);
	    printf("\tbr i1 %%%d, label %%or.do%d, label %%or.end%d\n\n", localVarCounter -1, labelNum, labelNum);

	    //res = a
	    printf("or.do%d:\n", labelNum);
	    printf("\tstore i1 %%%d, i1* %%%d\n", rightExpr.returnVarNum, resVarNumber);
	    printf("\tbr label %%or.end%d\n\n", labelNum);

	    printf("or.end%d:", labelNum);
	    printf("%%%d = load i1* %%%d\n", getAndIncrementLocalVarCounter(), resVarNumber);

	    returnValue.returnVarNum = localVarCounter -1;
	    returnValue.returnVarType = llvm_i1;

	}
	else if( strcasecmp ( "<>", op_str ) == 0 || strcasecmp ( "<=", op_str ) == 0
		  || strcasecmp ( ">=", op_str ) == 0 || strcasecmp ( "<", op_str ) == 0 
		  || strcasecmp ( ">", op_str ) == 0 || strcasecmp ( "=", op_str ) == 0 ){

		char* llvmOpStr = getLLVMOperationForExpression(op_str, exprType);
        if( exprType == llvm_double ){
	        printf("\t%%%d = fcmp %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
        }
        else{
        	printf("\t%%%d = icmp %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
        }
		returnValue.returnVarNum = resVarNumber;
        returnValue.returnVarType = exprType;

	}
	else if( strcasecmp ( "+", op_str ) == 0 || strcasecmp ( "-", op_str ) == 0 
		  || strcasecmp ( "*", op_str ) == 0 || strcasecmp ( "/", op_str ) == 0
		  || strcasecmp ( "div", op_str ) == 0 ){

		char* llvmOpStr = getLLVMOperationForExpression(op_str, exprType);
        printf("\t%%%d = %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
		returnValue.returnVarNum = resVarNumber;
        returnValue.returnVarType = exprType;
	}
	else if( strcasecmp ( "mod", op_str ) == 0){

        printf("\t%%%d = srem %s %%%d, %%%d\n\n", resVarNumber, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);

        // srem instruction returns a negative modulo if the left expressions returns a negative integer
        // to make it positive we have to add the second integer to the result fo the modulous

        int ifcond = getAndIncrementLocalVarCounter();
        int ifcont = getAndIncrementLabelCounter();
        int finalResVarNumber = getAndIncrementLocalVarCounter();

		printf("%%%d = icmp slt i32 %%%d, 0", ifcond, leftExpr.returnVarNum);
		printf("\tbr i1 %%%d, label %%if.then%d, label %%if.else%d", ifcond, ifcont, ifcont);
		printf("then:");
		printf("\t%%%d = add i32 %%%d, %%%d", finalResVarNumber, resVarNumber, rightExpr.returnVarNum);
		printf("\tbr label %%%d", ifcont);
		printf("else:");
		printf("\tbr label %%%d", ifcont);
		printf("%%%d:", ifcont);
		
		returnValue.returnVarNum = resVarNumber;
        returnValue.returnVarType = exprType;
	}
	else{

		char* llvmOpStr = getLLVMOperationForExpression(op_str, exprType);

        returnValue = printLLVMExpression(expr, leftExpr, rightExpr, llvmOpStr);
    }

    return returnValue;
}

LLVMType getLLVMTypeToUseInOP(char* op, LLVMType leftType, LLVMType rightType){

 	if (strcasecmp(op, "+") == 0 || strcasecmp(op, "-") == 0 || strcasecmp(op, "*") == 0) {
 		
 		// integer/real with integer/real
		if ( leftType == llvm_i32 && rightType == llvm_i32)
			return llvm_i32;
		else if ( (leftType == llvm_i32 || leftType == llvm_double) && (rightType == llvm_i32 || rightType == llvm_double) )
			return llvm_double;
 	}
 	else if (strcasecmp(op, "/") == 0)
 		return llvm_double;

 	else if (strcasecmp(op, "div") == 0 || strcasecmp(op, "mod") == 0) {
 		return llvm_i32;
 	}
 	else if (strcasecmp(op, ">") == 0 || strcasecmp(op, "<=") == 0 
 		  || strcasecmp(op, ">=") == 0 || strcasecmp(op, "<") == 0  
 		  || strcasecmp(op, "<>") == 0 || strcasecmp(op, "=") == 0 ) {
	
		if ( leftType == llvm_i32 && rightType == llvm_i32)
			return llvm_i32;
		else if ( leftType == llvm_i1 && rightType == llvm_i1)
			return llvm_i1;
		else if ( (leftType == llvm_i32 || leftType == llvm_double) && (rightType == llvm_i32 || rightType == llvm_double) )
			return llvm_double;
 	}
 	else if ((strcasecmp(op, "and") == 0 || strcasecmp(op, "or") == 0) ) {
		return llvm_i1;
 	}

 	return llvm_null;
}

char* getLLVMOperationForExpression(char* op, LLVMType resultType){

 	if (strcasecmp(op, "+") == 0){
 		return "add";
 	}
 	else if(strcasecmp(op, "-") == 0){
 		return "sub";
 	}
	else if(strcasecmp(op, "*") == 0){

		if ( resultType == llvm_i32)
			return "mul";
		else if ( resultType == llvm_double )
			return "fmul";
 	}
 	else if (strcasecmp(op, "/") == 0){

		if ( resultType == llvm_i32)
			return "sdiv";
		else if ( resultType == llvm_double )
			return "fdiv";
 	}
 	else if (strcasecmp(op, "div") == 0){
 		return "sdiv";
 	}
	else if(strcasecmp(op, "<>") == 0){
 		return "ne";
 	}
	else if( strcasecmp ( "<=", op ) == 0){
		return "sle";
	}
	else if( strcasecmp ( ">=", op ) == 0){
		return "sge";
	}
	else if( strcasecmp ( "<", op ) == 0){
		return "slt";
	}
	else if( strcasecmp ( ">", op ) == 0){
		return "sgt";
	}
	else if( strcasecmp ( "=", op ) == 0){
		return "eq";
	}
	// unused because of special cases
 	//else if( strcasecmp(op, "and" == 0 )
 	//else if( strcasecmp(op, "or") == 0 )
 	//else if( strcasecmp(op, "mod") == 0 )
 

 	return "llvm_null";
}




/* Aux functions */


char* getLLVMTypeStrFromNodeStr(char* str){
	return getLLVMTypeStr(getLLVMTypeFromStr(str));
}

char* getLLVMTypeStrFromNode(node* cur_node){
	return getLLVMTypeStr(getLLVMTypeFromNode(cur_node));
}

LLVMType getLLVMTypeFromStr(char* type_str){

	if( strcasecmp(type_str, "boolean") == 0 )
		return llvm_i1;

	if( strcasecmp(type_str, "real") == 0 )
		return llvm_double;

	if( strcasecmp(type_str, "integer") == 0 )
		return llvm_i32;

	if( strcasecmp(type_str, "string") == 0 )
		return llvm_null;

	return llvm_null;
}

LLVMType getLLVMTypeFromNode(node* cur_node){

	NodeType t = cur_node->type_of_node;

	if( t == DoubleType){
		return llvm_double;
	}
	else if( t == IntType){
		return llvm_i32;
	}
	else if( t == IDType ){
		return getLLVMTypeFromStr(cur_node->field1);
	}
	else if( t ==  StringType){
		return llvm_null;
	}

	return llvm_null;
}

char* getLLVMTypeStr(LLVMType t){

	char* str[] = { "i1", "i32", "double", "This cannot show!"};
	return str[t];
}

char* printCurLocalVar() {
    char* str = (char*) malloc(sizeof(int));
    sprintf(str, "%%%d", localVarCounter);
    return str;
}

char* printCurLabelCounter() {
    char* str = (char*) malloc(sizeof(int));
    sprintf(str, ".label%d", labelCounter);
    return str;
}

int getAndIncrementLocalVarCounter(){
	int temp = localVarCounter;
	localVarCounter += 1;
	return temp;
}

int getAndIncrementLabelCounter(){
	int temp = labelCounter;
	labelCounter += 1;
	return temp;
}




