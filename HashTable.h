/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog ID Number - 2016A7PS0004P*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


extern char *keywords[];// = {"with","parameters","end","while","type","_main", "global" ,"parameter", "list", "input", "output", "int", "real", "endwhile", "if", "then", "endif", "read", "write", "return", "call", "record", "endrecord", "else"};
extern char *keywords_tokens[];//= {"TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_ENDWHILE", "TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE"};

typedef struct record* link;
typedef struct hash *Table;
struct record
{
    int index;
    link next;
};
struct hash
{
    int tableSize;
    int a;// A prime value used to be used for horners rule
    link *buckets;
};
Table insert(Table t,char *arr[],int j);
Table create(int size);
link lookup(Table t,char arr[],char *keywords[]);
int calculateHash(char arr[],int a,int size);
// int check(Table t,char arr[],char *keywords[]);//to check if arr is keyword

#endif
