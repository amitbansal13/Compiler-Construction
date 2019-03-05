/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

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
