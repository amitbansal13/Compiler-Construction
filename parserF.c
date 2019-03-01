#include "parser.h"
#include "HashTable.h"
#include <string.h>
#define terminalsSize 54 //Number of Terminals including epsilon
#define nonTerminalsSize 51


char *tokens[]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL","TK_COMMA", "TK_SEM","TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_LE", "TK_NE","eps"};  
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
	"funCallStmt",
	"outputParameters",
	"inputParameters",
	"elsePart",
	"ioStmt",
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

int check[terminalsSize]; 

Table terminals=NULL;//HashTable to store Terminals
Table nonTerminals=NULL;//HashTable to store non Terminals
void initializeTNT()
//initializes both Terminals and Non Terminals hash tables
{
	int m;
	for(m=0;m<terminalsSize;m++){
		check[m] = 0;
	}//initializing the check table at the same time

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

grammar* newNode(char *temp)
//returns a new grammar node
{
	grammar* g=(grammar*)malloc(sizeof(grammar));
	strcpy(g->name,temp);
	g->more=NULL;
	g->next=NULL;
	return g;
}

grammar* makeNewRule(FILE* fp,int d)
//makes a new Rule by scanning d space separated strings in a line
{
	int i=0;
	char temp[30];
	fscanf(fp,"%s",temp);
	grammar* head=newNode(temp),*curr;
	curr=head;
	for(i=0;i<d-1;i++)
	{
		fscanf(fp,"%s",temp);
		curr->next=newNode(temp);
		curr=curr->next;
	}
	return head;
}

Grammar* readFile(char* fileName){
	FILE* fp=fopen(fileName,"r");
	if(fp==NULL)
	{
		printf("File Not opened\n");
		return NULL;
	}
	
	initializeTNT();
	

	Grammar *g=(Grammar *)malloc(sizeof(Grammar));
	g->arr=(grammar**)malloc(sizeof(grammar*)*nonTerminalsSize);
	g->size=nonTerminalsSize;//initial size for array of Grammar rules
	grammar** arr=g->arr;//using arr as temp pointer
	
	int d=0,i=0;
	for(i=0;i<nonTerminalsSize;i++)
		arr[i]=(grammar*)malloc(sizeof(grammar));
	char temp[30];
	link check=NULL;
	memset(temp,0,30);
	while(fscanf(fp,"%s %d",temp,&d)!=-1)//scan till EOF
	{
		printf("%s %d\n",temp,d);
		check=lookup(nonTerminals,temp,nonterminals);
		grammar* head;
		if(arr[check->index]->more==NULL)//if this is the first rule to be added 
			arr[check->index]->more=makeNewRule(fp,d);
		else
		{
			head=makeNewRule(fp,d);
			head->more=arr[check->index]->more;
			arr[check->index]->more=head;
		}
	memset(temp,0,30);
	}
	fclose(fp);
	return g;
}
FF tail(FF traverse){
	FF temp = traverse;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	return temp;
}

FF getFirstSet(Grammar* g1,grammar* cur){//, HashTable nt){
	
	grammar* temp = cur->more;
	int k; char* fname;
	FF head = NULL;
	
	while(temp!=NULL){
		link lookNT, lookT;
		if((lookT = lookup(terminals,temp->name,tokens))!=NULL){ //check if 1st RHS is a terminal
			if(check[lookT->index]==0){
				if(head==NULL){
					FF ft = (FF)malloc(sizeof(struct firstfollow));
					ft->next = NULL;
					strcpy((char*)ft->elem,temp->name);
					head = ft;	
					check[lookT->index] = 1;
				}	
				else{
					FF ft = (FF)malloc(sizeof(struct firstfollow));
					strcpy((char*)ft->elem,temp->name);
					ft->next = head;
					head = ft;
					check[lookT->index] = 1;
				}
			
			}
		}
		else{
			lookNT = lookup(nonTerminals,temp->name,nonterminals);//else its a nonterminal and store the index of NT in lookNT
			//Assuming it won't return NULL;
			if(head==NULL){
				FF epsCheck = getFirstSet(g1,g1->arr[lookNT->index]);
				if(strcmp((char*)epsCheck->elem,"eps")==0){//check if first of NT returned contains eps
					link lookTemp; //temporary link to lookup terminal table
					link lookNTemp; //temporary link to lookup nonterminal table
					if(temp->next==NULL){
						head = epsCheck;
						//free(lookNTemp);
						//free(lookTemp);
					}
					else if((lookTemp=lookup(terminals,temp->next->name,tokens))!=NULL){//check if temp's next is a terminal
						if(check[lookTemp->index]==0){
							if(epsCheck->next!=NULL){ //if returned first set contains terminals other than eps as well
								FF ftemp = (FF)malloc(sizeof(struct firstfollow));
								strcpy((char*)ftemp->elem,temp->next->name);
								ftemp->next = epsCheck->next; //join temp->next to the first set excluding eps
								head = ftemp; 
								check[lookTemp->index] = 1;
							}
							else{ //if returned first set has only eps
								FF ftemp = (FF)malloc(sizeof(struct firstfollow));
								strcpy((char*)ftemp->elem,temp->next->name);
								ftemp->next = NULL;
								head = ftemp;
								check[lookTemp->index] = 1;
							}
						}

						free(lookTemp);
						
					}
					else{
						//if the above conditions are false it is a nonterminal
						lookNTemp = lookup(nonTerminals,temp->next->name,nonterminals);
						FF nterm = getFirstSet(g1,g1->arr[lookNTemp->index]);//get first of next NT
						tail(nterm)->next = epsCheck->next; //join the first set to the firstset of 1st NT excluding eps
						head = nterm;
					}
				}
				else{
					head = epsCheck;	
				}
					//recursively call the function, now with a new NT
				//free(epsCheck);
			}
			else{
				FF res = getFirstSet(g1,g1->arr[lookNT->index]);
				//res->next = head;
				//head = res;
				FF epsCheck = getFirstSet(g1,g1->arr[lookNT->index]);
				if(strcmp((char*)epsCheck->elem,"eps")==0){//check if first of NT returned contains eps
					link lookTemp; //temporary link to lookup terminal table
					link lookNTemp; //temporary link to lookup nonterminal table
					if(temp->next==NULL){
						tail(epsCheck)->next = head;
						head = epsCheck;
						//free(lookNTemp);
						//free(lookTemp);
					}
					else if((lookTemp=lookup(terminals,temp->next->name,tokens))!=NULL){//check if temp's next is a terminal
						if(check[lookTemp->index]==0){
							if(epsCheck->next!=NULL){ //if returned first set contains terminals other than eps as well
								tail(epsCheck)->next = head;//join epsCheck to head eps
								FF ftemp = (FF)malloc(sizeof(struct firstfollow));
								strcpy((char*)ftemp->elem,temp->next->name);
								ftemp->next = epsCheck->next; //join temp->next to the first set excluding eps
								head = ftemp; 
								check[lookTemp->index] = 1;
							}
							else{ //if returned first set has only eps
								FF ftemp = (FF)malloc(sizeof(struct firstfollow));
								strcpy((char*)ftemp->elem,temp->next->name);
								ftemp->next = head;
								head = ftemp;
								check[lookTemp->index] = 1;
							}
						}

						free(lookTemp);
					}
					else{
						//if the above conditions are false it is a nonterminal
						lookNTemp = lookup(nonTerminals,temp->next->name,nonterminals);
						FF t = getFirstSet(g1,g1->arr[lookNTemp->index]);
						tail(epsCheck)->next = head;
						tail(t)->next = epsCheck->next;
						head = t;

					}
				}
				else{
					tail(epsCheck)->next=head;
					head = epsCheck;	
				}
			}
		}
		temp = temp->more;
	}
	return head;
	
}

FF getFollowSet(Grammar* g1,grammar* cur){

}

ffset computeFirstFollow(Grammar* g){//,HashTable nt){
	//Assuming g is already allocated
	int len = g->size;
	ffset firstFollow = (ffset)malloc(sizeof(struct ff)*nonTerminalsSize);
	firstFollow->first = (FF)malloc(sizeof(struct firstfollow)*terminalsSize);
	firstFollow->follow = (FF)malloc(sizeof(struct firstfollow)*terminalsSize);
	int i;
	Grammar* gTemp  = g;
	Grammar* gTemp2 = g;
	//grammar** ptr = g->arr; //ptr will point to the array of g

	for(i=0;i<len;i++){

		firstFollow[i].first = getFirstSet(gTemp,gTemp->arr[i]);//, nt);
		gTemp++;
	}
	//calculate follow using first obtained above
	for(i=0;i<len;i++){
		firstFollow[i].follow = getFollowSet(gTemp2,gTemp2->arr[i]);//, nt);
		gTemp2++;
	}
	return firstFollow;
	
}
