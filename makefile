# all:	main.o	lexer.o	HashTable.o FileIO.o
# 	gcc main.o lexer.o HashTable.o FileIO.o -o compiler

all: driver.o lexer.o HashTable.o
	gcc driver.o lexer.o HashTable.o -o compiler

test: test.o parser.o HashTable.o
	gcc test.o parser.o HashTable.o -o test

parser.o: parser.c parser.h
	gcc -g -c parser.c

test.o: test.c parser.h
	gcc -g -c test.c

driver.o:	driver.c	lexer.h
	gcc -g -c driver.c

lexer.o:	lexer.c lexer.h
	gcc -g -c lexer.c


HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c


clean:
	rm -rf *.o
