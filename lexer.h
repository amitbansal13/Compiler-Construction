/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

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
