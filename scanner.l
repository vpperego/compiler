%{
#include "tokens.h"
#include <stdio.h>
#include <string.h>
int lines=1;
int running = 1;

%}
digits [0-9]
letter   [A-Za-z]

%%

"//"(.)* {fprintf(stderr,"Single-line commentary \n"); return TOKEN_ERROR;}
"/*"(.|\n)*"*/" {fprintf(stderr,"Multiple-line commentary \n"); return TOKEN_ERROR;}

"if"	{return KW_IF;}
"byte"	{return KW_BYTE;}
"short"	{return KW_SHORT;}
"long"	{return KW_LONG;}
"float"	{return KW_FLOAT;}
"double"	{return KW_DOUBLE;}
"then"	{return KW_THEN;}
"else"	{return KW_ELSE;}
"while"	{return KW_WHILE;}
"for"	{return KW_FOR;}
"read"	{return KW_READ;}
"print"	{return KW_RETURN;}
"return"	{return KW_PRINT;}

"<="	{return OPERATOR_LE;}
">="	{return OPERATOR_GE;}
"=="	{return OPERATOR_EQ;}
"!="	{return OPERATOR_NE;}
"&&"	{return OPERATOR_AND;}
"||"	{return OPERATOR_OR;}

]|[|[*,;:(){}+-/<>=!&$#] {return yytext[0];}


{digits}+  {return LIT_INTEGER;}
{digits}+"."{digits}+  {return LIT_REAL;}

\'.\' {return LIT_CHAR;}
\"(\\.|[^"])*\" { return LIT_STRING;}

({letter}|_)({letter}|{digits}|[_ ])* {return TK_IDENTIFIER;}

"\n"      {++lines;}

. {return TOKEN_ERROR;}

%%


int getLineNumber(void){
  return lines;
}

int isRunning(){
	return running;
}

int yywrap(void){
 running = 0;
 return 1;
}

#include "main.c"
