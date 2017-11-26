#include "astree.h"
#include "hash.h"
#include "types.h"



void checkSemantics(AST *node);
void semanticSetTypes(AST * node);
void semanticCheckUndeclared();
void semanticCheckUsage(AST * node);
void semanticCheckOperands(AST *node);
