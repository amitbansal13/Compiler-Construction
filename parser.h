#ifndef PARSER_H
#define PARSER_H

#define terminalsSize 54 //Number of Terminals including epsilon
#define nonTerminalsSize 51//actual no of terminals in our code

#include "lexer.h"
#include<stdbool.h>
extern char *tokens[];
extern char *nonterminals[];
extern Table terminals;
extern Table nonTerminals;

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
Grammar* makeGrammar(char* fileName);
void printGrammar(Grammar *g);
bool isTerminal(char *text);
bool isNTerminal(char *text);
void initializeFF();
//void addFirst(int index,char *text);
void findFirst(int index_orig,int index,Grammar *g);
void computeFirstnFollow(Grammar *g);
void printFirst();
bool checkEps(int index,Grammar *g);
FF addToSet(FF set,char *text);

//ffset computeFirstFollow(Grammar* g,Table nt);//returns array of first and follow for all non terminals





#endif
