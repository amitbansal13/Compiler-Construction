#include "lexer.h"
#include "symbolTableDef.h"
#include "parserDef.h"
#include "parser.h"
#include "symbolTable.h"
#include "semanticAnalyser.h"

int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT){
	TreeNode funcNode = root->children;
	TreeNode temp;
	int error = 0;
	while(funcNode->next!=NULL){//iterating all functions except main
		char* funid=funcNode->children->token_info->lexeme;
		Func funEntry = lookupFunc(funcT,funid);
		idTable funIdTable = funEntry->localTable;
		TreeNode stmtsNode = getStmt(funcNode,3);

		int no_children = getChildrenNo(stmtsNode);//no of output pars actually returned
		TreeNode retNode = getStmt(stmtsNode,no_children-1);
		int no_ret = getChildrenNo(retNode);//no of returns
		//printf("no_ret = %d,noOut = %d\n",no_ret,funEntry->noOutput);

		if(no_ret!=funEntry->noOutput){
			printf("error:In function %s, number of parameters returned does not match number of output parameters in function definition ",funcNode->children->token_info->lexeme );
            error=-1;
        }
		temp = retNode->children;
		int i=0;
		int type;
		while(temp!=NULL){
			if(temp->token_info==NULL)
				return -1;

			//***********type matching problem****return->TK_ID doesnt knw its type int,real etc

			/*
			if(type!=funEntry->outputType[i]){
				 printf("lineNo %d returned type of %s does not match expected type\n",temp->token_info->lineNo, temp->token_info->Token);
				printf("type=%d,outtype=%d\n",type,funEntry->outputType[i]);
                error=-1;
            }
			*/
			temp=temp->next;i++;
		}
		if(funcStmtsCheck(funcNode,globalT,funcT)==-1)
			error=-1;
		funcNode=funcNode->next;
	}

	//mainFunction node here

	char* funid="_main";
	Func funEntry = lookupFunc(funcT,funid);
	idTable funIdTable = funEntry->localTable;
	if(funcStmtsCheck(funcNode,globalT,funcT)==-1)
            error=-1;
	return error;
}

//checks all stmt nodes of a function

int funcStmtsCheck(TreeNode funcNode,idTable globalT,funcTable funcT){
	int no_children = getChildrenNo(funcNode);
	TreeNode output_par,stmts;
	int error = 0;
	Func funEntry;
	int *out_alloc=NULL;
	stmts = getStmt(funcNode,no_children-1);
	if(no_children==1){//mainNode
		output_par=NULL;
		funEntry = lookupFunc(funcT,"_main");
	}
	else{
		output_par = getStmt(funcNode,2);
		int no_out = getChildrenNo(output_par);
		out_alloc = malloc( sizeof(int)* no_out/2);
        memset(out_alloc, 0 , sizeof(int)* no_out/2);
		char *funid=funcNode->children->token_info->lexeme;
		funEntry = lookupFunc(funcT,funid);
	}

	//got stmts node and also output_par node(if available),and also got funEntry 
	TreeNode stmt = getStmt(stmts,2);
	while(stmt!=NULL){
		if(funcStmtCheck(stmt, funcT,funEntry,out_alloc,output_par)==-1)
   		 	error=-1;
		stmt = stmt->next;
	}

	return error;
}
		

//checks individual stmt node
int funcStmtCheck(TreeNode stmtNode,funcTable funcT,Func funEntry,int *alloc,TreeNode output_par){

	char *stmt_type = nonterminals[stmtNode->index];

	int error = 0;

	if(strcmp("assignmentStmt",stmt_type)==0);

	if(strcmp("iterativeStmt",stmt_type)==0);

	if(strcmp("conditionalStmt",stmt_type)==0);

	if(strcmp("ioStmt",stmt_type)==0);

	if(strcmp("funCallStmt",stmt_type)==0);

	return error;
}	
