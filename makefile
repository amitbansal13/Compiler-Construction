all:	main.o	lexer.o	HashTable.o
	gcc main.o lexer.o HashTable.o -o compiler

main.o:	main.c	HashTable.h
	gcc -g -c main.c

lexer.o:	lexer.c	HashTable.h
	gcc -g -c lexer.c

HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c

clean:
	rm -rf *.o
