#ifndef PARSER_H
#define PARSER_H

#define terminalsSize 55 //Number of Terminals including epsilon
#define nonTerminalsSize 51//actual no of terminals in our code

#include "lexer.h"
#include<stdbool.h>
extern char *tokens[];
extern char *nonterminals[];
extern Table terminals;
extern Table nonTerminals;


//***********grammar *******************




typedef struct grammar{//contains one rule of grammar
	char name[30];
	struct grammar* next;
	struct grammar* more;// if there are more rules consisting of the same non terminal
}grammar;

typedef struct {//contatins array of linked list
	int size;
	struct grammar** arr;
}Grammar;




//***************firstfollow ********************





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



extern ffset fset;
//************parsetable**************






typedef struct elem{
	int type;		//stores the type of parsetable entry,-1->error,0->rule exists,1->syn,2->accept
	grammar* rule;		//stores the specific pointer of the rule to be used
						// as there can be rule spanning in multiple rows i.e rules having same LHS
}elem;				//an element of parse table
					//if syn is to be used then we can use 
						//check slide 48 topdown parsing for more
typedef struct parseTable{
	elem* tEntry[nonTerminalsSize][terminalsSize];
	//table contains element pointers 
}PT;



//***********functions***************




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
bool checkSet(FF set,char *elem);
FF addSets(FF set1,FF set2,int *no_added);
int computeFollow(Grammar *g);
void printFirstnFollow();
void initializePT();
void createParseTable(Grammar *g);
void printParseTable();
//ffset computeFirstFollow(Grammar* g,Table nt);//returns array of first and follow for all non terminals





#endif
