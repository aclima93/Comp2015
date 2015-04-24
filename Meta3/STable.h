


#ifndef STABLE
#define STABLE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <search.h>

/*
 * Symbols
 */

typedef enum {
    _boolean_, _integer_, _real_, _function_, _program_, _type_, _true_, _false_
} PredefType;

typedef enum {
    constantFlag, returnFlag, paramFlag, varparamFlag
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

/*
 * Insertions, printing and deletion functions
 */

int lookup_compare(const void* l, const void* r);

int insert_compare(const void* l, const void* r);

void walker(const void *node, const VISIT which, const int depth);

symbol makeSymbol(char* n, PredefType t, PredefFlag f, char* v);

void insertSymbol(symbol* s, void* table);

symbol lookupSymbol(symbol* s, void* table);

void printTable(void* table);

#endif




