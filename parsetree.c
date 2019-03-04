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
	n->token_info=NULL;
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

ParseTree parseInputSourceCode(char *testFile){
	//HASHTABLE ALREADY INITIALIZED,GRAMMAR,FIRSTFOLLOW,PARSETABLE ALREADY CREATED

	FILE *fp = fopen(testFile,"r");

    if(fp==NULL){
    	printf("File not found\n");
		return NULL;
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
			return tree;
		}


		if(top_stack==Dollar && lookAhead == NULL){	//if top of stack is dollar and input consumed
			printf("successfully parsed\n");
			return tree;
		}

		printf("Parsing :%s\n",lookAhead->Token);

		if(strcmp(lookAhead->Token,"TK_COMMENT") == 0){
				lookAhead = nextToken();
				continue;
		}
			
		if(top_stack->tNt==0){	//if top of stack is terminal
			if(strcmp(tokens[top_stack->index],"eps")==0){
				s = pop(s);
				top_stack->token_info=lookAhead;	//store the tokenInfo,doubt if it copies
				continue;
			}
			
			if(strcmp(tokens[top_stack->index],lookAhead->Token)==0){
				top_stack->token_info=lookAhead;	//store the tokenInfo
				s = pop(s);
				lookAhead = nextToken();
			}
			else{
				printf("error for now in terminal\n");
				return tree;
			}
		}
		else{//if top of stack is nonterminal,pop the stack and push the rule in reverse
			check = lookup(terminals,lookAhead->Token,tokens);
            T_index = check->index;
			rule = pTable->tEntry[top_stack->index][T_index]->rule;

		//add the rules as children of the treenode at top of stack


			if(rule==NULL){
				printf("error \n");
				return tree ;
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
	return tree;
}

void printParseTree(ParseTree ptree,char *outfile){
	if(ptree==NULL){
		printf("Tree not initialized\n");	
		return;
	}
	printf("***********PRINTING PARSE TREE ***************");

	printf("%s %s %s %s %s %s %s\n\n\n", "LEXEME","LINE","TOKEN","VALUE","PARENT","LEAF","NODE");

	printInOrder(ptree->root,outfile);
}

void printInOrder(TreeNode node,char *outfile){
	if(node==NULL)
		return;

	TreeNode temp_node = node->children;

	if(temp_node!=NULL){	//if it has children
			
		//printing left child
		printInOrder(temp_node,outfile);
		
		//printing node;
		
		printNode(node,outfile);
		//printing right childs in order
		temp_node=temp_node->next;

		while(temp_node!=NULL){
			printInOrder(temp_node,outfile);
			temp_node=temp_node->next;
		}
	}		
	else
		printNode(node,outfile);
		//printing node;

}	

void printNode(TreeNode node,char *outfile){	//file already opened

	FILE *f = fopen(outfile,"a");

	//did not do value type now

	bool isLeaf=false,isTerminal=false,isRoot=false;	
	int val_type=-1;	//-1=>error,0=>int,1=>float

	if(node->tNt==-1){//errorcase	TK_ERROR

	}

	if(node->children==NULL)		//if leaf node
		isLeaf=true;

	if(node->tNt==0)		//if it contains terminal symbol
		isTerminal=true;
	
	if(node->parent==NULL)		//if this node is the root
		isRoot=true;

	TreeNode parent = node->parent;

	if(isLeaf){	//for leaf node
		if(isTerminal==false){
			//leaf node is non terminal => error case
		}	
		else{
			if(isRoot)
				fprintf(f,"%21s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,"VALUE","ROOT","yes","----");

			else
				fprintf(f,"%21s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,"VALUE",nonterminals[parent->index],"yes","----");
			//print it;
		}
	}

	else{	//will be a nonterminal only
		if(isTerminal==true){
			//not possible
		}
		if(isRoot)
				fprintf(f,"%21s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","------","-----","-----","VALUE","ROOT","no","----");
			//root node print
		else
				fprintf(f,"%21s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","----","-----","------","VALUE",nonterminals[parent->index],"no",nonterminals[node->index]);
			//nonterminal print	
	}
	fclose(f);
}


