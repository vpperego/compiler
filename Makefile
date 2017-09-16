
# etapa1: lex.yy.o main.o
# 	gcc -o etapa1 lex.yy.o main.o
# main.o: main.c
# 	gcc -c main.c
all: etapa1
	
etapa1: lex.yy.o
	gcc -o etapa1 lex.yy.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
clean:
	rm -f *.o lex.yy.c etapa1
