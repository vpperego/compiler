 # Filipe Joner
 # Vinícius Pittigliani Perego

all: etapa2

etapa2: lex.yy.o main.o hash.o
	gcc -o etapa1 lex.yy.o hash.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: y.tab.h scanner.l
	flex --header-file=lex.yy.h scanner.l
y.tab.h: grammar.y
	yacc -d grammar.y
clean:
	rm -f *.o lex.yy.* y.tab.* etapa1
