#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 256
#define thresh 10

char* twinBuf1;
char* twinBuf2;
int i, end,flag=0,end1,end2;
FILE *fp;
int temp=0;

char* allocate(char* twinBuf)
{
    twinBuf = (char*)malloc(sizeof(char)*BUF_SIZE);
    return twinBuf;
}
char getNextChar()
{
    temp++;
// assuming memory for this is already allocated
        char temp1;
        char *buf;
        if(flag == 0)
        {
        	buf = twinBuf1;
        	end=end1;
        }
        else{
	        buf = twinBuf2;
	        end=end2;
	    }
        if(i>=end)
        {
            printf("%d\n",temp);
            if(flag == 0)
                end2=fread(twinBuf2,sizeof(char),BUF_SIZE-1,fp);
            else
                end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
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
        if(i>=end)
        {
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
        if(end1==0 && end2==0)return '\0';
        char temp=buf[i];
        i++;
        return temp;
}

int main(){
	twinBuf1 = allocate(twinBuf1);
	twinBuf2 = allocate(twinBuf2);
	FILE *fp = fopen("sample.txt", "r");
	end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
	char c;
	int count=0;
	while(count<300)
	{
		c=getNextChar();
		printf("%c",c);
		count++;
	}
}

