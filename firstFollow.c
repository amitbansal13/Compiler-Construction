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
/*
void addFirst(int index,char *text){
	FF t = fset[index].first;
	while(t!=NULL){
		if(strcmp(t->elem,text)==0)
			return;
		t=t->next;
	}
	t = (FF)malloc(sizeof(struct firstfollow));
	strcpy(t->elem,text);
	t->next=fset[index].first;
	fset[index].first = t;
	return;
	
}
*/

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
	
void findFirst(int index_orig,int index,Grammar *g){	//finds first of the index_orig of nonTs
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
			findFirst(index_orig,new_index,g);
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
					findFirst(index_orig,new_index,g);
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

void computeFirstnFollow(Grammar *g){		//compute both first and follow
	initializeTNT();
	initializeFF();
	for(int i=0;i<nonTerminalsSize;i++)
		findFirst(i,i,g);
}

void printFirst(){					//print all the first's
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

bool checkSet(FF set,char *elem){	//checks if elem exists already in FF set
	FF temp = set;
	while(temp!=NULL){
		if(strcmp(temp->elem,elem)==0)
			return true;
		temp=temp->next;
	}
	return false;
}

int addSets(FF set1,FF set2){//Adds all elements of FF set2 to set 1,returns true if some addition
	int flag=0;
	FF temp2 = set2;
	while(temp2!=NULL){
		if(checkSet(set1,temp2->elem)==false){
			flag=1;
			set1 = addToSet(set1,set2->elem);
		}
		temp2=temp2->next;
	}
	return flag;
}
			

