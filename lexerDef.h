#ifndef LEXERDEF_H
#define LEXERDEF_H
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

#endif
