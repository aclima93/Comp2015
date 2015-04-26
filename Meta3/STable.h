


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
    void* nextTable;
} table;

table* STroot;

int semanticErrorCounter;

int createSymbolTable(node* ASTroot);

void walkASTNodeChildren(table* cur_scope, node* cur_node, node* cur_declaration_type);

void walkASTNode(table* cur_scope, node* cur_node, node* cur_declaration_type);

char* getPredefFlagStr(PredefFlag f);

char* getPredefTypeStr(PredefType t);

PredefType getPredefTypeFromStr(char* t);

char* getPredefTableStr(PredefTable t);

/*
 * Insertions, printing and deletion functions
 */

 table* makeTable(PredefTable t);

int lookup_compare(const void* l, const void* r);

int insert_compare(const void* l, const void* r);

void walker(const void *node, const VISIT which, const int depth);

symbol* makeSymbol(char* n, PredefType t, PredefFlag f, char* v);

void insertSymbol(symbol* s, table* t);

symbol* lookupSymbol(symbol* s, table* t);

void printSymbol(symbol* s);

void printTable(table* t);

void printSymbolTables( table* root_table );

char* strlwr(char* str);

#endif




