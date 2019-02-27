#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 256
#define thresh 10

char* twinBuf1;
char* twinBuf2;
int i, end,flag=0,end1,end2,ans=1;
FILE *fp;
char* allocate(char* twinBuf)
{
    twinBuf = (char*)malloc(sizeof(char)*BUF_SIZE);
    return twinBuf;
}
char getNextChar()
{
// assuming memory for this is already allocated
        char temp1;
        char *buf;
        if(flag == 0)
        {
        	buf = twinBuf1;
        	end=end1;
        }
        else
        {
	        buf = twinBuf2;
	        end=end2;
	    }
        if(i>=end)
        {
            if(flag == 0)
                end2=fread(twinBuf2,sizeof(char),BUF_SIZE-1,fp);
            else
                end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
            i=0;
        	if(flag==0){
        		buf = twinBuf2;
	        	end=end2;
	        	flag=1;
        	}
        	else{
	        	buf = twinBuf1;
	        	end=end1;
	        	flag=0;
        	}
        }
        if(i<0)
        {
            // go to previous buffer
            i=0;
            if(flag == 0)
                return twinBuf2[end2-1];
            else
                return twinBuf1[end1-1];
        }
        if(end1==0 && end2==0)return '\0';
        /*
        One issue it there that it prints an extra character when called more times than the number of characters in file
        For the sample file the output contains one extra character (garbage) after the end of the file
        */
        char temp=buf[i];
        i++;
        return temp;
}

int main(){
	twinBuf1 = allocate(twinBuf1);
	twinBuf2 = allocate(twinBuf2);
    fp = fopen("sample.txt", "r");
	end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
	char c;
	int count=0;
	while(count<50000)//4088 is the number of characters in file
    {
        printf("%c",getNextChar());
        count++;
    }
    //printf("%c",-1);
    return 0;
}

