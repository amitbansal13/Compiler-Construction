#include "lexer.h"
#include <time.h>

void printFile(FILE *fp);
int main()
{
	////////// Variables /////////////////////
	clock_t start_time, end_time;
	int choice;
    double total_CPU_time, total_CPU_time_in_seconds;
    
    //////////// Status ///////////////////
	printf("Status:-\n");
	printf("1. Lexer Implemented\n");
	// printf("2. Parser Implemented\n"); Hopefully
	


	////////////// Initialization /////////////
	FILE* fp=fopen("testcase1.txt","r");//change sample.txt to the file name containing code
	if(fp==NULL){
		printf("File not found\n");
		return 1;
	}
	initialize(fp);//to initialize hashtable and file pointer
	
	////////////// Execution ///////////////
	printf("Enter your choice: ");
	scanf("%d",&choice);
	while(choice!=0)
	{
		if(choice==1)removeComments();
		//	printFile(fp);
		//We have to change the implementation of remove comments....
		else if (choice==2)printAllTokens();
		else if (choice==3)
		{
			start_time = clock();
    		// invoke your lexer and parser here
			end_time = clock();
			total_CPU_time  =  (double) (end_time - start_time);
			total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
		}
		else 
			printf("Total CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
		printf("Enter your choice: ");
		scanf("%d",&choice);
	}
	return 0;
}
