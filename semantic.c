#include "semantic.h"
/*
  Etapa 4:
  Filipe Joner
  Vinícius Pittigliani Perego
*/


void checkSemantics(AST *node) {
  emanticCheckUndeclared();
  semanticSetTypes(node);
  semanticCheckUsage(node);
  semanticCheckOperands(node)
}


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
  switch(node->type){
    case AST_ATRIB:
      if(node->symbol->type != SYMBOL_VAR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
        exitCode = 4;
      }
      break;
  
    //check right-side assign TODO colocar AST_ATRIB_ARRAY aqui tambem ?
    case AST_SYMBOL:
      if(node->symbol->type != SYMBOL_FUN){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
        exitCode = 4;
      }
      break;
  
  
    //check if function calls are functions TODO colocar AST_ATRIB_ARRAY aqui tambem ?
    case AST_FUNC:
      if(node->symbol->type != SYMBOL_FUN){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be function",node->symbol->text);
        exitCode = 4;
      }
    break;
  
  
  }

}

void semanticCheckOperands(AST *node){
  int i;
  if(!node)  return;

  // if(node->type == AST_ADD || node->type == AST_MUL){
  //   if(node->son[0] != AST_ADD || node->son[0] != AST_MUL || node->son[0] !=)
  // }
  int i;
	if (!node) return;
	
	if (node->type == ASTREE_ADD || node->type == ASTREE_SUB || node->type == ASTREE_MUL || node->type == ASTREE_DIV || node->type == ASTREE_G || node->type == ASTREE_L || node->type == ASTREE_NE || node->type == ASTREE_EQ || node->type == ASTREE_LE || node->type == ASTREE_GE){
		if(node->son[0]->type == ASTREE_G ||
		   node->son[0]->type == ASTREE_L || 
		   node->son[0]->type == ASTREE_GE || 
		   node->son[0]->type == ASTREE_LE || 
		   node->son[0]->type == ASTREE_NE || 
		   node->son[0]->type == ASTREE_EQ || 
		   node->son[0]->type == ASTREE_OR || 
		   node->son[0]->type == ASTREE_AND|| 
       node->son[0]->type == ASTREE_NOT){

			  fprintf(stderr, "ERRO: Operando esquerdo não pode ser logico. \n");
			  exitCode = 4;
		}
		if(node->son[1]->type == ASTREE_G ||
		   node->son[1]->type == ASTREE_L || 
		   node->son[1]->type == ASTREE_GE || 
		   node->son[1]->type == ASTREE_LE || 
		   node->son[1]->type == ASTREE_NE || 
		   node->son[1]->type == ASTREE_EQ || 
		   node->son[1]->type == ASTREE_OR || 
		   node->son[1]->type == ASTREE_AND|| 
       node->son[1]->type == ASTREE_NOT){

			  fprintf(stderr, "ERRO: Operando direito não pode ser logico. \n");
			  exitCode = 4;
		}
	}
		
	if (node->type == ASTREE_AND || node->type == ASTREE_OR || node->type == ASTREE_NOT){
	
		if(node->son[0]->type == ASTREE_MUL ||
		   node->son[0]->type == ASTREE_ADD || 
		   node->son[0]->type == ASTREE_SUB || 
		   node->son[0]->type == ASTREE_DIV){

			  fprintf(stderr, "ERRO: Operando esquerdo não pode ser aritmético. \n");
			  exitCode = 4;
		}
		if(node->son[1]->type == ASTREE_MUL ||
		   node->son[1]->type == ASTREE_ADD || 
		   node->son[1]->type == ASTREE_SUB || 
		   node->son[1]->type == ASTREE_DIV){

			  fprintf(stderr, "ERRO: Operando direito não pode ser aritmético. \n");
			  exitCode = 4;
		}
	}
	
	for (i=0; i<MAX_SONS; ++i)
    semanticCheckOperands(node->son[i]);

}

void semanticCheckUndeclared(){
  hashCheckUndeclared();
}
