#include "parser.h"

int main()
{
	Grammar* g=readFile("grammar.txt");
	int size=g->size;
	grammar** arr=g->arr,*temp,*temp1,*temp2;
	int i=0;
	for(i=0;i<size;i++)
	{
		temp=arr[i];
		if(temp==NULL)
			continue;
		while(temp)
		{
			temp1=temp;
			printf("%s->",nonterminals[i]);
			while(temp1)
			{
				printf("%s ",temp1->name);
				temp1=temp1->next;
			}
			printf("\n");
			temp=temp->more;
		}
	}
	return 0;
}
