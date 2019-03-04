#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>
#include<stdlib.h>
#include "HashTable.h"
#include "lexerDef.h"

void initialize(FILE *fp);
char getNextChar();
float stringToFloat(char *str);
int stringToInteger(char *str);
TokenInfo nextToken();
void removeComments();
void printAllTokens();

#endif
