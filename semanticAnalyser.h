#include "lexerDef.h"
#include "parserDef.h"
#include "symbolTable.h"
int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT);
int funcStmtsCheck(TreeNode funcNode,idTable globalT,funcTable funcT);
int funcStmtCheck(TreeNode stmtNode,funcTable funcT,Func funEntry,int *alloc,TreeNode output_par);


