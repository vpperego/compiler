// #include "y.tab.h" TODO - Don't know if this is needed
 #include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/



void hashInit(void){
  int i = 0;
  for (i = 0; i < HASH_SIZE; i++) {
      table[i] = 0;
  }
}

void initMe(void){
    hashInit();
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
  HASH_NODE *node;
  int address = hashAddress(text);

  for (node = table[address]; node; node = node->next) {
    if((strcmp(text, node->text)) == 0) {
      return node;
    }
  }

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

void hashCheckUndeclared(){
  
}
