#include "semantic.h"
/*
  Etapa 4:
  Filipe Joner
  Vinícius Pittigliani Perego
*/
int checkBooleanType(int type);

int checkArithmeticType(int type);

void checkParams(AST* node);

void checkSemantics(AST *node) {
<<<<<<< HEAD
=======
  semanticCheckUndeclared();
>>>>>>> 3511733f8ad9962135aab04197ae96858e327d99
  semanticSetTypes(node);
  semanticCheckUndeclared();
  semanticCheckUsage(node);
  semanticCheckOperands(node);
}

void setSymbolType(AST_NODE* node)
{
    switch (node->type) {
        case AST_VAR:
            node->symbol->type = SYMBOL_SCALAR;
            break;

        case AST_ARRAY:
            node->symbol->type = SYMBOL_ARRAY;
            break;

        case AST_FUNCTION:
            node->symbol->type = SYMBOL_FUNCTION;
            break;
        
        case AST_PARAMETER:
            node->symbol->type = SYMBOL_SCALAR;
            break;
        
        default:
            node->symbol->type = SYMBOL_UNDEF;
            break;
    }
}

/* sets hash symbol datatype based on ast node type */
void setSymbolDataType(AST_NODE* node)
{
    switch (node->sons[0]->type) {
        case AST_BYTE:
            node->symbol->dataType = DATATYPE_BYTE;
            break;

	    case AST_SHORT:
            node->symbol->dataType = DATATYPE_SHORT;
            break;

	    case AST_LONG:
            node->symbol->dataType = DATATYPE_LONG;
            break;

	    case AST_FLOAT:
            node->symbol->dataType = DATATYPE_FLOAT;
            break;

	    case AST_DOUBLE:
            node->symbol->dataType = DATATYPE_DOUBLE;
            break;
        
        case AST_LIT_INT:
            node->symbol->dataType = DATATYPE_INTEGER;
            break;

        default:
            node->symbol->dataType = SYMBOL_UNDEF;
            break;
    }
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
        case AST_BYTE:
          node->symbol->dataType = DATATYPE_BYTE;
          break;
        
        case AST_CHAR:
          node->symbol->dataType = DATATYPE_CHAR;
          break;

        case AST_SHORT:
          node->symbol->dataType = DATATYPE_SHORT;
          break;

        case AST_LONG:
          node->symbol->dataType = DATATYPE_LONG;
          break;

        case AST_FLOAT:
          node->symbol->dataType = DATATYPE_FLOAT;
          break;

        case AST_DOUBLE:
          node->symbol->dataType = DATATYPE_DOUBLE;
          break;

        case AST_INTEGER:
          node->symbol->dataType = DATATYPE_INTEGER;
          break;
        
        case AST_REAL:
          node->symbol->dataType = DATATYPE_REAL;
          break;

        default:
          break;
      }
    }

  } else if(node->type == AST_FUNDEC){

    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_FUN;
      switch (node->son[0]->type) {
        case AST_BYTE:
          node->symbol->dataType = DATATYPE_BYTE;
          break;
        
        case AST_CHAR:
          node->symbol->dataType = DATATYPE_CHAR;
          break;

        case AST_SHORT:
          node->symbol->dataType = DATATYPE_SHORT;
          break;

        case AST_LONG:
          node->symbol->dataType = DATATYPE_LONG;
          break;

        case AST_FLOAT:
          node->symbol->dataType = DATATYPE_FLOAT;
          break;

        case AST_DOUBLE:
          node->symbol->dataType = DATATYPE_DOUBLE;
          break;

        case AST_INTEGER:
          node->symbol->dataType = DATATYPE_INTEGER;
          break;
        
        case AST_REAL:
          node->symbol->dataType = DATATYPE_REAL;
          break;

        default:
          break;
      }
    }
  }

  else if(node->type == AST_ATRIB_ARRAY) {
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exitCode = 4;
    }
    else{
      node->symbol->type = SYMBOL_ARRAY;
      switch (node->son[0]->type) {
        case AST_BYTE:
          node->symbol->dataType = DATATYPE_BYTE;
          break;
        
        case AST_CHAR:
          node->symbol->dataType = DATATYPE_CHAR;
          break;

        case AST_SHORT:
          node->symbol->dataType = DATATYPE_SHORT;
          break;

        case AST_LONG:
          node->symbol->dataType = DATATYPE_LONG;
          break;

        case AST_FLOAT:
          node->symbol->dataType = DATATYPE_FLOAT;
          break;

        case AST_DOUBLE:
          node->symbol->dataType = DATATYPE_DOUBLE;
          break;

        case AST_INTEGER:
          node->symbol->dataType = DATATYPE_INTEGER;
          break;
        
        case AST_REAL:
          node->symbol->dataType = DATATYPE_REAL;
          break;

        default:
          break;
      }
    }
  }

  else if(node->type == AST_PARAMETER) {
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared\n",node->symbol->text );
      exitCode = 4;
    }
    else {
      node->symbol->type = SYMBOL_VAR;
      switch (node->son[0]->type) {
        case AST_BYTE:
          node->symbol->dataType = DATATYPE_BYTE;
          break;
        
        case AST_CHAR:
          node->symbol->dataType = DATATYPE_CHAR;
          break;

        case AST_SHORT:
          node->symbol->dataType = DATATYPE_SHORT;
          break;

        case AST_LONG:
          node->symbol->dataType = DATATYPE_LONG;
          break;

        case AST_FLOAT:
          node->symbol->dataType = DATATYPE_FLOAT;
          break;

        case AST_DOUBLE:
          node->symbol->dataType = DATATYPE_DOUBLE;
          break;

        case AST_INTEGER:
          node->symbol->dataType = DATATYPE_INTEGER;
          break;
        
        case AST_REAL:
          node->symbol->dataType = DATATYPE_REAL;
          break;

        default:
          break;
      }

    }
  }

  for(i=0; i < MAX_SONS; ++i){
    semanticSetTypes(node->son[i]);
  }
}

void semanticCheckUsage(AST * node){
  int i;
  if(!node)  return;

   switch(node->type){
    case AST_ATRIB:
      if(node->symbol->type != SYMBOL_VAR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
        exitCode = 4;
      }
      break;
    case AST_ATRIB_ARRAY:
      if(node->symbol->type != SYMBOL_VAR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
        exitCode = 4;
      }
      break;

    case AST_SYMBOL:
     if(node->symbol->type != SYMBOL_FUN){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar",node->symbol->text);
        exitCode = 4;
      }
    case AST_READ://TODO
    break;
    case AST_PRINT://TODO
    break;
    case AST_RETURN://TODO
    break;
    case AST_IF:
      if(checkBooleanType(node->son[0]->type)){
        fprintf(stderr, "SEMANTIC ERROR: if conditional must be boolean");
      }
    break;
    case AST_IF_ELSE: //TODO
    if(checkBooleanType(node->son[0]->type)){
      fprintf(stderr, "SEMANTIC ERROR: if conditional must be boolean");
    }
    if(node->son[1]->symbol->datatype != node->son[2]->symbol->datatype){
      fprintf(stderr, "SEMANTIC ERROR: if types must be equal");
    }
    break;
    case AST_WHILE:
      if(checkBooleanType(node->son[0]->type)){
        fprintf(stderr, "SEMANTIC ERROR: While conditional must be boolean");
      }
    break;

    //check if function calls are functions
    case AST_FUNC:
      if(node->symbol->type != SYMBOL_FUN){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be function",node->symbol->text);
        exitCode = 4;
      }
      checkParams(node->son[1]);
    break;


  }

}

void semanticCheckOperands(AST *node){
  int i;
  if(!node)  return;

	if (checkArithmeticType(node->type)
      || node->type == AST_LESS || node->type == AST_MORE || node->type == AST_NE || node->type == AST_EQ || node->type == AST_LE || node->type == AST_GE){
		if(checkBooleanType(node->son[0]->type)){
			  fprintf(stderr, "ERRO: Operando esquerdo não pode ser logico. \n");
			  exitCode = 4;
		}
		if(checkBooleanType(node->son[1]->type)){
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

int checkBooleanType(int type){
  return type == AST_LESS ||
     type == AST_MORE ||
     type == AST_GE ||
     type == AST_LE ||
     type == AST_NE ||
     type == AST_EQ ||
     type == AST_OR ||
     type == AST_AND||
     type == AST_NOT;
}

int checkArithmeticType(int type){
  return type == AST_ADD || type == AST_SUB || type == AST_MUL || type == AST_DIV ;
}


void checkParams(AST* node){
  //TODO
}
