/*
    Etapa 2 Trabalho de Compiladores:
        Filipe Joner e Vinicius Pittigliani
*/

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
    #include "astree.h"
    #include "hash.h"
    #include "semantic.h"
	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

    AST *root, * temp;

%}

%union{
  AST * ast;
  HASH_NODE * symbol;
}

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

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%nonassoc KW_THEN
%nonassoc KW_ELSE

%type <ast> program
%type <ast> listdecl
%type <ast> decl
%type <ast> fundec
%type <ast> vardec
%type <ast> expr
%type <ast> cmd
%type <ast> block
%type <ast> value
%type <ast> init
%type <ast> listPrint
%type <ast> listArgs
%type <ast> type
%type <ast> arg
%type <ast> listCmd


%left '<' '>'
%left '!' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%start program

%%

/* Exemplos tirados da aula do professor*/
program : listdecl      {root = $1;
                      //  astPrint(root,0);
                        checkSemantics(root);}
    ;

listdecl : decl listdecl  {$$ = astCreate(AST_START, 0, $1, $2, 0, 0);}
    |         { $$ = 0; }
    ;

decl : expr               {$$ = astCreate(AST_EXPRESSION, 0, $1, 0, 0, 0);}
    | fundec              {$$ = astCreate(AST_FUNCTION, 0, $1, 0, 0, 0);}
    | vardec              {$$ = astCreate(AST_VARIABLE, 0, $1, 0, 0, 0);}
    ;

vardec : TK_IDENTIFIER ':' type '=' value ';'    {$$ = astCreate(AST_VARDEC,$1,$3,$5,0,0);}
    | TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' init ';'   {temp = astCreate(AST_INTEGER,$5,0,0,0,0);$$ = astCreate(AST_INIT_ARRAY,$1,$3,temp,$7,0);}
    ;

value: LIT_INTEGER      {$$ = astCreate(AST_INTEGER,$1,0,0,0,0);}
    | LIT_REAL          {$$ = astCreate(AST_REAL,$1,0,0,0,0);}
    | LIT_CHAR          {$$ = astCreate(AST_CHAR,$1,0,0,0,0);}
    ;

init : value init {$$ = astCreate(AST_ARRAY_INIT_VALUES,0,$1,$2,0,0);}
    |             {$$ = 0;}
    ;

fundec : '(' type ')' TK_IDENTIFIER '(' listArgs ')' block    {$$ = astCreate(AST_FUNDEC,$4,$2,$6,$8,0);}
    | '(' type ')' TK_IDENTIFIER '('  ')' block               {$$ = astCreate(AST_FUNDEC,$4,$2,$7,0,0);}
    ;

block : '{' listCmd '}'    {$$ = astCreate(AST_BLOCK,0,$2,0,0,0);}
    ;

listCmd : cmd ';' listCmd   {$$ = astCreate(AST_LIST_CMD,0,$1,$3,0,0);}
    | cmd              {$$ = astCreate(AST_CMD,0,$1,0,0,0);}
    ;

cmd : TK_IDENTIFIER '=' expr      {$$ = astCreate(AST_ATRIB,$1,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr {$$ = astCreate(AST_ATRIB_ARRAY,$1,$3,$6,0,0);}
    | KW_READ '>' TK_IDENTIFIER   {$$ = astCreate(AST_READ,$3,0,0,0,0);}
    | KW_PRINT listPrint        {$$ = astCreate(AST_PRINT,0,$2,0,0,0);}
    | KW_RETURN expr            {$$ = astCreate(AST_RETURN,0,$2,0,0,0);}
    | KW_IF '(' expr ')' KW_THEN cmd                           {$$ = astCreate(AST_IF,0,$3,$6,0,0);}
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd              {$$ = astCreate(AST_IF_ELSE,0,$3,$6,$8,0);}
    | KW_WHILE '(' expr ')' cmd                               {$$ = astCreate(AST_WHILE,0,$3,$5,0,0);}
	| block                  {$$ = $1;}
    |                   {$$ = 0;}
	;

listPrint : expr ',' listPrint      {$$ = astCreate(AST_LIST_PARAM,0,$1,$3,0,0);}
    | expr                          {$$ = astCreate(AST_PARAM,0,$1,0,0,0);}
    ;

type : KW_BYTE          {$$ = astCreate(AST_BYTE,0,0,0,0,0);}
    | KW_SHORT          {$$ = astCreate(AST_SHORT,0,0,0,0,0);}
    | KW_LONG          {$$ = astCreate(AST_LONG,0,0,0,0,0);}
    | KW_FLOAT          {$$ = astCreate(AST_FLOAT,0,0,0,0,0);}
    | KW_DOUBLE          {$$ = astCreate(AST_DOUBLE,0,0,0,0,0);}
    ;


expr : expr '+' expr    {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
    | expr '-' expr     {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
    | expr '*' expr     {$$ = astCreate(AST_MUL,0,$1,$3,0,0);}
    | expr '/' expr     {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
    | expr '<' expr     {$$ = astCreate(AST_LESS,0,$1,$3,0,0);}
    | expr '>' expr     {$$ = astCreate(AST_MORE,0,$1,$3,0,0);}
    | '!' expr          {$$ = astCreate(AST_NOT,0,$2,0,0,0);}
    | '(' expr ')'      {$$ = astCreate(AST_PARENTHESES,0,$2,0,0,0);}
    | expr OPERATOR_LE expr       {$$ = astCreate(AST_LE,0,$1,$3,0,0);}
    | expr OPERATOR_GE expr        {$$ = astCreate(AST_GE,0,$1,$3,0,0);}
    | expr OPERATOR_EQ expr         {$$ = astCreate(AST_EQ,0,$1,$3,0,0);}
    | expr OPERATOR_NE expr         {$$ = astCreate(AST_NE,0,$1,$3,0,0);}
    | expr OPERATOR_AND expr       {$$ = astCreate(AST_AND,0,$1,$3,0,0);}
    | expr OPERATOR_OR expr       {$$ = astCreate(AST_OR,0,$1,$3,0,0);}
    | TK_IDENTIFIER '(' listArgs ')'     {$$ = astCreate(AST_FUNC,$1,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']'   {$$ = astCreate(AST_ARRAY,$1,$3,0,0,0);}
    | TK_IDENTIFIER             {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | value                 {$$ = $1;}
    | LIT_STRING            {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    ;

listArgs : arg ',' listArgs {$$ = astCreate(AST_LIST_ARG,0,$1,$3,0,0);}
    | arg   {$$ =  $1;}
    ;

arg: TK_IDENTIFIER ':' type     {$$ = astCreate(AST_ARG_ID,$1,$3,0,0,0);}
    | expr                      {$$ = $1;}
    ;

%%

AST* getAst(){
	return root;
}

int yyerror(char *s) {
 fprintf(stderr, "Problema! ERRO linha = %d\n", getLineNumber());
 exit(3);
}
