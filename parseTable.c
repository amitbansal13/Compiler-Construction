#include "HashTable.h"
#include "parser.h"

PT *pTable;	// parsetable;

void initializePT(){
	pTable = (PT*)malloc(sizeof(PT));
	for(int i=0;i<nonTerminalsSize;i++){
		for(int j=0;j<terminalsSize;j++){
			pTable->tEntry[i][j]=(elem*)malloc(sizeof(elem));
			pTable->tEntry[i][j]->index=-2;	//since -1 onwards can are valid
			pTable->tEntry[i][j]->rule=NULL;	
		}
	}
}
			
void createParseTable(Grammar *g){
	for(int i=0;i<nonTerminalsSize;i++){

			//iterating all the grammar rules
		grammar *rule = g->arr[i];

		link check;

		grammar *temp_rule = rule;

		grammar *temp2;
		int eps_flag=0,T_index,nonT_index;
		while(temp_rule!=NULL){

			temp2 = temp_rule;			//need to traverse this rule if NT gives eps
				
			while(temp2!=NULL){

				if(isTerminal(temp_rule->name)){	//means rule->name is in first of nonterminals[i]		
					if(strcmp(temp_rule->name,"eps") == 0){	//wont get anything after eps
	
				//if eps,replace with this rule if any terminal in follow set of this nonterminsl
	
						for(int j=0;j<terminalsSize;j++){
							if(checkSet(fset[i].follow,tokens[j]) == true){
								if(pTable->tEntry[i][j]->rule!=NULL)
									printf("Multiple rules clashing in Entry[%d][%d]\n",i,j);
								pTable->tEntry[i][j]->index=i;	
							    pTable->tEntry[i][j]->rule=temp_rule;	
							}
						}
						//temp2=temp2->next;
						//continue;//since this rule can be replaced with eps
						break;
					}
	
			//if other terminals,replace with this rule only
	
					else{
							check = lookup(terminals,temp_rule->name,tokens);
							T_index = check->index;
							if(pTable->tEntry[i][T_index]->rule!=NULL)
								printf("Multiple rules clashing in Entry[%d][%d]\n",i,T_index);
							pTable->tEntry[i][T_index]->index=i;
						    pTable->tEntry[i][T_index]->rule=temp_rule;	
						break;	//if got a terminal,always break
					}
				}
	
				else if(isNTerminal(temp_rule->name)){
					check = lookup(nonTerminals,temp_rule->name,nonterminals);
					nonT_index = check->index;
				
					//if first set of nonT_index has eps,need to traverse rule continuation
	
					FF first_set = fset[nonT_index].first;
					FF temp_f = first_set;
					eps_flag=0;
					while(temp_f!=NULL){
						if(strcmp(temp_f->elem,"eps")==0){
							eps_flag=1;
						}
						else{
							check = lookup(terminals,temp_f->elem,tokens);
							T_index = check->index;
							if(pTable->tEntry[i][T_index]->rule!=NULL)
								printf("Multiple rules clashing in Entry[%d][%d]\n",i,T_index);
							pTable->tEntry[i][T_index]->index=i;
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
			}
			temp_rule=temp_rule->next;
		}
	}
}

void printParseTable(){
	for(int i=0;i<nonTerminalsSize;i++){
		for(int j=0;j<terminalsSize;j++){
			printf("pEntry[%d][%d]:",i,j);
			printf("index:%d \n",pTable->tEntry[i][j]->index);
			printf("rule:");
			grammar *temp = pTable->tEntry[i][j]->rule;
			while(temp!=NULL){
				printf("%s ",temp->name);
				temp=temp->next;
			}
		printf("\n");
		}
	}
}
