#include "HashTable.h"

int line_no =0;
int state = 0;

char *nextToken(char *buf,int *index,int end){

	int i = *index;
	while(1){
	switch(state){
		case 0:
			switch(buf[i]){
				case '%' : 
					state = 1;
					i++;
					break;
				case '0' ... '9':
					state=7;
					i++;
					while(i<end && buf[i]<='9' && buf[i]>='0')
						i++;
					switch(buf[i]){
						case '.':	state = 9;
							break;
						default:
					}
					break;	
				
				default:;
			}
		case 1:
			switch(buf[i]){

				case '\n': 
					i++;
					line_no++;
					*index=i;
					state = 2;
						break;

				default:
					while(i<end && buf[i]!='\n')
						i++;
		case 2:
				return "TK_COMMENT";
				break;
				
		default:;
	}
	}

	return NULL;
}
			
int main(void){//helper main
	int index =0;
	nextToken("012",&index,3);

}
