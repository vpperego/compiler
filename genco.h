#include "hash.h"
#include "astree.h"
#include <string.h>

enum TAC_TYPE{
  TAC_SYMBOL,
  TAC_STRING,
  TAC_ADD,
  TAC_SUB,
  TAC_MUL,
  TAC_DIV,
  TAC_LESS,
  TAC_MORE,
  TAC_NOT,
  TAC_PARENTHESES,
  TAC_LE,
  TAC_GE,
  TAC_EQ,
  TAC_NE,
  TAC_AND,
  TAC_OR,
  TAC_FUNC,
  TAC_INIT_ARRAY,
  TAC_ARRAY_INIT_VALUES,
  TAC_ARRAY,
  TAC_ATRIB,
  TAC_ATRIB_ARRAY,
  TAC_READ,
  // TAC_PRINT,
  TAC_BEGIN_PRINT,
  TAC_END_PRINT,
  TAC_RETURN,
  TAC_BLOCK,
  TAC_LIST_PARAM,
  TAC_PARAM,
  TAC_ARG_ID,
  TAC_LIST_ARG,
  TAC_ARG,
  TAC_START,
  TAC_VARDEC,
  TAC_FUNDEC,
  TAC_LIST_CMD,
  TAC_CMD,
  TAC_BYTE,
  TAC_SHORT,
  TAC_LONG,
  TAC_FLOAT,
  TAC_DOUBLE,
  TAC_CHAR,
  TAC_INTEGER,
  TAC_REAL,
  TAC_FUNCTION,
  TAC_VARIABLE,
  TAC_EXPRESSION,
  TAC_BEGIN_FUN,
  TAC_END_FUN,
  TAC_JMP,
  TAC_IFZ,
  TAC_MOVE,
  TAC_MOV_IND,
  TAC_LABEL
};

typedef struct struct_tac
{
  int type;
  HASH_NODE * res;
  HASH_NODE * op1;
  HASH_NODE * op2;
  struct struct_tac * prev;
  struct struct_tac * next;
}TAC;

TAC * tacStart;

TAC * tacCreate(int type, HASH_NODE * res, HASH_NODE * op1, HASH_NODE * op2);
TAC * tacGenerator(AST * node);
TAC * tacJoin(TAC *l1, TAC *l2);
void tacPrintFoward(TAC* first);
void tacPrintSingle(TAC *tac);
TAC* tacReverse(TAC* tac);
TAC* tacGenerateOp(int type, TAC* op1, TAC* op2);
void generateAssembly(TAC * code);

void asmGen(TAC *first);
