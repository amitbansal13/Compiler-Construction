#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H


#include "symbolTable.h"
#include "parser.h"

/////////////////// IDENTIFIER TABLE


int hash(char arr[],int a,int tableSize);
idTable createID(int tableSize);
ID newID( char* name, int offset, int type, int width, char *tname);
idTable insertID(idTable t,char* name, int offset, int type, int width, char *tname);
ID lookupID(idTable t,char arr[]);
void printGlobalTable(idTable t,recTable r);

//////////////////FUNCTION TABLE


funcTable createFunc(int tableSize);
Func newFunc( char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width);
funcTable insertFunc(funcTable t,char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width);
Func lookupFunc(funcTable t,char arr[]);
void printFuncTable(funcTable t,recTable rec);

///////////////// Record Table


recTable createRec(int tableSize);
Rec newRec(char* name, int type, int width, int noField, int* fieldtype, char** fieldid);
recTable insertRec(recTable t,char* name, int type, int width, int noField, int* fieldtype, char** fieldid);
Rec lookupRec(recTable t,char arr[]);
void printRecTable(recTable t);


TreeNode getStmt(TreeNode temp, int lim);
int getType(TreeNode t,recTable table);
int getChildrenNo(TreeNode node);
int symbolTablePopulate(funcTable func, recTable rec, idTable identifier, ParseTree pTree);

int typeExtractHelper(TreeNode node, idTable local, recTable rec, idTable global);
int typeExtractor(TreeNode program,funcTable func, recTable rec, idTable identifier);

int checkType(TreeNode head,recTable r);
char* printType(recTable t,char *idname);//return a string containing the type of idname 

#endif
