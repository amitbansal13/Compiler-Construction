#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct id* ID;

struct id
{
	char* name;
	int offset;
	int type; //num=0 or real_num=1
	int width;
	ID next;
	char *tname;
};


typedef struct idtable* idTable;

struct idtable {
	int tableSize;
	int a;
	ID* table;
};

typedef struct func* Func;

struct func
{
	char* name;
	int offset;
	int noInput;//number of input pars
	int noOutput;//number of output pars
	int width;// no idea...
	int *inputType, *outputType;//num=0,rnum=1 types of par
	idTable localTable;
	Func next;
};


typedef struct functable* funcTable;

struct functable
{
	int tableSize;
	int a;
	Func* table;
};



typedef struct rec* Rec;

struct rec
{
	char* name;
	int typeIndex;
	int width;
	int noField;
	int* fieldtype;
	char** fieldid;
	Rec next;
};

typedef struct rectable* recTable;

struct rectable
{
	int tableSize;
	int a;
	Rec* table;
};



#endif



