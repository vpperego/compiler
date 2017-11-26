#include "semantic.h"
/*
  Etapa 4:
  Filipe Joner
  Vinícius Pittigliani Perego
*/

void checkParams(AST* node, AST * parameters);

void checkSemantics(AST *node) {
  semanticSetTypes(node);
  semanticCheckUndeclared();
  semanticCheckUsage(node);
  semanticCheckOperands(node);
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
  if(!node->son[1]) return 1;
  int totalParams = 1;

  do{
    node = node->son[1];
    totalParams++;
  }while(node->son[1] && node->son[1]->type == AST_LIST_ARG);

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
            node->symbol->parameters = node->son[1];
            fprintf(stderr, "depois de setFuncParameters %s\n",node->symbol->text);
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
    node->symbol->type = setSymbolType (node->type);;
    node->symbol->dataType = setDataType(node->son[0]->type);
  }else if(node->type == AST_ATRIB) {
    node->symbol->type = setSymbolType (node->type);;
    node->symbol->dataType = setDataType(node->son[0]->type);
  }else if (node->type == AST_SYMBOL){
    node->symbol->type = setSymbolType (node->type);
  }else if (node->type == AST_INTEGER){
    node->symbol->dataType = setDataType (node->type);
  }else if (node->type == AST_REAL){
    node->symbol->dataType = setDataType (node->type);
  }else if (node->type == AST_CHAR){
    node->symbol->dataType = setDataType (node->type);
  }

  for(i=0; i < MAX_SONS; ++i){
    semanticSetTypes(node->son[i]);
  }
}

int isIndexValid(AST * node){

  if (checkBooleanType(node->type)){
     return 0;
  }else if(checkArithmeticType(node->type)){
     return (isIndexValid(node->son[0]) &&
            (isIndexValid(node->son[1])));
  }
  else if (!isIntegerType(node->symbol->dataType)) {
    return 0;
  }
  return 1;
}

void semanticCheckUsage(AST * node){
  int i;
  if(!node)  return;

   switch(node->type){
    case AST_ATRIB:
      if(node->symbol->type != SYMBOL_SCALAR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar AST_ATRIB\n",node->symbol->text);
        exitCode = 4;
      }
      break;
    case AST_ATRIB_ARRAY:
      if(node->symbol->type != SYMBOL_SCALAR) {
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar AST_ATRIB_ARRAY\n",node->symbol->text);
        exitCode = 4;
      }
      fprintf(stderr, "AST_ATRIB_ARRAY\n" );
      if(!isIndexValid(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: vector index must be a integer value\n");
        exitCode = 4;
      }
      break;

    case AST_ARRAY:
      if(!isIndexValid(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: vector index must be a integer value\n");
        exitCode = 4;
      }
      break;
    case AST_SYMBOL:
     if(node->symbol->type != SYMBOL_SCALAR){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be scalar AST_SYMBOL\n",node->symbol->text);
        exitCode = 4;
      }
    case AST_READ://TODO
    break;
    case AST_PRINT://TODO
    break;
    case AST_RETURN://TODO
    break;
    case AST_IF:
      if(!checkBooleanType(node->son[0]->type)){
        fprintf(stderr, "SEMANTIC ERROR: if conditional must be boolean");
        exitCode = 4;
      }
    break;
    case AST_IF_ELSE:
      if(!checkBooleanType(node->son[0]->type)){
        fprintf(stderr, "SEMANTIC ERROR: if conditional must be boolean");
        exitCode = 4;
      }

      break;
    case AST_WHILE:
      if(!checkBooleanType(node->son[0]->type)){
        fprintf(stderr, "SEMANTIC ERROR: While conditional must be boolean");
        exitCode = 4;
      }
    break;

    //check if function calls are functions
    case AST_FUNC:
      fprintf(stderr,"\nAST_FUNC\n");
      if(node->symbol->type != SYMBOL_FUN){
        fprintf(stderr, "SEMANTIC ERROR: identifier %s must be function\n",node->symbol->text);
        exitCode = 4;
      }
      if(node->symbol->parametersNumber != countParameters(node->son[0])){
        fprintf(stderr, "SEMANTIC ERROR: function %s has wrong number of parameters\n",node->symbol->text);
        exitCode = 4;
      }
      checkParams(node->son[0],node->symbol->parameters);
      // fprintf(stderr, "Terminei a parte de funcao...\n" );
    break;
  }
  for (i=0; i<MAX_SONS; ++i)
    semanticCheckUsage(node->son[i]);
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

    if (node->type != AST_DIV) {
  //    node->symbol->dataType = getArithmeticType(node->son[0]->symbol->dataType, node->son[1]->symbol->dataType); TODO -ISSO NAO VAI SER FEITO AQUI
    } else {
       // TODO: divisão gera sempre float/double ou qualquer coisa?
       node->symbol->dataType = DATATYPE_DOUBLE;
    }

	}

	if (node->type == AST_AND || node->type == AST_OR || node->type == AST_NOT){

		if(checkArithmeticType(node->son[0]->type)){

			  fprintf(stderr, "SEMANTIC ERROR: cannot have left arithmetic operand. \n");
			  exitCode = 4;
		}
		if(checkArithmeticType(node->son[1]->type)){
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



void checkParams(AST* node, AST * parameters){
   AST* nodeIterator = node;
  while(1){
    if(!nodeIterator->son[1])
    {

    if(!compareDataType(nodeIterator->symbol->dataType, parameters->symbol->dataType)){
        fprintf(stderr, "Param:  %d hope is for : %d  \n",nodeIterator->symbol->dataType,parameters->symbol->dataType );
        fprintf(stderr, "SEMANTIC ERROR: Function parameter type is wrong...LAST\n" );
        exitCode = 4;
      }
      break;
    }
    if(!compareDataType(nodeIterator->son[0]->symbol->dataType, parameters->son[0]->symbol->dataType)){
      fprintf(stderr, "SEMANTIC ERROR: Function parameter type is wrong...FIRST\n" );
      exitCode = 4;
    }
    parameters = parameters->son[1];
    // fprintf(stderr, "identifier : %s dataType: %d\n", parameters->symbol->text,parameters->symbol->dataType);
    nodeIterator = nodeIterator->son[1];
  }
}
