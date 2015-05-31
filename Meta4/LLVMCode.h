


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


int localVarCounter;
int labelCounter;
int returnLabelCounter;

typedef enum {
	llvm_i1, llvm_i32, llvm_double, llvm_null
} LLVMType;

/* 
 * Structure used to remember what LLVM object we are refferencing and its LLVM data type
 */

typedef struct {
	int returnVarNum;
	LLVMType type;
} LLVMReturnReff;

/* 
 * Main code generation printing functions
 */

void printLLVM(node* ast_root);
void printLLVMHeader();
void printLLVMCode(node* cur_node);
void generateLLVMFunction(node* funcNode);

/* 
 * Auxiliary printing functions
 */

char* getLLVMTypeStrFromNode(node* cur_node);
LLVMType getLLVMTypeFromNode(node* cur_node);
char* getLLVMTypeStr(LLVMType t);
char* printCurLocalVar();
char* printCurLabelCounter();
char* printCurReturnLabel();

#endif




