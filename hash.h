#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 999

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 7
#define SYMBOL_VAR 8
#define SYMBOL_FUN 9
#define SYMBOL_ARR 10

/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
typedef struct  hash_node {
  int type;
  int datatype;
  char * text;
  struct hash_node * next;

}HASH_NODE;

HASH_NODE * table[HASH_SIZE];

int exitCode;

void initMe(void);
HASH_NODE * hashInsert(int type, char *text);
void hashPrint();
void hashCheckUndeclared();
#endif
