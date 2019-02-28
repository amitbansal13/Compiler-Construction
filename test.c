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
		temp1=arr[i]->more;
		while(temp1)
		{
			temp2=temp1;
			printf("%s ",temp->name);
			while(temp2)
			{
				printf("%s ",temp2->name);
				temp2=temp->next;
			}
			printf("\n");
			temp1=temp1->more;
		}
	}
	return 0;
}
