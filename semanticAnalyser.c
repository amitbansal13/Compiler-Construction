#include "lexer.h"
#include "symbolTableDef.h"
#include "parserDef.h"
#include "parser.h"
#include "symbolTable.h"
#include "semanticAnalyser.h"

int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT){
	TreeNode funcNode = root->children;
	TreeNode temp;
	int err = 0;

	while(funcNode->next!=NULL){//iterating all functions except main
		char* funid=funcNode->children->token_info->lexeme;
		Func funEntry = lookupFunc(funcT,funid);
		idTable funIdTable = funEntry->localTable;
		TreeNode stmtsNode = getStmt(funcNode,3);

		int no_children = getChildrenNo(stmtsNode);//no of output pars actually returned
		TreeNode retNode = getStmt(stmtsNode,no_children-1);
		int no_ret = getChildrenNo(retNode);//no of returns

		//printf("no_ret = %d,noOut = %d\n",no_ret,funEntry->noOutput);

		//first checking number of parametes returned error

		if(no_ret!=funEntry->noOutput){
			printf("err:In function %s, number of parameters returned does not match number of output parameters in function definition ",funcNode->children->token_info->lexeme );
            err=-1;
        }

		temp = retNode->children;
		int i=0;
		int type;
		
		while(temp!=NULL){
			if(temp->token_info==NULL)
				return -1;

			ID id = lookupID(globalT,temp->token_info->lexeme);//look into global table
			if(id==NULL)
				id = lookupID(funIdTable,temp->token_info->lexeme);//look into local table
			
			if(id==NULL)
				printf("line %d : return variable %s not initialized \n",temp->token_info->lineNo, temp->token_info->lexeme);
			
			else if(id->type!=funEntry->outputType[i])
				printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%s> of the formal output parameter\n",temp->token_info->lineNo,id->type==1?"real":"int",temp->token_info->lexeme,funEntry->outputType[i]==1?"real":"int");
				
			temp=temp->next;i++;
		}

		//now check for its statements after return param check is over

		if(funcStmtsCheck(funcNode,globalT,funcT)==-1)
			err=-1;
		funcNode=funcNode->next;
	}

	//doing the same for mainFunction

	char* funid="_main";
	Func funEntry = lookupFunc(funcT,funid);
	idTable funIdTable = funEntry->localTable;
	if(funcStmtsCheck(funcNode,globalT,funcT)==-1)
            err=-1;
	return err;
}

//checks all stmt nodes of a function

int funcStmtsCheck(TreeNode funcNode,idTable globalT,funcTable funcT){
	int no_children = getChildrenNo(funcNode);
	TreeNode output_par,stmts;
	int err = 0;
	Func funEntry;		//function Entry in the table
	int *out_alloc=NULL;
	int no_out=0;
	stmts = getStmt(funcNode,no_children-1);	//get stmts node

	if(no_children==1){//mainNode
		output_par=NULL;
		funEntry = lookupFunc(funcT,"_main");
	}

	else{
		output_par = getStmt(funcNode,2);		//get output_par node
		no_out = getChildrenNo(output_par);
		out_alloc = malloc( sizeof(int)* no_out/2);
        memset(out_alloc, 0 , sizeof(int)* no_out/2);
		char *funid=funcNode->children->token_info->lexeme;	//getting the name of this function to get its funcTable next
		funEntry = lookupFunc(funcT,funid);
	}
	
	//got stmts node and also output_par node(if available),and also got funEntry 

	TreeNode stmt = getStmt(stmts,2);	//get individual stmt

	while(stmt!=NULL){		//checking for individually all the stmt
		if(funcStmtCheck(funcNode,stmt, funcT,funEntry,out_alloc,output_par)==-1)
   		 	err=-1;
		stmt = stmt->next;
	}

	if(output_par!=NULL){		//checking if memory allocated for output_par of this function(in stmts memory allocated or not)
		for(int i=0;i<no_out/2;i++){
			if(out_alloc[i]==0){
				char *lexeme = tokens[getStmt(output_par,2*i+1)->index];
				int lineNo = getStmt(output_par,2*i+1)->token_info->lineNo;
				printf("Line %d : %s output parameter not assigned any value before returning it in function %s\n",lineNo,lexeme, nonterminals[funcNode->index] );
                err=-1;
			}
		}
	}
	if(out_alloc!=NULL)
		free(out_alloc);
	return err;
}
		

//checks individual stmt node
int funcStmtCheck(TreeNode funcNode,TreeNode stmtNode,funcTable funcT,Func funEntry,int *alloc,TreeNode output_par){

	char *stmt_type = nonterminals[stmtNode->index];
	int err = 0;

	//assignmentStmt

	if(strcmp("assignmentStmt",stmt_type)==0){
		if(alloc==NULL) return 0;
            for(int i=1;i<getChildrenNo(output_par);i+=2)
                if(stmtNode->children->children->tableEntry==getStmt(output_par,i)->tableEntry){
                    alloc[i/2]=1;
                    break;
        	    }
        return 0;
	}

	//iterativeStmt

	if(strcmp("iterativeStmt",stmt_type)==0){
		TreeNode temp = stmtNode->children->next;
		while(temp!=NULL){
			TreeNode child = temp;
			int res = funcStmtCheck(funcNode,child,funcT, funEntry,alloc, output_par);
			if(res==-1){
				err = -1;
			}
			temp = temp->next;
		}
		if(whileSemanticCheck(stmtNode)==-1){
			printf("Line %u : No updation of variables participating in the iterations of the while loop\n", stmtNode->children->token_info->lineNo);
			err=-1;		
		}
		return err;
	}

	//conditionalStmt

	if(strcmp("conditionalStmt",stmt_type)==0){
		
		TreeNode childList=stmtNode->children->next;
		while(childList->next)
		{
			if(funcStmtCheck(funcNode,childList,funcT,funEntry,alloc,output_par)==-1)
				err=-1;
			childList=childList->next;
		}
		childList=childList->children->next;
		while(childList)
		{
			if(funcStmtCheck(funcNode,childList,funcT,funEntry,alloc,output_par)==-1)
				err=-1;
			childList=childList->next;
		}
		return err;
	}

	//ioStmt

	if(strcmp("ioStmt",stmt_type)==0){
		if(alloc==NULL) return 0;
            for(int k=1;k<getChildrenNo(output_par);k+=2)
                if(stmtNode->children->next->children->tableEntry==getStmt(output_par,k)->tableEntry){
                    alloc[k/2]=1;
                    break;
        	    }
        return 0;
	}

 	//funCalLStmt

	if(strcmp("funCallStmt",stmt_type)==0){
		TreeNode temp_func;
		TreeNode funcCalled,outputPars,inPars;

		funcCalled = getStmt(stmtNode,1);	//funid token node containing the function token
		Func ftcalled = lookupFunc(funcT,funcCalled->token_info->lexeme);	//called function function table entry

		if(checkFuncDeclared(funcNode,stmtNode,funcT)==false){	//checks function calling errors
			err=-1;
			return err;
		}
		
		if(checkIOParams(funcCalled,stmtNode,ftcalled,alloc)==false){	//checks the function called input/output pars errors
			err=-1;
			return err;
		}
		return err;
	}
}	


bool checkFuncDeclared(TreeNode funcNode,TreeNode stmtNode,funcTable funcT){
		 TreeNode funcCalled = getStmt(stmtNode,1);
         Func ftcalled = lookupFunc(funcT,funcCalled->token_info->lexeme);
         TreeNode temp_func = funcNode->next;
		 if(temp_func==NULL){//mainFunction calls some other function
			if(ftcalled==NULL){
            	printf("Line %d : function %s is undefined \n",funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
				return false;
			}
			else if(strcmp(funcCalled->token_info->lexeme,"_main")==0){
            	printf("Line %d : function %s is undefined \n",funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
				return false;
			}

			else
				return true;
		}				
         while(temp_func && temp_func->next!=NULL){//avoid checking main function
             if(strcmp(temp_func->children->token_info->lexeme,funcCalled->token_info->lexeme)==0)
                 break;
             temp_func = temp_func->next;
         }
         if(ftcalled == NULL || temp_func->next!=NULL){      //calling function before declaration
             printf("Line %d : The function %s is undefined \n",funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
			return false;
         }
         if(temp_func==funcNode){    //recursive call
              printf("Line %d : A function <%s>  cannot be recursively\n",funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
				return false;
         }
		return true;
}

bool checkIOParams(TreeNode funcCalled,TreeNode stmtNode,Func ftcalled,int *alloc){
	TreeNode outputPars = stmtNode->children;
	int err=0;
	
	//first check output params

	if(getChildrenNo(outputPars)!= ftcalled->noOutput){
        printf("Line %d : Number of parameters required for function <%s> doesnt match number of returned paramters \n", funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
        err=-1;
	}
	
	TreeNode temp=outputPars->children;
	int i=0;
	while(temp!=NULL){
        if(temp->tableEntry==NULL || temp->tableEntry->type!=ftcalled->outputType[i])
         {
             printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%d> of the formal output parameter \n",temp->token_info->lineNo,ftcalled->inputType[i]==1?"real":"int",funcCalled->token_info->lexeme,ftcalled->outputType[i]);
             err=-1;
         }
         else if(alloc!=NULL)
                 alloc[i]=1;
		temp=temp->next;i++;
     }

	//now check input params

	TreeNode inPars = getStmt(stmtNode,2);
	if(getChildrenNo(inPars)!= ftcalled->noInput){
        printf("Line %d : The number of input parameters at function call <%s> is incorrect.\n", funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
        err=-1;
	}
	temp=inPars->children;
	i=0;
	while(temp!=NULL){
        if(temp->tableEntry==NULL || temp->tableEntry->type!=ftcalled->inputType[i])
         {
             printf("Line %d : type <%s> of input parameter in function <%s> doesnt match the returned type\n",temp->token_info->lineNo,ftcalled->inputType[i]==1?"real":"int",funcCalled->token_info->lexeme);
             err=-1;
         }
		temp=temp->next;i++;
	}
	if(err==0)
		return false;
	else
		return true;
}

Seq getSequence(TreeNode root){
	if(root->index==27 && root->tNt==1){//SingleOrRecID
		Seq i = malloc(sizeof(struct sequence));
		i->tableEntry = root->children->tableEntry;
		i->next = NULL;
		if(getChildrenNo(root)==2){
			i->fieldid = strdup(root->children->next->token_info->lexeme);
		}
		return i;
	}
	else if(root->index==3 && root->tNt==0)//TK_ID
	{
		Seq i = malloc(sizeof(struct sequence));
		i->tableEntry = root->tableEntry;
		i->next = NULL;
		return i;
	}
	Seq begin=NULL,end=NULL;
	TreeNode childList=root->children;
	while(childList)
	{
		if(begin==NULL)
		{
			begin=getSequence(childList);
			end=begin;
		}
		else{
			while(end->next)end=end->next;
			end->next=getSequence(childList);
		}
		childList=childList->next;
	}
	return begin;

}

int checkSequence(Seq begin,TreeNode root)
{
	int index;
	TreeNode childList= root->children;
	Seq temp;
	char *stmt_type = nonterminals[root->index];
	
	if(strcmp("assignmentStmt",stmt_type)==0){
		temp=begin;
		if(getChildrenNo(root->children)==1){
			while(temp!=NULL){
				if(root->children->children->tableEntry == temp->tableEntry){
					return 1;	
				}
				temp = temp->next;
			}
			return 0;			
		}
		else{
			while(temp!=NULL){
				if(root->children->children->tableEntry == temp->tableEntry){
					char* fieldid=childList->children->next->token_info->lexeme;
					if(strcmp(fieldid,temp->fieldid)==0){
						return 1;
					}					
				}
				temp = temp->next;
			}
			return 0;		
		}
	}
	
	if(strcmp("iterativeStmt",stmt_type)==0){
		TreeNode childList = root->children->next;
		while(childList!=NULL){
			TreeNode t = childList;
			if(checkSequence(begin,t)==1){
				return 1;
			}
			childList = childList->next;
		}
		return 0;		
	}

	if(strcmp("conditionalStmt",stmt_type)==0){
		TreeNode childList=root->children->next;
		while(childList->next)
		{
			if(checkSequence(begin,childList)==1)
				return 1;

			childList=childList->next;
		}
		childList=childList->children;
		while(childList)
		{
			if(checkSequence(begin,childList)==1)
				return 1;
		}
		return 0;
	}

	if(strcmp("funCallStmt",stmt_type)==0){
		while(childList)
		{
			temp=begin;
			while(temp)
			{
				if(childList->tableEntry==temp->tableEntry)
					return 1;
				temp=temp->next;
			}
			childList=childList->next;	
		}
		return 0;
	}

	if(strcmp("ioStmt",stmt_type)==0){
		if(strcmp(tokens[root->index],"TK_READ")==0)
		{
			temp=begin;
			while(temp)
			{
				if(temp->tableEntry==root->children->next->children->tableEntry)
				{
					int childNo=getChildrenNo(root->children->next);
					if(childNo==1)
						return 1;
					if(childNo==2 && strcmp(root->children->next->children->next->token_info->lexeme,temp->fieldid)==0)
						return 1;
				}
				temp=temp->next;
			}
		}
		return 0;
	}
	

	return 0;
}
int whileSemanticCheck(TreeNode node){
	Seq list=getSequence(node->children);
	TreeNode temp=node->children->next;
	while(temp)
	{
		if(checkSequence(list,temp)==1)return 0;
		temp=temp->next;
	}
	return -1;
}

