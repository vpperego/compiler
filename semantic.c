#include "semantic.h"
/*
  Etapa 4:
  Filipe Joner
  Vinícius Pittigliani Perego
*/


void checkSemantics(AST *node) {
  semanticCheckUndeclared();
  semanticSetTypes(node);
  semanticCheckUsage(node);
  semanticCheckOperands(node);
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

	if (node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV || node->type == AST_LESS || node->type == AST_MORE || node->type == AST_NE || node->type == AST_EQ || node->type == AST_LE || node->type == AST_GE){
		if(node->son[0]->type == AST_LESS ||
		   node->son[0]->type == AST_MORE ||
		   node->son[0]->type == AST_GE ||
		   node->son[0]->type == AST_LE ||
		   node->son[0]->type == AST_NE ||
		   node->son[0]->type == AST_EQ ||
		   node->son[0]->type == AST_OR ||
		   node->son[0]->type == AST_AND||
       node->son[0]->type == AST_NOT){

			  fprintf(stderr, "ERRO: Operando esquerdo não pode ser logico. \n");
			  exitCode = 4;
		}
		if(node->son[1]->type == AST_LESS ||
		   node->son[1]->type == AST_MORE ||
		   node->son[1]->type == AST_GE ||
		   node->son[1]->type == AST_LE ||
		   node->son[1]->type == AST_NE ||
		   node->son[1]->type == AST_EQ ||
		   node->son[1]->type == AST_OR ||
		   node->son[1]->type == AST_AND||
       node->son[1]->type == AST_NOT){

			  fprintf(stderr, "ERRO: Operando direito não pode ser logico. \n");
			  exitCode = 4;
		}
	}

	if (node->type == AST_AND || node->type == AST_OR || node->type == AST_NOT){

		if(node->son[0]->type == AST_MUL ||
		   node->son[0]->type == AST_ADD ||
		   node->son[0]->type == AST_SUB ||
		   node->son[0]->type == AST_DIV){

			  fprintf(stderr, "ERRO: Operando esquerdo não pode ser aritmético. \n");
			  exitCode = 4;
		}
		if(node->son[1]->type == AST_MUL ||
		   node->son[1]->type == AST_ADD ||
		   node->son[1]->type == AST_SUB ||
		   node->son[1]->type == AST_DIV){

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
