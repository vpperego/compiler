#include "astree.h"
#include "hash.h"

enum DATATYPE{
  DATATYPE_BYTE,
  DATATYPE_CHAR,
  DATATYPE_SHORT,
  DATATYPE_FLOAT,
  DATATYPE_DOUBLE,
  DATATYPE_LONG,
  DATATYPE_REAL,
  DATATYPE_STRING,
  DATATYPE_BOOL,
  DATATYPE_UNDEF
};


void checkSemantics(AST *node);
void semanticSetTypes(AST * node);
void semanticCheckUndeclared();
void semanticCheckUsage(AST * node);
void semanticCheckOperands(AST *node);
