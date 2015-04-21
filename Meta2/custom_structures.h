


#ifndef CUSTOM_STRUCTURES
#define CUSTOM_STRUCTURES

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>


#define DEBUG 0
#define DEBUG_TYPE 0

typedef enum {
	ProgType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, 
	FuncDeclarationListType, FuncDeclarationType, FuncDefinitionType, FuncDefinition2Type, FuncHeadingType, FuncIdentType, FuncParamsListType, VarParamsType, 
	ParamsType, FuncBlockType, StatListType, StatType, IfElseStatType, WhileStatType, RepeatStatType, ValParamStatType, AssignStatType, 
	WriteLnStatType, WritelnPListType, ExprType, SimpleExprType, OPFactorListType, FactorType, OPTermListType, UnaryTermType, TermType, ExprListType, ParamListType, 
	DoubleType, IDType, StringType, OPType, UnaryOPType, IntType, CallType
} NodeType;

typedef struct {
    NodeType type_of_node;
    void* field1;
    void* field2;
    void* field3;
    int depth;
} node;

node* root;

int dotCounter;
int errorCounter;
int printTree;
int printSymbolTable;

void incrementDotCounter();

void decrementDotCounter();

void printDots();

char* getIndependantStr(NodeType t);

char* getLeafStr(NodeType t);

char* getStatStr(NodeType t);

char* getUnaryOPStr(char* str);

char* getOPStr(char* str);

void printChildren(node* cur_node);

void printNode(node* cur_node, NodeType lastNodeType);

node* makenode(NodeType t, node* f1, node* f2, node* f3);

node* makeleaf(NodeType t, char* str);

node* createTree(node* n);

int isLeaf(node* cur_node);

void cleanStatLists(node* cur_node);

void freeNode(node* cur_node);

#endif




