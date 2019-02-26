#include "HashTable.h"
#include "library.h"

int lineNo =1;
int state = 0;

TokenInfo nextToken(){//char *buf,int *index,int end){
	// assuming fp = fopen("language.txt") is written in main before calling
	TokenInfo token = (TokenInfo)malloc(sizeof(struct tokenInfo));
	//end = fread(twinBuf0,sizeof(char),256,fp);//First fread is from here
	int i = *index;
	while(1){
	    
	    if(buf[i] == '\n'){
	        i++;
	        lineNo++;
	    }
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
					case '_':
					    i++;
					    state = 12;
					    break;
					case '#':
					    i++;
					    state = 16;
					    break;
				    case '&':
				        i++;
				        state = 18 ;
			            break;                 //'[', ']', '|'...etc. are handled below      
					case '@':
					    i++;
					    state = 21;
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
                    case '[':					//rest all go to state 18 making single tokens
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_SQL"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case ']':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_SQR"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case ',':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_COMMA"); 
						i++;
						*index=i;
						state = 18;
						break;						
                    case ';':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_SEM"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case ':':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_COLON"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case '.':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_DOT"); 
						i++;
						*index=i;
						state = 18;
						break;						

                    case '(':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_OP"); 
						i++;
						*index=i;
						state = 18;
						break;		
                    case ')':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_CP"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case '+':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_PLUS"); 
						i++;
						*index=i;
						state = 18;
						break;
				    case '-':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_MINUS"); 
						i++;
						*index=i;
						state = 18;
						break;
                    case '*':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_MUL"); 
						i++;
						*index=i;
						state = 18;
						break;
					case '/':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_DIV"); 
						i++;
						*index=i;
						state = 18;
						break;
					case '~':
                        token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_NOT"); 
						i++;
						*index=i;
						state = 18;
						break;                      //'[', ']', '|'...etc. are handled below 
						
						default:;	
											//need to update
				}
			case 1:
				switch(buf[i]){
					case '\n': 							//create_token and move to state 2
						i++;
						lineNo++;
						state = 2;
						break;
	
					default:
						while(i<end && buf[i]!='\n')	//stay in state 1 while iterating the inputs
							i++;
						break;
				}
			case 2:
					token->lineNo = lineNo;
					strncpy(token->lexeme,buf,i-*index+1);
					strcpy(token->Token,"TK_COMMENT"); 
					*index=i;
					return token;								//return token TK_COMMENT
            case 3:

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
					return token;
					
			case 18:									// return one letter tokens '[' ,';'etc
				return token;
			case 19:
					switch(buf[i]){
						case '&' :i++;state=20;	
							break;
						default:;						//error
					}
						
			case 20:
					switch(buf[i]){						//return TK_AND
						case '&' :i++;	
						default:		;				//error
					}
			case 21:
						*index=i;
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_AND"); 
						return token;
				

			case 22:
					switch(buf[i]){
						case '@' :i++;state=20;	
							break;
						default:	;					//error
					}
						
			case 23:
					switch(buf[i]){								//return TK)_OR
						case '@' :i++;	
							state=24;
						default:	;					//error
					}
			case 24:
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_OR"); 
						*index=i;
						return token;
			case 25:
					switch(buf[i]){
						case '=' :i++;			
							state = 30;
							break;
						case '-' : i++;
							state=26;
							break;
		
					}

			case 26 :	
					switch(buf[i]){
						case '-' :i++;			
							state = 27;
							break;
						default:	;			//error
					}
			case 27:
					switch(buf[i]){
						case '-' :i++;			
							state = 28;
							break;
						default:		;		//error
					}
			case 28:
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_ASSIGNOP"); 
						return token;

			case 29:					//return TK_LT
					token->lineNo = lineNo;
					strncpy(token->lexeme,buf,i-*index+1);
					strcpy(token->Token,"TK_LT"); 
					i--;
					*index=i;
					return token;

			case 30:
					switch(buf[i]){
						case '=' :i++;			//return TK_LE
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_LE"); 
						*index=i;
						return token;
					}

			case 31:
					switch(buf[i]){
						case '=' :i++;			
						state=33;
						break;
						default:i++;		;				
						state=32;
					}
		
			case 32:
						token->lineNo = lineNo;			//return TK_GT and retract
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_GT"); 
						i--;
						*index=i;
						return token;

			case 33:
						token->lineNo = lineNo;			//return TK_GE
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_GE"); 
						*index=i;
						return token;

			case 34:
					switch(buf[i]){							// move to state 35
						case '=':state = 35;i++;
						default:		;				//error
					}
			case 35:
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_EQ"); 
						*index=i;
						return token;
					
			case 36:
					switch(buf[i]){						//return TK_NE
						case '=':i++;
							state=37;
						default:		;				//error
					}
			case 37:
						token->lineNo = lineNo;
						strncpy(token->lexeme,buf,i-*index+1);
						strcpy(token->Token,"TK_NE"); 
						*index=i;
						return token;
			default:;									//error
		}
	}

	return NULL;
}

void removeComments(char *testcaseFile, char *cleanFile){
	int i=0;
	while(testcaseFile[i])
	{
		if(testcaseFile[i]=='%')
		{
			while(testcaseFile[i]!='\n')i++;
			i++;
		}
		cleanFile[i]=testcaseFile[i];
		i++;
	}
}

