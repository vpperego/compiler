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

/* Exemplos tirados da aula do professor*/
program : decl

decl : dec decl

dec : vardec
    | fundec
    ;

vardec : TK_IDENTIFIER':' type '=' value
    ;
    
fundec : KW_BYTE TK_IDENTIFIER '(' listArgs ')' cmd
    ;

cmd : TK_IDENTIFIER '=' expr
	| block
	;

block : '{' listCmd '}'

listCmd : cmd listCmd
    |
    ;

type : KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    ;

/* inicio nosso */

expr :
    KW_SHORT { $$ = $1; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | expr '&&' expr    
    | '(' expr ')'
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_NE expr
    | expr OPERATOR_AND expr
    | expr OPERATOR_OR expr
    | TK_IDENTIFIER '(' listArgs  ')'
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER
    | LIT_INTEGER   { $$ = $1; }
    | LIT_REAL  { $$ = $1; }
    ;

listArgs : arg listArgs
    | 
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
