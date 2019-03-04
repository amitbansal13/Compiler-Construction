# all:	main.o	lexer.o	HashTable.o FileIO.o
# 	gcc main.o lexer.o HashTable.o FileIO.o -o compiler

all: driver.o lexer.o HashTable.o parser.o	stack.o	
	gcc driver.o lexer.o HashTable.o parser.o  stack.o -o compiler

parser.o: parser.c parser.h
	gcc -g -c parser.c

driver.o:	driver.c	lexer.h
	gcc -g -c driver.c

lexer.o:	lexer.c lexer.h
	gcc -g -c lexer.c

HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c

stack.o:	stack.c	stack.h
	gcc -g -c stack.c

clean:
	rm -rf *.o
