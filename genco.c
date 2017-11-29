#include "genco.h"

TAC* makeFuncDec(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol);
TAC* makeIfThen(TAC* code0, TAC* code1);
TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFuncDef(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol);
TAC* tacGenerateNot(int type, TAC* op1);
TAC* tacGenerateOp(int type, TAC* op1, TAC* op2);

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
    case AST_NOT:  return tacGenerateNot(TAC_NOT, code[0]); break;
    case AST_PARENTHESES: break;
    case AST_FUNC: return tacJoin(code[0], tacCreate(TAC_FUNC, makeTemp(), node->symbol, 0)); break;
    case AST_INIT_ARRAY: break;
    case AST_ARRAY_INIT_VALUES: break;
    case AST_ARRAY: break;
    case AST_ATRIB: return tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); break;
    case AST_ATRIB_ARRAY: break;
    case AST_READ: return tacCreate(TAC_READ, node->symbol, 0, 0); break;
    case AST_PRINT: return tacJoin(code[0], tacCreate(TAC_PRINT, 0,0,0)); break;
    case AST_RETURN: return tacJoin(code[0], tacCreate(TAC_RETURN, node->symbol, code[0]?code[0]->res:0, 0)); break;
    case AST_IF: return makeIfThen(code[0], code[1]); break;
    case AST_IF_ELSE: return makeIfThenElse(code[0], code[1], code[2]); break;
    case AST_WHILE: return makeWhile(code[0], code[1]); break;
    case AST_BLOCK: return code[0]; break;
    case AST_LIST_PARAM: return tacJoin(tacJoin(code[0], tacCreate(TAC_LIST_PARAM, code[0]? code[0]->res : 0, 0, 0)), code[1]); break;
    case AST_PARAM: return tacCreate(TAC_PARAM, node->symbol, 0, 0); break;
    case AST_ARG_ID: return tacJoin(code[0],tacCreate(TAC_ARG_ID, node->symbol, 0, 0)); break;
    case AST_LIST_ARG: break;
    case AST_ARG: break;
    case AST_VARDEC: break;
    case AST_FUNDEC: return makeFuncDec(code[0],code[1],code[2],node->symbol); break;
    case AST_LIST_CMD: break;
    case AST_CMD: break;
    case AST_FUNCTION: break;
    case AST_VARIABLE: break;
    case AST_EXPRESSION: break;
    case AST_START: break;
    default: 
      printf("Default case %d\n", node->type);
      return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
      break;
  }
}




TAC* tacGenerateNot(int type, TAC* op1){
    return tacJoin(code[0], tacCreate(type, makeTemp(), code[0]?code[0]->res:0, 0));
}


TAC* tacGenerateOp(int type, TAC* op1, TAC* op2){
    return tacJoin(op1,
                tacJoin(op2, tacCreate(type, makeTemp(), op1?op1->res:0, op2?op2->res:0)));
}


TAC* makeIfThen(TAC* code0, TAC* code1) {
  TAC *iftac, *labeltac;
  HASH_NODE* newlabel = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  return tacJoin(tacJoin(tacJoin(code0,iftac),code1),labeltac);
}

TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2) {
  TAC *iftac, *jumptac, *labeltac, *labeltac2;
  HASH_NODE *newlabel, *newlabel2;
  newlabel = makeLabel();
  newlabel2 = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  jumptac = tacCreate(TAC_JMP, newlabel2, 0, 0);
  labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0,iftac),code1),jumptac),labeltac),code2),labeltac2);
}

TAC* makeWhile(TAC* code0, TAC* code1) {
  TAC *iftac, *jumptac, *labeltac, *labeltac2, *movetac;
  HASH_NODE *newlabel, *newlabel2;
  newlabel = makeLabel();
  newlabel2 = makeLabel();
  iftac = tacCreate(TAC_IFZ, newlabel,code0?code0->res:0,0);
  labeltac = tacCreate(TAC_LABEL, newlabel, 0,0);
  jumptac = tacCreate(TAC_JMP, newlabel2, 0, 0);
  labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
  return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac2,code0),iftac),code1),jumptac),labeltac);
}

TAC* makeFuncDec(TAC* type, TAC* params, TAC* cmdBlock, HASH_NODE *symbol) {
  TAC* beginf = tacCreate(TAC_BEGIN_FUN, symbol, 0, 0);
  TAC* endf = tacCreate(TAC_END_FUN, symbol, 0, 0);

  return tacJoin(tacJoin(tacJoin(tacJoin(type,params),beginf), cmdBlock), endf);
}
