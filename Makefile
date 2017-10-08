 # Filipe Joner
 # Vinícius Pittigliani Perego

all: etapa2

etapa2: y.tab.o lex.yy.o main.o hash.o
	gcc -o etapa2 lex.yy.o y.tab.o hash.o main.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: y.tab.h scanner.l
	flex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.h
	gcc -c y.tab.c
y.tab.h: parser.y
	yacc -d parser.y
clean:
	rm -f *.o lex.yy.* y.tab.* etapa2
