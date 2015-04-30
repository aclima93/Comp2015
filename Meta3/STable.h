


#ifndef STABLE
#define STABLE

#include "ASTree.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <search.h>
#include <ctype.h>

//#define DEBUG_WALKNODES 0

#define DEFINED 1
#define NOT_DEFINED 0

/*
 * Symbols
 */

typedef enum {
    _boolean_, _integer_, _real_, _function_, _program_, _type_, _true_, _false_, _NULL_
} PredefType;

typedef enum {
    constantFlag, returnFlag, paramFlag, varparamFlag, NULLFlag
} PredefFlag;

typedef struct {
    char* name;
    PredefType type;
    PredefFlag flag;
    char* value;
    int isDefined;
} symbol;

/*
 * Tables
 */

typedef enum {
    outerTable, programTable, functionTable
} PredefTable;

typedef struct {
    PredefTable type;
    void* symbol_variables;
    void* childrenTableList;
    void* nextSiblingTable;
    void* parentTable;
} table;

table* STroot;

int semanticErrorCounter;

int createSymbolTable(node* ASTroot);

void walkASTNodeChildren(table* cur_scope, node* cur_node, node* cur_declaration_type, PredefFlag cur_flag);

void walkASTNode(table* cur_scope, node* cur_node, node* cur_declaration_type, PredefFlag cur_flag);

char* getPredefFlagStr(PredefFlag f);

char* getPredefTypeStr(PredefType t);

PredefType getPredefTypeFromStr(char* t);

char* getPredefTableStr(PredefTable t);

/*
 * Insertions, printing and deletion functions
 */

table* makeTable(PredefTable t);

table* insertSiblingTable(table* cur_table, table* new_table);

table* insertChildTable(table* cur_table, table* new_table);

int lookup_compare(const void* l, const void* r);

int insert_compare(const void* l, const void* r);

void walker(const void *node, const VISIT which, const int depth);

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v, int d);

void insertSymbol(symbol* s, table* t);

symbol* lookupSymbol(symbol* s, table* t);

void printSymbol(symbol* s);

void printTable(table* t);

void printSiblings(table* cur_table);

void printAllSymbolTables( table* root_table );

char* strlwr(char* str);

/*
 * Error printing functions
 */

 void printErrorLineCol(int l, int c);

void printTypeError(char* type);

void printFunctionIDError();

void printIncompatibleTypeCallFunctionError(int num, char* functionStr, char* gotType, char* expectedType);

void printIncompatibleTypeAssignmentError(char* tokenStr, char* gotType, char* expectedType);

void printIncompatibleTypeStatementError(char* statementStr, char* gotType, char* expectedType);

void printOperatorTypeError(char* tokenStr, char* type);

void printOperatorTypesError(char* leftTokenStr, char* righttTokenStr, char* type);

void printSymbolAlreadyDefinedError(char* tokenStr);

void printSymbolNotDefinedError(char* tokenStr);

void printTypeIdentifierExpectedError();

void printVariableIdentifierExpectedError();

void printWrongNumberCallFunctionError(char* tokenStr, int gotNArgs, int expectedNArgs);

#endif




