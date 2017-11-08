 # Filipe Joner
 # Vinícius Pittigliani Perego

all: etapa4

etapa4: y.tab.o lex.yy.o main.o hash.o astree.o semantic.o
	gcc -o etapa4 lex.yy.o y.tab.o hash.o main.o astree.o semantic.o
main.o: main.c
	gcc -c main.c
semantic.o: semantic.c
	gcc -c semantic.c
hash.o: hash.c
	gcc -c hash.c
astree.o: astree.c
	gcc -c astree.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: y.tab.h scanner.l
	flex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.h
	gcc -c y.tab.c
y.tab.h: parser.y
	yacc -d parser.y
clean:
	rm -f *.o lex.yy.* y.tab.* etapa4
