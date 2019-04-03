/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#include "parserDef.h"
#include "parser.h"
#include "HashTable.h"
#include "stack.h"

//DOLLAR AND eps in tokens ie terminals

char *tokens[]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL","TK_COMMA", "TK_SEM","TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE","eps","DOLLAR"};  
char *nonterminals[]={
	"program",
	"mainFunction",
	"otherFunctions",
	"function",
	"input_par",
	"output_par",
	"parameter_list",
	"dataType",
	"primitiveDatatype",
	"constructedDatatype",
	"remaining_list",
	"stmts",
	"typeDefinitions",
	"typeDefinition",
	"fieldDefinitions",
	"fieldDefinition",
	"moreFields",
	"declarations",
	"declaration",
	"global_or_not",
	"otherStmts",
	"stmt",
	"assignmentStmt",
	"iterativeStmt",
	"conditionalStmt",
	"ioStmt",
	"funCallStmt",
	"singleOrRecId",
	"new_24",
	"outputParameters",
	"inputParameters",
	"elsePart",
	"allVar",
	"arithmeticExpression",
	"expPrime",
	"term",
	"termPrime",
	"factor",
	"highPrecedenceOperator",
	"lowPrecedenceOperators",
	"all",
	"temp",
	"booleanExpression",
	"var",
	"logicalOp",
	"relationalOp",
	"returnStmt",
	"optionalReturn",
	"idList",
	"more_ids"};


Table terminals=NULL;//HashTable to store Terminals
Table nonTerminals=NULL;//HashTable to store non Terminals

void initializeTNT()
//initializes both Terminals and Non Terminals hash tables
{
	int i=0;
	if(terminals==NULL){
		terminals=create(97);
		for(i=0;i<terminalsSize;i++)//54 is terminals size
			insert(terminals,tokens,i);
	}
	if(nonTerminals==NULL){
		nonTerminals=create(97);
		for(i=0;i<nonTerminalsSize;i++)
			insert(nonTerminals,nonterminals,i);
	}
}


		//************GRAMMAR**************

grammar* newNode(char *temp,int line_no)			//new grammar node
//returns a new grammar node
{
	grammar* g=(grammar*)malloc(sizeof(grammar));
	strcpy(g->name,temp);
	g->more=NULL;
	g->next=NULL;
	g->rule_no=line_no;
	return g;
}

grammar* makeNewRule(FILE* fp,int d,int line_no)		//makes a new grammar rule and returns grammar*
//makes a new Rule by scanning d space separated strings in a line
{
	int i=0;
	char temp[30];
	fscanf(fp,"%s",temp);
	grammar* head=newNode(temp,line_no),*curr;
	curr=head;
	for(i=0;i<d-1;i++)
	{
		fscanf(fp,"%s",temp);
		curr->next=newNode(temp,line_no);
		curr=curr->next;
	}
	return head;
}

Grammar* makeGrammar(char* fileName){			// making the Grammar data structures
	FILE* f=fopen(fileName,"r");
	if(f==NULL)
	{
		printf("File %s could not be opened\n",fileName);
		return NULL;
	}
	
	initializeTNT();
	int line_no=1;

	Grammar *g=(Grammar *)malloc(sizeof(Grammar));
	g->arr=(grammar**)malloc(sizeof(grammar*)*nonTerminalsSize);
	g->size=nonTerminalsSize;//initial size for array of Grammar rules
	grammar** arr=g->arr;//using arr as temp pointer
	
	int d=0,i=0;
	for(i=0;i<nonTerminalsSize;i++)
	//	arr[i]=(grammar*)malloc(sizeof(grammar));
		arr[i]=NULL;
	char temp[30];
	link check=NULL;
	while(fscanf(f,"%s %d",temp,&d)!=-1)//scan till EOF
	{
	//	printf("%s %d\n",temp,d);
		check=lookup(nonTerminals,temp,nonterminals);
		grammar* head;
	//	if(arr[check->index]->more==NULL)//if this is the first rule to be added 
	//		arr[check->index]->more=makeNewRule(fp,d);
		if(arr[check->index]==NULL){//if this is the first rule to be added 
			arr[i]=(grammar*)malloc(sizeof(grammar));
			arr[check->index]=makeNewRule(f,d,line_no);
		}
		else
		{
			head=makeNewRule(f,d,line_no);
			head->more=arr[check->index]->more;
			arr[check->index]->more=head;
		}
		line_no++;
	}
	fflush(f);
	return g;
}

void printGrammar(Grammar *g)		//prints the already made grammar
{
	printf("\n\n********Printing Grammar ******\n\n");
    int size=g->size;
    grammar** arr=g->arr,*temp,*temp1,*temp2;
    int i=0;
	int rule_no;
    for(i=0;i<size;i++)
    {
        temp=arr[i];
        while(temp)
        {
            temp1=temp;
            printf("%s->",nonterminals[i]);
            while(temp1)
            {
			rule_no=temp1->rule_no;
            printf("%d:",rule_no);
                printf("%s ",temp1->name);
                temp1=temp1->next;
            }
            printf("\n");
            temp=temp->more;
        }
    }
} 




		//***************FIRSTANDFOLLOW***********************




bool isTerminal(char *text){
	link check = lookup(terminals,text,tokens);
	if(check==NULL)
		return false;
	return true;
}

bool isNTerminal(char *text){
	link check = lookup(nonTerminals,text,nonterminals);
	if(check==NULL)
		return false;
	return true;
}

ffset initializeFF(){ 	//initializes firt follow sets to NULL
	ffset fset = (ffset)malloc(sizeof(struct ff)*nonTerminalsSize);
	for(int i=0;i<nonTerminalsSize;i++){
		fset[i].first=NULL;
		fset[i].follow=NULL;
	}
	fset[0].follow = addToSet(fset[0].follow,"DOLLAR");
	return fset;
}

FF addToSet(FF set,char *text){	//adds text  to set FF
	if(set==NULL){
		set = (FF)malloc(sizeof(struct firstfollow));
		strcpy(set->elem,text);
		set->next=NULL;
		return set;
	}
	FF temp = set;
	while(temp!=NULL){
		if(strcmp(temp->elem,text)==0)
			return set;
		temp=temp->next;
	}
	temp = (FF)malloc(sizeof(struct firstfollow));
	strcpy(temp->elem,text);
	temp->next=set;
	return temp;
}


bool checkEps(int index,Grammar *g){//returns true if "eps" found in g->arr[index] mores
	grammar *temp = g->arr[index];
	while(temp!=NULL){
		if(strcmp(temp->name,"eps")==0)
			return true;
		temp=temp->more;
	}
	return false;
}
	
void findFirst(int index_orig,int index,Grammar *g,ffset fset){	//finds first of the index_orig of nonTs
	if(index>=nonTerminalsSize){
		printf("Error\n");
		return;
	}
	grammar *temp = g->arr[index];
	grammar *temp1;
	link check;int new_index;bool b;
	int eps_flag=0;
	while(temp!=NULL){
		if(strcmp(temp->name,"eps")!=0 && isTerminal(temp->name))//if terminal,add to the first set
			fset[index_orig].first = addToSet(fset[index_orig].first,temp->name);
			//addFirst(index_orig,temp->name);

		else if(isNTerminal(temp->name)){		//if NT,
			check = lookup(nonTerminals,temp->name,nonterminals);
			new_index = check->index;
			findFirst(index_orig,new_index,g,fset);
			b = checkEps(new_index,g);		//if NT has an eps,go till all eps found
			temp1=temp;
			while(b==true){
				temp1=temp1->next;
				if(temp1==NULL)
					break;
				if(isTerminal(temp1->name)){		//if terminal,add to the first set
					//addFirst(index_orig,temp1->name);
					fset[index_orig].first = addToSet(fset[index_orig].first,temp1->name);
					break;
				}
				else if(isNTerminal(temp1->name)){		//if NT,
					check = lookup(nonTerminals,temp1->name,nonterminals);
					new_index = check->index;
					findFirst(index_orig,new_index,g,fset);
					b = checkEps(new_index,g);
				}
			}
		}
		temp=temp->more;
	}
	if(index == index_orig){
			if(checkEps(index,g) || fset[index].first==NULL)
			//	addFirst(index_orig,"eps");
				fset[index_orig].first = addToSet(fset[index_orig].first,"eps");
	}
}


void printFirstnFollow(ffset fset){					//print all the first's
	printf("\n\n*********Printing First sets**************\n\n");
	FF temp;
	for(int i=0;i<nonTerminalsSize;i++){
		printf("%s->",nonterminals[i]);
		temp=fset[i].first;
		while(temp!=NULL){
			printf("%s ",temp->elem);
			temp=temp->next;
		}
		printf("\n");
	}

	printf("\n\n\n*******Printing Follow sets***********\n\n\n");
	for(int i=0;i<nonTerminalsSize;i++){
		printf("%s->",nonterminals[i]);
		temp=fset[i].follow;
		while(temp!=NULL){
			printf("%s ",temp->elem);
			temp=temp->next;
		}
		printf("\n");
	}
}

ffset computeFirstnFollow(Grammar *g){		//compute both first and follow
	initializeTNT();
	ffset fset = initializeFF();
	for(int i=0;i<nonTerminalsSize;i++)
		findFirst(i,i,g,fset);
	int follow_changes=1;
	while(follow_changes!=0)
		follow_changes = computeFollow(g,fset);
	return fset;
}

bool checkSet(FF set,char *elem){	//checks if elem exists already in FF set
	FF temp = set;
	while(temp!=NULL){
		if(strcmp(temp->elem,elem)==0)
			return true;
		temp=temp->next;
	}
	return false;
}

FF addSets(FF set1,FF set2,int *no_added){//Adds all elements of FF set2 to set 1,returns set1
	FF temp2 = set2;
	while(temp2!=NULL){

		if(strcmp(temp2->elem,"eps")==0){		//Dont add eps
			temp2=temp2->next;
			continue;
		}

		if(checkSet(set1,temp2->elem)==false){
			*no_added+=1;
			set1 = addToSet(set1,temp2->elem);
		}
		temp2=temp2->next;
	}
	return set1;
}
			
int computeFollow(Grammar *g,ffset fset){
	grammar *rule,*temp1,*temp2;

	int change_flag=0;
	link check;
	int nonT_index,index2;
	for(int i=0;i<nonTerminalsSize;i++){

		rule = g->arr[i];

		while(rule!=NULL){		//iterate all rules of that non terminal

			temp1=rule;

			while(temp1!=NULL){		//iterate all production elements on by one of that rule

				if(isTerminal(temp1->name)){	//if terminal,no need to calc its follow

					temp1=temp1->next;

					continue;
				}

			/* will calc follow of temp1 */
							
				check = lookup(nonTerminals,temp1->name,nonterminals);
				nonT_index = check->index;

			//got index of the non terminal whose follow to be calc

				temp2=temp1->next;	
				while(temp2!=NULL){
					if(isTerminal(temp2->name)){	//if followed by a terminal,add it if not already
	
						if(checkSet(fset[nonT_index].follow,temp2->name) == false ){

						fset[nonT_index].follow = addToSet((fset[nonT_index].follow),temp2->name);
							change_flag+=1;
						}
						break;
	
					}
					else if(isNTerminal(temp2->name)){
	
						check = lookup(nonTerminals,temp2->name,nonterminals);
						index2 = check->index;
			fset[nonT_index].follow=addSets(fset[nonT_index].follow,fset[index2].first,&change_flag);
	
						if(checkEps(index2,g)==false)	// if this NT doesnt give epsilon,done
							break;
					}
					temp2=temp2->next;
				}
				if(temp2==NULL){
			fset[nonT_index].follow=addSets(fset[nonT_index].follow,fset[i].follow,&change_flag);
				}
				temp1=temp1->next;	
			}
			rule=rule->more;	
		}
	}	
	return change_flag;
}









		//***************PARSETABLE*******************









PT* initializePT(){
	PT *pTable = (PT*)malloc(sizeof(PT));
	for(int i=0;i<nonTerminalsSize;i++){
		for(int j=0;j<terminalsSize;j++){
			pTable->tEntry[i][j]=(elem*)malloc(sizeof(elem));
			pTable->tEntry[i][j]->type=-1;	//since -1->error,0->grammar exist,1->syn,2->accept
			pTable->tEntry[i][j]->rule=NULL;	
		}
	}
	return pTable;
}
			
void createParseTable(Grammar *g,ffset fset,PT *pTable){
	pTable->tEntry[0][terminalsSize-1]->type=2;		//2 is accept state	
	for(int i=0;i<nonTerminalsSize;i++){
		

			//iterating all the grammar rules
		grammar *rule = g->arr[i];

		link check;

		grammar *temp_rule = rule;
		FF temp_f;

		grammar *temp2;
		int eps_flag=0,T_index,nonT_index;
		while(temp_rule!=NULL){

			temp2 = temp_rule;			//need to traverse this rule if NT gives eps
				
			while(temp2!=NULL){

	
				if(isNTerminal(temp2->name)){
					check = lookup(nonTerminals,temp2->name,nonterminals);
					nonT_index = check->index;
				
					//if first set of nonT_index has eps,need to traverse rule continuation
	
					FF first_set = fset[nonT_index].first;
					temp_f = first_set;
					eps_flag=0;
					while(temp_f!=NULL){
						if(strcmp(temp_f->elem,"eps")==0){
							eps_flag=1;
						}
						else{
							check = lookup(terminals,temp_f->elem,tokens);
							T_index = check->index;
							if(pTable->tEntry[i][T_index]->rule!=NULL)
								printf("Multiple rules clashing in Entry[%s][%s]\n",nonterminals[i],tokens[T_index]);
							pTable->tEntry[i][T_index]->type=0;// 0 is grammar exists
						    pTable->tEntry[i][T_index]->rule=temp_rule;	
						}
						temp_f=temp_f->next;
					}
					if(eps_flag==1){
						temp2=temp2->next;
						continue;
					}
					else
						break;
				}

				else if(isTerminal(temp2->name)){	//means rule->name is in first of nonterminals[i]		
					if(strcmp(temp2->name,"eps") == 0){	//wont get anything after eps
	
				//if eps,replace with this rule if any terminal in follow set of this nonterminsl
	
						for(int j=0;j<terminalsSize;j++){
							if(checkSet(fset[i].follow,tokens[j]) == true){
								if(pTable->tEntry[i][j]->rule!=NULL)
									printf("Multiple rules clashing in Entry[%d][%d]\n",i,j);
								pTable->tEntry[i][j]->type=0;	
							    pTable->tEntry[i][j]->rule=temp_rule;	
							}
						}
						break;
					}
	
			//if other terminals,replace with this rule only
	
					else{
							check = lookup(terminals,temp2->name,tokens);
							T_index = check->index;
							if(pTable->tEntry[i][T_index]->rule!=NULL)
								printf("Multiple rules clashing in Entry[%s][%s]\n",nonterminals[i],tokens[T_index]);
							pTable->tEntry[i][T_index]->type=0;
						    pTable->tEntry[i][T_index]->rule=temp_rule;	
						break;	//if got a terminal,always break
					}
				}
			}
			temp_rule=temp_rule->more;
		}
		if(checkSet(fset[i].first,"eps") ==false){ 	//if doesnt have eps in first,get syn entries
			temp_f = fset[i].follow;
			while(temp_f!=NULL){
				check = lookup(terminals,temp_f->elem,tokens);
				T_index = check->index;
				if(pTable->tEntry[i][T_index]->type==-1)
					pTable->tEntry[i][T_index]->type=1;//1 is for syn
				temp_f = temp_f->next;
			}
		}
	}
}

void printParseTable(PT *pTable){
		printf("\n\n");
	for(int i=0;i<nonTerminalsSize;i++){
		for(int j=0;j<terminalsSize;j++){
			if(pTable->tEntry[i][j]->type ==-1)//error case
				continue;
			if(pTable->tEntry[i][j]->type ==2){	//accept case
				printf("pEntry[%s][%s]:",nonterminals[i],tokens[j]);
				printf("accept\n\n");
				continue;
			}
			if(pTable->tEntry[i][j]->type ==1){	//SYN case
				printf("pEntry[%s][%s]:",nonterminals[i],tokens[j]);
				printf("SYN\n\n");
				continue;
			}
			printf("pEntry[%s][%s]:",nonterminals[i],tokens[j]);
		//	printf("index:%d \n",pTable->tEntry[i][j]->type);
		//	printf("\nrule:");
			grammar *temp = pTable->tEntry[i][j]->rule;
			printf("\n%s-> ",nonterminals[i]);
			while(temp!=NULL){
			printf("%s ",temp->name);
				temp=temp->next;
			}
		printf("\n\n");
		}
	}
}


		//******************PARSETREE*******************






ParseTree initializeParseTree(void){
	ParseTree pt = (ParseTree)malloc(sizeof(struct parsetree));
	pt->root=createtreeNode(1,0,-1);	//nonterminal , "program",index=0;
	return pt;
}

TreeNode createtreeNode(int tNt,int index,int rule_no){
	TreeNode n = (TreeNode)malloc(sizeof(struct treenode));
	n->next=NULL;
	n->children=NULL;
	n->index=index;
	n->tNt=tNt;
	n->token_info=NULL;
	n->parent=NULL;
	n->rule_no=rule_no;
    n->addr=n->syn=n->inh=n;
	return n;
}
	
TreeNode addChildren(TreeNode node,grammar *rule){		//add the rules as children of node
	TreeNode newNode;
	link check;
	int T_index,nonT_index;
	int rule_no = rule->rule_no;
	if(rule!=NULL){
		if(isTerminal(rule->name)){
			check = lookup(terminals,rule->name,tokens);
            T_index = check->index;
			newNode = createtreeNode(0,T_index,rule_no);
		}	
		else if(isNTerminal(rule->name)){
			check = lookup(nonTerminals,rule->name,nonterminals);
            nonT_index = check->index;
			newNode = createtreeNode(1,nonT_index,rule_no);
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
			newNode = createtreeNode(0,T_index,rule_no);
		}	
		else if(isNTerminal(temp->name)){
			check = lookup(nonTerminals,temp->name,nonterminals);
            nonT_index = check->index;
			newNode = createtreeNode(1,nonT_index,rule_no);
		}
		newNode->parent=node;
		prev->next=newNode;
		temp=temp->next;
		prev=newNode;
	}
	return node;
}

ParseTree parseInputSourceCode(char *testFile,PT *pTable,bool *parseError){
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

	TreeNode Dollar  = createtreeNode(0,terminalsSize-1,-1);

	s = push(s,Dollar);
	
	s = push(s,tree->root);

	//EVERYTHING INITIALIZED,now,get the tokens and parse the tokens extracted
	TreeNode top_tree,temp_treenode;

	TokenInfo lookAhead = nextToken();

	grammar *rule,*temp_rule;
	link check;
	int T_index,nonT_index;

	while(1){

		top_tree = top(s);	//get top of stack node
		s = pop(s);			//also pop the stack

		if(top_tree==Dollar && lookAhead == NULL){	//if top of stack is dollar and input consumed
			printf("Parsed Successfully\n");
			break;
		}

		if(top_tree==Dollar && lookAhead!=NULL){		//input consumed 
			printf("Stack Empty,but unexpected tokens left\n");
			break;
		}

		if(lookAhead==NULL){		//input consumed 
			printf("Stack Empty,but unexpected tokens left\n");
			break;
		}
		if(strcmp(lookAhead->Token,"TK_ERROR")==0){	//already popped
				lookAhead = nextToken();
				continue;
		}
			

		//printf("Parsing :%s\n",lookAhead->Token);
	

		if(strcmp(lookAhead->Token,"TK_COMMENT") == 0){	//remove comments tokens
				lookAhead = nextToken();
				s=push(s,top_tree);		//need to push back the stack content
				continue;
		}
			
		if(top_tree->tNt==0){	//if top of stack is terminal
			if(strcmp(tokens[top_tree->index],"eps")==0){
				top_tree->token_info=lookAhead;	//store the tokenInfo
				continue;
			}
			
			if(strcmp(tokens[top_tree->index],lookAhead->Token)==0){	//token matched
				top_tree->token_info=lookAhead;	//store the tokenInfo
				lookAhead = nextToken();
				continue;
			}

		/*********PANIC MODE************/

			else{			
				printf("Line %d:The token %s for lexeme %s  does not match with the expected token %s\n",lookAhead->lineNo,lookAhead->Token,lookAhead->lexeme,tokens[top_tree->index]);
				*parseError = true;

				continue;	//popped already and lookahead same
			}
		}
		else{//if top of stack is nonterminal,pop the stack and push the rule in reverse
			check = lookup(terminals,lookAhead->Token,tokens);
            T_index = check->index;
			rule = pTable->tEntry[top_tree->index][T_index]->rule;

		//add the rules as children of the treenode at top of stack

			if(rule!=NULL){	// Grammar rule exists 


				temp_treenode = top_tree;
				temp_treenode = addChildren(temp_treenode,rule);
				temp_treenode = temp_treenode->children;


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
		
		/*********PANIC MODE************/

			else{		 
				printf("Line %d:The token of type %s for lexeme  does not match with the expected token of type <%s>\n",lookAhead->lineNo,lookAhead->Token,nonterminals[top_tree->index]);
				
					//keep iterating the inputs until you get input as syn on top_stack ie.type=1
				check = lookup(terminals,lookAhead->Token,tokens);
				T_index = check->index;

				while(lookAhead != NULL && pTable->tEntry[top_tree->index][T_index]->type!=1){	//go till syn set
					*parseError=true;
					lookAhead = nextToken();
					if(lookAhead==NULL || strcmp(lookAhead->Token,"TK_ERROR")==0)
						break;
					check = lookup(terminals,lookAhead->Token,tokens);
					T_index = check->index;
				}
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
	printInOrder(ptree->root,outfile);
	printf("ParseTree Printed in file %s\n",outfile);
}

void printInOrder(TreeNode node,char *outfile){
	if(node==NULL)
		return;

	//TreeNode temp_node = node->children;
	TreeNode temp_node = node->addr;

	if(node->children!=NULL){	//if it has children
			
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

void printNode(TreeNode node,char *outfile){    //file already opened

    FILE *f = fopen(outfile,"a");
	fprintf(f,"rule:%d\t",node->rule_no);

    //did not do value type now

    bool isLeaf=false,isTerminal=false,isRoot=false;    

    int val_type = -1;

    if(node->children==NULL)        //if leaf node
  //  if(node->addr==NULL)        //if leaf node
        isLeaf=true;

    if(node->tNt==0)        //if it contains terminal symbol
        isTerminal=true;
    
    if(node->parent==NULL)        //if this node is the root
        isRoot=true;

    TreeNode parent = node->parent;


    if(isLeaf){    //for leaf node
        if(isTerminal==false){
            //leaf node is non terminal => error case
        }    
        else{
            if(strcmp(tokens[node->index],"TK_NUM")==0)    // has NUM value field
                val_type=1;
            if(strcmp(tokens[node->index],"TK_RNUM")==0)    // has float value field
                val_type=0;

            if(isRoot){
               if(strcmp(tokens[node->index],"eps")==0)    
               fprintf(f,"%30s\t %5s\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","-----","-----","------","----","ROOT","yes","----");

                else if(val_type==1)//intval case
                    fprintf(f,"%30s\t %5d\t %21s\t nahi %5d\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,node->token_info->tkVal.intVal,"ROOT","yes","----");


                else if(val_type==0)//floatvl case
                    fprintf(f,"%30s\t %5d\t %21s\t  yahi %.2f\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,node->token_info->tkVal.floatVal,"ROOT","yes","----");


                else    //other case
                fprintf(f,"%30s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,"-----","ROOT","yes","----");
            }


            else{//if not root
                if(strcmp(tokens[node->index],"eps")==0)    
                   fprintf(f,"%30s\t %5s\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","-----","-----","------","----","ROOT","yes","----");
                else if(val_type==1)//intval case
                    fprintf(f,"%30s\t %5d\t %21s\t  %5d\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,node->token_info->tkVal.intVal,"ROOT","yes","----");


                else if(val_type==0)//floatvl case
                    fprintf(f,"%30s\t %5d\t %21s\t   %.2f\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,node->token_info->tkVal.floatVal,"ROOT","yes","----");


               else
                fprintf(f,"%30s\t %5d\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n",node->token_info->lexeme,node->token_info->lineNo,node->token_info->Token,"------",nonterminals[parent->index],"yes","----");
                }//print it;

        }

    }

    else{    //will be a nonterminal only

        if(isTerminal==true){
            //not possible
        }

        if(isRoot){

                fprintf(f,"%30s\t %5s\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","------","-----","-----","------","ROOT","no","----");

            //root node print
        }

        else

                fprintf(f,"%30s\t %5s\t %21s\t %5s\t %20s\t %3s\t %20s\n\n\n","----","-----","------","-----",nonterminals[parent->index],"no",nonterminals[node->index]);

            //nonterminal print    

    }

    fclose(f);
}


