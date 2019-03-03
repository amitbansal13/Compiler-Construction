#include "HashTable.h"
#include "parser.h"

//PT *pTable;	// parsetable;

void initializePT(){
	pTable = (PT*)malloc(sizeof(PT));
	for(int i=0;i<nonTerminalsSize;i++){
		for(int j=0;j<terminalsSize;j++){
			pTable->tEntry[i][j]=(elem*)malloc(sizeof(elem));
			pTable->tEntry[i][j]->type=-1;	//since -1->error,0->grammar exist,1->syn,2->accept
			pTable->tEntry[i][j]->rule=NULL;	
		}
	}
}
			
void createParseTable(Grammar *g){
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
							pTable->tEntry[i][T_index]->type=0;//1 for syn
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

void printParseTable(){
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
