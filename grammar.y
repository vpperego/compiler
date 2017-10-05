%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '+' '-'
%left '*' '/'
%{
 void yyerror(char *);
 int yylex(void);
 int sym[26];
%}

%%

program:
 program expr '\n' { printf("%d\n", $2); }
 |
 ;
expr:
 KW_SHORT { $$ = $1; }
 | expr '+' expr { $$ = $1 + $3; }
 | expr '-' expr { $$ = $1 - $3; }
 ;


%%

void yyerror(char *s) {
 fprintf(stderr, "%s\n", s);
 return 0;
}
int main(void) {
 yyparse();
 return 0;
}
