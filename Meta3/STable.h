


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
#define INSERTION_DEBUG 0
#define LOOKUP_DEBUG 0


// don't change these
#define DEFINED 1
#define NOT_DEFINED 0

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

/*
 * Symbols
 */

typedef enum {
    _boolean_, _integer_, _real_, _function_, _program_, _type_, _true_, _false_, _string_, _NULL_
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
    table* declarationScope;
} symbol;

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

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v, int d, table* scope);

void insertSymbol(symbol* s, table* t);

symbol* lookupSymbol(char* key, table* t);

void printSymbol(symbol* s);

void printTable(table* t);

void printSiblings(table* cur_table);

void printAllSymbolTables( table* root_table );

char* strlwr(char* str);

/*
 * Error printing functions
 */

 int isValidWriteLnArgument(PredefType p);

PredefType outcomeOfOperation(char* op, PredefType leftType, PredefType rightType);

int isValidOperation(char* op, PredefType leftType, PredefType rightType);

PredefType outcomeOfUnaryOperation(char* op, PredefType rightType);

int isValidUnaryOperation(char* op, PredefType rightType);

PredefType getPredefTypeOfExpr(node* cur_node, table* cur_scope);

PredefType getPredefTypeOfSimpleExpr(node* cur_node, table* cur_scope);

PredefType getPredefTypeOfTerm(node* cur_node, table* cur_scope);

PredefType getPredefTypeOfFactor(node* cur_node, table* cur_scope);

PredefType getPredefTypeOfNode(node* cur_node, table* cur_scope);

PredefType searchForTypeOfSymbolInRelevantScopes(node* cur_node, table* cur_scope);

symbol* searchForSymbolInRelevantScopes(node* cur_node, table* cur_scope);

table* getFuncScope(char* key, table* cur_scope);

void printErrorLineCol(int l, int c, char* errorStr);

char* printTypeError(char* type);

char* printFunctionIDError();

char* printIncompatibleTypeCallFunctionError(int num, char* functionStr, char* gotType, char* expectedType);

char* printIncompatibleTypeAssignmentError(char* tokenStr, char* gotType, char* expectedType);

char* printIncompatibleTypeStatementError(char* statementStr, char* gotType, char* expectedType);

char* printOperatorTypeError(char* op, char* type);

char* printOperatorTypesError(char* op, char* leftType, char* rightType);

char* printSymbolAlreadyDefinedError(char* tokenStr);

char* printSymbolNotDefinedError(char* tokenStr);

char* printTypeIdentifierExpectedError();

char* printVariableIdentifierExpectedError();

char* printWrongNumberCallFunctionError(char* tokenStr, int gotNArgs, int expectedNArgs);

#endif




