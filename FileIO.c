#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"
#define BUF_SIZE 256

char* twinBuf0;
char* twinBuf1;
int i, end,flag;
#define thresh 10
FILE *fp;


char* allocate(char* twinBuf)
{

	    twinBuf = (char*)malloc(sizeof(char)*256);
	    return twinBuf;	    
}
char getNextChar()
{// assuming memory for this is already allocated
        char temp1;
        char *buf; 
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
                return temp1;
            }
            else if(flag == 1)
            {
                i = end;
                buf = twinBuf0;
                temp1 = buf[i];
                buf = twinBuf1;
                i = 0;
                return temp1;
            }
        }
}

int main(){
	twinBuf0 = allocate(twinBuf0);
	twinBuf1 = allocate(twinBuf1);
	FILE *fp = fopen("sample.txt", "r");
	
	printf("%s\n",twinBuf1);
	printf("cobra's venom");
	return 0;
}

