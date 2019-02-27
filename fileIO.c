#include<stdio.h>
#include<stdlib.h>
char *buff1, *buff2;
FILE *getStream(FILE *fp)
{
    int nBytes1,nBytes2;
    nBytes2 = fread(bff2, 1, 256, fp);
    printf("%d \n", nBytes2);
    return fp;
}
int main()
{
    buff1 = (char *)malloc((sizeof(char))*256);
    buff2 = (char *)malloc((sizeof(char))*256);
    FILE *fp1;
    int a =0;
    //printf(sizeof( a));
    //printf(sizeof("\n"));
    fp1 = fopen("lang.txt", "r");
    fp1 = getStream(fp1);
   
    printf("%s", buff1);
    printf("\nballe balle\n");
    printf("%s", buff2);
    for(int i=0;i<256; i++)
    {
        printf("%c",buff1[i] );
    }
   return 0;
    
}
