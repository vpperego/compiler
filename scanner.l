
digits [0-9]

%%
"byte"	{fprintf(stderr,"Found Byte Token: %d/n", KW_BYTE);}
"short"	{fprintf(stderr,"Found Short Token: %d/n", KW_SHORT);}
"long"	{fprintf(stderr,"Found Long Token: %d/n", KW_LONG);}
"float"	{fprintf(stderr,"Found Float Token: %d/n", KW_FLOAT);}
"double"	{fprintf(stderr,"Found Double Token: %d/n", KW_DOUBLE);}
"if"	{fprintf(stderr,"Found If Token: %d/n", KW_IF);}
"then"	{fprintf(stderr,"Found Then Token: %d/n", KW_THEN);}
"else"	{fprintf(stderr,"Found Else Token: %d/n", KW_ELSE);}
"while"	{fprintf(stderr,"Found While Token: %d/n", KW_WHILE);}
"for"	{fprintf(stderr,"Found For Token: %d/n", KW_FOR);}
"read"	{fprintf(stderr,"Found Read Token: %d/n", KW_READ);}
"print"	{fprintf(stderr,"Found Print Token: %d/n", KW_RETURN);}
"return"	{fprintf(stderr,"Found Return Token: %d/n", KW_PRINT);}

[,;:()[]{}+-*/<>=!&$#] {fprintf(stderr,"Found Operator Token: %s/n", yytext[0]);}
"<="	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_LE);}
">="	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_GE);}
"=="	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_EQ);}
"!="	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_NE);}
"&&"	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_AND);}
"||"	{fprintf(stderr,"Found Operator Token: %d/n", OPERATOR_OR);}

[A-Za-Z][A-Za-z0-9_ ]* {fprintf(stderr,"Found Identifier Token: %d/n", TK_IDENTIFIER);}

{digits}+  {fprintf(stderr,"Found Literal Token: %d/n", LIT_INTEGER);}
{digits}+[.]{digits}+  {fprintf(stderr,"Found Literal Token: %d/n", LIT_REAL);}

['][A-Za-z]['] {fprintf(stderr,"Found Literal Token: %d/n", LIT_CHAR);}
["][A-Za-z]["] {fprintf(stderr,"Found Literal Token: %d/n", LIT_STRING);}

. {fprintf(stderr,"Found Error Token: %d/n", TOKEN_ERROR);}

%%




int yywrap(void){
 return 1;
}

int main(){
 yylex();
 return 1; 
}

