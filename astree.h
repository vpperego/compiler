#ifndef ASTREE_H
#define ASTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#define MAX_SONS 4

typedef struct ast_node{
  int type;
  HASH_NODE * symbol;
  struct ast_node * son[MAX_SONS];
}AST;

AST * astCreate(int type, HASH_NODE *symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint (AST* node, int level);
#endif
