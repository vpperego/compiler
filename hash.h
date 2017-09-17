// TODO:

// 3-Atualizar o Makefile
// 4-Corrigir eventuais bugs
// 5-Popular o hash com um codigo de entrada
// 6-Testar a saida
#define HASH_SIZE 999

typedef struct  hash_node {
  int type;
  char * text;
  struct hash_node * next;

}HASH_NODE;

HASH_NODE * table[HASH_SIZE];

void hashInit(void);
HASH_NODE * hashInsert(int type, char *text);
void hashPrint();
