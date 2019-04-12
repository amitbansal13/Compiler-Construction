#include "lexer.h"
#include "symbolTableDef.h"
#include "parserDef.h"
#include "parser.h"
#include "symbolTable.h"
#include "semanticAnalyser.h"

int funSemanticCheck(TreeNode root,idTable globalT,funcTable funcT){
	TreeNode funcNode = root->children;
	TreeNode id_node;
	int err = 0;

	while(funcNode->next!=NULL){//iterating all functions except main
		char* funid=funcNode->children->token_info->lexeme;
		Func funEntry = lookupFunc(funcT,funid);
		idTable funIdTable = funEntry->localTable;
		TreeNode stmtsNode = getStmt(funcNode,3);

		int no_children = getChildrenNo(stmtsNode);//no of output pars actually returned
		TreeNode retNode = getStmt(stmtsNode,no_children-1);
		int no_ret = getChildrenNo(retNode);//no of returns

		//first checking if number of parametes returned matches or not

		if(no_ret!=funEntry->noOutput){
			printf("err:In function %s, number of parameters returned does not match number of output parameters in function definition ",funcNode->children->token_info->lexeme );
            err=-1;
        }

		//no of returns as required

		TreeNode id_node = retNode->children;
		int i=0;
		int type;
		
		//iterating all the returned id nodes

		while(id_node!=NULL){
			if(id_node->token_info==NULL)
				return -1;

			ID id = lookupID(globalT,id_node->token_info->lexeme);//look into global table
			if(id==NULL)
				id = lookupID(funIdTable,id_node->token_info->lexeme);//look into local table
			
			if(id==NULL)
				printf("line %d : return variable %s not initialized \n",id_node->token_info->lineNo, id_node->token_info->lexeme);
			
			//id type does not matches expected
			else if(id->type!=funEntry->outputType[i])
				if(id->type<=1)	//int/real types
					printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%s> of the formal output parameter\n",id_node->token_info->lineNo,id->type==1?"real":"int",id_node->token_info->lexeme,funEntry->outputType[i]==1?"real":"int");
				
				else
					printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%s> of the formal output parameter\n",id_node->token_info->lineNo,"record",id_node->token_info->lexeme,funEntry->outputType[i]==1?"real":"int");
					
				
			id_node=id_node->next;i++;
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
		if(alloc==NULL)
		    return 0;
		TreeNode assign_id = stmtNode->children->children;	//tkid which was assigned some value
		TreeNode out_id;
        for(int i=1;i<getChildrenNo(output_par);i+=2){
			out_id = getStmt(output_par,i);		
            if(assign_id->tableEntry==out_id->tableEntry){
                alloc[i/2]=1;
                break;
       	    }
		}
        return 0;
	}

	//iterativeStmt

	if(strcmp("iterativeStmt",stmt_type)==0){
		TreeNode child_stmt = stmtNode->children->next;
		//iterate the same function for all the stmt nodes
		while(child_stmt!=NULL){
			if(funcStmtCheck(funcNode,child_stmt,funcT, funEntry,alloc, output_par))
				err = -1;
			child_stmt = child_stmt->next;
		}
		//check if loop variables change
		if(whileSemanticCheck(stmtNode)==-1){//stmtNode passed since semantic check on entire iterativeStmt
			printf("Line %u : No updation of variables participating in the iterations of the while loop\n", stmtNode->children->token_info->lineNo);
			err=-1;		
		}
		return err;
	}

	//conditionalStmt

	if(strcmp("conditionalStmt",stmt_type)==0){
		
		TreeNode child_stmt=stmtNode->children->next;

		//getting all stmt node

		while(child_stmt->next)
		{
			//recurse the function  since all are stmt
			if(funcStmtCheck(funcNode,child_stmt,funcT,funEntry,alloc,output_par)==-1)
				err=-1;
			child_stmt=child_stmt->next;
		}

		//traversing all the else statements

		//elsePart is child_stmt
		TreeNode else_stmt = child_stmt->children;
		while(else_stmt)
		{
			//recursing for all those statements
			if(funcStmtCheck(funcNode,else_stmt,funcT,funEntry,alloc,output_par)==-1)
				err=-1;
			else_stmt=else_stmt->next;
		}
		return err;
	}

	//ioStmt

	if(strcmp("ioStmt",stmt_type)==0){
		if(alloc==NULL) 
			return 0;
		int no_out_pars = getChildrenNo(output_par);
		TreeNode singleOrRecId = stmtNode->children->next;
		TreeNode out_id;
        for(int i=1;i<no_out_pars;i+=2){
			//see if that varible is read/write....if so we allocate memory for that
			out_id = getStmt(output_par,i);
            if(singleOrRecId->children->tableEntry==out_id->tableEntry){//matching the ids and allocating if found
                alloc[i/2]=1;
                break;
            }
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
			if(ftcalled==NULL || strcmp(funcCalled->token_info->lexeme,"_main")==0){
            	printf("Line %d : function %s is undefined \n",funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
				return false;
			}
			else	//since this would be the last function
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
	
	TreeNode out_id=outputPars->children;
	int i=0;

	if(err==-1)
		out_id=NULL;	//to skip the next while loop since if output_pars number dont match,dont compare the values

	while(out_id!=NULL){
        if(out_id->tableEntry==NULL || out_id->tableEntry->type!=ftcalled->outputType[i])
         {
			if(ftcalled->inputType[i]<=1)
	             printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%d> of the formal output parameter \n",out_id->token_info->lineNo,ftcalled->inputType[i]==1?"real":"int",funcCalled->token_info->lexeme,ftcalled->outputType[i]);
			else
   		          printf("line %d : The type <%s> of variable <%s> returned does not match with the type <%d> of the formal output parameter \n",out_id->token_info->lineNo,"record",funcCalled->token_info->lexeme,ftcalled->outputType[i]);
             err=-1;
         }

         else if(alloc!=NULL)	//if type matches,we allocated
                 alloc[i]=1;
		out_id=out_id->next;i++;
     }




	//now check input params

	TreeNode inPars = getStmt(stmtNode,2);
	if(getChildrenNo(inPars)!= ftcalled->noInput){
        printf("Line %d : The number of input parameters at function call <%s> is incorrect.\n", funcCalled->token_info->lineNo,funcCalled->token_info->lexeme);
        err=-1;
		return false;	//if numbers dont match return immediately avoid checking the individual values
	}
	TreeNode in_id=inPars->children;
	i=0;
	while(in_id!=NULL){
        if(in_id->tableEntry==NULL || in_id->tableEntry->type!=ftcalled->inputType[i])
         {
			if(ftcalled->inputType[i]<=1)
             printf("Line %d : type <%s> of input parameter in function <%s> doesnt match the returned type\n",in_id->token_info->lineNo,ftcalled->inputType[i]==1?"real":"int",funcCalled->token_info->lexeme);
			else
             printf("Line %d : type <%s> of input parameter in function <%s> doesnt match the returned type\n",in_id->token_info->lineNo,"record",funcCalled->token_info->lexeme);
             err=-1;
         }
		in_id=in_id->next;i++;
	}
	if(err==0)
		return true;
	else
		return false;
}

//returns list of all the elements in while conditions
Seq getWhileVars(TreeNode root){
	//can be singleOrRecId or TK_ID
	if(root->index==27 && root->tNt==1){//SingleOrRecID
		Seq i = malloc(sizeof(struct sequence));
		TreeNode tkid_node = root->children;
		i->id_name = strdup(tkid_node->tableEntry->name);
		i->fieldid=NULL;
		i->next = NULL;
		if(getChildrenNo(root)==2){		//if it has fieldid
			TreeNode fieldid_node = root->children->next;//got the fieldid_node
			i->fieldid = strdup(fieldid_node->token_info->lexeme);	//copy the fieldid
		}
		return i;	//returns the sequence
	}
	else if(root->index==3 && root->tNt==0)//TK_ID
	{
		Seq i = malloc(sizeof(struct sequence));
		i->id_name = strdup(root->tableEntry->tname);
		i->fieldid=NULL;
		i->next = NULL;
		return i;
	}
	Seq begin=NULL,end=NULL;
	TreeNode childList=root->children;
	while(childList)
	{
		if(begin==NULL)
		{
			//get the first element of sequence
			begin=getWhileVars(childList);
			end=begin;
		}
		else{
			//append the next sequence
			while(end->next)
				end=end->next;
			end->next=getWhileVars(childList);
		}
		childList=childList->next;
	}
	return begin;

}

int checkVarChanges(Seq begin,TreeNode stmtNode)
{
	int index;
	TreeNode childList= stmtNode->children;
	Seq temp;
	char *stmt_type = nonterminals[stmtNode->index];
	
	if(strcmp("assignmentStmt",stmt_type)==0){
		temp=begin;
		TreeNode singleOrRecId = stmtNode->children;
		if(getChildrenNo(singleOrRecId)==1){	//only TK_ID present
			//iterate for all the seq elements
			while(temp!=NULL){
				if(strcmp(singleOrRecId->children->tableEntry->name,temp->id_name)==0){//if entry matched,then return,since it is being assigned values
					return 1;	
				}
				temp = temp->next;
			}
			return 0;			
		}
		else{	//it has TK_ID as well as TK_FIELDID
			while(temp!=NULL){
				if(strcmp(singleOrRecId->children->tableEntry->name,temp->id_name)==0){
					TreeNode fieldid_node = singleOrRecId->children->next;
					char* fieldid=fieldid_node->token_info->lexeme;
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
		TreeNode new_stmt = stmtNode->children->next;	//get stmt node
		while(new_stmt!=NULL){
			if(checkVarChanges(begin,new_stmt)==1)	//recurse again with original list
				return 1;
			new_stmt = new_stmt->next;
		}
		return 0;		
	}

	if(strcmp("conditionalStmt",stmt_type)==0){
		TreeNode new_stmt=stmtNode->children->next;
		//iterate all the IF nodes
		while(new_stmt->next)
		{
			if(checkVarChanges(begin,new_stmt)==1)
				return 1;

			new_stmt = new_stmt->next;
		}
		TreeNode elsePart = new_stmt;
		new_stmt = elsePart->children;
		//iterate all the else nodes
		while(new_stmt)
		{
			if(checkVarChanges(begin,new_stmt)==1)
				return 1;
			new_stmt = new_stmt->next;
		}
		return 0;
	}

	if(strcmp("funCallStmt",stmt_type)==0){
		TreeNode outputPars = stmtNode->children;
		TreeNode output_id = outputPars->children;
		//iterate all the output_ids since their values change
		while(output_id)
		{
			temp=begin;
			while(temp)
			{
				if(strcmp(output_id->tableEntry->name,temp->id_name)==0)	//it has only TK_ID entry
					return 1;
				temp=temp->next;
			}
			output_id=output_id->next;	
		}
		return 0;
	}

	if(strcmp("ioStmt",stmt_type)==0){
		TreeNode rw_node = stmtNode->children;
		TreeNode singleOrRecId = stmtNode->children->next;
		if(strcmp(tokens[rw_node->index],"TK_READ")==0)//if it is reading value into the variable
		{
			temp=begin;
			while(temp)
			{
				if(strcmp(temp->id_name,singleOrRecId->children->tableEntry->name)==0)	//if TK_ID matches
				{
					int childNo=getChildrenNo(singleOrRecId);
					if(childNo==1)//TKID only present
						return 1;
								//TK_FIELD id also present
					if(childNo==2 && strcmp(singleOrRecId->children->next->token_info->lexeme,temp->fieldid)==0)
						return 1;
				}
				temp=temp->next;
			}
		}
		return 0;
	}
	

	return 0;
}
int whileSemanticCheck(TreeNode node){	//takes as input the iterative stmt node
	TreeNode bool_node = node->children;	//bool_node = relational_op / logical_op / TK_NOT
	Seq list=getWhileVars(bool_node);		//get sequence of all the elements in while loop
	TreeNode stmt=node->children->next;		//get the stmt 
	//check the sequence over all stmt one by one
	while(stmt)	
	{
		if(checkVarChanges(list,stmt)==1)//if any one variable is changed,then return
			return 0;
		stmt=stmt->next;
	}
	return -1;
}

