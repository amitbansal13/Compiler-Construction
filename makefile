# all:	main.o	lexer.o	HashTable.o FileIO.o
# 	gcc main.o lexer.o HashTable.o FileIO.o -o compiler

all: driver.o lexer.o HashTable.o parser.o firstFollow.o parseTable.o
	gcc driver.o lexer.o HashTable.o parser.o firstFollow.o parseTable.o -o compiler

parser.o: parser.c parser.h
	gcc -g -c parser.c

test.o: test.c parser.h
	gcc -g -c test.c

firstFollow.o: firstFollow.c parser.h
	gcc -g -c firstFollow.c

parseTable.o: parseTable.c parser.h 
	gcc -g -c parseTable.c

driver.o:	driver.c	lexer.h
	gcc -g -c driver.c

lexer.o:	lexer.c lexer.h
	gcc -g -c lexer.c

HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c

clean:
	rm -rf *.o
