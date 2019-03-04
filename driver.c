#include "lexer.h"
#include "parserDef.h"
#include "parser.h"
#include <time.h>

int main(int argc,char *argv[])
{
	////////// Variables /////////////////////
	if(argc!=3){
		printf("Please enter in this format:\n");
		printf("$./stage1exe   testcase.txt   parsetreeOutFile.txt\n");
		return 1;
	}

	char *grammarFile = "grammar.txt";

	char *testcaseFile = argv[1];

	char *outfile = argv[2];

	clock_t start_time, end_time;
	int choice;
    double total_CPU_time, total_CPU_time_in_seconds;

	bool parseError = false;
	ffset fset;
	PT *pTable;

    //////////// Status ///////////////////


	


	////////////// Initialization /////////////
	FILE* fp=fopen(testcaseFile,"r");//change sample.txt to the file name containing code
	if(fp==NULL){
		printf("File %s not found\n",testcaseFile);
		return 1;
	}

	printf("Status:-\n");
	printf("c) Both Lexical and syntax analysis modules implemented\n"); 

	while(1){
		initialize(fp);//to initialize hashtable and file pointer
	
	////////////// Execution ///////////////

		printf("\nSelect your choice: \n");
	//	printf("0:For exit\n1 : For removal of comments ‐ print the comment free code on the console \n2 : For printing the token list (on the console) generated by the lexe.\nr3 : For parsing and printing the parse tree appropriately.\n4: For printing (on the console) the total time taken by your stage 1 code of lexer and parser to verify the syntactic correctness.\n\n\n");
		printf("\nChoice = ");

		scanf("%d",&choice);

		//removes the outfile if it already exists
		printf("\n\n");

		if(choice==0)
			break;
		if(choice==1)
			removeComments();
		else if (choice==2)
			printAllTokens();
		else if(choice ==3){
			remove(outfile);
			Grammar *g = makeGrammar(grammarFile);
			fset = computeFirstnFollow(g);
			pTable = initializePT();
			createParseTable(g,fset,pTable);
			ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
			if(parseError==false)
				printParseTree(ptree,outfile);
		}
		else if (choice==4)
			{
				start_time = clock();
				Grammar *g = makeGrammar(grammarFile);
				fset = computeFirstnFollow(g);
				pTable = initializePT();
				createParseTable(g,fset,pTable);
				ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
				end_time = clock();
				total_CPU_time  =  (double) (end_time - start_time);
				total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
				printf("\n\nTotal CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
			}
	}
	return 0;
}
