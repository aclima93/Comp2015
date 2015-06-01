


#include "LLVMCode.h"


void printLLVM(table* st_root, node* ast_root){

	labelCounter = 1;
	tabCounter = 1;

	printLLVMHeader();

	printLLVMCode(st_root, ast_root);
}

void printLLVMHeader(){

	// helper functions
	printf("\n\n");
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
    printf("@str.blank_line = private unnamed_addr constant [2 x i8] c\"\\0A\\00\", align 1\n");
    printf("@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8]* @str.true, i32 0, i32 0)]\n");
    printf("\n\n");

    // definição da função paramcount
    printf("define i32 @paramcount(){\n\n");
    printf("\tret i32 0\n");
	printf("}\n\n");
}

void printLLVMCodeChildren(table* cur_scope, node* cur_node){

	printLLVMCode(cur_scope, cur_node->field1);
	printLLVMCode(cur_scope, cur_node->field2);
	printLLVMCode(cur_scope, cur_node->field3);
}

void printLLVMCode(table* cur_scope, node* cur_node){

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
			printLLVMCode(curFunctionScope, progBlock->field2);

			//
			// create a function stub for LLVM's main function from the program's VarPart and StatPart

			// change the title to "main" and add a return type
			node* progFuncHeading = makenode(FuncHeadingType, cur_node->field1, NULL, NULL, -1, -1);

			// "glue" the VarPart and StatPart nodes together so that they can be called with generateLLVMFunction()
			node* progFuncBlock = makenode(FuncDefinitionType, progBlock->field1, progBlock->field3, NULL, -1, -1);

			// print LLVM's main function and its body
			node* mainFuncNode = makenode(FuncDefinitionType, progFuncHeading, progFuncBlock, NULL, -1, -1);
			curFunctionScope = cur_scope;
			generateLLVMFunction(mainFuncNode, 1);

			break;

		case FuncDeclarationListType:

			; // very importnt voodoo magic ;)

			node* funcNode = cur_node->field1;
			node* funcHeading = funcNode->field1;
			node* funcID = funcHeading->field1;
			char* funcIDStr = funcID->field1;
			curFunctionScope = lookupFuncSymbolInAllTables(funcIDStr, 0);
			generateLLVMFunction(funcNode, 0);
			printLLVMCode(curFunctionScope, cur_node->field2);

			break;

		default:
			printLLVMCodeChildren(curFunctionScope, cur_node);
			break;
	}

}

void generateLLVMFunction(node* funcNode, int isMainFunc){

	// we can't define the function in LLVM with just a declaration, wait for the actual definition later on
	if( funcNode->field2 == NULL )
		return;

    // "regular" function declaration and definition
    if( funcNode->type_of_node == FuncDefinitionType){

    	node* funcHeading = funcNode->field1;
    	node* funcBlock = funcNode->field2;

	    node* funcReturnType = funcHeading->field3;
	    node* funcID = funcHeading->field1;
	    char* funcIDStr = funcID->field1;

	    // function header
	    if( isMainFunc ){

			localVarCounter = LOCAL_VAR_COUNTER_START;

		    printf("define void @main(i32 %%argc, i8** %%argv) #0 {\n\n");
	    	printf("\t%%1 = alloca i32, align 4\n");
			printf("\t%%2 = alloca i32, align 4\n");
			printf("\t%%3 = alloca i8**, align 8\n");
			printf("\tstore i32 0, i32* %%1\n");
			printf("\tstore i32 %%argc, i32* %%2, align 4\n");
			printf("\tstore i8** %%argv, i8*** %%3, align 8\n\n");
		}
		else{

			localVarCounter = 1;

		    printf("define %s @%s(", getLLVMTypeStrFromNodeStr(funcReturnType->field1), funcIDStr);

	    	// function parameters (quadratic complexity!)
		    generateLLVMFunctionParameters(funcHeading->field2);
		    printf("){\n\n");
		}

	    //Save arguments to stack
	    if( isMainFunc ){
			saveLLVMFunctionParamaterInStack("program", 1);
	    }
	    else{
			saveLLVMFunctionParamaterInStack(funcIDStr, 0);
		}

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
	    printTabCounter();
	    if( isMainFunc ){
	    	printf("ret void\n");
	    }
	    else{
	    	printf("ret %s 0\n", getLLVMTypeStrFromNodeStr(funcReturnType->field1));
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
        		printf("%s %%%s.param", formalParamsIDListTypeStr, strlwr(formalParamID->field1)); // because Pascal is case-insensitive
        	}
        	else{
	        	printf(", %s %%%s.param", formalParamsIDListTypeStr, strlwr(formalParamID->field1));// because Pascal is case-insensitive
	        }
        	formalParamsIDList = formalParamsIDList->field2;
        }

        formalParamList = formalParamList->field2;
    }
}

void saveLLVMFunctionParamaterInStack(char* funcIDStr, int isMainFunc){
    
	table* localTable = lookupFuncSymbolInAllTables(funcIDStr, isMainFunc);

	if( localTable != NULL ){

		symbol* aux3 = localTable->symbol_variables;
		char* symTypeStr = getLLVMTypeStr( getLLVMTypeFromPredefType(aux3->type) );

		while( aux3 != NULL){
			if(aux3->flag == paramFlag){

				char* varStr = strlwr(aux3->name); // because Pascal is case-insensitive!
				printTabCounter();
				printf("%%%s = alloca %s\n", varStr, symTypeStr);
				printTabCounter();
				printf("store %s %%%s.param, %s* %%%s\n", symTypeStr, varStr, symTypeStr, varStr);

			}
			aux3 = aux3->nextSymbol;
		}
	}
}

void generateLLVMLocalVar(node* varDeclarationNode){

    node* IDList = varDeclarationNode->field1;
    node* IDListType = varDeclarationNode->field2;
    char* llvmType = getLLVMTypeStrFromNode(IDListType);
    node* IDNode;

    while( IDList != NULL){

    	IDNode = IDList->field1;
    	printTabCounter();
        printf("%%%s = alloca %s\n", strlwr(IDNode->field1), llvmType); // because Pascal is case-insensitive!
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

	
	LLVMReturnReff returnReff;
	
	incrementTabCounter();

    if(statement->type_of_node == CompStatType){

        generateLLVMStatementList(statement->field1);
    }
    else if(statement->type_of_node == IfElseStatType){

    	// new label, increment counter
        COUNTER_TYPE labelNum = getAndIncrementLabelCounter();

        returnReff = generateLLVMExpression(statement->field1);

        printTabCounter();
        printf("br i1 %%%d, label %%if.then%d, label %%if.else%d\n\n", returnReff.returnVarNum, labelNum, labelNum);

		printTabCounter();
        printf("if.then%d:\n", labelNum);
        generateLLVMStatement(statement->field2);
        printTabCounter();
        printf("\tbr label %%if.end%d\n\n", labelNum);

        printTabCounter();
        printf("if.else%d:\n", labelNum);
        generateLLVMStatement(statement->field3);
        printTabCounter();
        printf("\tbr label %%if.end%d\n\n", labelNum);

        printTabCounter();
        printf("if.end%d:\n", labelNum);

    }
    else if(statement->type_of_node == WhileStatType){

		// new label, increment counter
        COUNTER_TYPE labelNum = getAndIncrementLabelCounter();

        printTabCounter();
        printf("\tbr label %%while.start%d\n\n", labelNum);

        printTabCounter();
        printf("while.start%d:\n", labelNum);
        
		returnReff = generateLLVMExpression(statement->field1);
        
        printTabCounter();
        printf("\tbr i1 %%%d, label %%while.do%d, label %%while.end%d\n\n", returnReff.returnVarNum, labelNum, labelNum);

        printTabCounter();
        printf("while.do%d:\n", labelNum);

        generateLLVMStatement(statement->field2);

        printTabCounter();
        printf("\tbr label %%while.start%d\n\n", labelNum);

        printTabCounter();
        printf("while.end%d:\n", labelNum);
    }
    else if(statement->type_of_node == WriteLnStatType){

    	// percorrer a lista de argumentos da chamda ao writeln e imprimi-los

    	if( statement == NULL){
			printf("%%%d = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @str.blank_line, i32 0, i32 0))", getAndIncrementLocalVarCounter());
    	}
    	else{

	        while( statement != NULL ){

		        returnReff = generateLLVMExpression(statement->field1);

		        if(returnReff.returnVarType == llvm_i32){

		        	printTabCounter();
		            printf("call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @str.int_lit, i32 0, i32 0), i32 %%%d)\n\n", returnReff.returnVarNum);
		        }
		        else if(returnReff.returnVarType == llvm_i1){

		        	printTabCounter();
		            printf("%%%d = zext i1 %%%d to i32\n", getAndIncrementLocalVarCounter(), returnReff.returnVarNum);
		            printTabCounter();
		            printf("%%%d = getelementptr inbounds [2 x i8*]* @str.bools, i32 0, i32 %%%d\n", getAndIncrementLocalVarCounter(), localVarCounter -1);
		            printTabCounter();
		            printf("%%%d = load i8** %%%d\n", getAndIncrementLocalVarCounter(), localVarCounter -1);
		            printTabCounter();
		            printf("call i32 (i8*, ...)* @printf(i8* %%%d)\n\n", localVarCounter -1);
		        }
		        else if(returnReff.returnVarType == llvm_double){

		        	printTabCounter();
		        	printf("call double (i8*, ...)* @printf(i8* getelementptr inbounds ([8 x i8]* @str.real_lit, double 0, double 0), double %%%d)\n\n", returnReff.returnVarNum);
		        }
		        else if( returnReff.returnVarType == llvm_i8 ){
		        	// TODO
		        	// imprimir string
		        }

		        getAndIncrementLocalVarCounter();
		        statement = statement->field2;
		    }
		}

    }
    else if(statement->type_of_node == RepeatStatType){

    }
    else if(statement->type_of_node == ValParamStatType){

    }
    else if(statement->type_of_node == AssignStatType){

    	node* IDNode = statement->field1;
		returnReff = generateLLVMExpression(statement->field2);

		symbol* aux = searchForSymbolInRelevantScopes(IDNode->field1, curFunctionScope);
		char* symTypeStr = getLLVMTypeStr( getLLVMTypeFromPredefType(aux->type) );

    	printTabCounter();
		printf("store %s* %%%s, %s* %%%d\n", symTypeStr, strlwr(IDNode->field1) , getLLVMTypeStr(returnReff.returnVarType), returnReff.returnVarNum );
    }

    decrementTabCounter();
}

LLVMReturnReff printLLVMExpression(node* expr, LLVMReturnReff leftExpr, LLVMReturnReff rightExpr, char* operation){

    LLVMReturnReff returnValue;
    char* llvmType = getLLVMTypeStr(leftExpr.returnVarType);

    returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    returnValue.returnVarType = leftExpr.returnVarType;

    printTabCounter();
    printf("%%%d = %s %s %%%d, %%%d\n\n", returnValue.returnVarNum, operation, llvmType, leftExpr.returnVarNum, rightExpr.returnVarNum);

    return returnValue;
}

LLVMReturnReff generateLLVMExpression(node* expr){

    LLVMReturnReff returnValue;

    if( expr == NULL ){
    	returnValue.returnVarType = llvm_null;
    	returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    	return returnValue;
    }

    if(expr->type_of_node == OPType){

        returnValue = printOPLLVMCode(expr);
    }
    else if(expr->type_of_node == UnaryOPType){

        returnValue = printUnaryOPLLVMCode(expr);
    }
    else if(expr->type_of_node == IDType){

        returnValue.returnVarType = getLLVMTypeFromPredefType( searchForTypeOfSymbolInRelevantScopes(expr->field1, curFunctionScope)) ;
        returnValue.returnVarNum = getAndIncrementLocalVarCounter();

        printTabCounter();
        printf("%%%d = load %s* %%%s\n", returnValue.returnVarNum, getLLVMTypeStr(returnValue.returnVarType), strlwr(expr->field1) );
        
    }
    else if(expr->type_of_node == IntType){

		printTabCounter();
        printf("%%%d = add i32 0, %d\n", returnValue.returnVarNum, atoi(expr->field1));
        returnValue.returnVarType = llvm_i32;
    }
    else if(expr->type_of_node == DoubleType){

		double d;
		sscanf(expr->field1, "%lf", &d);
		printTabCounter();
        printf("%%%d = add double 0, %f.12E\n", returnValue.returnVarNum, d);
        returnValue.returnVarType = llvm_double;
    }
	/*
    else if(opNode->type_of_node == CallType){

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

		printTabCounter();
        printf("%%%d = call %s @%s(", getAndIncrementLocalVarCounter(), llvmType, expr->idOrLit);
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
    else{
    	returnValue.returnVarType = llvm_null;
    	returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    }

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

		printTabCounter();
        printf("%%%d = add %s 0, %%%d\n\n", returnValue.returnVarNum, getLLVMTypeStr(exprId.returnVarType), exprId.returnVarNum);
    }
	else if( strcasecmp ( "-", op_str ) == 0){

		printTabCounter();
        printf("%%%d = sub %s 0, %%%d\n\n", returnValue.returnVarNum, getLLVMTypeStr(exprId.returnVarType), exprId.returnVarNum);
    }
	else if( strcasecmp ( "not", op_str ) == 0){

		printTabCounter();
        printf("%%%d = icmp ne i1 %%%d, 0\n", returnValue.returnVarNum, exprId.returnVarNum);
        printTabCounter();
        printf("%%%d = xor i1 %%%d, true\n\n", localVarCounter, returnValue.returnVarNum);
        returnValue.returnVarNum = getAndIncrementLocalVarCounter();
    }

	returnValue.returnVarType = exprId.returnVarType;

    return returnValue;
}

LLVMReturnReff printOPLLVMCode(node* expr){

	node* op_expr = expr->field2;
	char* op_str = op_expr->field1;

	// new label, increment counter
    COUNTER_TYPE labelNum = getAndIncrementLabelCounter();
	LLVMReturnReff returnValue;

	COUNTER_TYPE resVarNumber = getAndIncrementLocalVarCounter();
	LLVMReturnReff leftExpr = generateLLVMExpression(expr->field1);
	LLVMReturnReff rightExpr = generateLLVMExpression(expr->field3);

	LLVMType exprType = getLLVMTypeToUseInOP(op_str, leftExpr.returnVarNum, rightExpr.returnVarNum);

	if( strcasecmp ( "and", op_str ) == 0){

        //res = a
        printTabCounter();
        printf("%%%d = alloca i1\n", resVarNumber);
        printTabCounter();
        printf("store i1 %%%d, i1* %%%d\n", leftExpr.returnVarNum, resVarNumber);

        //if(a)
        printTabCounter();
        printf("%%%d = icmp eq i1 1, %%%d\n", getAndIncrementLocalVarCounter(), leftExpr.returnVarNum);
        printTabCounter();
        printf("br i1 %%%d, label %%and.do%d, label %%and.end%d\n\n", localVarCounter -1, labelNum, labelNum);

        //res = a
        printTabCounter();
        printf("and.do%d:\n", labelNum);
        printTabCounter();
        printf("\tstore i1 %%%d, i1* %%%d\n", rightExpr.returnVarNum, resVarNumber);
        printTabCounter();
        printf("\tbr label %%and.end%d\n\n", labelNum);

        printTabCounter();
        printf("and.end%d:", labelNum);
        printTabCounter();
        printf("\t%%%d = load i1* %%%d\n", getAndIncrementLocalVarCounter(), resVarNumber);

        returnValue.returnVarNum = localVarCounter -1;
        returnValue.returnVarType = llvm_i1;

	}
	else if( strcasecmp ( "or", op_str ) == 0){

	    //res = a
	    printTabCounter();
	    printf("%%%d = alloca i1\n", resVarNumber);
	    printTabCounter();
	    printf("store i1 %%%d, i1* %%%d\n", leftExpr.returnVarNum, resVarNumber);

	    //if(!a)
	    printTabCounter();
	    printf("%%%d = icmp eq i1 0, %%%d\n", getAndIncrementLocalVarCounter(), leftExpr.returnVarNum);
	    printTabCounter();
	    printf("br i1 %%%d, label %%or.do%d, label %%or.end%d\n\n", localVarCounter -1, labelNum, labelNum);

	    //res = a
	    printTabCounter();
	    printf("or.do%d:\n", labelNum);
	    printTabCounter();
	    printf("\tstore i1 %%%d, i1* %%%d\n", rightExpr.returnVarNum, resVarNumber);
	    printTabCounter();
	    printf("\tbr label %%or.end%d\n\n", labelNum);

		printTabCounter();
	    printf("or.end%d:", labelNum);
	    printTabCounter();
	    printf("\t%%%d = load i1* %%%d\n", getAndIncrementLocalVarCounter(), resVarNumber);

	    returnValue.returnVarNum = localVarCounter -1;
	    returnValue.returnVarType = llvm_i1;

	}
	else if( strcasecmp ( "<>", op_str ) == 0 || strcasecmp ( "<=", op_str ) == 0
		  || strcasecmp ( ">=", op_str ) == 0 || strcasecmp ( "<", op_str ) == 0 
		  || strcasecmp ( ">", op_str ) == 0 || strcasecmp ( "=", op_str ) == 0 ){

		char* llvmOpStr = getLLVMOperationForExpression(op_str, exprType);
        if( exprType == llvm_double ){
        	printTabCounter();
	        printf("%%%d = fcmp %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
        }
        else{
        	printTabCounter();
        	printf("%%%d = icmp %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
        }
		returnValue.returnVarNum = resVarNumber;
        returnValue.returnVarType = exprType;

	}
	else if( strcasecmp ( "+", op_str ) == 0 || strcasecmp ( "-", op_str ) == 0 
		  || strcasecmp ( "*", op_str ) == 0 || strcasecmp ( "/", op_str ) == 0
		  || strcasecmp ( "div", op_str ) == 0 ){

		char* llvmOpStr = getLLVMOperationForExpression(op_str, exprType);
        printTabCounter();
        printf("%%%d = %s %s %%%d, %%%d\n\n", resVarNumber, llvmOpStr, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);
		returnValue.returnVarNum = resVarNumber;
        returnValue.returnVarType = exprType;
	}
	else if( strcasecmp ( "mod", op_str ) == 0){

		printTabCounter();
        printf("%%%d = srem %s %%%d, %%%d\n\n", resVarNumber, getLLVMTypeStr(exprType), leftExpr.returnVarNum, rightExpr.returnVarNum);

        // srem instruction returns a negative modulo if the left expressions returns a negative integer
        // to make it positive we have to add the second integer to the result fo the modulous

        COUNTER_TYPE ifcond = getAndIncrementLocalVarCounter();
        COUNTER_TYPE ifcont = getAndIncrementLabelCounter();
        COUNTER_TYPE finalResVarNumber = getAndIncrementLocalVarCounter();

        printTabCounter();
		printf("%%%d = icmp slt i32 %%%d, 0", ifcond, leftExpr.returnVarNum);
		printTabCounter();
		printf("br i1 %%%d, label %%if.then%d, label %%if.else%d", ifcond, ifcont, ifcont);
		printTabCounter();
		printf("then:");
		printTabCounter();
		printf("\t%%%d = add i32 %%%d, %%%d", finalResVarNumber, resVarNumber, rightExpr.returnVarNum);
		printTabCounter();
		printf("\tbr label %%%d", ifcont);
		printTabCounter();
		printf("else:");
		printTabCounter();
		printf("\tbr label %%%d", ifcont);
		printTabCounter();
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


table* lookupFuncSymbolInAllTables(char *key, int isMainFunc) {

	table* cur_scope = STroot;
	table* cur_child_scope;

	table* lookup_result = getFuncScope(key, cur_scope);

	while( lookup_result == NULL && cur_scope != NULL) {

		cur_child_scope = cur_scope->childrenTableList;

		if( isMainFunc ){
			while(cur_child_scope != NULL && lookupProgramSymbol(key, cur_child_scope) == NULL) {
				cur_child_scope = cur_child_scope->nextSiblingTable;
			}
		}
		else{
			while(cur_child_scope != NULL && lookupFuncSymbol(key, cur_child_scope) == NULL) {
				cur_child_scope = cur_child_scope->nextSiblingTable;
			}
		}

		if(cur_child_scope != NULL){
			lookup_result = getFuncScope(key, cur_child_scope);
		}
		cur_scope = cur_scope->nextSiblingTable;
	}

	return lookup_result;
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
		return llvm_i8;
	}

	return llvm_null;
}

char* getLLVMTypeStr(LLVMType t){

	char* str[] = { "i1", "i8", "i32", "double", "i32"/*"This cannot show!"*/};
	return str[t];
}

LLVMType getLLVMTypeFromPredefType(PredefType t){

	if( t == _real_){
		return llvm_double;
	}
	else if( t == _integer_){
		return llvm_i32;
	}
	else if( t == _boolean_){
		return llvm_i1;
	}
	else if( t == _string_ ){
		return llvm_i8;
	}

	return llvm_null;
}

char* printCurLocalVar() {
    char* str = (char*) malloc(sizeof(COUNTER_TYPE));
    sprintf(str, "%%%d", localVarCounter);
    return str;
}

char* printCurLabelCounter() {
    char* str = (char*) malloc(sizeof(COUNTER_TYPE));
    sprintf(str, ".label%d", labelCounter);
    return str;
}

COUNTER_TYPE getAndIncrementLocalVarCounter(){
	COUNTER_TYPE temp = localVarCounter;
	localVarCounter += 1;
	return temp;
}

COUNTER_TYPE getAndIncrementLabelCounter(){
	COUNTER_TYPE temp = labelCounter;
	labelCounter += 1;
	return temp;
}

void printTabCounter(){
	COUNTER_TYPE temp = 0;
	while( temp < tabCounter ){
		printf("\t");
		temp++;
	}
}

void incrementTabCounter(){
	tabCounter +=1 ;
}

void decrementTabCounter(){
	tabCounter -= 1;
}



