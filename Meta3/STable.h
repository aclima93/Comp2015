


#ifndef STABLE
#define STABLE

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>

typedef enum {
    _boolean_, _integer_, _real_, _function_, _program_, _type_, _true_, _false_
} PredefType;

typedef enum {
    constantFlag, returnFlag, paramFlag, varparamFlag
} PredefFlag;

typedef struct {
    char* symname;
    PredefType type;
    PredefFlag flag;
    char* sim_value;
} symbol;

typedef enum {
    outerTable, programTable, functionTable
} PredefTable;

/*
bool comparison_function(char* name, symbol* sym){
    return true;
}

typedef struct {
    PredefTable type;
    void* next;
    map <char*, symbol*, comparison_function> symbol_variables;
} table;

*/

#endif




