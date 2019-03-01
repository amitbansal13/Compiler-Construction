#include "parser.h"
#include "HashTable.h"
#include<stdbool.h>
void printFirst();

ffset fset = NULL;

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

void initializeFF(){ 	//initializes firt follow sets to NULL
	fset = (ffset)malloc(sizeof(struct ff)*nonTerminalsSize);
	for(int i=0;i<nonTerminalsSize;i++){
		fset->first=NULL;
		fset->follow=NULL;
	}
	return;
}
void addFirst(int index,char *text){
	FF t = (FF)malloc(sizeof(struct firstfollow));
	strcpy(t->elem,text);
	t->next=fset[index].first;
	fset[index].first = t;
	return;
	
}
int findFirst(int index_orig,int index,Grammar *g){
	if(index>=nonTerminalsSize){
		printf("Error\n");
		return 0;
	}
	grammar *temp = g->arr[index];
	grammar *temp2;
	int eps_flag=0;
	while(temp!=NULL){
		if(strcmp(temp->name,"eps")==0){
	//		addFirst(index_orig,"eps");
			eps_flag=1;		//set flag
		}
		else if(isTerminal(temp->name))		//if terminal,add to the first set
			addFirst(index_orig,temp->name);

		else if(isNTerminal(temp->name)){		//if NT,
			link check = lookup(nonTerminals,temp->name,nonterminals);
			int new_index = check->index;
			int ret = findFirst(index_orig,new_index,g);
			if(ret==1){		//this non terminal has eps 
				temp2=temp->next;
				if(temp2==NULL)
					addFirst(index_orig,"eps");
				else if(isTerminal(temp2->name))		//if terminal,add to the first set
					addFirst(index_orig,temp2->name);
				else if(isNTerminal(temp->name)){		//if NT,
					check = lookup(nonTerminals,temp2->name,nonterminals);
					int new_index = check->index;
					findFirst(index_orig,new_index,g);
				}
			}
		}
		temp=temp->more;
	}
	//if(fset[index_orig].first ==NULL)
	if(eps_flag==1 && index_orig == index)
		addFirst(index_orig,"eps");
	return eps_flag;
}

void computeFirstnFollow(Grammar *g){
	initializeTNT();
	initializeFF();
	for(int i=0;i<nonTerminalsSize;i++)
		findFirst(i,i,g);
}

void printFirst(){
	printf("Printing First sets\n\n");
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
}
