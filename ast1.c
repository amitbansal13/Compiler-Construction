#include "parserDef.h"
#include "ast.h"

TreeNode createAST(TreeNode root)
{
	if(!root)return root;
	TreeNode children=root->children;
	int flag=0;
	while(children)
	{
		createAST(children);

		if(flag==0){
			ASThelper(children);	//this children may be free here
			children=root->children->next;
		}

		else
			children=children->next;
		flag=1;
	}
	return root;
}

void ASThelper(TreeNode node){
	printf("helper called\n");
	TreeNode par = node->parent;
	switch(node->rule_no){


		case 1:
		case 3:
		case 9:
		case 17:
		case 18:
		case 21:
		case 23:
		case 25:
		case 30:
		case 38:
		case 54:
		case 55:
		case 57:
		case 58:
		case 72:
			node=par->children;
			par->addr = node->addr;
			break;
		

		//********************* NULL CASES**************88

		case 4:
		case 8:
		case 16:
		case 19:
		case 24:
		case 26:
		case 29:
		case 31:
		case 39:
		case 43:
		case 56:
		case 59:
		case 69:
			node=par->children;
			//free(node->token_info);
			free(node);
			par->addr =NULL;
			break;

		//**************** Serially Mixed Cases ***************

		case 2:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;

		case 5:
			par->children = deleteN(par->children,5);
			par->children = deleteN(par->children,3);
			node=par->children;
			par->addr = node->addr;
			break;

		case 6:
			for(int i=5;i>=0;i--)
				if(i!=4)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		
		case 7:
			for(int i=5;i>=0;i--)
				if(i!=4)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		
		case 10:
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		 case 11:
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			free(node);
			break;
		
		case 12 ... 13:
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);//*****************DOUBT*************************
			//free(node);	//wont free since its terminal
			break;

		case 14:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			//free(node);
			break;

		case 15:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			free(node);
			break;

		case 20:
			par->children = deleteN(par->children,4);
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 22:
			par->children = deleteN(par->children,4);
			par->children = deleteN(par->children,2);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;

		case 27:
			par->children = deleteN(par->children,5);
			par->children = deleteN(par->children,2);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;

		case 28:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			free(node);
			break;
		
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			free(node);
			break;

		case 37:
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,1);
			node=par->children;
			par->addr = node->addr;
			break;

		case 40:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			//free(node);//***HERE too
			break;


		case 41:
			par->children = deleteN(par->children,6);
			par->children = deleteN(par->children,4);
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,1);
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 42://to be checked	
			for(int i=3;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			break;


		case 44:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			free(node);
			break;

		case 45:
			par->children = deleteN(par->children,6);
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,1);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 46:
			par->children = deleteN(par->children,4);
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,1);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 47:
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;


		case 48:
			par->addr=node->addr;
			break;
		
		case 49:
		case 50:
			for(int i=4;i>=0;i--)
				if(i!=2)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
	//		free(node->token_info);
			free(node);
			break;

		case 51:
		case 68:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
		//	free(node->token_info);
			free(node);//***HERE too
			break;

		case 52 ... 53:
		case 66 ... 67:
			par->addr = node->addr;
			break;

		case 60:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		
		case 61:
			par->addr=node->addr;
			free(node);
		case 62 ... 65:
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			//free(node);
			break;
		
		case 70:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			//free(node);
			break;
		
		case 71:
			par->children = deleteN(par->children,6);
			par->children = deleteN(par->children,4);
			par->children = deleteN(par->children,2);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 73:
			par->children = deleteN(par->children,3);
			par->children = deleteN(par->children,1);
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		
		case 74 ... 84:
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
		//	free(node);		//DOUBT
			break;
		
		case 85:
		case 86:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;
		
		case 87:
		case 90:
			node=par->children;
			//free(node->token_info);
			free(node);
			par->addr =NULL;
			break;
		
		case 88:
		case 89:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			//free(node->token_info);
			free(node);
			break;


		

		
		
		
		
	}
}

TreeNode deleteN(TreeNode head,int index){	//indexing from 0
	if(head==NULL){
		printf("nothing to deleteN\n");
		return head;
	}
	TreeNode temp = head;
	if(index==0){
		temp=head->next;
		//free(head->token_info);
		free(head);
		return temp;
	}
	TreeNode prev = head;
	while(index--){
		prev=temp;
		temp=temp->next;	
	}
	prev->next=temp->next;
//	free(temp->token_info);
	free(temp);
	return head;
}
