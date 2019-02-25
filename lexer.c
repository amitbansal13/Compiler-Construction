#include "HashTable.h"

int line_no =0;

char *nextToken(char *buf,int *index,int end){
	int state = 0;
	int i = *index;
	switch(state){
		case 0:
			switch(buf[i]){
				case '%' : 
						i++;
						while(i<end && buf[i]!='\n')
							i++;
						i++;
						line_no++;
						*index=i;
						return "TK_COMMENT";
				default:;
			}
		default:;
	}

	return NULL;
}
			
