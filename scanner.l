%{
#include "tokens.h"
int lines=0;
extern FILE *yyin;
%}
digits [0-9]
letter   [A-Za-z]

%%
\n      {fprintf(stderr,"Found newline... Total lines:%d\n", lines);lines++;}
"//"(.)* {fprintf(stderr,"Single-line commentary \n");}
"/*"(.)*"\*" {fprintf(stderr,"Multiple-line commentary \n");}

"if"	{fprintf(stderr,"Found If Token: %d\n", KW_WHEN);}
"byte"	{fprintf(stderr,"Found Byte Token: %d\n", KW_BYTE);}
"short"	{fprintf(stderr,"Found Short Token: %d\n", KW_SHORT);}
"long"	{fprintf(stderr,"Found Long Token: %d\n", KW_LONG);}
"float"	{fprintf(stderr,"Found Float Token: %d\n", KW_FLOAT);}
"double"	{fprintf(stderr,"Found Double Token: %d\n", KW_DOUBLE);}
"then"	{fprintf(stderr,"Found Then Token: %d\n", KW_THEN);}
"else"	{fprintf(stderr,"Found Else Token: %d\n", KW_ELSE);}
"while"	{fprintf(stderr,"Found While Token: %d\n", KW_WHILE);}
"for"	{fprintf(stderr,"Found For Token: %d\n", KW_FOR);}
"read"	{fprintf(stderr,"Found Read Token: %d\n", KW_READ);}
"print"	{fprintf(stderr,"Found Print Token: %d\n", KW_RETURN);}
"return"	{fprintf(stderr,"Found Return Token: %d\n", KW_PRINT);}

"<="	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_LE);}
">="	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_GE);}
"=="	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_EQ);}
"!="	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_NE);}
"&&"	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_AND);}
"||"	{fprintf(stderr,"Found Operator Token: %d\n", OPERATOR_OR);}

]|[|[*,;:(){}+-/<>=!&$#] {fprintf(stderr,"Found Operator Token: %s\n", yytext);}


{digits}+  {fprintf(stderr,"Found Literal Token: %d\n", LIT_INTEGER);}
{digits}+[.]{digits}+  {fprintf(stderr,"Found Literal Token: %d\n", LIT_REAL);}

['][A-Za-z]['] {fprintf(stderr,"Found Literal Token: %d\n", LIT_CHAR);}
["][A-Za-z]["] {fprintf(stderr,"Found Literal Token: %d\n", LIT_STRING);}

{letter}({letter}|{digits}|[_ ])* {fprintf(stderr,"Found Identifier Token: %d\n", TK_IDENTIFIER);}

. {fprintf(stderr,"Found Error Token: %d\n", TOKEN_ERROR);}

%%


int getLineNumber(void){
  return lines;
}

int yywrap(void){
 return 1;
}

int main(){
//  yyin=fopen("input.txt","r");

 yylex();
 printf("Lines: %d",getLineNumber());
 return 1;
}
