


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
#define DEBUG_STATLIST 0
#define DEBUG_MAKENODE 0

typedef enum {
	_boolean_, _integer_, _real_, _function_, _program_, _type_, _true_, _false_
} PredefType;

typedef enum {
	_constant_, _return_, _param_, _varparam_
} PredefFlag;

typedef struct {
	char* symname;
	PredefType type;
	PredefFlag flag;
	char* sim_value;
} symbol;

typedef enum {
	_outer_, _program_, _function_
} PredefTable;

int comparison_function(char* name, symbol* sym);

typedef struct {
	PredefTable type;
	void* next;
	map <char*, symbol*, comparison_function> functions;
	map <char*, symbol*, comparison_function> constants;
	map <char*, symbol*, comparison_function> returns;
	map <char*, symbol*, comparison_function> params;
	map <char*, symbol*, comparison_function> varparams;
} table;


typedef enum {
	ProgType, ProgBlockType, VarPartType, VarDeclarationListType, VarDeclarationType, IDListType, CommaIDListType, FuncPartType, 
	FuncDeclarationListType, FuncDeclarationType, FuncDefinitionType, FuncDefinition2Type, FuncHeadingType, FuncIdentType, FuncParamsListType, FuncParamsListType2, VarParamsType, 
	ParamsType, FuncBlockType, CompStatType, StatListType, StatType, IfElseStatType, WhileStatType, RepeatStatType, ValParamStatType, AssignStatType, 
	WriteLnStatType, WritelnPListType, ExprType, SimpleExprType, OPFactorListType, FactorType, OPTermListType, UnaryTermType, TermType, ExprListType, ParamListType, 
	DoubleType, IDType, StringType, OPType, UnaryOPType, IntType, CallType
} NodeType;

typedef struct {
    NodeType type_of_node;
    void* field1;
    void* field2;
    void* field3;
} node;

node* root;

int dotCounter;
int errorCounter;
int printTree;
int printSymbolTable;


/*
 * AST creation and deletion functions
 */

int getNodeDepth(node* n);

node* makenode(NodeType t, node* f1, node* f2, node* f3);

node* makeleaf(NodeType t, char* str);

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




