#include "semantic.h"




void semanticSetTypes(AST * node){
  if(node)  return;
  if(node->type==VARDEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exit(4);//TODO: remover isso daqui e colocar no fim da avaliacao semantica
    }else{
      node->symbol->type = SYMBOL_VAR;
      if(son[0] == AST_TYPECHAR){
        node->symbol->datatype = DATATYPE_CHAR;
      }
    }

  }else if(node-->type FUNDEC)
}

void semanticCheckUndeclared(){
  hashCheckUndeclared();
}
