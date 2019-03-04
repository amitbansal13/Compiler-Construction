#include "lexer.h"
#include "parserDef.h"
#include "parser.h"
#include <time.h>

int main()
{
	////////// Variables /////////////////////

	clock_t start_time, end_time;
	int choice;
    double total_CPU_time, total_CPU_time_in_seconds;

	char *grammarFile = "grammar2.txt";
	char *testcaseFile = "testcase2.txt";
	char *outfile = "outfile.txt";

	ffset fset;
	PT *pTable;

    //////////// Status ///////////////////

	printf("Status:-\n");
	printf("1. Lexer Implemented\n");
	printf("2. Parser Implemented\n"); 

	


	////////////// Initialization /////////////
	FILE* fp=fopen(testcaseFile,"r");//change sample.txt to the file name containing code
	if(fp==NULL){
		printf("File not found\n");
		return 1;
	}
	initialize(fp);//to initialize hashtable and file pointer
	
	////////////// Execution ///////////////

	printf("\nSelect your choice: \n");

	//printf("0.Exit\n1. View comments removed file\n2.Print all tokens\n3.Call Parser and Lexer\n4.Print Time taken by program\n");


	/****kept this for testing,will make driver.c later finally ****/


	printf("0.Exit\n1. View comments removed file\n2.Print all tokens\n3.Call Parser and Lexer\n4.print grammar\n5.make grammar and make and print first follow 6.Make and Print ParseTable \n7.Print Time taken by program\n");

	printf("Choice = ");

	scanf("%d",&choice);

	while(choice!=0)
	{
		if(choice==1)removeComments();
		else if (choice==2)printAllTokens();
		else if (choice==3)
		{
			start_time = clock();
			end_time = clock();
			total_CPU_time  =  (double) (end_time - start_time);
			total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
		}
		else if(choice ==4){
			Grammar *g = makeGrammar(grammarFile);
			printGrammar(g);
		}
		else if(choice ==5){
			Grammar *g = makeGrammar(grammarFile);
			fset = computeFirstnFollow(g);
			printFirstnFollow(fset);
		}
		else if(choice ==6){
			Grammar *g = makeGrammar(grammarFile);
			fset = computeFirstnFollow(g);
			pTable = initializePT();
			createParseTable(g,fset,pTable);
			printParseTable(pTable);
		}
		else if(choice ==7){
			Grammar *g = makeGrammar(grammarFile);
			fset = computeFirstnFollow(g);
			pTable = initializePT();
			createParseTable(g,fset,pTable);
			ParseTree ptree=parseInputSourceCode(testcaseFile,pTable);
			printParseTree(ptree,outfile);
		}
		else 

			printf("Total CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);

		printf("\nSelect your choice: \n");
	printf("0.Exit\n1. View comments removed file\n2.Print all tokens\n3.Call Parser and Lexer\n4.print grammar\n5.make grammar and make and print first follow 6.Make and Print ParseTable \n7.Print Time taken by program\n");

		printf("Choice = ");

		scanf("%d",&choice);

	}
	return 0;
}
