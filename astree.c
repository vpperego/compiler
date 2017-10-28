#include "astree.h"


AST * astCreate(int type, HASH_NODE *symbol,AST* son0, AST* son1, AST* son2, AST* son3){
  AST * newNode = (AST *) calloc(1,sizeof(AST));
  newNode-> symbol = symbol;
  newNode->type = type;
  newNode->son[0] = son0;
  newNode->son[1] = son1;
  newNode->son[2] = son2;
  newNode->son[3] = son3;
  return newNode;
}

void astPrint(AST* node, int level){
  int i;
  if(node){
    for(i=0; i < level ; ++i){
      fprintf(stderr, "\t");
    }
    fprintf(stderr, "AST(\n" );
    // switch (node->type) {
    //   case /* value */:
    //     break;
    //   default:
    //     break;
    // }

    if(node->symbol){
      fprintf(stderr, "%s\n", node->symbol->text);
    }else{
      fprintf(stderr, "0\n");
    }
    for(i=0; i < MAX_SONS; ++i){
      astPrint(node->son[i],++level);
    }
  }
}
