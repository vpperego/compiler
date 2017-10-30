#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
extern int yylex();
extern char *yytext;
extern FILE* file();
extern int lines;
extern FILE *yyin;
extern HASH_NODE * table[HASH_SIZE];
extern int getLineNumber(void);
extern int yyparse();
extern void initMe();
extern AST* getAst();
extern void hashPrint();

FILE *out;
int isRunning();


int main(int argc, char *argv[]) {
	int token;
	if(argc<3){
		fprintf(stderr,"Execute: ./etapa3 inputfile outputfile\n");
		return 1;
	}
	if(!(yyin = fopen(argv[1],"r"))){
		fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[1]);
		return 2;
	}
	
	initMe();
	
	yyparse();

	AST *tree = getAst();

    out = fopen(argv[2], "w");

    if(out == NULL){
        fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[2]);
		return 2;
	} else {
		astPrintSrc(tree, out);
	}
		
	fclose(out);
	hashPrint();
     
    return 0; 
}
