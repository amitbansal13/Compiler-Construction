/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#ifndef PARSER_H
#define PARSER_H
#define terminalsSize 55 //Number of Terminals including epsilon
#define nonTerminalsSize 47//actual no of terminals in our code

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
	int rule_no;
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

//**************PARSETREE**************

typedef struct treenode *TreeNode;
typedef struct parsetree *ParseTree;

struct treenode{
    int tNt;    //terminal->0,nonT->1,TK_ERROR=>-1
    TreeNode children;
    TreeNode next;
    int index;      //terminal or non_terminals index
    TokenInfo token_info;   //will need linenos and other details while printing
    TreeNode parent;
    TreeNode addr,syn,inh;
	int rule_no;
    // TokenInfo *token; //TokenInfo structure pointer if terminal
};

struct parsetree{
    TreeNode root;
};



#endif
