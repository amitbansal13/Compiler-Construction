/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#include "lexer.h"
#include "parserDef.h"
#include "symbolTableDef.h"
#include "symbolTable.h"
#include "semanticAnalyser.h"

#include "parser.h"
#include <time.h>
#include "ast.h"

int main(int argc,char *argv[])
{
	////////// Variables /////////////////////
	if(argc!=3){
		printf("Please enter in this format:\n");
		printf("$./compiler   testcase.txt  code.asm\n");
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
	printf("LEVEL 3: Symbol table/ AST/ Semantic Rules/TypeChecking modules work.\n"); 

	while(1){
		parseError = false;
		initialize(fp);//to initialize hashtable and file pointer
	
	////////////// Execution ///////////////

		printf("\nSelect your choice: \n");
		printf("\
		0:For exit\n\
		1: For printing the token list (on the console) generated by the lexer.\n\
		2: For parsing and printing the parse tree appropriately.\n\
		3: For printing (on the console) the AST and total time taken \n\
		4: Display the amount of memory allocated and Compression Ratio\n\
		5: Display the symbol table\n\
		6: Display the global variables\n\
		7: Display Function List\n\
		8: Display Record List\n\
		9: Verify Semantic Correctness of Output\n\
		10: Produce assembly code\n");
		printf("\nChoice = ");

		scanf("%d",&choice);

		//removes the outfile if it already exists
		printf("\n\n");

		if(choice==0)
			break;
		if(choice==1)
		{
			printAllTokens();
			continue;
		}
		start_time = clock();
		Grammar *g = makeGrammar(grammarFile);
		fset = computeFirstnFollow(g);
		pTable = initializePT();
		createParseTable(g,fset,pTable);
		ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
		if(choice ==2){
			if(parseError==false)
				printParseTree(ptree,1);
			else{
				printf("Parsing Unsuccessful\nExiting\n");
			}
			continue;
		}
		int ptree_nodes = printParseTree(ptree,0);
		createAST(ptree->root);
		int ast_nodes = printParseTree(ptree,0);
	//	printf("\n\n AST created successfully\n\n");
				
		if (choice==3)
		{
			printf("\n\n\nprinting AST in Inorder Traversal*********\n\n\n");
			printParseTree(ptree,1);
			continue;
		}
		if (choice==4)
		{
			//To be modified to show size of memory allocated
			int size = sizeof(struct treenode);
			printf ("Parse tree Number of nodes = %d\tAllocated Memory = %d Bytes\nAST Number of nodes = %d\tAllocated Memory = %d Bytes\n",ptree_nodes,ptree_nodes*size,ast_nodes,ast_nodes*size);
			float compressionRatio = ((float)(ptree_nodes-ast_nodes)/(float)ptree_nodes)*100;
			printf("CompressionRatio=%f\n",compressionRatio);
			continue;
		}
		funcTable functionTable=createFunc(59);
		idTable globalTable=createID(59);
		recTable recordTable=createRec(59);
		symbolTablePopulate(functionTable,recordTable,globalTable,ptree);
		if (choice==5)
		{
			printf("%20s %20s %20s %20s\n","Lexeme","type","scope","offset"); 
			printGlobalTable(globalTable,recordTable);
			printFuncTable(functionTable,recordTable);
			continue;
		}
		if(choice==6)
		{
			printf("%20s %20s %20s\n","Name","Type","Offset");
			for(int i=0;i<globalTable->tableSize;i++)
			{
				ID temp=globalTable->table[i];
				while(temp)
				{
					printf("%20s %20s %20d\n",temp->name,printType(recordTable,temp->tname),temp->width);
					temp=temp->next;
				}
			}
			continue;
		}
		if(choice==7)
		{
			printf("%20s %20s\n","Function Name","Width");
			for(int i=0;i<functionTable->tableSize;i++)
			{
				Func temp=functionTable->table[i];
				while(temp)
				{
					printf("%20s %20d\n",temp->name,temp->width);
					temp=temp->next;
				}
			}
			continue;
		}
		if(choice==8)
		{
			printf("%20s %20s %20s\n","Name","Type","Offset");
			for(int i=0;i<recordTable->tableSize;i++)
			{
				Rec temp=recordTable->table[i];
				while(temp)
				{
					printf("%20s %20s %20d\n",temp->name,printType(recordTable,temp->name),temp->width);
					temp=temp->next;
				}
			}
			continue;
		}
		if(choice==9)
		{
			declarationErrorCheck(functionTable,recordTable,globalTable,ptree);
			checkType(ptree->root, recordTable);
			funSemanticCheck(ptree->root,globalTable,functionTable);
			end_time = clock();
			total_CPU_time  =  (double) (end_time - start_time);
			total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
			printf("\n\nTotal CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
			continue;
		}
		//choice 10 to be implemented
			
	}
	return 0;
}
