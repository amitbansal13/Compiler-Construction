#include "HashTable.h"

int calculateHash(char arr[],int a,int tableSize)
{
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
Table create(int tableSize){
	Table t=(Table)malloc(sizeof(struct hash));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->buckets=(link*)malloc(tableSize*sizeof(link));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->buckets)[i]=(link)malloc(sizeof(struct record));
		((t->buckets)[i])->index=-1;	
	}
	return t;
}

Table insert(Table t,char *arr[],int j){
	//insert all strings in arr in hashtable
	int i=0;
	int key=calculateHash(arr[j],t->a,t->tableSize);
	link chain=(t->buckets)[key];
	if(chain->index==-1)//index=-1 means that the linked list is empty
	{
		chain->index=j;
		chain->next=NULL;
	}
	else{
		link newNode=(link)malloc(sizeof(struct record));
		newNode->index=j;
		newNode->next=chain;
		(t->buckets)[key]=newNode;
	}
	return t;
}

int check(Table t,char arr[],char *keywords[]){
	//to check whether arr is keyword
	int key=calculateHash(arr,t->a,t->tableSize);
	link chain=(t->buckets)[key];
	while(chain)
	{
		if(strcmp(arr,keywords[chain->index])==0)
		return 1;
		chain=chain->next;
	}
	return 0;
}

