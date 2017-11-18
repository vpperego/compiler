#include "astree.h"
#include "hash.h"

enum DATATYPE{
  DATATYPE_CHAR,
  DATATYPE_INT,
  DATATYPE_REAL,
  DATATYPE_STRING
};

void semanticSetTypes(AST * node);
void semanticCheckUndeclared();
void semanticCheckUsage(AST * node);
