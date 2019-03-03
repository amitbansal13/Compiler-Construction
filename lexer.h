#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>
#include<stdlib.h>
#include "HashTable.h"

#define MAX_TOKEN 20
#define MAX_LEXEME 100

typedef struct tokenInfo* TokenInfo;
typedef union{
	int intVal;
	float floatVal;
}tokenVal;
// tokenVal.floatVal=stringToFloat(lexeme);
struct tokenInfo{
	int lineNo;
	char lexeme[MAX_LEXEME];
	char Token[MAX_TOKEN];
	tokenVal tkVal;
};

void initialize(FILE *fp);
char getNextChar();
float stringToFloat(char *str);
int stringToInteger(char *str);
TokenInfo nextToken();
void removeComments();
void printAllTokens();

#endif
