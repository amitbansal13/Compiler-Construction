#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define BUF_SIZE 256

char* twinBuf1;
char* twinBuf2;

char* allocate(char* twinBuf){
	twinBuf = (char*)malloc(sizeof(char)*256);
	return twinBuf;
}

FILE* getStream(FILE* fp){
	
	char ch;
	int i=0;
	if(fp == NULL)
	{
		printf("Error openning the file!!");
    	}
	else{
		fread(readBuf,sizeof(char),256,fp);
	}
    	fclose(fp);
}

void getNextToken(){
	
	
}

int main(){
	
	twinBuf1 = allocate(twinBuf1);
	twinBuf2 = allocate(twinBuf2);
	FILE *fp = fopen("sample.txt", "r");
	fp = getStream(fp);
	printf("%s\n",twinBuf1);
	return 0;
}
//a sample program to read input into buffer



