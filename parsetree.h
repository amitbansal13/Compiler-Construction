#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

typedef struct treenode *TreeNode;
typedef struct parsetree *ParseTree;

struct treenode{
	int tNt;	//terminal->0,nonT->1,TK_ERROR=>-1
	TreeNode children;
	TreeNode next;
	int index;		//terminal or non_terminals index
	TokenInfo token_info;	//will need linenos and other details while printing
	TreeNode parent;
	//TokenInfo *token;	//TokenInfo structure pointer if terminal
};

struct parsetree{
	TreeNode root;
};


TreeNode addChildren(TreeNode node,grammar *rule);
TreeNode createtreeNode(int tNt,int index);
ParseTree initializeParseTree(void);
ParseTree parseInputSourceCode(char *testFile);
void printInOrder(TreeNode node,char *outfile);
void printParseTree(ParseTree ptree,char *outfile);
void printNode(TreeNode node,char *outfile);
