
#ifndef CUSTOM_STRUCTURES
#define CUSTOM_STRUCTURES

#include <stdlib.h>
#include <stdio.h>

typedef enum {ProgType, ProgHeadingType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, FuncDeclarationListType, FuncDeclarationType, FuncHeadingType, FuncIdentType, FormalParamsListType, FormalParamsType, FuncBlockType, StatPartType, CompStatType, StatListType, StatType, WritelnPListType, ExprType, OPType, ParamListType} nodeType;

typedef struct {
    nodeType type_of_node;
    void* field1;
    void* field2;
    void* field3;
} node;

node* makenode(nodeType t, node* f1, node* f2, node* f3);

node* makeleafInt(int i);

node* makeleafOP(char* s);

node* makeleafString(char* s);

node* makeleafDouble(double d);

#endif