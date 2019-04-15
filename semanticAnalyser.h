/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "lexerDef.h"
#include "parserDef.h"
#include "symbolTable.h"
#include "symbolTableDef.h"
typedef struct sequence* Seq;
struct sequence
{
	char* id_name;
	char* fieldid;
	Seq next; 
};

int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT);
int funcStmtsCheck(TreeNode funcNode,idTable globalT,funcTable funcT);
int funcStmtCheck(TreeNode funcNode,TreeNode stmtNode,funcTable funcT,Func funEntry,int *alloc,TreeNode output_par);
bool checkFuncDeclared(TreeNode funcNode,TreeNode stmtNode,funcTable funcT);
int whileSemanticCheck(TreeNode node);
int checkVarChanges(Seq begin,TreeNode stmtNode);
Seq getWhileVars(TreeNode root);
bool checkIOParams(TreeNode funcCalled,TreeNode stmtNode,Func ftcalled,int *alloc);

#endif
