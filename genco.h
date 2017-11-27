#include "hash.h"
#include "astree.h"

enum TAC_TYPE{
  TAC_SYMBOL,
  TAC_ADD,
  TAC_MUL,
  TAC_SUB
};
typedef struct_tac
{
  int type;
  HASH_NODE * res;
  HASH_NODE * op1;
  HASH_NODE * op2;
  struct struct_tac * prev;
  struct struct_tac * next;
}TAC;

TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2);
TAC * tacGenerator(AST * node);
TAC * tacJoin(TAC *l1, TAC *l2);
void tacPrintBack(TAC * last);
