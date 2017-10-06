/* Exemplos tirados da aula do professor*/
program : decl

decl : dec decl

dec : vardec
    | fundec
    ;

vardec : TK_IDENTIFIER':' type '=' value
    ;

fundec : type TK_IDENTIFIER '(' listArgs ')' cmd
    | type TK_IDENTIFIER '('  ')' cmd
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
