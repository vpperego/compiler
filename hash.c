#include "tokens.h"
#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void hashInit(void){
  for (int i = 0; i < HASH_SIZE; i++) {
      table[i] = 0;
  }
}

int hashAddress(char * text){
  int address = 0;
  int i;
  for (i = 0; i < strlen(text); i++) {
    address = (address * text[i]) % HASH_SIZE +1;
  }
  return address -1;
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
  int i;
  HASH_NODE  * node;
  for (i = 0; i < HASH_SIZE; i++) {
      for (node = table[i]; node; node = node->next) {
        printf("Table[%d] has %s\n",i,node->text );
      }
  }

}
