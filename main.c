#include <stdio.h>
#include <stdlib.h>

/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
extern int yylex();
extern char *yytext;
extern int lines;
extern FILE *yyin;
extern HASH_NODE * table[HASH_SIZE];
extern int getLineNumber(void);
extern int yyparse();
extern void initMe();
extern void hashPrint();

int isRunning();

int main(int argc, char *argv[]) {
	int token = 0;

	if(argc < 2) {
		fprintf(stderr, "Must execute ./etapa2 <inputFile> \n");
		exit(1);
	}

	if(!(yyin = fopen(argv[1], "r"))) {
		fprintf(stderr, "Couldn't open file %s\n", argv[1]);
		exit(1);
	}

	initMe();
	printf("Hash init complete.\n");
	while(isRunning()) {
		yyparse();
	}
	hashPrint();
	printf("Congratulations, Syntax is correct!s");
    return 0;
}
