#include "semantic.h"




void semanticSetTypes(AST * node){

  if(!node)  return;

  if(node->type == AST_VARDEC){
    fprintf(stderr, "AST_VARDEC\n");

    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exit(4);//TODO: remover isso daqui e colocar no fim da avaliacao semantica
    }else{
      fprintf(stderr, "ELSE\n");

      node->symbol->type = SYMBOL_VAR; // TODO - não sei se isso tá certo
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
      exit(4);//TODO: remover isso daqui e colocar no fim da avaliacao semantica
    }
  }

  semanticSetTypes(node->son[0]);
  semanticSetTypes(node->son[1]);
  semanticSetTypes(node->son[2]);
  semanticSetTypes(node->son[3]);
}

void semanticCheckUsage(AST * node){

  if(!node)  return;

}

void semanticCheckUndeclared(){
  hashCheckUndeclared();
}
