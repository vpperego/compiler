#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "genco.h"
/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
extern int yylex();
extern int exitCode;
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
	if(argc<2){
		fprintf(stderr,"Execute: ./etapa5 inputfile \n");
		return 1;
	}
	if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[1]);
			return 2;
	}

	initMe();
	yyparse();

	// AST *tree = getAst();
	tacPrintBack(tacStart);
//	hashPrint();
	exit(exitCode);
    return 0;
}
