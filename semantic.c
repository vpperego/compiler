#include "semantic.h"




void semanticSetTypes(AST * node){
  int i;
  if(!node)  return;

  if(node->type == AST_VARDEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_VAR;
      switch (node->son[0]->type) {
        case AST_INTEGER:
          node->symbol->datatype = DATATYPE_INT;
          break;
        case AST_REAL:
          node->symbol->datatype = DATATYPE_REAL;
          break;
        case AST_CHAR:
          node->symbol->datatype = DATATYPE_CHAR;
          break;
        default:
          break;
      }
    }

  }else if(node->type == AST_FUNDEC){

    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_FUN;
    }
  }
  for(i=0; i < MAX_SONS; ++i){
    semanticSetTypes(node->son[i]);
  }
}

void semanticCheckUsage(AST * node){
  int i;
  if(!node)  return;

  //check left-side assign TODO colocar AST_ATRIB_ARRAY aqui tambem ?
  if(node->type == AST_ATRIB){
    if(node->symbol->type != SYMBOL_VAR){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
      exitCode = 4;
    }
  }

  //check right-side assign TODO colocar AST_ATRIB_ARRAY aqui tambem ?
  if(node->type == AST_SYMBOL){
    if(node->symbol->type != SYMBOL_FUN){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
      exitCode = 4;
    }
  }

  //check if function calls are functions TODO colocar AST_ATRIB_ARRAY aqui tambem ?
  if(node->type == AST_FUNC){
    if(node->symbol->type != SYMBOL_FUN){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s must be function",node->symbol->text);
      exitCode = 4;
    }
  }
}

void semanticCheckOperands(AST *node){
  int i;
  if(!node)  return;

  // if(node->type == AST_ADD || node->type == AST_MUL){
  //   if(node->son[0] != AST_ADD || node->son[0] != AST_MUL || node->son[0] !=)
  // }

  for(i=0; i < MAX_SONS; ++i){
    semanticSetTypes(node->son[i]);
  }
}

void semanticCheckUndeclared(){
  hashCheckUndeclared();
}
