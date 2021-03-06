%{

#include "astree.h"
#include "y.tab.h"
#include "hash.h"
#include <stdio.h>


void yyerror(char *);


int lines=1;
int running = 1;
int yyparse();

%}
digits [0-9]
letter   [A-Za-z]

%x COMMENT

%%

"//"(.)*
"/*"	{BEGIN(COMMENT);}

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
"print"	{return KW_PRINT;}
"return"	{return KW_RETURN;}

"<="	{return OPERATOR_LE;}
">="	{return OPERATOR_GE;}
"=="	{return OPERATOR_EQ;}
"!="	{return OPERATOR_NE;}
"&&"	{return OPERATOR_AND;}
"||"	{return OPERATOR_OR;}

]|[|[*,;:(){}+-/<>=!&$#] {return yytext[0];}


{digits}+  {yylval.symbol = hashInsert(SYMBOL_LIT_INT, yytext);return LIT_INTEGER;}
{digits}+"."{digits}+  {yylval.symbol = hashInsert(SYMBOL_LIT_REAL,yytext);return LIT_REAL;}

\'.\' {yylval.symbol = hashInsert(SYMBOL_LIT_CHAR, yytext);return LIT_CHAR;}
\"(\\.|[^"])*\" {yylval.symbol =  hashInsert(SYMBOL_LIT_STRING, yytext);return LIT_STRING;}

[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])* {yylval.symbol = hashInsert(SYMBOL_IDENTIFIER, yytext);return TK_IDENTIFIER;}


"\n"      {++lines;}
"\t"
" "
. {return TOKEN_ERROR;}


<COMMENT>"\n" { ++lines; }
<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>.


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
