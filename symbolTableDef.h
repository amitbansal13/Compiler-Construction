/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct id* ID;

struct id
{
	char* name;//name of var
	int offset;
	int type; //num=0 or real_num=1
	int width;
	ID next;
	char *tname;	//type name
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



