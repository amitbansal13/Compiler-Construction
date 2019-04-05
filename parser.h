/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

//#ifndef PARSER_H
//#define PARSER_H
#include "parserDef.h"
#include<stdbool.h>


void initializeTNT();//to initialize terminal and non terminals hash table
grammar* newNode(char *temp,int line_no);
grammar* makeNewRule(FILE* fp,int d,int line_no);
Grammar* makeGrammar(char* fileName);
void printGrammar(Grammar *g);
bool isTerminal(char *text);
bool isNTerminal(char *text);
ffset initializeFF();
//void addFirst(int index,char *text);
void findFirst(int index_orig,int index,Grammar *g,ffset fset);
ffset computeFirstnFollow(Grammar *g);
void printFirst();
bool checkEps(int index,Grammar *g);
FF addToSet(FF set,char *text);
bool checkSet(FF set,char *elem);
FF addSets(FF set1,FF set2,int *no_added);
int computeFollow(Grammar *g,ffset fset);
void printFirstnFollow(ffset fset);
PT* initializePT();
void createParseTable(Grammar *g,ffset fset,PT *pTable);
void printParseTable(PT *pTable);
TreeNode addChildren(TreeNode node,grammar *rule);
TreeNode createtreeNode(int tNt,int index,int rule_no);
ParseTree initializeParseTree(void);
ParseTree parseInputSourceCode(char *testFile,PT *pTable,bool *parseError);
int printInOrder(TreeNode node,char *outfile);
int printParseTree(ParseTree ptree,char *outfile);
void printNode(TreeNode node,char *outfile);



//#endif
