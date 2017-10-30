#ifndef ASTREE_H
#define ASTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#define MAX_SONS 4

enum AST_TYPE{
  AST_SYMBOL,
  AST_ADD,
  AST_SUB,
  AST_MUL,
  AST_DIV,
  AST_LESS,
  AST_MORE,
  AST_NOT,
  AST_PARENTHESES,
  AST_LE,
  AST_GE,
  AST_EQ,
  AST_NE,
  AST_AND,
  AST_OR,
  AST_FUNC,
  AST_INIT_ARRAY,
  AST_ARRAY_INIT_VALUES,
  AST_ARRAY,
  AST_ATRIB,
  AST_ATRIB_ARRAY,
  AST_READ,
  AST_PRINT,
  AST_RETURN,
  AST_IF,
  AST_IF_ELSE,
  AST_WHILE,
  AST_BLOCK,
  AST_LIST_PARAM,
  AST_PARAM,
  AST_ARG_ID,
  AST_LIST_ARG,
  AST_ARG,
  AST_START,
  AST_VARDEC,
  AST_FUNDEC,
  AST_LIST_CMD,
  AST_CMD,
  AST_BYTE,
  AST_SHORT,
  AST_LONG,
  AST_FLOAT,
  AST_DOUBLE,
  AST_CHAR,
  AST_INTEGER,
  AST_REAL
  };


typedef struct ast_node{
  int type;
  HASH_NODE * symbol;
  struct ast_node * son[MAX_SONS];
}AST;

AST * astCreate(int type, HASH_NODE *symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint (AST* node, int level);
void astPrintSrc(AST* node, FILE *out);

#endif
