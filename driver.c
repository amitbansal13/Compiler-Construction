#include "lexer.h"
#include "parser.h"
#include "parsetree.h"
#include <time.h>

PT *pTable; // parsetable;

int main()
{
	////////// Variables /////////////////////
	clock_t start_time, end_time;
	int choice;
    double total_CPU_time, total_CPU_time_in_seconds;
/*
			Grammar *g = makeGrammar("grammar.txt");
			computeFirstnFollow(g);
	//		link check = lookup(nonTerminals,"more_ids",nonterminals);
       //     int new_index = check->index;
        //    bool b = checkEps(new_index,g);
	//		printf("%d\n",b);
			printf("%d\n",isTerminal("DOsLLAR"));
			return 1;

	//		Grammar *g = makeGrammar("grammar.txt");
//			computeFirstnFollow(g);
//
    
*/
    //////////// Status ///////////////////
	printf("Status:-\n");
	printf("1. Lexer Implemented\n");
	// printf("2. Parser Implemented\n"); Hopefully
/*
	printf("%d\n",isNTerminal("outputParameters"));
	printf("%d\n",isTerminal("TK_CALL"));
	return 1;
*/
	


	////////////// Initialization /////////////
	FILE* fp=fopen("testcase1.txt","r");//change sample.txt to the file name containing code
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
		//We have to change the implementation of remove comments....
		else if (choice==2)printAllTokens();
		else if (choice==3)
		{
			start_time = clock();
    		// invoke your lexer and parser here
	//		readFile("grammar.txt");
			end_time = clock();
			total_CPU_time  =  (double) (end_time - start_time);
			total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
		}
		else if(choice ==4){
			Grammar *g = makeGrammar("grammar2.txt");
			printGrammar(g);
		}
		else if(choice ==5){
			Grammar *g = makeGrammar("grammar2.txt");
			computeFirstnFollow(g);
			printFirstnFollow();
		}
		else if(choice ==6){
			Grammar *g = makeGrammar("grammar2.txt");
			computeFirstnFollow(g);
	//		printFirstnFollow();
			initializePT();
			createParseTable(g);
			printParseTable();
		}
		else if(choice ==7){
			Grammar *g = makeGrammar("grammar2.txt");
			computeFirstnFollow(g);
			initializePT();
			createParseTable(g);
		ParseTree ptree=parseInputSourceCode("testcase1.txt");
			printParseTree(ptree,"outfile");
		}
		else 
			printf("Total CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
		printf("\nSelect your choice: \n");
	printf("0.Exit\n1. View comments removed file\n2.Print all tokens\n3.Call Parser and Lexer\n4.print grammar\n5.make grammar and make and print first follow 6.Make and Print ParseTable \n7.Print Time taken by program\n");
	//	printf("0.Exit\n1. View comments removed file\n2.Print all tokens\n3.Call Parser and Lexer\n4.Print Time taken by program\n");
		printf("Choice = ");
		scanf("%d",&choice);

	}
	return 0;
}
