#include<stdio.h>
#include<stdlib.h>
#include "HashTable.h"
typedef struct tokenInfo* TokenInfo;
typedef union{
	int intVal;
	float floatVal;
}tokenVal;

struct tokenInfo{
int lineNo;
char* lexeme;
char* Token;
tokenVal tkVal;
};

void initialize(FILE *fp);
char getNextChar();
float stringToFloat(char *str);
int stringToInteger(char *str);
TokenInfo nextToken();
void removeComments(char *testcaseFile, char *cleanFile);
void printAllTokens();
