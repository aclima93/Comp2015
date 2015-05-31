


#include "LLVMCode.h"


void printLLVM(node* ast_root){

	localVarCounter = 0;
	labelCounter = 0;
	returnLabelCounter = 0;

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

	if( cur_node == NULL ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	switch(t) {

		case ProgType:
			

			break;

		case ProgBlockType:

			// TODO: criar aqui a função "main" onde são chamadas as outras

			printLLVMCodeChildren(cur_node);
			break;

		case FuncDeclarationListType:

			generateLLVMFunction(cur_node->field1);
			printLLVMCode(cur_node->field2);

			break;

		case ExprType:

			// SimpleExpr OP2 SimpleExpr
			if(cur_node->field1 != NULL && cur_node->field1 != NULL){

				/*
				case DoubleType:
				case IntType:
				case IDType:
				case StringType:

					printf("%s(%s)\n", getLeafStr(t), cur_node->field1 );
					break;

				case CallType:

					printf("Id(%s)\n", (char*) cur_node->field1);
					break;

				case UnaryOPType:

					printUnaryOPLLVMCode(cur_node->field1);
					break;

				case OPType:
				
					printOP
				LLVMCode(cur_node->field1);
					break;
				*/
			}
			// SimpleExpr
			else{
			}

			printLLVMCodeChildren(cur_node);
			break;

		case SimpleExprType:
		case FactorType:
		case OPTermListType: 

			printLLVMCodeChildren(cur_node);
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

	    node* funcReturnType = funcHeading->field3;
	    node* funcID = funcHeading->field1;

	    //
	    // function header
	    printf("define %s @%s(", getLLVMTypeStrFromNode(funcReturnType->field1), funcID->field1);

	    //
	    // function parameters (cubic complexity! ouch)
	    node* formalParamList = funcHeading->field2;
	    node* formalParams;
		node* formalParamsIDList;
		char* formalParamsIDListTypeStr;
		node* formalParamID;
		char firstFormalParam = 1;

	    while( formalParamList != NULL){

	    	formalParams = formalParamList->field1;

	    	while( formalParams != NULL ){

		    	formalParamsIDList = formalParams->field1;
		    	formalParamsIDListTypeStr = getLLVMTypeStrFromNode(formalParams->field2);
		        
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
		        formalParams = formalParams->field2;
		    }
	        formalParamList = formalParamList->field2;
	    }

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

	    //Generate variable definition code
	    node* aux2 = funcBlockNode->field1;
	    while( aux2 != NULL){

	        generateLocalVar(aux2->field2);
	        aux2 = aux2->field1;
	    }

	    //Generate statements code
	    generateStmtList(funcBlockNode->field2);

	    //Add a default return
	    if(funcReturnType == VOID_T)
	        printf("\tret double 0\n");
	    else if(funcReturnType == INT_T)
	        printf("\tret i32 0\n");
	    else if(funcReturnType == BOOL_T)
	        printf("\tret i1 0\n");

	    printf("}\n\n");

	    */
	}
}


char* getLLVMTypeStrFromNode(node* cur_node){
	return getLLVMTypeStr(getLLVMTypeFromNode(cur_node));
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

		if( strcasecmp(cur_node->field1, "boolean") == 0 )
			return llvm_i1;
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

void printUnaryOPLLVMCode(char* op_str){

	if( strcasecmp ( "+", op_str ) == 0){

	}
	else if( strcasecmp ( "-", op_str ) == 0){

	}
	else if( strcasecmp ( "not", op_str ) == 0){

	}

}

void printOPLLVMCode(char* op_str){

	if( strcasecmp ( "and", op_str ) == 0){

	}
	else if( strcasecmp ( "or", op_str ) == 0){

	}
	else if( strcasecmp ( "<>", op_str ) == 0){

	}
	else if( strcasecmp ( "<=", op_str ) == 0){

	}
	else if( strcasecmp ( ">=", op_str ) == 0){

	}
	else if( strcasecmp ( "<", op_str ) == 0){

	}
	else if( strcasecmp ( ">", op_str ) == 0){

	}
	else if( strcasecmp ( "=", op_str ) == 0){

	}
	else if( strcasecmp ( "+", op_str ) == 0){

	}
	else if( strcasecmp ( "-", op_str ) == 0){

	}
	else if( strcasecmp ( "*", op_str ) == 0){

	}
	else if( strcasecmp ( "/", op_str ) == 0){

	}
	else if( strcasecmp ( "mod", op_str ) == 0){

	}
	else if( strcasecmp ( "div", op_str ) == 0){

	}
}


/* Counter printing functions */

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

char* printCurReturnLabel() {
    char* str = (char*) malloc(sizeof(int));
    sprintf(str, ".return%d", returnLabelCounter);
    return str;
}





