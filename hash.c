#include "tokens.h"

#define HASH_SIZE 999
int myHash() {

    return 0;
}

void hashInit(void){
  for (size_t i = 0; i < HASH_SIZE; i++) {
      table[i] = 0;
  }
}

int hashAddress(char * text){
  int address = 0;
  int i;
  for (size_t i = 0; i < strlen(text); i++) {
    address = (address * text[i]) % HASH_SIZE;
  }
  return address;
}

HASH_NODE * hashInsert(int type, char *text){
  HASH_NODE *newNode;
  int address = hashAddress(text);
  newNode = (HASH_NODE *) calloc(1,sizeof(HASH_NODE));
  newNode->type = type;
  newNode->text = calloc(strlen(text)+1,sizeof(char));
  strcpy(newNode->text,text);
  newNode->next = table[address];
  table[address] = newNode;
  return newNode;
}

void hashPrint(){

}
