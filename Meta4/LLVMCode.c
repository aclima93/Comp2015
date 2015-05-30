


#include "LLVMCode.h"


void printLLVM(node* ast_root){

	printLLVMHeader();

	printLLVMCode(ast_root);
}

void printLLVMHeader(){

	// helper functions
    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*) nounwind readonly\n");
    printf("\n");

	// global variables used for printing values 
	// --- booleans "TRUE" and "FALSE"
	// --- integer and real literals
    printf("@str.int_lit = private unnamed_addr constant [i32] c\"%%d\\0A\\00\"\n");
    printf("@str.real_lit = private unnamed_addr constant [double] c\"%%.12E\\0A\\00\"\n");
    printf("@str.false = private unnamed_addr constant [7 x i8] c\"FALSE\\0A\\00\"\n");
    printf("@str.true = private unnamed_addr constant [7 x i8] c\"TRUE\\0A\\00\\00\"\n");
    printf("@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8]* @str.true, i32 0, i32 0)]\n");
    printf("\n");
}

LLVMReturnReff printLLVMCode(node* cur_node){

	if( cur_node == NULL ){
		return;
	}

	NodeType t = cur_node->type_of_node;

	switch(t) {

		case ProgType:
			
			printLLVMCode(cur_node);
			break;

		case VarDeclarationType:
		case FuncPartType:
		case FuncDeclarationType:
		case FuncDefinitionType:
		case FuncDefinition2Type:
		case ParamsType:
		case VarPartType:
		case VarParamsType:


			printf("%s\n", getIndependantStr(t) );

			printLLVMCode(cur_node);
			break;

		case FuncHeadingType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printLLVMCode(cur_node);
			break;

		case FuncParamsListType:

			printLLVMCode(cur_node);
			break;

		case ProgBlockType:

			// TODO: criar aqui a função "main" onde são chamadas as outras

			break;

		case FuncIdentType:
		case FuncBlockType:
		case StatType:

			// print nothing, intermediate node
			// don't even increment dot counter

			printLLVMCode(cur_node);

			break;

		case IfElseStatType:

			printf("%s\n", getStatStr(t));

			printLLVMCode(cur_node);
			break;

		case RepeatStatType:
		case WhileStatType:
		case ValParamStatType:
		case AssignStatType:
		case WriteLnStatType:

			;
			char* stat_str = getStatStr(t);

			if( stat_str != NULL ){
				printf("%s\n", stat_str);
			}

			printLLVMCode(cur_node);
			break;

		case ExprType:

			// SimpleExpr OP2 SimpleExpr
			if(cur_node->field1 != NULL && cur_node->field1 != NULL){

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

					getUnaryOPStr(cur_node->field1);
					break;

				case OPType:
				
					printLLVMCodeOP(cur_node->field1);
					break;
			}
			// SimpleExpr
			else{
			}
			break;

		case SimpleExprType:
		case FactorType:
		case OPTermListType: 

			// the operator is always printed first
			// don't call printLLVMCode !!

			//printChildrenMiddleFirst(cur_node);

			break;

		case StatListType:
			
			printLLVMCode(cur_node);
			break;

		case FuncParamsListType2:
		case FuncDeclarationListType:
		case VarDeclarationListType:
		case IDListType:
		case CommaIDListType:
		case CompStatType:
		case WritelnPListType:
		case ParamListType:
		case ExprListType:

			// print nothing, intermediate node
			// don't even increment dot counter
			// all members are the same "depth"

			printLLVMCode(cur_node);

			break;

		case DoubleType:
		case IntType:
		case IDType:
		case StringType:
		case CallType:
		case UnaryOPType:
		case OPType:
			break;

		default:
			break;
	}

}

void printLLVMFunction(node* methodDecl){

    localVarCounter = 1;
    curFunctionType = methodDecl->type;
    curFunctionName = methodDecl->id;
    currentLocalTable = getLocalTable(methodDecl->id);

    //If generating main, adapt the type
    char llvmType[MAX_LLVM_TYPE_SIZE];
    if(strcmp(methodDecl->id, "main") == 0)
        getTypeLLVM(llvmType, INT_T);
    else
        getTypeLLVM(llvmType, methodDecl->type);

    printf("define %s @%s(", llvmType, methodDecl->id);

    ParamList* aux = methodDecl->paramList;
    if(aux != NULL)
    {
        getTypeLLVM(llvmType, aux->type);
        if(aux->type == STRINGARRAY) //If generating main, adapt the parameters
        {
            printf("i32 %%%s.len, ", aux->id);
            argCountName = aux->id;
        }
        printf("%s %%%s.param", llvmType, aux->id);

        aux = aux->next;
    }
    for(; aux != NULL; aux = aux->next)
    {
        getTypeLLVM(llvmType, aux->type);
        if(aux->type == STRINGARRAY) //If generating main, adapt the parameters
        {
            printf("i32 %%%s.len", aux->id);
            argCountName = aux->id;
        }
        printf(", %s %%%s.param", llvmType, aux->id);
    }

    printf(")\n{\n");

    //Save arguments to stack
    MethodTable* localTable = getLocalTable(methodDecl->id);
    MethodTableEntry* aux3 = localTable->entries;
    for(; aux3 != NULL; aux3 = aux3->next)
        if(aux3->isParam)
        {
            getTypeLLVM(llvmType, aux3->type);
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
        else if(methodDecl->type == INTARRAY)
            printf("\tret %%Int.Array {i32 0, i32* null}\n");
        else if(methodDecl->type == BOOLARRAY)
            printf("\tret %%Bool.Array {i32 0, i1* null}\n");
    }

    printf("}\n\n");
}

char* getUnaryOPStr(char* str){

	if( strcasecmp ( "+", str ) == 0){
		return "Plus";
	}
	else if( strcasecmp ( "-", str ) == 0){
		return "Minus";
	}
	else if( strcasecmp ( "not", str ) == 0){
		return "Not";
	}
	else{
		return NULL;
	}
}

char* printLLVMCodeOP(char* str){

	if( strcasecmp ( "and", str ) == 0){
		return "And";
	}
	else if( strcasecmp ( "or", str ) == 0){
		return "Or";
	}
	else if( strcasecmp ( "<>", str ) == 0){
		return "Neq";
	}
	else if( strcasecmp ( "<=", str ) == 0){
		return "Leq";
	}
	else if( strcasecmp ( ">=", str ) == 0){
		return "Geq";
	}
	else if( strcasecmp ( "<", str ) == 0){
		return "Lt";
	}
	else if( strcasecmp ( ">", str ) == 0){
		return "Gt";
	}
	else if( strcasecmp ( "=", str ) == 0){
		return "Eq";
	}
	else if( strcasecmp ( "+", str ) == 0){
		return "Add";
	}
	else if( strcasecmp ( "-", str ) == 0){
		return "Sub";
	}
	else if( strcasecmp ( "*", str ) == 0){
		return "Mul";
	}
	else if( strcasecmp ( "/", str ) == 0){
		return "RealDiv";
	}
	else if( strcasecmp ( "mod", str ) == 0){
		return "Mod";
	}
	else if( strcasecmp ( "div", str ) == 0){
		return "Div";
	}
	else{
		return NULL;
	}
}


/* Counter printing functions */
char* printCurVar() {
    char* str = (char*) malloc(sizeof(int));
    sprintf(str, "%%%d", varCounter);
    return str;
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

char* printCurReturnLabel() {
    char* str = (char*) malloc(sizeof(int));
    sprintf(str, ".return%d", returnLabelCounter);
    return str;
}





