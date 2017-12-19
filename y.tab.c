/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 7 "parser.y"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
    #include "astree.h"
    #include "hash.h"
    #include "semantic.h"
    #include "genco.h"

	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

    AST *root, * temp;

#line 23 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
  AST * ast;
  HASH_NODE * symbol;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 48 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_BYTE 257
#define KW_SHORT 258
#define KW_LONG 259
#define KW_FLOAT 260
#define KW_DOUBLE 261
#define KW_IF 262
#define KW_THEN 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_FOR 266
#define KW_READ 267
#define KW_RETURN 268
#define KW_PRINT 269
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define TK_IDENTIFIER 276
#define LIT_INTEGER 277
#define LIT_REAL 278
#define LIT_CHAR 279
#define LIT_STRING 280
#define TOKEN_ERROR 281
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    4,    4,    8,    8,
    8,    9,    9,    3,    3,    7,   14,   14,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,   10,   10,
   12,   12,   12,   12,   12,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,   11,   11,   13,   13,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    1,    1,    1,    6,    8,    1,    1,
    1,    2,    0,    8,    7,    3,    3,    1,    3,    6,
    3,    2,    2,    6,    8,    5,    1,    0,    3,    1,
    1,    1,    1,    1,    1,    3,    3,    3,    3,    3,
    3,    2,    3,    3,    3,    3,    3,    3,    3,    4,
    4,    1,    1,    1,    3,    1,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    9,   10,   11,   54,    0,    0,    0,    1,    0,
    5,    6,    0,   53,    0,    0,    0,    0,    0,    0,
   31,   32,   33,   34,   35,    0,    0,    2,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   38,   39,
    0,    0,   51,    0,   50,    0,    0,    0,    0,   57,
   55,    0,    7,    0,    0,    0,    0,    0,    0,   15,
    0,   12,    8,    0,    0,    0,    0,    0,    0,    0,
   27,    0,   14,    0,    0,    0,    0,    0,   22,    0,
    0,    0,   16,    0,    0,   21,    0,    0,    0,   17,
    0,    0,   29,    0,    0,   26,    0,    0,    0,    0,
   25,
};
static const YYINT yydgoto[] = {                          8,
    9,   10,   11,   12,   44,   90,   91,   14,   78,   99,
   45,   27,   46,   92,
};
static const YYINT yysindex[] = {                       195,
  -38,    0,    0,    0,    0,  295,  222,    0,    0,  195,
    0,    0,  590,    0, -161,  295,  323,  -36,  295,   34,
    0,    0,    0,    0,    0,  516,  -27,    0,  295,  295,
  295,  295,  295,  295,  295,  295,  295,  295,  295,  295,
  -42,  574,  -37,  590,   -9,   -4,    0, -238,   34,   34,
   34,   34,   34,   34,  404,  404,   -6,   -6,    0,    0,
 -158, -227,    0, -161,    0,  323,   11,   -1,  -31,    0,
    0,  146,    0, -158,  -50,   44, -158,   30,  386,    0,
  -50,    0,    0,   61,   62,   42,  295,  295,  -39,   53,
    0,  -12,    0,  295,  295, -160,  590,  522,    0,  295,
  295,  386,    0,  546,  568,    0,  295,  590,  580,    0,
 -141,  386,    0,   63,  386,    0,  295, -139,  590,  386,
    0,
};
static const YYINT yyrindex[] = {                       123,
  470,    0,    0,    0,    0,    0,    0,    0,    0,  123,
    0,    0,   75,    0,    0,    0,    0,    1,    0,   70,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -34,   15,    0,   86,    0,    0,   95,  118,
  141,  164,  189,  445,  487,  493,   24,   47,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   72,    0,    0,   72,    0,  -59,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    8,
    0,    0,    0,    0,    0,    0,  -54,  -47,    0,    0,
    0,  -59,    0,    0,    0,    0,    0,  -43,    0,    0,
    0,  -32,    0,    0,  -32,    0,    0,  -53,  -20,  -32,
    0,
};
static const YYINT yygindex[] = {                         0,
  124,    0,    0,    0,  866,  -97,  -46,  -44,   60,   31,
  -35,   10,    0,   40,
};
#define YYTABLESIZE 983
static const YYINT yytable[] = {                         28,
   52,   17,   17,   17,   23,   24,   52,   52,   52,   52,
   52,   30,   52,   48,  116,   19,   68,  118,   61,   15,
   64,  100,  121,   36,   41,   52,   28,   52,   80,   77,
   71,   65,   77,   52,   93,   39,   76,   67,   20,   66,
   40,   52,   52,   52,   52,   52,   37,   52,   62,   69,
   72,  101,   16,   16,   16,   58,   36,   73,   58,   52,
   52,   74,   52,   36,   36,   28,   36,   36,   36,   42,
   23,   24,   79,   70,    4,   39,   37,   30,   38,   37,
   40,   19,   36,   36,   81,   36,   37,   37,   83,   37,
   37,   37,   28,   52,   44,   21,   22,   23,   24,   25,
   94,   95,   42,   96,   20,   37,   37,    4,   37,   42,
   42,  102,  103,   42,    4,  106,   36,   45,    2,    3,
    4,  115,    3,  117,  120,   52,   56,   44,   42,   42,
   13,   42,   18,   28,   44,   44,   82,  113,   44,   37,
   46,  110,    0,    0,    0,    0,    0,    0,   36,    0,
   45,    0,    0,   44,   44,    0,   44,   45,   45,    0,
    0,   45,   42,   47,    0,    0,    0,    0,    0,    0,
    0,   37,    0,   46,    0,    0,   45,   45,    6,   45,
   46,   46,    0,    0,   46,   19,   75,   44,   48,    0,
    0,    0,    0,    0,   42,    0,   47,    0,    0,   46,
   46,    0,   46,   47,   47,    0,    0,   47,    0,   23,
   45,    0,    0,    0,    0,    0,   30,    0,    0,   44,
   19,   48,   47,   47,    0,   47,    0,    6,   48,   48,
    0,   28,   48,   46,    7,   52,   52,   52,   52,   52,
   52,    0,   45,   20,    0,    0,    0,   48,   48,    0,
   48,    0,    0,    0,    6,    0,   47,    0,    0,    0,
    0,   19,    0,    0,   52,   46,    0,    0,    0,    0,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   52,   48,    0,    0,    0,    0,    0,   36,   47,    0,
    0,    0,    0,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,    0,    0,    0,    0,    0,    0,
   37,    0,    0,   48,    0,    0,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,    6,    0,    0,
    0,    0,    0,   42,   19,    0,    0,    0,    0,   42,
   42,   42,   42,   42,   42,   42,   42,   42,   42,   42,
    4,    4,    4,    4,    4,    6,    0,    0,   44,    0,
    0,    0,   19,    0,   44,   44,   44,   44,   44,   44,
   44,   44,   44,   44,   44,    0,    0,    0,    0,    0,
    0,   45,    0,    0,    0,    0,    0,   45,   45,   45,
   45,   45,   45,   45,   45,   45,   45,   45,    0,    0,
    0,    0,    0,    0,   46,    0,    0,    0,    0,    0,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
   46,   43,    2,    3,    4,    5,    0,   47,    0,    0,
    0,    0,    0,   47,   47,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   49,   39,   37,    0,   38,    0,
   40,    0,   48,    0,    0,    0,    0,    0,   48,   48,
   48,   48,   48,   48,   48,   48,   48,   48,   48,   52,
    1,    2,    3,    4,    5,    0,    0,   49,   21,   22,
   23,   24,   25,    0,   49,   49,   40,    0,   49,    0,
    0,    0,   41,    0,    0,    0,    0,   18,    2,    3,
    4,    5,   52,   49,   49,    0,   49,    0,   79,    0,
    0,   52,   52,    0,   52,    0,   52,    0,    0,   40,
    0,    0,    0,    0,    0,   41,   40,   40,    0,   52,
   40,   52,   41,   41,    0,    0,   41,   49,    0,    0,
    0,    0,    0,    0,    0,   40,   40,    0,   40,    0,
    0,   41,   41,    0,   41,    0,   47,   39,   37,    0,
   38,    0,   40,   39,   37,  107,   38,    0,   40,   49,
   18,    2,    3,    4,    5,   35,    0,   36,    0,   40,
    0,   35,    0,   36,    0,   41,  111,   39,   37,    0,
   38,    0,   40,    0,    0,    0,    0,    0,   43,    2,
    3,    4,    5,    0,    0,   35,    0,   36,  112,   39,
   37,   40,   38,    0,   40,   39,   37,   41,   38,    0,
   40,   39,   37,    0,   38,    0,   40,   35,    0,   36,
    0,   39,   37,   35,   38,   36,   40,    0,    0,   35,
    0,   36,    0,    0,    0,    0,    0,   84,    0,   35,
   85,   36,   86,   87,   88,    0,    0,    0,    0,    0,
    0,   89,    0,    0,    0,    0,   63,    0,    0,    0,
    0,    0,  114,   29,   30,   31,   32,   33,   34,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   49,    0,
    0,    0,    0,    0,   49,   49,   49,   49,   49,   49,
   49,   49,   49,   49,   49,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   52,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   40,    0,    0,    0,    0,    0,   41,    0,    0,    0,
    0,    0,   40,   40,   40,   40,   40,    0,   41,   41,
   41,   41,   41,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   29,   30,   31,   32,   33,
   34,   29,   30,   31,   32,   33,   34,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   29,   30,   31,   32,   33,
   34,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   29,   30,   31,
   32,   33,   34,   29,   30,   31,   32,   33,   34,   29,
   30,   31,   32,   33,   34,    0,    0,    0,    0,   29,
   30,   31,   32,   33,   34,   13,    0,    0,    0,    0,
    0,   20,   26,    0,    0,   13,    0,    0,    0,    0,
    0,   42,    0,    0,   26,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   49,   50,   51,   52,   53,   54,
   55,   56,   57,   58,   59,   60,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   97,   98,    0,    0,    0,    0,    0,  104,
  105,    0,    0,    0,    0,  108,  109,    0,    0,    0,
    0,    0,   98,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  119,
};
static const YYINT yycheck[] = {                         59,
    0,   40,   40,   40,   59,   59,   41,   42,   43,   44,
   45,   59,   47,   41,  112,   59,   61,  115,   61,   58,
   58,   61,  120,    0,   15,   60,   59,   62,   75,   74,
   66,   41,   77,   33,   81,   42,   72,  276,   59,   44,
   47,   41,   42,   43,   44,   45,    0,   47,   91,  277,
   40,   91,   91,   91,   91,   41,   33,   59,   44,   59,
   60,   93,   62,   40,   41,  125,   43,   44,   45,    0,
  125,  125,  123,   64,    0,   42,   43,  125,   45,   33,
   47,  125,   59,   60,   41,   62,   40,   41,   59,   43,
   44,   45,  125,   93,    0,  257,  258,  259,  260,  261,
   40,   40,   33,   62,  125,   59,   60,   33,   62,   40,
   41,   59,  125,   44,   40,  276,   93,    0,  277,  278,
  279,  263,    0,   61,  264,  125,   41,   33,   59,   60,
   59,   62,  125,   10,   40,   41,   77,  107,   44,   93,
    0,  102,   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,
   33,   -1,   -1,   59,   60,   -1,   62,   40,   41,   -1,
   -1,   44,   93,    0,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  125,   -1,   33,   -1,   -1,   59,   60,   33,   62,
   40,   41,   -1,   -1,   44,   40,   41,   93,    0,   -1,
   -1,   -1,   -1,   -1,  125,   -1,   33,   -1,   -1,   59,
   60,   -1,   62,   40,   41,   -1,   -1,   44,   -1,  264,
   93,   -1,   -1,   -1,   -1,   -1,  264,   -1,   -1,  125,
  264,   33,   59,   60,   -1,   62,   -1,   33,   40,   41,
   -1,  264,   44,   93,   40,  270,  271,  272,  273,  274,
  275,   -1,  125,  264,   -1,   -1,   -1,   59,   60,   -1,
   62,   -1,   -1,   -1,   33,   -1,   93,   -1,   -1,   -1,
   -1,   40,   -1,   -1,  264,  125,   -1,   -1,   -1,   -1,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,   93,   -1,   -1,   -1,   -1,   -1,  264,  125,   -1,
   -1,   -1,   -1,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,
  264,   -1,   -1,  125,   -1,   -1,  270,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,   33,   -1,   -1,
   -1,   -1,   -1,  264,   40,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  276,  277,  278,  279,  280,   33,   -1,   -1,  264,   -1,
   -1,   -1,   40,   -1,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,
   -1,  264,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,   -1,   -1,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  276,  277,  278,  279,  280,   -1,  264,   -1,   -1,
   -1,   -1,   -1,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,    0,   42,   43,   -1,   45,   -1,
   47,   -1,  264,   -1,   -1,   -1,   -1,   -1,  270,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,    0,
  276,  277,  278,  279,  280,   -1,   -1,   33,  257,  258,
  259,  260,  261,   -1,   40,   41,    0,   -1,   44,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,  276,  277,  278,
  279,  280,   33,   59,   60,   -1,   62,   -1,  123,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   33,
   -1,   -1,   -1,   -1,   -1,   33,   40,   41,   -1,   60,
   44,   62,   40,   41,   -1,   -1,   44,   93,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   60,   -1,   62,   -1,
   -1,   59,   60,   -1,   62,   -1,   41,   42,   43,   -1,
   45,   -1,   47,   42,   43,   44,   45,   -1,   47,  125,
  276,  277,  278,  279,  280,   60,   -1,   62,   -1,   93,
   -1,   60,   -1,   62,   -1,   93,   41,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,  276,  277,
  278,  279,  280,   -1,   -1,   60,   -1,   62,   41,   42,
   43,  125,   45,   -1,   47,   42,   43,  125,   45,   -1,
   47,   42,   43,   -1,   45,   -1,   47,   60,   -1,   62,
   -1,   42,   43,   60,   45,   62,   47,   -1,   -1,   60,
   -1,   62,   -1,   -1,   -1,   -1,   -1,  262,   -1,   60,
  265,   62,  267,  268,  269,   -1,   -1,   -1,   -1,   -1,
   -1,  276,   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,
   -1,   -1,   93,  270,  271,  272,  273,  274,  275,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  264,   -1,
   -1,   -1,   -1,   -1,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  264,   -1,   -1,   -1,   -1,   -1,  264,   -1,   -1,   -1,
   -1,   -1,  276,  277,  278,  279,  280,   -1,  276,  277,
  278,  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,  274,
  275,  270,  271,  272,  273,  274,  275,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,  274,
  275,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,
  273,  274,  275,  270,  271,  272,  273,  274,  275,  270,
  271,  272,  273,  274,  275,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,  274,  275,    0,   -1,   -1,   -1,   -1,
   -1,    6,    7,   -1,   -1,   10,   -1,   -1,   -1,   -1,
   -1,   16,   -1,   -1,   19,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   29,   30,   31,   32,   33,   34,
   35,   36,   37,   38,   39,   40,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   87,   88,   -1,   -1,   -1,   -1,   -1,   94,
   95,   -1,   -1,   -1,   -1,  100,  101,   -1,   -1,   -1,
   -1,   -1,  107,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  117,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#define YYUNDFTOKEN 298
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_BYTE","KW_SHORT","KW_LONG","KW_FLOAT",
"KW_DOUBLE","KW_IF","KW_THEN","KW_ELSE","KW_WHILE","KW_FOR","KW_READ",
"KW_RETURN","KW_PRINT","OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE",
"OPERATOR_AND","OPERATOR_OR","TK_IDENTIFIER","LIT_INTEGER","LIT_REAL",
"LIT_CHAR","LIT_STRING","TOKEN_ERROR",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : listdecl",
"listdecl : decl listdecl",
"listdecl :",
"decl : expr",
"decl : fundec",
"decl : vardec",
"vardec : TK_IDENTIFIER ':' type '=' value ';'",
"vardec : TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' init ';'",
"value : LIT_INTEGER",
"value : LIT_REAL",
"value : LIT_CHAR",
"init : value init",
"init :",
"fundec : '(' type ')' TK_IDENTIFIER '(' listArgs ')' block",
"fundec : '(' type ')' TK_IDENTIFIER '(' ')' block",
"block : '{' listCmd '}'",
"listCmd : cmd ';' listCmd",
"listCmd : cmd",
"cmd : TK_IDENTIFIER '=' expr",
"cmd : TK_IDENTIFIER '[' expr ']' '=' expr",
"cmd : KW_READ '>' TK_IDENTIFIER",
"cmd : KW_PRINT listPrint",
"cmd : KW_RETURN expr",
"cmd : KW_IF '(' expr ')' KW_THEN cmd",
"cmd : KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd",
"cmd : KW_WHILE '(' expr ')' cmd",
"cmd : block",
"cmd :",
"listPrint : expr ',' listPrint",
"listPrint : expr",
"type : KW_BYTE",
"type : KW_SHORT",
"type : KW_LONG",
"type : KW_FLOAT",
"type : KW_DOUBLE",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : '!' expr",
"expr : '(' expr ')'",
"expr : expr OPERATOR_LE expr",
"expr : expr OPERATOR_GE expr",
"expr : expr OPERATOR_EQ expr",
"expr : expr OPERATOR_NE expr",
"expr : expr OPERATOR_AND expr",
"expr : expr OPERATOR_OR expr",
"expr : TK_IDENTIFIER '(' listArgs ')'",
"expr : TK_IDENTIFIER '[' expr ']'",
"expr : TK_IDENTIFIER",
"expr : value",
"expr : LIT_STRING",
"listArgs : arg ',' listArgs",
"listArgs : arg",
"arg : TK_IDENTIFIER ':' type",
"arg : expr",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 188 "parser.y"

AST* getAst(){
	return root;
}

int yyerror(char *s) {
 fprintf(stderr, "Problema! ERRO linha = %d\n", getLineNumber());
 exit(3);
}
#line 511 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 87 "parser.y"
	{root = yystack.l_mark[0].ast;
                        /*astPrint(root,0);*/
                        /*  checkSemantics(root);*/
						tacStart = tacGenerator(root);
                        tacPrintFoward(tacReverse(tacStart));
                        asmAddTemp();
                        asmAddImm();    
                        asmAddData(yyval.ast);

                        generateAssembly(tacReverse(tacStart));
                        /* tacPrintSingle(tacReverse(tacGenerator(root)));*/
						}
break;
case 2:
#line 101 "parser.y"
	{yyval.ast = astCreate(AST_START, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0);}
break;
case 3:
#line 102 "parser.y"
	{ yyval.ast = 0; }
break;
case 4:
#line 105 "parser.y"
	{yyval.ast = astCreate(AST_EXPRESSION, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 5:
#line 106 "parser.y"
	{yyval.ast = astCreate(AST_FUNCTION, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 6:
#line 107 "parser.y"
	{yyval.ast = astCreate(AST_VARIABLE, 0, yystack.l_mark[0].ast, 0, 0, 0);}
break;
case 7:
#line 110 "parser.y"
	{yyval.ast = astCreate(AST_VARDEC,yystack.l_mark[-5].symbol,yystack.l_mark[-3].ast,yystack.l_mark[-1].ast,0,0);}
break;
case 8:
#line 111 "parser.y"
	{temp = astCreate(AST_INTEGER,yystack.l_mark[-3].symbol,0,0,0,0);yyval.ast = astCreate(AST_INIT_ARRAY,yystack.l_mark[-7].symbol,yystack.l_mark[-5].ast,temp,yystack.l_mark[-1].ast,0);}
break;
case 9:
#line 114 "parser.y"
	{yyval.ast = astCreate(AST_INTEGER,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 10:
#line 115 "parser.y"
	{yyval.ast = astCreate(AST_REAL,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 11:
#line 116 "parser.y"
	{yyval.ast = astCreate(AST_CHAR,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 12:
#line 119 "parser.y"
	{yyval.ast = astCreate(AST_ARRAY_INIT_VALUES,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0);}
break;
case 13:
#line 120 "parser.y"
	{yyval.ast = 0;}
break;
case 14:
#line 123 "parser.y"
	{yyval.ast = astCreate(AST_FUNDEC,yystack.l_mark[-4].symbol,yystack.l_mark[-6].ast,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0);}
break;
case 15:
#line 124 "parser.y"
	{yyval.ast = astCreate(AST_FUNDEC,yystack.l_mark[-3].symbol,yystack.l_mark[-5].ast,yystack.l_mark[0].ast,0,0);}
break;
case 16:
#line 127 "parser.y"
	{yyval.ast = astCreate(AST_BLOCK,0,yystack.l_mark[-1].ast,0,0,0);}
break;
case 17:
#line 130 "parser.y"
	{yyval.ast = astCreate(AST_LIST_CMD,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 18:
#line 131 "parser.y"
	{yyval.ast = astCreate(AST_CMD,0,yystack.l_mark[0].ast,0,0,0);}
break;
case 19:
#line 134 "parser.y"
	{yyval.ast = astCreate(AST_ATRIB,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 20:
#line 135 "parser.y"
	{yyval.ast = astCreate(AST_ATRIB_ARRAY,yystack.l_mark[-5].symbol,yystack.l_mark[-3].ast,yystack.l_mark[0].ast,0,0);}
break;
case 21:
#line 136 "parser.y"
	{yyval.ast = astCreate(AST_READ,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 22:
#line 137 "parser.y"
	{yyval.ast = astCreate(AST_PRINT,0,yystack.l_mark[0].ast,0,0,0);}
break;
case 23:
#line 138 "parser.y"
	{yyval.ast = astCreate(AST_RETURN,0,yystack.l_mark[0].ast,0,0,0);}
break;
case 24:
#line 139 "parser.y"
	{yyval.ast = astCreate(AST_IF,0,yystack.l_mark[-3].ast,yystack.l_mark[0].ast,0,0);}
break;
case 25:
#line 140 "parser.y"
	{yyval.ast = astCreate(AST_IF_ELSE,0,yystack.l_mark[-5].ast,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0);}
break;
case 26:
#line 141 "parser.y"
	{yyval.ast = astCreate(AST_WHILE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 27:
#line 142 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 28:
#line 143 "parser.y"
	{yyval.ast = 0;}
break;
case 29:
#line 146 "parser.y"
	{yyval.ast = astCreate(AST_LIST_PARAM,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 30:
#line 147 "parser.y"
	{yyval.ast = astCreate(AST_PARAM,0,yystack.l_mark[0].ast,0,0,0);}
break;
case 31:
#line 150 "parser.y"
	{yyval.ast = astCreate(AST_BYTE,0,0,0,0,0);}
break;
case 32:
#line 151 "parser.y"
	{yyval.ast = astCreate(AST_SHORT,0,0,0,0,0);}
break;
case 33:
#line 152 "parser.y"
	{yyval.ast = astCreate(AST_LONG,0,0,0,0,0);}
break;
case 34:
#line 153 "parser.y"
	{yyval.ast = astCreate(AST_FLOAT,0,0,0,0,0);}
break;
case 35:
#line 154 "parser.y"
	{yyval.ast = astCreate(AST_DOUBLE,0,0,0,0,0);}
break;
case 36:
#line 158 "parser.y"
	{yyval.ast = astCreate(AST_ADD,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 37:
#line 159 "parser.y"
	{yyval.ast = astCreate(AST_SUB,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 38:
#line 160 "parser.y"
	{yyval.ast = astCreate(AST_MUL,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 39:
#line 161 "parser.y"
	{yyval.ast = astCreate(AST_DIV,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 40:
#line 162 "parser.y"
	{yyval.ast = astCreate(AST_LESS,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 41:
#line 163 "parser.y"
	{yyval.ast = astCreate(AST_MORE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 42:
#line 164 "parser.y"
	{yyval.ast = astCreate(AST_NOT,0,yystack.l_mark[0].ast,0,0,0);}
break;
case 43:
#line 165 "parser.y"
	{yyval.ast = astCreate(AST_PARENTHESES,0,yystack.l_mark[-1].ast,0,0,0);}
break;
case 44:
#line 166 "parser.y"
	{yyval.ast = astCreate(AST_LE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 45:
#line 167 "parser.y"
	{yyval.ast = astCreate(AST_GE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 46:
#line 168 "parser.y"
	{yyval.ast = astCreate(AST_EQ,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 47:
#line 169 "parser.y"
	{yyval.ast = astCreate(AST_NE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 48:
#line 170 "parser.y"
	{yyval.ast = astCreate(AST_AND,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 49:
#line 171 "parser.y"
	{yyval.ast = astCreate(AST_OR,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 50:
#line 172 "parser.y"
	{yyval.ast = astCreate(AST_FUNC,yystack.l_mark[-3].symbol,yystack.l_mark[-1].ast,0,0,0);}
break;
case 51:
#line 173 "parser.y"
	{yyval.ast = astCreate(AST_ARRAY,yystack.l_mark[-3].symbol,yystack.l_mark[-1].ast,0,0,0);}
break;
case 52:
#line 174 "parser.y"
	{yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 53:
#line 175 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
case 54:
#line 176 "parser.y"
	{yyval.ast = astCreate(AST_STRING,yystack.l_mark[0].symbol,0,0,0,0);}
break;
case 55:
#line 179 "parser.y"
	{yyval.ast = astCreate(AST_LIST_ARG,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0);}
break;
case 56:
#line 180 "parser.y"
	{yyval.ast =  yystack.l_mark[0].ast;}
break;
case 57:
#line 183 "parser.y"
	{yyval.ast = astCreate(AST_ARG_ID,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0);}
break;
case 58:
#line 184 "parser.y"
	{yyval.ast = yystack.l_mark[0].ast;}
break;
#line 956 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
