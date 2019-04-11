#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "lexerDef.h"
#include "parserDef.h"
#include "symbolTable.h"
#include "symbolTableDef.h"
typedef struct sequence* Seq;
struct sequence
{
	ID tableEntry;
	char* fieldid;
	Seq next; 
};

int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT);
int funcStmtsCheck(TreeNode funcNode,idTable globalT,funcTable funcT);
int funcStmtCheck(TreeNode funcNode,TreeNode stmtNode,funcTable funcT,Func funEntry,int *alloc,TreeNode output_par);
bool checkFuncDeclared(TreeNode funcNode,TreeNode stmtNode,funcTable funcT);
int whileSemanticCheck(TreeNode node);
int checkSequence(Seq begin,TreeNode root);
Seq getSequence(TreeNode root);

#endif