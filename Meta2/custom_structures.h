
#ifndef CUSTOM_STRUCTURES
#define CUSTOM_STRUCTURES

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>
#include <unistd.h>


#define DEBUG 0

typedef enum {ProgType, ProgHeadingType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, FuncDeclarationListType, FuncDeclarationType, FuncHeadingType, FuncIdentType, FormalParamsListType, FormalParamsType, FuncBlockType, StatPartType, CompStatType, StatListType, StatType, WritelnPListType, ExprType, ExprListType, ParamListType, DoubleType, IDType, StringType, OPType, UnaryOPType, IntType, CallType} nodeType;

typedef struct {
    nodeType type_of_node;
    void* field1;
    void* field2;
    void* field3;
} node;

node* root;

int dotCounter;
int errorCounter;
int printTree;
int printSymbolTable;

void incrementDotCounter();

void decrementDotCounter();

void printDots();

void printNode(node* cur_node);

node* makenode(nodeType t, node* f1, node* f2, node* f3);

node* makeleafInt(int i);

node* makeleafCall(char* s);

node* makeleafUnaryOP(char* o);

node* makeleafOP(char* o);

node* makeleafID(char* s);

node* makeleafString(char* s);

node* makeleafDouble(double d);

node* createTree(node* n);

int isLeaf(node* cur_node);

void freeNode(node* cur_node);

#endif