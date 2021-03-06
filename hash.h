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
#define SYMBOL_ARRAY 10
#define SYMBOL_ARG_ID 11
#define SYMBOL_SCALAR 12
#define SYMBOL_UNDEF 13
#define SYMBOL_LABEL 14
#define SYMBOL_DATATYPE_BYTE 201
#define SYMBOL_DATATYPE_SHORT 202
#define SYMBOL_DATATYPE_LONG 203

#define SYMBOL_DATATYPE_FLOAT 204
#define SYMBOL_DATATYPE_DOUBLE 205

#define SYMBOL_DATATYPE_BOOL 206
#define SYMBOL_TEMP 207
/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
 typedef struct  hash_node {
  int type;
  int dataType;
  int parametersNumber;
  void * parameters;
  char * text;
  struct hash_node * next;
}HASH_NODE;

HASH_NODE * table[HASH_SIZE];

int exitCode;

void initMe(void);
HASH_NODE * hashInsert(int type, char *text);
void hashPrint();
void hashCheckUndeclared();
HASH_NODE * getHashByDatatype(char *text,int datatype);
HASH_NODE * makeTemp(void);
HASH_NODE * makeLabel(void);

void asmAddTemp();
void asmAddImm();
#endif
