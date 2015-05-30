


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

/* Counts current local variables. Don't forget to reset it once we start a new method! */

int varCounter = 0;
int localVarCounter = 0;
int labelCounter = 0;
int returnLabelCounter = 0;

/* Structure used to remember what LLVM object we are refferencing and its LLVM data type, namely in complex expressions */
typedef struct {
	int tempVarNum;
	LLVMType type;
} LLVMReturnReff;

/* Main code generation printing functions */

void printLLVM(node* ast_root);
void printLLVMHeader();
void printLLVMCode(node* cur_node);
void printChildrenLLVMCode(node* cur_node);

/* Counter printing functions */

char* printCurVar();
char* printCurLocalVar();
char* printCurLabelCounter();
char* printCurReturnLabel();

#endif




