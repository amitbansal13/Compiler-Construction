# all:	main.o	lexer.o	HashTable.o FileIO.o
# 	gcc main.o lexer.o HashTable.o FileIO.o -o compiler

all: driver.o lexer.o HashTable.o
	gcc driver.o lexer.o HashTable.o -o compiler


driver.o:	driver.c	lexer.h
	gcc -g -c driver.c

lexer.o:	lexer.c lexer.h
	gcc -g -c lexer.c

# lexer2.o:	Lexer2_0.c	HashTable.h
# 	gcc -g -c Lexer2_0.c


HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c

FileIO.o:	FileIO.c	lexer.h
	gcc -g -c FileIO.c

clean:
	rm -rf *.o
