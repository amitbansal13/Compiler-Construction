#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define BUF_SIZE 256

char* twinBuf0;
char* twinBuf1;
<<<<<<< HEAD
int i, end,flag;
#define thresh = 10;
FILE *fp;
//int start=0, end=0;
char* allocate(char* twinBuf)
{
=======
int start=0;
int globalptr = 0; //the forward pointer to traverse the buffer 

char* allocate(char* twinBuf){
>>>>>>> dadc1d11d8b6897945dc65cd7e7d734b1ef36a2d
	twinBuf = (char*)malloc(sizeof(char)*256);
	return twinBuf;
}
char getNextChar()
{// assuming memory for this is already allocated
    char temp1;
    char *buf 
    if(i<BUF_SIZE-thresh && flag == 0)
    {
        buf = twinBuf0;
    }
    else if(i<BUF_SIZE-thresh && flag == 1)
    {
        buf = twinBuf1;
    }
    else if(i>=thresh)
    {
        if(flag == 0)
            fread(twinBuf1,sizeof(char),256,fp);
        else if(flag == 1)
            fread(twinBuf0,sizeof(char),256,fp);
    }    
    if(i<end)
    {
        temp1 = buf[i];
        i++;
        return temp1;
    }
    else if(i<0)
    {
        // go to previous buffer
        if(flag == 0)
        {
            i = end;
            buf = twinBuf1;
            temp1 = buf[i];
            buf = twinBuf0;
            i = 0;
            return temp1
        }
        else if(flag == 1)
        {
            i = end;
            buf = twinBuf0;
            temp1 = buf[i];
            buf = twinBuf1;
            i = 0;
            return temp1
        }
    }
    
}
/*FILE* getStream(FILE* fp , int flag){
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
<<<<<<< HEAD
}*/
/*char* extract_str(FILE *fp,char *buf, int st, int en, int fl)
=======
}
char* extract_str(FILE *fp,char *buf, int fl,char* temp1)
>>>>>>> dadc1d11d8b6897945dc65cd7e7d734b1ef36a2d
{
       int k = 0;
       while(k!=BUF_SIZE && buf[k] != " ") // extract till empty space
       {
            temp1[globalptr] = buf[k];
            k++;
            globalptr++;
       }
       // reloads if it is traversed till end
       if(k==BUF_SIZE && fl == 0)
       {
            fp = getStream(fp, 1);
	    return extract_str(fp,twinbuf1,1,temp1);
            
       }
<<<<<<< HEAD
       else if(k==end && fl == 1)
=======
       else if(k==BUF_SIZE && fl == 1)
>>>>>>> dadc1d11d8b6897945dc65cd7e7d734b1ef36a2d
       {
            fp = getStream(fp, 0);//load the the 1st buffer
	    return extract_str(fp,twinbuf0,0,temp1);//make the flag 0, since the buffer0 would be traversed
       }
       else
       return temp1;
}
void write(){
	//	
}
<<<<<<< HEAD
*/
=======
>>>>>>> dadc1d11d8b6897945dc65cd7e7d734b1ef36a2d
TokenInfo getNextToken(FILE* fp){
	
	//get 256 char into first buffer
	TokenInfo tk = (TokenInfo)malloc(sizeof(struct tokenInfo));//main list of tokeninfo to be sent as output;100 is just for example
	char *temp1;
	temp1 = (char*)malloc(sizeof(char)*20);//20 is random
	temp1 = extract_str(fp,twinbuf0,0,temp1);//extract str till space and send it to DFA
	tk = checkDFA(temp1,start);
	TokenInfo temp = tk;
	while(start<=strlen(temp1)){
		tk->next = checkDFA(temp1,start);
		tk = tk->next;	
	    }
	}
	return temp;
}

void tokenize(FILE* f){//will create a list of token(tokeninfo) present in the raw input
	TokenInfo tarr;
	int i=1;
	tarr = (TokenInfo)malloc(sizeof(struct tokenInfo));
	while(!feof(f)){
		fp = getStream(fp, 0);
		tarr = (TokenInfo)realloc(tarr,sizeof(struct tokenInfo)*i);
		tarr[k] = getNextToken(fp); //repeatedly call getnexttoken.and add it to the list
		i*=2;
		k++;
	}
}

int main(){
	twinBuf1 = allocate(twinBuf1);
	twinBuf2 = allocate(twinBuf2);
	FILE *fp = fopen("sample.txt", "r");
	//tokenize(fp);
	printf("%s\n",twinBuf1);
	return 0;
}
//a sample program to read input into buffer



