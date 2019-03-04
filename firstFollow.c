#include "HashTable.h"
#include "parserDef.h"
#include "parser.h"
#include<stdbool.h>

//ffset fset = NULL;

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
