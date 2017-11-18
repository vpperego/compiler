#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 999
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

void initMe(void);
HASH_NODE * hashInsert(int type, char *text);
void hashPrint();
void hashCheckUndeclared();
#endif
