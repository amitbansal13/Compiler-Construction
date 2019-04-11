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
		parseError = false;
		initialize(fp);//to initialize hashtable and file pointer
	
	////////////// Execution ///////////////

		printf("\nSelect your choice: \n");
		printf("0:For exit\n1 : For removal of comments ‐ print the comment free code on the console \n2 : For printing the token list (on the console) generated by the lexer.\n3 : For parsing and printing the parse tree appropriately.\n4: For printing (on the console) the total time taken and make ast and symbol table,also print both\n5: creating till symbol table and printing only symbol table\n\n");
		printf("\nChoice = ");

		scanf("%d",&choice);

		//removes the outfile if it already exists
		printf("\n\n");

		if(choice==0)
			break;
		if(choice==1)
			printAllTokens();
		else if(choice ==2){
			remove(outfile);
			Grammar *g = makeGrammar(grammarFile);
			fset = computeFirstnFollow(g);
			pTable = initializePT();
			createParseTable(g,fset,pTable);
			ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
			if(parseError==false)
				printParseTree(ptree,outfile,1);
		}
		else if (choice==3)
			{
				start_time = clock();
				Grammar *g = makeGrammar(grammarFile);
				fset = computeFirstnFollow(g);
				pTable = initializePT();
				createParseTable(g,fset,pTable);
				ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
				if(parseError==true){
					printf("Code has errors.\nSo exited\n");
					continue;
				}
				int ptree_nodes = printParseTree(ptree,outfile,0);
				printf("\n\n\nprinting AST in Inorder Traversal*********\n\n\n");
				createAST(ptree->root);
				int ast_nodes = printParseTree(ptree,outfile,1);
				printf("\n\n AST created successfully\n\n");
				end_time = clock();
				total_CPU_time  =  (double) (end_time - start_time);
				total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
				printf("\n\nTotal CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
				funcTable f=createFunc(59);
				idTable id=createID(59);
				recTable r=createRec(59);
				symbolTablePopulate(f,r,id,ptree);
				printf("\n\n SymbolTable created successfully\n\n");
				printf("%20s %20s %20s %20s\n","Lexeme","type","scope","offset"); 
				// printRecTable(r);
				printGlobalTable(id,r);
				printFuncTable(f,r);
			}
		else if (choice==4)
			{
				start_time = clock();
				Grammar *g = makeGrammar(grammarFile);
				fset = computeFirstnFollow(g);
				pTable = initializePT();
				createParseTable(g,fset,pTable);
				ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
				if(parseError==true){
					printf("Code has errors.\nSo exited\n");
					continue;
				}
				int ptree_nodes = printParseTree(ptree,outfile,0);
				printf("\n\n\nprinting AST in Inorder Traversal*********\n\n\n");
				createAST(ptree->root);
				int ast_nodes = printParseTree(ptree,outfile,0);
				printf("\n\n AST created successfully\n\n");
				end_time = clock();
				total_CPU_time  =  (double) (end_time - start_time);
				total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
				printf("\n\nTotal CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
				printf("ptreeNodes = %d\n,astNodes=%d\n",ptree_nodes,ast_nodes);
				float compressionRatio = ((float)(ptree_nodes-ast_nodes)/(float)ptree_nodes)*100;
				printf("CompressionRatio=%f\n",compressionRatio);
			}
		else if (choice==5)
			{
				start_time = clock();
				Grammar *g = makeGrammar(grammarFile);
				fset = computeFirstnFollow(g);
				pTable = initializePT();
				createParseTable(g,fset,pTable);
				ParseTree ptree=parseInputSourceCode(testcaseFile,pTable,&parseError);
				createAST(ptree->root);
				printf("\n\n AST created successfully\n\n");
				end_time = clock();
				total_CPU_time  =  (double) (end_time - start_time);
				total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
				printf("\n\nTotal CPU time = %lf\nTotal CPU time(secs) = %lf\n",total_CPU_time,total_CPU_time_in_seconds);
				funcTable f=createFunc(59);
				idTable id=createID(59);
				recTable r=createRec(59);
				symbolTablePopulate(f,r,id,ptree);
				printf("\n\n SymbolTable created successfully\n\n");
				printf("%20s %20s %20s %20s\n","Lexeme","type","scope","offset"); 
				printGlobalTable(id,r);
				printFuncTable(f,r);
				declarationErrorCheck(f,r,id,ptree);
				// funSemanticCheck(ptree->root,id,f);
			}
	}
	return 0;
}
