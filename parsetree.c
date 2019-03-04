#include "parser.h"
#include "parsetree.h"
#include "stack.h"

ParseTree initializeParseTree(void){
	ParseTree pt = (ParseTree)malloc(sizeof(struct parsetree));
	pt->root=createtreeNode(1,0);	//nonterminal , "program",index=0;
	return pt;
}

TreeNode createtreeNode(int tNt,int index){
	TreeNode n = (TreeNode)malloc(sizeof(struct treenode));
	n->next=NULL;
	n->children=NULL;
	n->index=index;
	n->tNt=tNt;
	n->parent=NULL;
	return n;
}
	
TreeNode addChildren(TreeNode node,grammar *rule){		//add the rules as children of node
	TreeNode newNode;
	link check;
	int T_index,nonT_index;
	if(rule!=NULL){
		if(isTerminal(rule->name)){
			check = lookup(terminals,rule->name,tokens);
            T_index = check->index;
			newNode = createtreeNode(0,T_index);
		}	
		else if(isNTerminal(rule->name)){
			check = lookup(nonTerminals,rule->name,nonterminals);
            nonT_index = check->index;
			newNode = createtreeNode(1,nonT_index);
		}
		newNode->parent=node;
		node->children=newNode;
	}
	TreeNode prev = newNode;
	grammar *temp = rule->next;
	while(temp!=NULL){
		if(isTerminal(temp->name)){
			check = lookup(terminals,temp->name,tokens);
            T_index = check->index;
			newNode = createtreeNode(0,T_index);
		}	
		else if(isNTerminal(temp->name)){
			check = lookup(nonTerminals,temp->name,nonterminals);
            nonT_index = check->index;
			newNode = createtreeNode(1,nonT_index);
		}
		newNode->parent=node;
		prev->next=newNode;
		temp=temp->next;
		prev=newNode;
	}
	return node;
}

void parseInputSourceCode(char *testFile){
	//HASHTABLE ALREADY INITIALIZED,GRAMMAR,FIRSTFOLLOW,PARSETABLE ALREADY CREATED

	FILE *fp = fopen(testFile,"r");

    if(fp==NULL){
    	printf("File not found\n");
		return;
	}

	//Initializing parsetree and Stack

	ParseTree tree = initializeParseTree();
	Stack s = createStack();
	Stack s2 = createStack();//helper stack
	
	//Pushing Dollar node to stack

	TreeNode Dollar  = createtreeNode(0,terminalsSize-1);

	s = push(s,Dollar);
	
	s = push(s,tree->root);

	//EVERYTHING INITIALIZED,now,get the tokens and parse the tokens extracted
	TreeNode top_stack,temp_treenode;

	TokenInfo lookAhead = nextToken();

	grammar *rule,*temp_rule;
	link check;
	int T_index,nonT_index;

	while(1){

		top_stack = top(s);

			
		if(top_stack==NULL){
			printf("error for now\n");
			return;
		}


		if(top_stack==Dollar && lookAhead == NULL){	//if top of stack is dollar and input consumed
			printf("successfully parsed\n");
			return;
		}

		printf("Parsing :%s\n",lookAhead->Token);

		if(strcmp(lookAhead->Token,"TK_COMMENT") == 0){
				lookAhead = nextToken();
				continue;
		}
			
		if(top_stack->tNt==0){	//if top of stack is terminal
			if(strcmp(tokens[top_stack->index],"eps")==0){
				s = pop(s);
				continue;
			}
			
			if(strcmp(tokens[top_stack->index],lookAhead->Token)==0){
				s = pop(s);
				lookAhead = nextToken();
			}
			else{
				printf("error for now in terminal\n");
				return;
			}
		}
		else{//if top of stack is nonterminal,pop the stack and push the rule in reverse
			check = lookup(terminals,lookAhead->Token,tokens);
            T_index = check->index;
			rule = pTable->tEntry[top_stack->index][T_index]->rule;

		//add the rules as children of the treenode at top of stack


			if(rule==NULL){
				printf("error \n");
				return ;
			}

			temp_treenode = top_stack;
			temp_treenode = addChildren(temp_treenode,rule);
			temp_treenode = temp_treenode->children;

			s = pop(s);

		//add the rules to stack in reverse

			while(temp_treenode!=NULL){
				s2 = push(s2,temp_treenode);
				temp_treenode = temp_treenode->next;
			}
			while(top(s2)!=NULL){
				temp_treenode = top(s2);
				s = push(s,temp_treenode);
				pop(s2);	
			}
		}
	}
}

void printParseTree(ParseTree ptree){
	if(ptree==NULL){
		printf("Tree not initialized\n");	
		return;
	}
	printf("***********PRINTING PARSE TREE ***************");

	printf("%s %s %s %s %s %s %s\n\n\n", "LEXEME","LINE","TOKEN","VALUE","PARENT","LEAF","NODE");

	printInOrder(ptree->root);
}

void printInOrder(TreeNode node){

}
