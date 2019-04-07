#GROUP Number = 20
#Name-Amit Bansal ID Number- 2016A7PS0140P
#Name- Vedant Patwary ID Number-2016A7PS0031P
#Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
#Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

stage1exe: driver.o lexer.o HashTable.o parser.o	stack.o	ast.o symbolTable.o
	gcc driver.o lexer.o HashTable.o parser.o  stack.o ast.o symbolTable.o -o stage1exe

parser.o: parser.c parser.h
	gcc -g -c parser.c

symbolTable.o: symbolTable.c parser.h symbolTableDef.h symbolTable.h
	gcc -g -c symbolTable.c

driver.o:	driver.c	lexer.h
	gcc -g -c driver.c

lexer.o:	lexer.c lexer.h
	gcc -g -c lexer.c

HashTable.o:	HashTable.c	HashTable.h
	gcc -g -c HashTable.c

stack.o:	stack.c	stack.h
	gcc -g -c stack.c

ast.o:	ast.c
	gcc -g -c ast.c

clean:
	rm -f *.o 
