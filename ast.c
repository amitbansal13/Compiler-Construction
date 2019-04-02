#include "parserDef.h"
#include "ast.h"

TreeNode createAST(TreeNode root)
{
	if(!root)return root;
	TreeNode children=root->children;
	while(children)
	{
		createAST(children);

		ASThelper(children);
		children=children->next;
	}
	ASThelper(root);
	return root;
}

void ASThelper(TreeNode node){
	TreeNode par = node->parent;
	switch(node->rule_no){
		case 2:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			
			break;
		case 6:
			for(int i=5;i>=0;i--)
				if(i!=4)
					par->children = deleteN(par->children,i);
			break;
		case 7:
			for(int i=5;i>=0;i--)
				if(i!=4)
					par->children = deleteN(par->children,i);
			break;
		case 10:
			break;
		case 11:
			break;
		case 15:
			par->children = deleteN(par->children,0);
			break;
		case 28:
			par->children = deleteN(par->children,0);
			break;
		case 32:
			break;
		case 33:
			break;
		case 34:
			break;
		case 35:
			break;
		case 36:
			break;
		/*DOUBT
		case 42:	
			for(int i=3;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			break;
		*/
		case 44:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			break;
		case 49:
			for(int i=4;i>=0;i--)
				if(i!=2)
					par->children = deleteN(par->children,i);
			break;
		case 50:
			for(int i=4;i>=0;i--)
				if(i!=2)
					par->children = deleteN(par->children,i);
			break;
		case 60:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			break;
			
		case 61 ... 65:
			break;
		case 70:
			par->children = deleteN(par->children,0);
			break;
		case 73:
			par->children = deleteN(par->children,1);
			break;
		case 74 ... 84:
			break;
		case 85:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			break;
		case 86:
			for(int i=2;i>=0;i--)
				if(i!=1)
					par->children = deleteN(par->children,i);
			break;
		case 89:
			par->children = deleteN(par->children,0);
			break;
	}
}

TreeNode deleteN(TreeNode head,int index){	//indexing from 0
	TreeNode temp = head;
	if(index==0){
		temp=head->next;
		free(head->token_info);
		free(head);
		return temp;
	}
	TreeNode prev = head;
	while(index--){
		prev=temp;
		temp=temp->next;	
	}
	prev->next=temp->next;
	free(temp->token_info);
	free(temp);
	return head;
}	
