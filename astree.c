#include "astree.h"
#include <stdio.h>
#include <stdlib.h>


AST * astCreate(int type, HASH_NODE *symbol,AST* son0, AST* son1, AST* son2, AST* son3){
  AST * newNode = calloc(1,sizeof(AST));
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

  if(!node)
    return;

  fprintf(stderr, "AST(");

  for(i=0;i<level;i++)
    fprintf(stderr, "  ");

  switch(node->type) {
    case AST_SYMBOL:
      fprintf(stderr, "AST_SYMBOL" );
      break;
    case AST_ADD:
      fprintf(stderr, "AST_ADD" );
      break;
    case AST_SUB:
      fprintf(stderr, "AST_SUB" );
      break;
    case AST_MUL:
      fprintf(stderr, "AST_MUL" );
      break;
    case AST_DIV:
      fprintf(stderr, "AST_DIV" );
      break;
    case AST_LESS:
      fprintf(stderr, "AST_LESS" );
      break;
    case AST_MORE:
      fprintf(stderr, "AST_MORE");
      break;
    case AST_NOT:
      fprintf(stderr, "AST_NOT");
      break;
    case AST_PARENTHESES:
      fprintf(stderr, "AST_PARENTHESES");
      break;
    case AST_LE:
      fprintf(stderr, "AST_LE");
      break;
    case AST_GE:
      fprintf(stderr, "AST_GE");
      break;
    case AST_EQ:
      fprintf(stderr, "AST_EQ");
      break;
    case AST_NE:
      fprintf(stderr, "AST_NE");
      break;
    case AST_AND:
      fprintf(stderr, "AST_AND");
      break;
    case AST_OR:
      fprintf(stderr, "AST_OR");
      break;
    case AST_FUNC:
      fprintf(stderr, "AST_FUNC");
      break;
    case AST_INIT_ARRAY:
      fprintf(stderr, "AST_INIT_ARRAY");
      break;
    case AST_ARRAY:
      fprintf(stderr, "AST_ARRAY");
      break;
    case AST_ATRIB:
      fprintf(stderr, "AST_ATRIB");
      break;
    case AST_ATRIB_ARRAY:
      fprintf(stderr, "AST_ATRIB_ARRAY");
      break;
    case AST_READ:
      fprintf(stderr, "AST_READ");
      break;
    case AST_PRINT:
      fprintf(stderr, "AST_PRINT");
      break;
    case AST_RETURN:
      fprintf(stderr, "AST_RETURN");
      break;
    case AST_IF:
      fprintf(stderr, "AST_IF");
      break;
    case AST_IF_ELSE:
      fprintf(stderr, "AST_IF_ELSE");
      break;
    case AST_WHILE:
      fprintf(stderr, "AST_WHILE");
      break;
    case AST_BLOCK:
      fprintf(stderr, "AST_BLOCK");
      break;
    case AST_LIST_PARAM:
      fprintf(stderr, "AST_LIST_PARAM");
      break;
    case AST_PARAM:
      fprintf(stderr, "AST_PARAM");
      break;
    case AST_ARG_ID:
      fprintf(stderr, "AST_ARG_ID");
      break;
    case AST_LIST_ARG:
      fprintf(stderr, "AST_LIST_ARG");
      break;
    case AST_ARG:
      fprintf(stderr, "AST_ARG");
      break;
    case AST_START:
      fprintf(stderr, "AST_START");
      break;
    case AST_VARDEC:
      fprintf(stderr, "AST_VARDEC");
      break;
    case AST_FUNDEC:
      fprintf(stderr, "AST_FUNDEC");
      break;
    case AST_LIST_CMD:
      fprintf(stderr, "AST_LIST_CMD");
      break;
    case AST_BYTE:
      fprintf(stderr, "AST_BYTE");
      break;
    case AST_SHORT:
      fprintf(stderr, "AST_SHORT");
      break;
    case AST_LONG:
      fprintf(stderr, "AST_LONG");
      break;
    case AST_FLOAT:
      fprintf(stderr, "AST_FLOAT");
      break;
    case AST_DOUBLE:
      fprintf(stderr, "AST_DOUBLE");
      break;
    case AST_CHAR:
      fprintf(stderr, "AST_CHAR");
      break;
    case AST_INTEGER:
      fprintf(stderr, "AST_INTEGER");
      break;
    case AST_REAL:
      fprintf(stderr, "AST_REAL");
      break;
    case AST_ARRAY_INIT_VALUES:
      fprintf(stderr, "AST_ARRAY_INIT_VALUES");
      break;
    case AST_VARIABLE:
      fprintf(stderr, "AST_VARIABLE");
      break;
    case AST_FUNCTION:
      fprintf(stderr, "AST_FUNCTION");
      break;
    case AST_EXPRESSION:
      fprintf(stderr, "AST_EXPRESSION");
      break;
    default:
      fprintf(stderr, "Node Type: %d", node->type);
      break;
  }


  if(node->symbol){
    fprintf(stderr, " ,%s\n", node->symbol->text);
  } else {
    fprintf(stderr, " )\n");
  }
  for(i=0; i < MAX_SONS; ++i){
    astPrint(node->son[i],++level);
  }

}

void astPrintSrc(AST* node, FILE *yyout) {
  if(!node)
      return;
  int i;
  // fprintf(stderr,"BEGIN\n");

  switch(node->type) {
    case AST_SYMBOL:
      fprintf(yyout, "%s", node->symbol->text);
      break;
    case AST_ADD:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " + " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_SUB:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " - " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_DIV:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " / " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_MUL:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " * " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_LESS:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " < " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_MORE:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " > " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_NOT:
      fprintf(yyout, "!" );
      astPrintSrc(node->son[0], yyout);
      break;
    case AST_LE:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " <= " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_GE:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " >= " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_EQ:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " == " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_NE:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " != " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_AND:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " && " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_OR:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " || " );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_BLOCK:
      fprintf(yyout,"{\n");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout,"\n}");
      break;
    case AST_READ:
      fprintf(yyout, "read > " );
      fprintf(yyout, "%s", node->symbol->text);
      break;
    case AST_PRINT:
      fprintf(yyout, "print " );
      astPrintSrc(node->son[0], yyout);
      break;
    case AST_RETURN:
      fprintf(yyout, "return " );
      astPrintSrc(node->son[0], yyout);
      break;
    case AST_IF:
      fprintf(yyout, "if (" );
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ") then \n" );
      astPrintSrc(node->son[1], yyout);
      break;
    case AST_IF_ELSE:
      fprintf(yyout, "if ( " );
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ") then \n" );
      astPrintSrc(node->son[1], yyout);
      fprintf(yyout, " else \n" );
      astPrintSrc(node->son[2], yyout);
      break;
    case AST_WHILE:
      fprintf(yyout, "while(" );
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ") \n" );
      astPrintSrc(node->son[1], yyout);
      break;

    case  AST_FUNC:
      fprintf(yyout, "%s", node->symbol->text);
      fprintf(yyout, "( ");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " )");
      break;
    case  AST_ATRIB:
      fprintf(yyout,"%s", node->symbol->text);
      fprintf(yyout," = ");
      astPrintSrc(node->son[0], yyout);
      break;
    case AST_INIT_ARRAY:
      fprintf(yyout, "%s : ", node->symbol->text);
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, "[");
      astPrintSrc(node->son[1], yyout);
      fprintf(yyout, "] ");
      astPrintSrc(node->son[2], yyout);
      break;

    case AST_ARRAY_INIT_VALUES:
      if(node->son[1]){
        astPrintSrc(node->son[0], yyout);
        fprintf(yyout, " ");
        astPrintSrc(node->son[1], yyout);
      }
      else {
        astPrintSrc(node->son[0], yyout);
        // fprintf(yyout, ";");
      }
      break;

    case  AST_ARRAY:
      fprintf(yyout, "%s", node->symbol->text);
      fprintf(yyout, "[");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, "]");
      break;
    case  AST_ATRIB_ARRAY:
      fprintf(yyout, "%s", node->symbol->text);
      fprintf(yyout, "[");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, "]");
      fprintf(yyout, "=");
      astPrintSrc(node->son[1], yyout);
      break;
    case  AST_LIST_PARAM:
      if(node->son[1]){
        astPrintSrc(node->son[0], yyout);
        fprintf(yyout, ",");
        astPrintSrc(node->son[1], yyout);
      }
      else {
        astPrintSrc(node->son[0], yyout);
      }
      break;
    case  AST_PARAM:
      astPrintSrc(node->son[0], yyout);
      break;
    case  AST_ARG_ID:
      fprintf(yyout, "%s ", node->symbol->text);
      astPrintSrc(node->son[0], yyout);
      break;
    case  AST_LIST_ARG:
    if(node->son[1]){
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ",");
      astPrintSrc(node->son[1], yyout);
    }
    else {
      astPrintSrc(node->son[0], yyout);
    }
      break;
    case  AST_ARG:
      astPrintSrc(node->son[0], yyout);
      break;
    case  AST_START:
      if(node->son[0]){
        astPrintSrc(node->son[0], yyout);
      }
      astPrintSrc(node->son[1], yyout);
      break;
    case  AST_VARDEC:
      fprintf(yyout,"%s",node->symbol->text);
      fprintf(yyout,": ");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout,"=");
      astPrintSrc(node->son[1], yyout);
      break;
    case  AST_FUNDEC:
      fprintf(yyout, "( ");
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, " ) %s ( ", node->symbol->text);
      if(node->son[2]){
        astPrintSrc(node->son[1], yyout);
        fprintf(yyout, ")");
        astPrintSrc(node->son[2], yyout);
      }
      else {
        fprintf(yyout, ")");
        astPrintSrc(node->son[1], yyout);
      }
      break;
    case  AST_LIST_CMD:
      if(node->son[1]){
        astPrintSrc(node->son[0], yyout);
        fprintf(yyout, ";\n");
        astPrintSrc(node->son[1], yyout);
      }
      else if(node->son[0]) {
        astPrintSrc(node->son[0], yyout);
        fprintf(yyout, ";");
      }
      break;
    case AST_CMD:
      astPrintSrc(node->son[0], yyout);
      // fprintf(yyout, ";");
      break;
    case AST_BYTE:
      fprintf(yyout, "byte " );
      break;
    case AST_SHORT:
      fprintf(yyout, "short " );
      break;
    case AST_LONG:
      fprintf(yyout, "long " );
      break;
    case AST_FLOAT:
      fprintf(yyout, "float " );
      break;
    case AST_DOUBLE:
      fprintf(yyout, "double " );
      break;
    case AST_CHAR:
      fprintf(yyout, "%s", node->symbol->text);
      break;
    case AST_INTEGER:
      fprintf(yyout, "%s", node->symbol->text);
      break;
    case AST_REAL:
      fprintf(yyout, "%s", node->symbol->text);
      break;

    case AST_PARENTHESES:
      fprintf(yyout, "(" );
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ")" );
      break;
    case AST_VARIABLE:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ";\n");
      break;
    case AST_FUNCTION:
      astPrintSrc(node->son[0], yyout);
      break;
    case AST_EXPRESSION:
      astPrintSrc(node->son[0], yyout);
      fprintf(yyout, ";\n");
      break;
  }
}
