#include "HashTable.h"
char *tokens[]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL","TK_COMMA", "TK_SEM","TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_LE", "TK_NE"};  
char *keywords[]= {"with","parameters","end","while","type","_main", "global" ,"parameter", "list", "input", "output", "int", "real", "endwhile", "if", "then", "endif", "read", "write", "return", "call", "record", "endrecord", "else"};
char *keywords_tokens[]= {"TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_ENDWHILE", "TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE"};

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

link lookup(Table t,char arr[],char *keywords[]){
	int key=calculateHash(arr,t->a,t->tableSize);
	link chain=t->buckets[key];
	while(chain)
	{
		
		if(chain->index != -1 && strcmp(keywords[chain->index],arr)==0)return chain;
		chain=chain->next;
	}
	return NULL;
}
