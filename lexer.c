#include "HashTable.h"

int line_no =0;
int state = 0;

char *nextToken(char *buf,int *index,int end){
	int i = *index;
	switch(state){
		case 0:
			switch(buf[i]){
				case '%' : 
						state = 1;
						i++;
						while(i<end && buf[i]!='\n')
							i++;
						if(i==end);//need send some signal to fetch next buffer,will figure out later
						else{
							i++;
							line_no++;
							*index=i;
							state = 2;
							return "TK_COMMENT";
						}
				default:;
			}
		default:;
	}

	return NULL;
}
			
