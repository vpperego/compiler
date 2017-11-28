#include "genco.h"

TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2){
  TAC * newtac = (TAC *) calloc(1,sizeof(TAC));
  newtac->type = type;
  newtac->res = res;
  newtac->op1 = op1;
  newtac->op2 = op2;
  newtac->prev = 0;
  newtac->next = 0;
  return newtac;
}

TAC * tacJoin(TAC *l1, TAC *l2){
  TAC * tac;
  if (!l1) return 0;
  if (!l2) return 0;

  while(tac->prev){
    tac = tac->prev;
  }
  tac->prev = l1;
  //l1->next = l2; will be used to invert the tac three later

  return l2;
}

void tacPrintSingle(TAC *tac){
  if (!tac) return;
  fprintf(stderr, "TAC(" );
  switch (tac->type) {
    case TAC_SYMBOL:  fprintf(stderr,"TAC_SYMBOL"); break;
    case TAC_ADD:  fprintf(stderr,"TAC_ADD"); break;
    case TAC_MUL:  fprintf(stderr,"TAC_MUL"); break;
    case TAC_SUB:  fprintf(stderr,"TAC_SUB"); break;
    default: break;
  }

  if(tac->res) fprintf(stderr, "%s\n",tac->res->text ); else fprintf(stderr, ", null" );
  if(tac->op1) fprintf(stderr, "%s\n",tac->op1->text ); else fprintf(stderr, ", null" );
  if(tac->op2) fprintf(stderr, "%s\n",tac->op2->text ); else fprintf(stderr, ", null" );
}

void tacPrintBack(TAC * last){
  TAC * tac;
  for ( tac = last; tac; tac = tac->prev) {
     tacPrintBack(tac);
  }
}

TAC * tacGenerator(AST * node){
  int i;

  TAC * code[MAX_SONS];
  if (!node) return 0;

  for (i = 0; i < MAX_SONS; i++) {
    code[i] = tacGenerator(node->son[i]);
  }


  //TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2) Just to remind the order of parameters
  switch (node->type) {
    case AST_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
    case AST_ADD:  return tacGenerateOp(TAC_ADD, code[0], code[1]); break;
    case AST_SUB:  return tacGenerateOp(TAC_SUB, code[0], code[1]); break;
    case AST_MUL:  return tacGenerateOp(TAC_MUL, code[0], code[1]); break;
    case AST_DIV:  return tacGenerateOp(TAC_DIV, code[0], code[1]); break;
    case AST_LESS: return tacGenerateOp(TAC_LESS, code[0], code[1]); break;
    case AST_MORE: return tacGenerateOp(TAC_MORE, code[0], code[1]); break;
    case AST_LE:   return tacGenerateOp(TAC_LE, code[0], code[1]); break;
    case AST_GE:   return tacGenerateOp(TAC_GE, code[0], code[1]); break;
    case AST_EQ:   return tacGenerateOp(TAC_EQ, code[0], code[1]); break;
    case AST_NE:   return tacGenerateOp(TAC_NE, code[0], code[1]); break;
    case AST_AND:  return tacGenerateOp(TAC_AND, code[0], code[1]); break;
    case AST_OR:   return tacGenerateOp(TAC_OR, code[0], code[1]); break;
    case AST_BYTE: return tacCreate(TAC_BYTE, 0, 0, 0); break;
    case AST_SHORT: return tacCreate(TAC_SHORT, 0, 0, 0); break;
    case AST_LONG:  return tacCreate(TAC_LONG, 0, 0, 0); break;
    case AST_FLOAT: return tacCreate(TAC_FLOAT, 0, 0, 0); break;
    case AST_DOUBLE: return tacCreate(TAC_DOUBLE, 0, 0, 0); break;
    case AST_CHAR:  return tacCreate(TAC_CHAR, 0, 0, 0); break;
    case AST_INTEGER: return tacCreate(TAC_INTEGER, 0, 0, 0); break;
    case AST_REAL:  return tacCreate(TAC_REAL, 0, 0, 0); break;
    case AST_START: return; //Fill with necessary return for program
    default: break;
  }
}

TAC * makeIfThen(TAC * code0, TAC * code1){
  TAC * newJumpTac = 0;
  TAC * newLabelTac = 0;
  HASH_NODE * newLabel = makeLabel() ;
  newJumpTac =tacCreate(TAC_JMP,newLabel,0,0);
  newLabelTac = tacCreate(TAC_LABEL,newLabel,0,0);
  return NULL;
}


TAC* tacGenerateOp(int type, TAC* op1, TAC* op2) {
    return tacJoin(op1,
                tacJoin(op2, tacCreate(type, makeTemp(), op1?op1->res:0, op2?op2->res:0)));
    return NULL;
}
