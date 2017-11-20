#include "semantic.h"
/*
  Etapa 4:
  Filipe Joner
  Vinícius Pittigliani Perego
*/
int checkBooleanType(int type);

int checkArithmeticType(int type);

int setDataType(int nodeType);

void checkParams(AST* node, HASH_NODE * parameters);
HASH_NODE * setFuncParameters (AST * node);

void checkSemantics(AST *node) {
  semanticSetTypes(node);
  semanticCheckUndeclared();
  semanticCheckUsage(node);
  semanticCheckOperands(node);
}

// void setSymbolType(AST * node)
// {
//     switch (node->type) {
//         case AST_VAR:
//             node->symbol->type = SYMBOL_SCALAR;
//             break;
//
//         case AST_ARRAY:
//             node->symbol->type = SYMBOL_ARRAY;
//             break;
//
//         case AST_FUNCTION:
//             node->symbol->type = SYMBOL_FUNCTION;
//             break;
//
//         case AST_PARAM:
//             node->symbol->type = SYMBOL_SCALAR;
//             break;
//
//         default:
//             node->symbol->type = SYMBOL_UNDEF;
//             break;
//     }
// }

/* sets hash symbol datatype based on ast node type */
void setSymbolDataType(AST * node)
{
    switch (node->son[0]->type) {
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

        // case AST_LIT_INT:
        //     node->symbol->dataType = DATATYPE_INT;
        //     break;

        // default:
        //     node->symbol->dataType = SYMBOL_UNDEF;
        //     break;
    }
}

int checkParameters(AST * node){
  int totalParams = 1;
  while(node->son[1]->type == AST_LIST_ARG){
    if(node->son[0]->type != AST_ARG_ID)
    node = node->son[1];
    totalParams++;
  }
  return totalParams;
}

int countParameters(AST * node){
  int totalParams = 1;
  while(node->son[1]->type == AST_LIST_ARG){
    node = node->son[1];
    totalParams++;
  }
  return totalParams;
}

void semanticSetTypes(AST * node){

  int i;
  if(!node)  return;

  if(node->type == AST_VARDEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared AST_VARDEC\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_VAR;
      node->symbol->dataType = setDataType(node->son[0]->type);
    }
  }else if(node->type == AST_INIT_ARRAY){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared AST_VARDEC\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_VAR;
      node->symbol->dataType = setDataType(node->son[0]->type);
    }
  }else if(node->type == AST_FUNDEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared AST_FUNDEC\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_FUN;
      node->symbol->dataType = setDataType(node->son[0]->type);
      if(node->son[2]){
           node->symbol->parametersNumber = countParameters(node->son[1]);
           node->symbol->funcParameters = setFuncParameters(node->son[1]);
      }
    }
  }
  else if(node->type == AST_ARG_ID){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "SEMANTIC ERROR: parameter %s already declared\n",node->symbol->text );
      exitCode = 4;
    }else{
      node->symbol->type = SYMBOL_ARG_ID;
      node->symbol->dataType = setDataType(node->son[0]->type);
    }
  }
  else if(node->type == AST_ATRIB_ARRAY) {
    // if(node->symbol->type != SYMBOL_IDENTIFIER){TODO - isso precisa estar aqui?
    //   fprintf(stderr, "SEMANTIC ERROR: identifier %s already declared AST_ATRIB_ARRAY\n",node->symbol->text );
    //   exitCode = 4;
    // }
    // else{
    // }
    node->symbol->type = SYMBOL_ARRAY;
    node->symbol->dataType = setDataType(node->son[0]->type);
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
    if(node->son[1]->symbol->dataType != node->son[2]->symbol->dataType){
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
      if(node->symbol->parametersNumber != countParameters(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: function %s has wrong number of parameters",node->symbol->text);
        exitCode = 4;
      }
      checkParams(node->son[0],node->symbol->funcParameters);
    break;


  }

}

void semanticCheckOperands(AST *node){
  int i;
  if(!node)  return;

	if (checkArithmeticType(node->type)
      || node->type == AST_LESS || node->type == AST_MORE || node->type == AST_NE || node->type == AST_EQ || node->type == AST_LE || node->type == AST_GE){
		if(checkBooleanType(node->son[0]->type)){
			  fprintf(stderr, "SEMANTIC ERROR: cannot have left logical operand. \n");
			  exitCode = 4;
		}
		if(checkBooleanType(node->son[1]->type)){
			  fprintf(stderr, "SEMANTIC ERROR: cannot have right logical operand. \n");
			  exitCode = 4;
		}
	}

	if (node->type == AST_AND || node->type == AST_OR || node->type == AST_NOT){

		if(node->son[0]->type == AST_MUL ||
		   node->son[0]->type == AST_ADD ||
		   node->son[0]->type == AST_SUB ||
		   node->son[0]->type == AST_DIV){

			  fprintf(stderr, "SEMANTIC ERROR: cannot have left arithmetic operand. \n");
			  exitCode = 4;
		}
		if(node->son[1]->type == AST_MUL ||
		   node->son[1]->type == AST_ADD ||
		   node->son[1]->type == AST_SUB ||
		   node->son[1]->type == AST_DIV){

			  fprintf(stderr, "SEMANTIC ERROR: cannot have right arithmeic operand. \n");
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

int setDataType(int nodeType){
  switch(nodeType){
    case AST_BYTE:
      return DATATYPE_BYTE;
      break;

    case AST_CHAR:
      return DATATYPE_CHAR;
      break;

    case AST_SHORT:
      return DATATYPE_SHORT;
      break;

    case AST_LONG:
      return DATATYPE_LONG;
      break;

    case AST_FLOAT:
      return DATATYPE_FLOAT;
      break;

    case AST_DOUBLE:
      return DATATYPE_DOUBLE;
      break;

    case AST_INTEGER:
      return DATATYPE_INT;
      break;

    case AST_REAL:
      return DATATYPE_REAL;
      break;
      default:
      break;
    }
}

void checkParams(AST* node, HASH_NODE * parameters){
  while(node->son[1]->type == AST_LIST_ARG ){
    if(node->son[0]->symbol->dataType != parameters->dataType){
      fprintf(stderr, "SEMANTIC ERROR: Function parameter type is wrong!\n" );
      exitCode = 4;
      break;
    }
    parameters = parameters->next;
    node = node->son[1];
  }
}

HASH_NODE * setFuncParameters (AST * node){
  HASH_NODE * iterator = NULL;

  HASH_NODE * funcParameters  = malloc(sizeof( HASH_NODE *));
  funcParameters = node->son[0]->symbol;

  funcParameters->next = iterator;
   while(node->son[1]->type == AST_LIST_ARG){
    node = node->son[1];
    iterator = malloc(sizeof( HASH_NODE *));
    iterator = node->son[0]->symbol;
    iterator = iterator->next;
    iterator->next = NULL;
  }
  return funcParameters;
}
