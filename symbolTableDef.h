#include "symbolTable.h"


/////////////////// IDENTIFIER TABLE


int calculateHash(char arr[],int a,int tableSize);
idTable createID(int tableSize);
ID newID( char* name, int offset, int type, int width, char *tname);
idTable insertID(idTable t,char* name, int offset, int type, int width, char *tname);
ID lookupID(idTable t,char arr[]);


//////////////////FUNCTION TABLE


funcTable createFunc(int tableSize);
Func newFunc( char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width,int childNo);
funcTable insertFunc(funcTable t,char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width,int childNo);
Func lookupFunc(funcTable t,char arr[]);


///////////////// Record Table


recTable createRec(int tableSize);
Rec newRec(char* name, int type, int width, int noField, int* fieldtype, char** fieldid);
recTable insertRec(recTable t,char* name, int type, int width, int noField, int* fieldtype, char** fieldid);
Rec lookupRec(recTable t,char arr[]);