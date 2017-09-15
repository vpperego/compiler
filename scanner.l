digits [0-9]
%%
"int"	{fprintf(stderr,"Int detectado");}
{digits}*  {fprintf(stderr,"Numero....");}

%%



int yywrap(void){
 return 1;
}

int main(){
 yylex();
 return 1;
}

