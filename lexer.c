#include "HashTable.h"
#include "library.h"

int lineNo =1;
int state = 0;

TokenInfo nextToken(char *buf,int *index,int end){
	TokenInfo token = (TokenInfo)malloc(sizeof(struct tokenInfo));
	int i = *index;
	while(1){
		switch(state){
			case 0:
				switch(buf[i]){
					case '%' : 						//move to state 1
						state = 1;
						i++;
						break;
					case '0' ... '9':				// move to state 7
						i++;
						state=7;
						break;
					case '-':
					    i++;
					    state = 12;
					    break;
					case '#':
					    i++;
					    state = 16;
					    break
				    case '&':
				        i++;
				        state = 18 
			            break;                 //'[', ']', '|'...etc. will handle this case later     
					case '@':
					    i++;
					    state = 21
					    break;  
				    case  '<':
				        i++;
				        state = 24;
				        break;
			        case '>':
			            i++;
			            state = 30;
			            break;
		            case '=':
		                i++;
		                state = 33;
		                break;
	                case '!':
	                    i++;
	                    state = 35;
	                    break;
					default:;							//need to update
				}
			case 1:
				switch(buf[i]){
					case '\n': 							//create_token and move to state 2
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_COMMENT"); 
						i++;
						lineNo++;
						*index=i;
						state = 2;
						break;
	
					default:
						while(i<end && buf[i]!='\n')	//stay in state 1 while iterating the inputs
							i++;
						break;
				}
			case 2:
					return token;								//return token TK_COMMENT

			case 7:												//switch to state 8 or 9
					while(i<end && buf[i]<='9' && buf[i]>='0')
						i++;
					switch(buf[i]){
						case '.':	i++;state = 9;
							break;
						default:	i++;state = 8;
									
					}
					break;	
			case 8:											//return token TK_NUM and retract
					token->lineNo = lineNo;
					strncpy(token->lexeme,buf,i-*index+1);
					strcpy(token->Token,"TK_NUM"); 
					i--;*index=i;
					return token;	
			case 9:
				switch(buf[i]){
					case '0' ... '9':
						i++;
						state = 10;
						break;
					default:		;						//error it is
				}
			case 10:
				switch(buf[i]){
					case '0' ... '9':						//move to state 11
						i++;
						state = 11;
						break;
					default:	;							//error it is
				}

			case 11:											//return token TK_RNUM 
					token->lineNo = lineNo;
					strncpy(token->lexeme,buf,i-*index+1);
					strcpy(token->Token,"TK_RNUM"); 
					i++;*index=i;
					return token;
					
			default:;
		}
	}

	return NULL;
}
	/*		
int main(void){//helper main
	int index =0;
	nextToken("012",&index,3);

}*/
