#include<stdio.h>
#include<stdlib.h>

typedef struct tokenInfo* TokenInfo;

struct tokenInfo{
int lineNo;
char* lexeme;
char* Token;
};

