/*
    Etapa 2 Trabalho de Compiladores:
        Filipe Joner e Vinicius Pittigliani
*/

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	
	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

%}

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

%left '<' '>'  
%left '!' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%start prog

%%

/* Exemplos tirados da aula do professor*/
program : dec

dec : expr
    | fundec
    | vardec
    ;

vardec : TK_IDENTIFIER ':' type '=' value ';'
    | TK_IDENTIFIER ':' type '['LIT_INTEGER']' init';'
    ;

value: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    ;

init : value init
    |
    ;

fundec : '(' type ')' TK_IDENTIFIER '(' listArgs ')' block
    ;

block : '{' listCmd '}'
    ;

listCmd : cmd ';' listCmd
    | cmd
    ;

cmd : TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    | KW_READ '>' TK_IDENTIFIER
    | KW_PRINT listPrint
    | KW_RETURN expr
    | KW_IF '(' expr ')' KW_THEN cmd
    | KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd
    | KW_WHILE '(' expr ')' cmd
	| block
    |
	;

listPrint : printable ',' listPrint
    ;

printable : expr
    |
    ;

type : KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;


expr : expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | expr '<' expr
    | expr '>' expr
    | '!' expr
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
    | value
    | LIT_STRING
    ;

listArgs : arg ',' listArgs
    |
    ;

arg: TK_IDENTIFIER ':' type
    | TK_IDENTIFIER
    | value
    | LIT_STRING
    ;

%%

void yyerror(char *s) {
 fprintf(stderr, "%s\n", s);
 return 0;
}

