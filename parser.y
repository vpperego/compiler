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

	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

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

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%nonassoc KW_THEN
%nonassoc KW_ELSE

%type <ast> expr
%type <ast> cmd
%type <ast> block

%left '<' '>'
%left '!' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%start program

%%

/* Exemplos tirados da aula do professor*/
program : listdecl
    ;

listdecl : decl listdecl
    |
    ;

decl : expr
    | fundec
    | vardec
    ;

vardec : TK_IDENTIFIER ':' type '=' value ';'
    | TK_IDENTIFIER ':' type '['LIT_INTEGER']' init ';'
    ;

value: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    ;

init : value init
    |
    ;

fundec : '(' type ')' TK_IDENTIFIER '(' listArgs ')' block
    | '(' type ')' TK_IDENTIFIER '('  ')' block
    ;

block : '{' listCmd '}'
    ;

listCmd : cmd ';' listCmd
    | cmd
    ;

cmd : TK_IDENTIFIER '=' expr      {$$ = astCreate(AST_ATRIB,yylval.symbol,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr {$$ = astCreate(AST_ATRIB_ARRAY,yylval.symbol,$3,0,0,0);}
    | KW_READ '>' TK_IDENTIFIER   {$$ = astCreate(AST_READ,yylval.symbol,0,0,0,0);}
    | KW_PRINT listPrint        {$$ = astCreate(AST_PRINT,0,$2,0,0,0);}
    | KW_RETURN expr            {$$ = astCreate(AST_RETURN,0,$2,0,0,0);}
    | KW_IF '(' expr ')' KW_THEN cmd                           {$$ = astCreate(AST_IF,0,$3,0,0,0);}
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd              {$$ = astCreate(AST_IF_ELSE,0,$3,0,0,0);}
    | KW_WHILE '(' expr ')' cmd                               {$$ = astCreate(AST_WHILE,0,$3,0,0,0);}
	| block                  {$$ = $1;}
    |                   {$$ = 0;}
	;

listPrint : expr ',' listPrint
    | expr
    ;

type : KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;


expr : expr '+' expr    {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
    | expr '-' expr     {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
    | expr '*' expr     {$$ = astCreate(AST_MUL,0,$1,$3,0,0);}
    | expr '/' expr     {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
    | expr '<' expr     {$$ = astCreate(AST_LESS,0,$1,$3,0,0);}
    | expr '>' expr     {$$ = astCreate(AST_MORE,0,$1,$3,0,0);}
    | '!' expr          {$$ = astCreate(AST_NOT,0,$2,0,0,0);}
    | '(' expr ')'      {$$ = astCreate(AST_PARENTHESES,0,$2,0,0,0);}
    | expr OPERATOR_LE expr       {$$ = astCreate(OPERATOR_LE,0,$1,$3,0,0);}
    | expr OPERATOR_GE expr        {$$ = astCreate(OPERATOR_GE,0,$1,$3,0,0);}
    | expr OPERATOR_EQ expr         {$$ = astCreate(OPERATOR_EQ,0,$1,$3,0,0);}
    | expr OPERATOR_NE expr         {$$ = astCreate(OPERATOR_NE,0,$1,$3,0,0);}
    | expr OPERATOR_AND expr       {$$ = astCreate(OPERATOR_AND,0,$1,$3,0,0);}
    | expr OPERATOR_OR expr       {$$ = astCreate(OPERATOR_OR,0,$1,$3,0,0);}
    | TK_IDENTIFIER '(' listArgs  ')'     {$$ = astCreate(AST_FUNC,yylval.symbol,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']'   {$$ = astCreate(AST_ARRAY,yylval.symbol,$3,0,0,0);}
    | TK_IDENTIFIER             {$$ = astCreate(TK_IDENTIFIER,yylval.symbol,0,0,0,0);}
    | value
    | LIT_STRING            {$$ = astCreate(LIT_STRING,yylval.symbol,0,0,0,0);}
    ;

listArgs : arg ',' listArgs
    | arg
    ;

arg: TK_IDENTIFIER ':' type
    | TK_IDENTIFIER
    | value
    | LIT_STRING
    ;

%%

int yyerror(char *s) {
 fprintf(stderr, "Problema! ERRO linha = %d\n", getLineNumber());
 exit(3);
}
