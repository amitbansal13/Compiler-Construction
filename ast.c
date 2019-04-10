#include "parserDef.h"
#include "ast.h"




//IMPORTANT************************************************************8
//need to change 45,46 because of booleanE(TK_CALL comes bcoz of that)



void createAST(TreeNode root){
	TreeNode children=root->children;
	int child_no=0;
	while(children)
	{
		if(children->tNt==1)//if non terminal,first recurse these
			createAST(children);

		if(children->rule_no==54 && child_no==0)//after term is calculated in arithmeticExp->term expPrime
			children->next->inh=children->addr;
		if(children->rule_no==55 && child_no==1)//after term is calculated in expPrime->lowPrecedence term expPrime
		{
			root->children->next->next->inh = root->children->addr;
			root->children->addr->children=root->inh;
			root->children->addr->children->next=root->children->next->addr;

	    }
		if(children->rule_no==57 && child_no==0)//after factor is calculated in term->factor termPrime
			root->children->next->inh = root->children->addr;
		
		if(children->rule_no==58 && child_no==1)//after factor is calculated in termPrime->highPrecedence factor termPrime
		{
			root->children->next->next->inh = root->children->addr;
			root->children->addr->children = root->inh;
			root->children->addr->children->next = root->children->next->addr;
		}
		children=children->next;
		child_no++;
	}
		ASThelper(root->children);	
	return ;
}

void ASThelper(TreeNode node){
	printf("helper rule %d\n",node->rule_no);
	TreeNode par = node->parent;
	TreeNode node0=node;
	TreeNode end=NULL,node1=NULL,node2=NULL,node3=NULL,node4=NULL,node5=NULL,node6=NULL,node7=NULL;
	if(node0)
		node1=node0->next;
	if(node1)
		node2=node1->next;
	if(node2)
		node3=node2->next;
	if(node3)
		node4=node3->next;
	if(node4)
		node5=node4->next;
	if(node5)
		node6=node5->next;
	if(node6)
		node7=node6->next;
	//printf("%p %p %p %p %p %p %p %p",par,node0,node1,node2,node3,node4,node5,node6);

	switch(node->rule_no){

		//*****************addr copy cases********************
		//A->a cases where a is important and A->B where B is also important
		//we just copy the addr in this case

		//*******22 such cases**********

		case 12:
		case 13:
		case 32 ... 36:
		case 51 ... 53:
		case 63 ... 66://updated
		case 70 ... 77:

			par->addr = node->addr;
			break;
		

		//********************* NULL CASES**************88
		//free that node and make parent children as NULL

		//************14 such cases*************
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
		case 80:
		case 83:
			free(node);
			par->children=NULL;
			//par->addr = NULL;
			break;

		//**************** Serially Mixed Cases ***************

		case 1:	//par=concat(node0.children,node1.addr),free(node0)

			end = getEndNode(node0->children);
			if(end==NULL){
				setParentChild(par,node1->addr);
				free(node0);
				break;
			}
			end->next=node1->addr;
			node1->addr->next=NULL;	//since it might have siblings we dont need now
			setParentChild(par,node0->children);
			free(node0);
			break;

		case 2:		//delete(n0,n2)
			free(node0);free(node2);
			node1->next=NULL;
			par->children=node1;
			break;

		case 3:	//par=concat(node0.addr,node1.children),free(node1)
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			break;

		case 5://par=concat(node0.addr,node1.addr,node2.addr,node4.addr),free(n3,n5)
			node0->addr->next = node1->addr;
			node1->addr->next = node2->addr;
			node2->addr->next = node4->addr;
			node4->addr->next=NULL;
			setParentChild(par,node0->addr);
			free(node5);free(node3);
			break;

		case 6:
		case 7://par->children = node4->children,free(node4)
			free(node0);free(node1);free(node2);free(node3);free(node5);
			setParentChild(par,node4->children);
			free(node4);
			break;
		
		case 9://par=concat(node0.addr,node1.addr,node2.children),free(n0,n2)
			node0->addr->next = node1->addr;
			node1->addr->next = node2->children;
			setParentChild(par,node0->addr);
			free(node0);free(node2);
			break;

		case 10:
		case 11://par->addr = node0->addr,free(node0),par->children=NULL
			par->addr = node0->addr;
			free(node0);
			par->children=NULL;
			break;
		
		case 14:	//par->addr=node1->addr,free(node0),par->children=NULL
			par->addr=node1->addr;
			free(node0);
			par->children=NULL;
			break;

		case 15:	//par->children=node1->children,free(node1,node0)
			par->children=node1->children;
			setParentChild(par,node1->children);
			free(node0);
			free(node1);
			break;
		case 17://par=concat(node0.addr,node1.addr,node2.children,node3.addr),free(node2)
            node0->addr->next = node1->addr;
            node1->addr->next = node2->children;
			end = getEndNode(node2->children);
			if(end==NULL)
				node1->addr->next=node3->addr;
			else 
				end->next=node3->addr;
			node3->addr->next=NULL;
            setParentChild(par,node0->addr);
			free(node2);
            break;

		case 18:	//par->children=concat(node0.addr,node1.children),free(node1)
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			break;

		case 20:	//par->children=concat(node1.addr,node2.children),free(node2)
			node1->addr->next=node2->children;
			setParentChild(par,node1->addr);
			free(node2);
			free(node0);
			free(node3);
			free(node4);
			break;

		case 21:	//par->children=concat(node0.addr,node1.addr,node2.children),free(node2)
			node0->addr->next=node1->addr;
			node1->addr->next=node2->children;
			setParentChild(par,node0->addr);
			free(node2);
			break;
		
		case 22://par->children=concat(node1.addr,node3.addr),free(node1)
            node1->addr->next = node3->addr;
			node3->addr->next=NULL;
			setParentChild(par,node1->addr);
			free(node4);
			free(node2);
			free(node1);
			free(node0);
            break;

		case 23:	//par->children=concat(node0.addr,node1.children),free(node1)
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			break;

		case 25:	//par->children=concat(node0.addr,node1.children),free(node1)
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			break;

		case 27:	//par->children=concat(node1.addr,node3.addr,node4->addr),free(node1,node4)
			node1->addr->next=node3->addr;
			node3->addr->next=node4->children;
			free(node4);free(node1);free(node0);free(node2);free(node5);
			setParentChild(par,node1->addr);
			break;

		case 28:	//par->addr=node1->addr,free(node0)
			par->addr=node1->addr;
			free(node0);
			break;

		case 30:	//par->children=concat(node0.addr,node1.children),free(node1),free(node0);
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			free(node0);
			break;

		case 37://par->children=concat(node0.addr,node2.addr)
            node0->addr->next = node2->addr;
			node2->addr->next=NULL;
			setParentChild(par,node0->addr);
			free(node3);
			free(node1);
            break;

		case 38://par->children=concat(node0.addr,node1.children),free(node1)
            node0->addr->next = node1->children;
			setParentChild(par,node0->addr);
			free(node1);
            break;

		case 40:	//par->addr=node1->addr,free(node0)
			par->addr=node1->addr;
			free(node0);
			par->children=NULL;
			break;

		case 41://par->children=concat(node0.addr,node2.addr,node5.addr)
            node0->addr->next = node2->addr;
			node2->addr->next=node5->addr;
			node5->addr->next=NULL;
			setParentChild(par,node0->addr);
			free(node6);
			free(node4);
			free(node3);
			free(node1);
            break;
		
		case 42:	//par->children=node1.children,free(node1)
			setParentChild(par,node1->children);
			free(node3);
			free(node2);
			free(node1);
			free(node0);
			break;

		case 44:	//par->children=concat(node1.children),free(node1)
			setParentChild(par,node1->children);
			free(node2);
			free(node1);
			free(node0);
			break;






			//IMPORTANT************************************************************8
			//need to change 45,46 because of booleanE(TK_CALL comes bcoz of that)
			//changed




		case 45:	//par->children=concat(node2.addr,node4.addr,node5.children),free(node2,node4,node5)
			node2->addr->next=node4->addr;
			node4->addr->next=node5->children;
			//node4->addr->next=NULL;
			setParentChild(par,node2->addr);
			free(node6);
			free(node5);
			free(node4);
			free(node3);
			free(node2);
			free(node1);
			free(node0);
			break;
		
		case 46:	//par->children=concat(node2.addr,node5.addr,node6.children,node7.addr),free(node2,node5,node6)
			node2->addr->next=node5->addr;
			node5->addr->next=node6->children;
			end = getEndNode(node6->children);
			if(end==NULL)
				node5->addr->next=node7->addr;
			else 
				end->next=node7->addr;
			node7->addr->next=NULL;
			setParentChild(par,node2->addr);
			free(node6);
			free(node5);
			free(node4);
			free(node3);
			free(node2);
			free(node1);
			free(node0);
			break;

		case 47:	//par->children=concat(node1.addr,node2.children),free(node1,node2);
			node1->addr->next=node2->children;
			setParentChild(par,node1->addr);
			free(node3);
			free(node2);
			free(node1);
			free(node0);
			break;

		case 48://par->children=NULL,free(node0)
			free(node0);
			par->children=NULL;
			break;
		
		case 49://par->children=concat(node0.addr,node2.addr)
		case 50:
            node0->addr->next = node2->addr;
			node2->addr->next=NULL;
			setParentChild(par,node0->addr);
			free(node4);
			free(node3);
			free(node1);
            break;
			//correct and commented for debug
		case 54://par.addr=node1.syn
			par->addr=node1->syn;
			break;
			
		case 55://par.syn=node2.syn
			par->syn=node2->syn;
			break;

		case 56://par.syn=par.inh
			par->syn=par->inh;
			break;

		case 57://par.addr=node1.syn
			par->addr=node1->syn;
			break;

		case 58://par.syn=node2.syn
			par->syn=node2->syn;
			break;

		case 59://par.syn=par.inh
			par->syn=par->inh;
			break;
		
		/*
		case 54 ... 59:	//debugging
			par->children=NULL;
			break;
		*/

		case 60:	//par->addr=node1.addr,free(node1)
			par->addr=node1->addr;
			par->children=NULL;
			free(node2);
			free(node1);
			free(node0);
			break;
		
		case 61:	//par->addr=node0.addr,free(node0)
			par->addr=node0->addr;
			par->children=NULL;
			free(node0);
			break;
		
		case 67://par.addr = node3.addr,node3.addr.children=makenode(node1.addr,node5.addr),free(node3,node1,node5);
			par->addr=node3->addr;
			node1->addr->next=node5->addr;
			node5->addr->next=NULL;
			node3->addr->children=node1->addr;
			par->children=NULL;
			free(node6);
			free(node5);
			free(node4);
			free(node3);
			free(node2);
			free(node1);
			free(node0);
			break;
		
		case 68://par.addr = node1.addr,node1.addr.children=makenode(node0.addr,node2.addr),free(node0,node1,node2);
			par->addr=node1->addr;
			node0->addr->next=node2->addr;
			node2->addr->next=NULL;
			setParentChild(node1->addr,node0->addr);
			par->children=NULL;
			free(node2);
			free(node1);
			free(node0);
			break;

		case 69://par.addr = node0.addr,node0.addr.children=node2->addr,free(node1,node2,node3);
			par->addr=node0->addr;
			node0->addr->children=node2->addr;
			node2->addr->next=NULL;
			par->children=NULL;
			free(node3);
			free(node2);
			free(node1);
			break;
		
		/*
		case 67 ... 69:
			par->children=NULL;
			break;
		*/
		case 78:	//par->children=node1.children,free(node1)
		case 79:
			setParentChild(par,node1->children);
			free(node2);
			free(node1);
			free(node0);
			break;
		
		case 81:	//par->children=concat(node0.addr,node1.children),free(node1)
			node0->addr->next=node1->children;
			setParentChild(par,node0->addr);
			free(node1);
			break;

		case 82:	//par->children=node1.children,free(node1)
			setParentChild(par,node1->children);
			free(node1);
			free(node0);
			break;
	}
}
/*
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
*/
void setParentChild(TreeNode parent,TreeNode childList){
	parent->children=childList;
	TreeNode temp = childList;
	while(temp!=NULL){
		temp->parent=parent;
		temp=temp->next;
	}
}


TreeNode getEndNode(TreeNode node){
	if(node==NULL)
		return NULL;
	TreeNode temp = node;
	while(temp->next!=NULL)
		temp=temp->next;
	return temp;
}	

