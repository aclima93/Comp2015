
#ifndef CUSTOM_STRUCTURES
#define CUSTOM_STRUCTURES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 1

typedef enum {ProgType, ProgHeadingType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, FuncDeclarationListType, FuncDeclarationType, FuncHeadingType, FuncIdentType, FormalParamsListType, FormalParamsType, FuncBlockType, StatPartType, CompStatType, StatListType, StatType, WritelnPListType, ExprType, ExprListType, ParamListType, DoubleType, StringType, OPType, IntType} nodeType;

typedef struct {
    nodeType type_of_node;
    void* field1;
    void* field2;
    void* field3;
    void* next;
} node;

node* root;

int dotCounter;

void incrementDotCounter();

void decrementDotCounter();

void printDots();

void printList(node* cur_node);

void printNode(node* cur_node);

node* makenode(nodeType t, node* f1, node* f2, node* f3);

node* makeleafInt(int* i);

node* makeleafOP(char* o);

node* makeleafString(char* s);

node* makeleafDouble(double* d);

node* createTree(node* n);

void freeNode(node* cur_node);

#endif