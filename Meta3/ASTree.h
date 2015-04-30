


#ifndef ASTREE
#define ASTREE

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>


#define DEBUG 0
#define DEBUG_TYPE 0
#define DEBUG_STATLIST 0
#define DEBUG_MAKENODE 0

typedef struct {
	char* string;
	int line;
	int col;
} tokenInfo;

typedef enum {
	ProgType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, 
	FuncDeclarationListType, FuncDeclarationType, FuncDefinitionType, FuncDefinition2Type, FuncHeadingType, FuncIdentType, FuncParamsListType, FuncParamsListType2, VarParamsType, 
	ParamsType, FuncBlockType, CompStatType, StatListType, StatType, IfElseStatType, WhileStatType, RepeatStatType, ValParamStatType, AssignStatType, 
	WriteLnStatType, WritelnPListType, ExprType, SimpleExprType, OPFactorListType, FactorType, OPTermListType, UnaryTermType, TermType, ExprListType, ParamListType, 
	DoubleType, IDType, StringType, OPType, UnaryOPType, IntType, CallType
} NodeType;

typedef struct {
    NodeType type_of_node;
    int line;
    int col;
    void* field1;
    void* field2;
    void* field3;
} node;

node* ASTroot;

int dotCounter;
int errorCounter;
int printTree;
int printSymbolTable;

// function used to crceate and store the string, line and col of a token
tokenInfo* makeTokenInfo(char* str, int l, int c);

/*
 * AST creation and deletion functions
 */

int getNodeDepth(node* n);

node* makenode(NodeType t, node* f1, node* f2, node* f3, int l, int c);

node* makeleaf(NodeType t, char* str, int l, int c);

node* createTree(node* n);

int isLeaf(node* cur_node);

void freeNode(node* cur_node);

/*
 * AST printing functions
 */

void incrementDotCounter();

void decrementDotCounter();

void printDots();

void printChildrenMiddleFirst(node* cur_node);

void printChildren(node* cur_node);

void printNode(node* cur_node, NodeType lastNodeType);

/*
 * Functions that fetch strings for output & debug
 */

char* getNodeTypeStr(NodeType t);

char* getIndependantStr(NodeType t);

char* getLeafStr(NodeType t);

char* getStatStr(NodeType t);

char* getUnaryOPStr(char* str);

char* getOPStr(char* str);

#endif




