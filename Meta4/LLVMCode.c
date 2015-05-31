


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
			break;

		case SimpleExprType:
		case FactorType:
		case OPTermListType: 


			break;


		default:
			printLLVMCode(cur_node->field1);
			printLLVMCode(cur_node->field2);
			printLLVMCode(cur_node->field3);
			break;
	}

}

/*
void printLLVMFunction(node* methodDecl){

    localVarCounter = 1;
    curFunctionType = methodDecl->type;
    curFunctionName = methodDecl->id;
    currentLocalTable = getLocalTable(methodDecl->id);

    // function header
    printf("define %s @%s(", getLLVMTypeStr(methodDecl->type)), methodDecl->id);

    node* aux = methodDecl->paramList;
    if(aux != NULL){

        getLLVMTypeStr(aux->type);
        printf("%s %%%s.param", llvmgetLLVMTypeStr(aux->type), aux->id);
        aux = aux->next;
    }
    while( aux != NULL){

        printf(", %s %%%s.param", llvmType, aux->id);
        aux = aux->next;
    }

    printf(")\n{\n");

    //Save arguments to stack
    MethodTable* localTable = getLocalTable(methodDecl->id);
    MethodTableEntry* aux3 = localTable->entries;
    for(; aux3 != NULL; aux3 = aux3->next)
        if(aux3->isParam)
        {
            getLLVMTypeStr(aux3->type);
            printf("\t%%%s = alloca %s\n", aux3->id, llvmType);
            printf("\tstore %s %%%s.param, %s* %%%s\n", llvmType, aux3->id, llvmType, aux3->id);
        }

    //Generate variable definition code
    VarDeclList* aux2 = methodDecl->varDeclList;
    for(; aux2 != NULL; aux2 = aux2->next)
        genLocalVar(aux2->varDecl);

    //Generate statements code
    genStmtList(methodDecl->stmtList);

    //Add a default return
    if(strcmp(methodDecl->id, "main") == 0)
        printf("\tret i32 0\n");
    else
    {
        if(methodDecl->type == VOID_T)
            printf("\tret void\n");
        else if(methodDecl->type == INT_T)
            printf("\tret i32 0\n");
        else if(methodDecl->type == BOOL_T)
            printf("\tret i1 0\n");
    }

    printf("}\n\n");
}
*/


char* getLLVMTypeStr(LLVMType t){

	char* str[] = { "i1", "i32", "double"};
	return str[t];
}

void printUnaryOPLLVMCode(char* str){

	if( strcasecmp ( "+", str ) == 0){

	}
	else if( strcasecmp ( "-", str ) == 0){

	}
	else if( strcasecmp ( "not", str ) == 0){

	}

}

void printOPLLVMCode(char* str){

	if( strcasecmp ( "and", str ) == 0){

	}
	else if( strcasecmp ( "or", str ) == 0){

	}
	else if( strcasecmp ( "<>", str ) == 0){

	}
	else if( strcasecmp ( "<=", str ) == 0){

	}
	else if( strcasecmp ( ">=", str ) == 0){

	}
	else if( strcasecmp ( "<", str ) == 0){

	}
	else if( strcasecmp ( ">", str ) == 0){

	}
	else if( strcasecmp ( "=", str ) == 0){

	}
	else if( strcasecmp ( "+", str ) == 0){

	}
	else if( strcasecmp ( "-", str ) == 0){

	}
	else if( strcasecmp ( "*", str ) == 0){

	}
	else if( strcasecmp ( "/", str ) == 0){

	}
	else if( strcasecmp ( "mod", str ) == 0){

	}
	else if( strcasecmp ( "div", str ) == 0){

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





