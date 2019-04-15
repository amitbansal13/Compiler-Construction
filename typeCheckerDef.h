
#ifndef TYPECHECKINGDEF_H
#define TYPECHECKINGDEF_H


#include "symbolTableDef.h"
#include "HashTable.h"

int typeExtractHelper(TreeNode node, idTable local, recTable rec, idTable global);
int typeExtractor(TreeNode program,funcTable func, recTable rec, idTable identifier);
int checkType(TreeNode head, recTable table1)

#endif
