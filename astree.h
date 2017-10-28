#ifndef ASTREE_H
#define ASTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#define MAX_SONS 4

#define AST_ADD 1
#define AST_SUB 2
#define AST_MUL 3
#define AST_DIV 4
#define AST_LESS 5
#define AST_MORE 6
#define AST_NOT 7
#define AST_PARENTHESES 8
typedef struct ast_node{
  int type;
  HASH_NODE * symbol;
  struct ast_node * son[MAX_SONS];
}AST;

AST * astCreate(int type, HASH_NODE *symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint (AST* node, int level);
#endif
