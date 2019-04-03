#include "parserDef.h"
#include "ast.h"

void createAST(TreeNode root,int flag)
{
	if(!root)return ;
	TreeNode children=root->children;
	int chld_no=1;
	TreeNode next_child;
	while(children)
	{
		next_child = children->next;	//need this since children can get freed in next stmt
		if(chld_no==1)
			createAST(children,0);
		else
			createAST(children,1);


		children=next_child;
		chld_no++;
	}
	if(flag==0 && root->rule_no!=-1)
		ASThelper(root);	
	return ;
}

void ASThelper(TreeNode node){
	TreeNode par = node->parent;
	switch(node->rule_no){

		//*****************addr copy cases********************

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
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 57:
		case 58:
		case 66:
		case 67:
		case 68:
		case 72:
		case 88:
			par->addr = node->addr;
			break;
		

		//********************* NULL CASES**************88
		//free that node and make parent addr and children as NULL
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
		case 87:
		case 90:
			free(node);
			par->children=NULL;
			par->addr =NULL;
			break;

		//**************** Serially Mixed Cases ***************

		case 2:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
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
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 7:
			for(int i=5;i>=0;i--)
				if(i!=4)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 10:
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		 case 11:
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 12 ... 13:
			node=par->children;
			par->addr = node->addr;
			break;

		case 14:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			break;

		case 15:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
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
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
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
			setParentChild(par,node->children);
			free(node);
			break;


		case 44:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
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
			setParentChild(par,node->children);
			free(node);
			break;

		case 60:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 61:
			par->addr=node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		case 62 ... 65:
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 70:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
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
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 74 ... 84:
			node=par->children;
			par->addr = node->addr;
			break;
		
		case 85:
		case 86:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
			free(node);
			break;
		
		case 89:
			par->children = deleteN(par->children,0);
			node=par->children;
			par->addr = node->addr;
			setParentChild(par,node->children);
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
		free(head);
		return temp;
	}
	TreeNode prev = head;
	while(index--){
		if(temp==NULL){
			printf("nothing to delete1\n");
			return head;
		}
		prev=temp;
		temp=temp->next;	
	}
		if(temp==NULL){
			printf("nothing to delete2\n");
			return head;
		}
	prev->next=temp->next;
	free(temp);
	return head;
}

void setParentChild(TreeNode parent,TreeNode childList){
	parent->children=childList;
	TreeNode temp = childList;
	while(temp!=NULL){
		temp->parent=parent;
		temp=temp->next;
	}
}
