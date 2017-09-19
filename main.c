#include "tokens.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Filipe Joner
* Vinícius Pittigliani Perego
*/
int yylex();
extern char *yytext;
extern int lines;
extern FILE *yyin;
extern HASH_NODE * table[HASH_SIZE];
extern int getLineNumber(void);

int isRunning();

int main(int argc, char *argv[]) {
	int token = 0;

	if(argc < 2) {
		fprintf(stderr, "Must execute ./etapa1 <inputFile> \n");
		exit(1);
	}

	if(!(yyin = fopen(argv[1], "r"))) {
		fprintf(stderr, "Couldn't open file %s\n", argv[1]);
		exit(1);
	}

	initMe();
	printf("Hash init complete.\n");
	while(isRunning()) {
		token = yylex();

		switch(token) {

			case KW_IF: {fprintf(stderr,"%d. Found If Token: %d\n", lines, KW_IF); break;}
			case KW_BYTE:	{fprintf(stderr,"%d. Found Byte Token: %d\n", lines, KW_BYTE); break;}
			case KW_SHORT:	{fprintf(stderr,"%d. Found Short Token: %d\n", lines, KW_SHORT); break;}
			case KW_LONG:	{fprintf(stderr,"%d. Found Long Token: %d\n", lines, KW_LONG); break;}
			case KW_FLOAT:	{fprintf(stderr,"%d. Found Float Token: %d\n", lines, KW_FLOAT); break;}
			case KW_DOUBLE:	{fprintf(stderr,"%d. Found Double Token: %d\n", lines, KW_DOUBLE); break;}
			case KW_THEN:	{fprintf(stderr,"%d. Found Then Token: %d\n", lines, KW_THEN); break;}
			case KW_ELSE:	{fprintf(stderr,"%d. Found Else Token: %d\n", lines, KW_ELSE); break;}
			case KW_WHILE:	{fprintf(stderr,"%d. Found While Token: %d\n", lines, KW_WHILE); break;}
			case KW_FOR:	{fprintf(stderr,"%d. Found For Token: %d\n", lines, KW_FOR); break;}
			case KW_READ:	{fprintf(stderr,"%d. Found Read Token: %d\n", lines, KW_READ); break;}
			case KW_PRINT:	{fprintf(stderr,"%d. Found Print Token: %d\n", lines, KW_PRINT); break;}
			case KW_RETURN:	{fprintf(stderr,"%d. Found Return Token: %d\n", lines, KW_PRINT); break;}

			case OPERATOR_LE:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_LE); break;}
			case OPERATOR_GE:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_GE); break;}
			case OPERATOR_EQ:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_EQ); break;}
			case OPERATOR_NE:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_NE); break;}
			case OPERATOR_AND:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_AND); break;}
			case OPERATOR_OR:	{fprintf(stderr,"%d. Found Operator Token: %d\n", lines, OPERATOR_OR); break;}

			case LIT_INTEGER: {fprintf(stderr,"%d. Found Literal Token: %d\n", lines, LIT_INTEGER); break;}
			case LIT_REAL:  {fprintf(stderr,"%d. Found Literal Token: %d\n", lines, LIT_REAL); break;}

			case LIT_CHAR: {fprintf(stderr,"%d. Found Literal Token: %d\n", lines, LIT_CHAR); break;}
			case LIT_STRING: {fprintf(stderr,"%d. Found Literal Token: %d\n", lines, LIT_STRING); break;}

			case TK_IDENTIFIER: {fprintf(stderr,"%d. Found Identifier Token: %d (with value ""%s"")\n", lines, TK_IDENTIFIER,yytext); break;}

			case TOKEN_ERROR: {fprintf(stderr,"%d. Found Error Token: %d\n", lines, TOKEN_ERROR); break;}

			default: {fprintf(stderr,"%d. Found Operator Token:%c (ascii value %d)\n", lines,(char)token,token); break;}
		}
		if(token!=TOKEN_ERROR)
			hashInsert(token,yytext);

	}
	hashPrint();
	printf("End. Total input lines:%d\n",getLineNumber() );
    return 0;
}
