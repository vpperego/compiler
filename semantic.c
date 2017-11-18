#include "semantic.h"




void semanticSetTypes(AST * node){
  if(node)  return;
  if(node->type == AST_VARDEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exit(4);//TODO: remover isso daqui e colocar no fim da avaliacao semantica
    }else{
      node->symbol->type = SYMBOL_IDENTIFIER; // TODO - não sei se isso tá certo
      if(node->son[0] == AST_BYTE){
        node->symbol->datatype = DATATYPE_CHAR;
      }
    }

  }else if(node->symbol->type == AST_FUNDEC){

  }
}

void semanticCheckUndeclared(){
  hashCheckUndeclared();
}
