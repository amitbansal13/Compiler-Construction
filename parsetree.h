#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

typedef struct treenode *TreeNode;
typedef struct parsetree *ParseTree;

struct treenode{
	int tNt;	//terminal->0
	TreeNode children;
	TreeNode next;
	int index;		//terminal or non_terminals index
	//TokenInfo *token;	//TokenInfo structure pointer if terminal
};

struct parsetree{
	TreeNode root;
};


TreeNode addChildren(TreeNode node,grammar *rule);
TreeNode createtreeNode(int tNt,int index);
ParseTree initializeParseTree(void);
void parseInputSourceCode(char *testFile);
