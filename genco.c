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

  return l2;
}

void tacPrintSingle(TAC *tac){
  if (!tac) return;
  fprintf(stderr, "TAC(", );
  switch (tac->type;) {
    case TAC_SYMBOL:  fprintf(stderr,"TAC_SYMBOL"); break;
    case TAC_ADD:  fprintf(stderr,"TAC_ADD"); break;
    case TAC_MUL:  fprintf(stderr,"TAC_MUL"); break;
    case TAC_SUB:  fprintf(stderr,"TAC_SUB"); break;
    default: break;
  }

  if(tac->res) fprintf(stderr, "%s\n",tac->res->text ) else fprintf(stderr, ", null" );
  if(tac->op1) fprintf(stderr, "%s\n",tac->op1->text ) else fprintf(stderr, ", null" );
  if(tac->op2) fprintf(stderr, "%s\n",tac->op2->text ) else fprintf(stderr, ", null" );
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

  switch (node->type) {
    case TAC_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
    case TAC_ADD:  fprintf(stderr,"TAC_ADD"); break;
    case TAC_MUL:  fprintf(stderr,"TAC_MUL"); break;
    case TAC_SUB:  fprintf(stderr,"TAC_SUB"); break;
    default: break;
  }
}
