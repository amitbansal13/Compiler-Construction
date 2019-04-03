#include "symbolTableDef.h"


/////////////////// IDENTIFIER TABLE

int calculateHash(char arr[],int a,int tableSize){
	long int key=0,i=0,prod=1;
	while(arr[i])
	{
		key=arr[i]+key*prod;
		prod*=a;
		prod%=tableSize;
		key%=tableSize;
		i++;
	}
	return key%tableSize;
}

idTable createID(int tableSize){
	idTable t=(idTable)malloc(sizeof(struct idtable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(ID*)malloc(tableSize*sizeof(ID));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL
	}
	return t;
}
ID newID( char* name, int offset, int type, int width, char *tname){
	ID id=(ID)malloc(sizeof(struct id));
	id->name=strdup(name);
	id->offset=offset;
	id->type=type;
	id->width=width;
	id->tname=strdup(tname);
	id->next=NULL;
	return id;
}
idTable insertID(idTable t,char* name, int offset, int type, int width, char *tname){
	int i=calculateHash(arr,t->a,t->tableSize);
	ID temp=newID(name,offset,type,width,tname);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

ID lookupID(idTable t,char arr[]){
	ID res=NULL;
	int i=calculateHash(arr,t->a,t->tableSize);
	ID temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}


//////////////////FUNCTION TABLE

funcTable createFunc(int tableSize){
	funcTable t=(funcTable)malloc(sizeof(struct functable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(funcTable*)malloc(tableSize*sizeof(funcTable));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL
	}
	return t;
}
Func newFunc( char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width,int childNo){
	Func f=(Func)malloc(sizeof(struct func));
	f->name=strdup(name);
	f->offset=offset;
	f->noOutput=noOutput;
	f->noInput=noInput;
	f->width=width;
	f->inputType=inputType;
	f->outputType=outputType;
	f->childNo=childNo;//NO IDEA ABOUT THIS
	f->localtable=localtable;
	f->next=NULL;
	return f;
}
funcTable insertFunc(funcTable t,char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width,int childNo){
	int i=calculateHash(arr,t->a,t->tableSize);
	Func temp=newFunc(name,offset,noInput, noOutput, inputType, outputType,localtable,width,childNo);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

Func lookupFunc(funcTable t,char arr[]){
	Func res=NULL;
	int i=calculateHash(arr,t->a,t->tableSize);
	Func temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}


/////////////// Record Table

recTable createRec(int tableSize){
	recTable t=(recTable)malloc(sizeof(struct rectable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(funcTable*)malloc(tableSize*sizeof(recTable));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL
	}
	return t;
}
Rec newRec(char* name, int type, int width, int noField, int* fieldtype, char** fieldid){
	Rec r=(Rec)malloc(sizeof(struct rec));
	r->name=strdup(name);
	r->type=type;
	r->width=width;
	r->noField=noField;
	r->fieldtype=fieldtype;
	r->fieldid=fieldid;
	r->next=NULL;
	return r;
}
recTable insertRec(recTable t,char* name, int type, int width, int noField, int* fieldtype, char** fieldid){
	int i=calculateHash(arr,t->a,t->tableSize);
	Rec temp=newRec(name,  type,width, noField, fieldtype, fieldid);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

Rec lookupRec(recTable t,char arr[]){
	Rec res=NULL;
	int i=calculateHash(arr,t->a,t->tableSize);
	Recc temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}