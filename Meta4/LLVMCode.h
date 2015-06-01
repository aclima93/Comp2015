


#ifndef LLVMCODE
#define LLVMCODE

#include "ASTree.h"
#include "STable.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

#define LLVM_DEBUG_PRINTS 1

// greater range with unsigned variables
#define COUNTER_TYPE unsigned int
#define LOCAL_VAR_COUNTER_START 4

COUNTER_TYPE localVarCounter;
COUNTER_TYPE labelCounter;
COUNTER_TYPE tabCounter;
table* curFunctionScope;

typedef enum {
	llvm_i1, llvm_i8, llvm_i32, llvm_double, llvm_null
} LLVMType;

/* 
 * Structure used to remember what LLVM object we are refferencing and its LLVM data type
 */

typedef struct {
	COUNTER_TYPE returnVarNum;
	LLVMType returnVarType;
} LLVMReturnReff;

/* 
 * Main code generation printing functions
 */

void printLLVM(table* st_root, node* ast_root);
void printLLVMHeader();
void printLLVMCodeChildren(table* cur_scope, node* cur_node);
void printLLVMCode(table* cur_scope, node* cur_node);

void generateLLVMFunction(node* funcNode, int isMainFunc);
void generateLLVMFunctionParameters(node* formalParamList);
void saveLLVMFunctionParamaterInStack(char* funcIDStr, int isMainFunc);
void generateLLVMLocalVar(node* varDeclarationNode);

void generateLLVMStatementList(node* statementList);
void generateLLVMStatement(node* statement);

LLVMReturnReff printLLVMExpression(node* expr, LLVMReturnReff leftExpr, LLVMReturnReff rightExpr, char* operation);
LLVMReturnReff generateLLVMExpression(node* expr);

LLVMReturnReff printUnaryOPLLVMCode(node* expr);
LLVMReturnReff printOPLLVMCode(node* expr);

LLVMType getLLVMTypeToUseInOP(char* op, LLVMType leftType, LLVMType rightType);
char* getLLVMOperationForExpression(char* op, LLVMType resultType);

table* lookupFuncSymbolInAllTables(char *key, int isMainFunc);

/* 
 * Auxiliary printing functions
 */

char* getLLVMTypeStrFromNodeStr(char* str);
char* getLLVMTypeStrFromNode(node* cur_node);
LLVMType getLLVMTypeFromStr(char* type_str);
LLVMType getLLVMTypeFromNode(node* cur_node);
char* getLLVMTypeStr(LLVMType t);
LLVMType getLLVMTypeFromPredefType(PredefType t);

char* printCurLocalVar();
char* printCurLabelCounter();

COUNTER_TYPE getAndIncrementLocalVarCounter();
COUNTER_TYPE getAndIncrementLabelCounter();
void printTabCounter();
void incrementTabCounter();
void decrementTabCounter();

#endif




