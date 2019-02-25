#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct record* link;
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
typedef struct hash *Table;
Table insert(Table t,char *arr[],int j);
Table create(int size);
// link lookup(Table t,char arr[]);
int calculateHash(char arr[],int a,int size);
int check(Table t,char arr[],char *keywords[]);//to check if arr is keyword

