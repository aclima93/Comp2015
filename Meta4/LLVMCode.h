


#ifndef LLVMCODE
#define LLVMCODE

#include "ASTree.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

#define LLVM_DEBUG_PRINTS 1

int localVarCounter;
int labelCounter;

typedef enum {
	llvm_i1, llvm_i32, llvm_double, llvm_null
} LLVMType;

/* 
 * Structure used to remember what LLVM object we are refferencing and its LLVM data type
 */

typedef struct {
	int returnVarNum;
	LLVMType returnVarType;
} LLVMReturnReff;

/* 
 * Main code generation printing functions
 */

void printLLVM(node* ast_root);
void printLLVMHeader();
void printLLVMCode(node* cur_node);

void generateLLVMFunction(node* funcNode);
void generateLLVMFunctionParameters(node* formalParamList);
void generateLLVMLocalVar(node* varDeclarationNode);

void generateLLVMStatementList(node* statementList);
void generateLLVMStatement(node* statement);

LLVMReturnReff printLLVMExpression(node* expr, LLVMReturnReff leftExpr, LLVMReturnReff rightExpr, char* operation);
LLVMReturnReff generateLLVMExpression(node* expr);

LLVMReturnReff printUnaryOPLLVMCode(node* expr);
LLVMReturnReff printOPLLVMCode(node* expr);

LLVMType getLLVMTypeToUseInOP(char* op, LLVMType leftType, LLVMType rightType);
char* getLLVMOperationForExpression(char* op, LLVMType resultType);

/* 
 * Auxiliary printing functions
 */

char* getLLVMTypeStrFromNodeStr(char* str);
char* getLLVMTypeStrFromNode(node* cur_node);
LLVMType getLLVMTypeFromStr(char* type_str);
LLVMType getLLVMTypeFromNode(node* cur_node);
char* getLLVMTypeStr(LLVMType t);

char* printCurLocalVar();
char* printCurLabelCounter();

int getAndIncrementLocalVarCounter();
int getAndIncrementLabelCounter();

#endif




