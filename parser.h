#ifndef PARSER_H
#define PARSER_H


#include "lexer.h"
extern char* tokens[];

typedef struct grammar{//contains one rule of grammar
	char name[30];
	struct grammar* next;
	struct grammar* more;// if there are more rules consisting of the same non terminal
}grammar;

typedef struct {//contatins array of linked list
	int size;
	struct grammar** arr;
}Grammar;

typedef struct firstfollow* FF;
struct firstfollow{//stores info about either first or follow
	char elem[MAX_TOKEN];
	FF next;
};

struct ff{//first and follow sets for one non terminal
	FF first;
	FF follow;
};
typedef struct ff* ffset;


void initializeTNT();//to initialize terminal and non terminals hash table
grammar* newNode(char *temp);
grammar* makeNewRule(FILE* fp,int d);
Grammar* readFile(char* fileName);

ffset computeFirstFollow(Grammar* g);//, Table nTerm, Table term);//,Table nt);//returns array of first and follow for all non terminals





#endif