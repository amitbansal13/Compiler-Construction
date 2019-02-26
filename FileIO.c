#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define BUF_SIZE 256

char* twinBuf0;
char* twinBuf1;
int i=0, j=0;
char* allocate(char* twinBuf){
	twinBuf = (char*)malloc(sizeof(char)*256);
	return twinBuf;
}

FILE* getStream(FILE* fp , int flag){
	//char* temp;
	//temp = tbuf;
	char ch;
	int i=0;
	if(fp == NULL)
	{
		printf("Error openning the file!!");
    	}
	else{
		if(flag==0){
			fread(twinBuf0,sizeof(char),256,fp);
		}
		else{
			fread(twinBuf1,sizeof(char),256,fp);
	}
    	fclose(fp);
	return fp;
}
char* extract_str(char *buf)
{
    
}

TokenInfo getNextToken(FILE* fp){
	fp = getStream(fp, 0);
	TokenInfo tk;//(TokenInfo)malloc(sizeof(struct tokenInfo));
    char *temp1  = extract_str(twinbuf1);
	tk=checkDFA(temp1, i, j);
	return tk;
}

void tokenize(FILE* f){
	TokenInfo tarr;
	int i=0;
	tarr = (TokenInfo)malloc(sizeof(struct tokenInfo));
	while(!feof(f)){
		tarr = (TokenInfo)realloc(tarr,sizeof(struct tokenInfo)*i);
		getNextToken(f);	
		i*=2;
	}
}

int main(){
	twinBuf1 = allocate(twinBuf1);
	twinBuf2 = allocate(twinBuf2);
	FILE *fp = fopen("sample.txt", "r");
	tokenize(fp);
	printf("%s\n",twinBuf1);
	return 0;
}
//a sample program to read input into buffer



