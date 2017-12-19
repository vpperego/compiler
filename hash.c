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
    exitCode = 0;
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

HASH_NODE * getHashBydataType(char *text,int dataType){
  HASH_NODE *node;
  int address = hashAddress(text);
  for (node = table[address]; node; node = node->next) {
    if(node->dataType == dataType) {
      return node;
    }
  }
  return NULL;
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
  if (type == SYMBOL_LIT_INT) newNode->dataType = SYMBOL_DATATYPE_LONG;
	if (type == SYMBOL_LIT_REAL) newNode->dataType = SYMBOL_DATATYPE_DOUBLE;
	if (type == SYMBOL_LIT_CHAR) newNode->dataType = SYMBOL_DATATYPE_LONG;
	if (type == SYMBOL_LIT_STRING) newNode->dataType = SYMBOL_DATATYPE_DOUBLE;
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
  int i;
  HASH_NODE  * node;
  for (i = 0; i < HASH_SIZE; i++) {
    for (node = table[i]; node; node = node->next) {
      if(node->type == SYMBOL_IDENTIFIER)
        fprintf(stderr,"SEMANTIC ERROR: symbol %s not declared\n",node->text );
      }
  }
}


HASH_NODE * makeTemp(void){
  static int factorySerialNumber = 0;
  char  nameBuffer[256];
  sprintf(nameBuffer,"myOwnvarPrefix%d",factorySerialNumber++);
  return hashInsert(SYMBOL_TEMP,nameBuffer);
}

HASH_NODE * makeLabel(void){
  static int factorySerialNumber = 0;
  char  nameBuffer[256];
  sprintf(nameBuffer,"LabEl%d",factorySerialNumber++);
  return hashInsert(SYMBOL_LABEL,nameBuffer);
}


void asmAddTemp(){
	int i;
	FILE* fout = fopen("asm.s", "a");
	for(i=0;i<HASH_SIZE;i++)
	{	
		HASH_NODE* aux;
		for(aux = table[i]; aux; aux = aux->next){
			if(aux->type == SYMBOL_TEMP) {
				fprintf(fout, "\t.globl	_%s\n"
				"\t.data\n"
				"\t.type	_%s, @object\n"
				"\t.size	_%s, 4\n"
				"_%s:\n" 				
				"\t.long 0\n" , aux->text, aux->text, aux->text, aux->text);
			}		
		}
	}	

	fclose(fout);
}

void asmAddImm(){
	int i;
	FILE* fout = fopen("asm.s", "a");
	for(i=0;i<HASH_SIZE;i++)
	{	
		HASH_NODE* aux;
		for(aux = table[i]; aux; aux = aux->next){
			if((aux->type == SYMBOL_LIT_INT || aux->type == SYMBOL_LIT_REAL) && (aux->dataType == SYMBOL_DATATYPE_BYTE ||aux->dataType == SYMBOL_DATATYPE_SHORT || aux->dataType == SYMBOL_DATATYPE_LONG))
			{ 
				    fprintf(fout, "\t.globl	_%s\n"
				    "\t.data\n"
				    "\t.type	_%s, @object\n"
				    "\t.size	_%s, 4\n"
				    "_%s:\n" ,aux->text, aux->text, aux->text, aux->text);
                		    if(aux->dataType == SYMBOL_DATATYPE_FLOAT || aux->dataType == SYMBOL_DATATYPE_DOUBLE)
			            {
					    fprintf(fout, "\t.float	%s\n", aux->text);
			   	    }
				    else if(aux->dataType == SYMBOL_DATATYPE_BYTE ||aux->dataType == SYMBOL_DATATYPE_SHORT || aux->dataType == SYMBOL_DATATYPE_LONG){
				    	fprintf(fout, "\t.long	%s\n", aux->text);
			    	    }
			}
		}
	}	

	fclose(fout);
}
