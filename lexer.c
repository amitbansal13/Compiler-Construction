#include "lexerDef.h"
#include "lexer.h"
#define BUF_SIZE 256

int lineNo = 1;
char* twinBuf1=NULL,*twinBuf2=NULL;
Table keywordsTable =NULL;
char temp[100];										//stores lexeme temporarily
int i=0,end,flag=0,end1,end2,ans=1;				// i for getNextCharacter function buf pointer
FILE *fp;

void initialize(FILE *f)	// initializes hashtable ,filepointers
{
	fp=f;
	fseek(fp,0,SEEK_SET);
	lineNo = 1;
	i=0;end=0;flag=0;end1=0;end2=0;ans=1;
	int tableSize=53;
	if(twinBuf1==NULL)
		twinBuf1 = (char*)malloc(sizeof(char)*BUF_SIZE);
	if(twinBuf2==NULL)
    	twinBuf2 = (char*)malloc(sizeof(char)*BUF_SIZE);
    end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
	if(keywordsTable==NULL){
		keywordsTable=create(tableSize);
		for(int j=0;j<24;j++)//24 is keyword table size
			insert(keywordsTable,keywords,j);
	}
	
}

char getNextChar()				// returns next character in buf and also increments i
{
// assuming memory for this is already allocated
        char *buf;
        if(flag == 0)
        {
        	buf = twinBuf1;
        	end=end1;
        }
        else
        {
	        buf = twinBuf2;
	        end=end2;
	    }
        if(i>=end)
        {
            if(flag == 0)
                end2=fread(twinBuf2,sizeof(char),BUF_SIZE-1,fp);
            else
                end1=fread(twinBuf1,sizeof(char),BUF_SIZE-1,fp);
            i=0;
        	if(flag==0){
        		buf = twinBuf2;
	        	end=end2;
	        	flag=1;
        	}
        	else{
	        	buf = twinBuf1;
	        	end=end1;
	        	flag=0;
        	}
        }
        if(i<0)
        {
            // go to previous buffer
            i=0;
            if(flag == 0)
                return twinBuf2[end2-1];
            else
                return twinBuf1[end1-1];
        }
        if(end1==0 && end2==0)return '\0';
        char temp=buf[i];
        i++;
        return temp;
}

float stringToFloat(char *str)
{
	float f=0.0,p=10.0;
	int i=0;
	while(str[i] && str[i]!='.')
	{
	    //printf("%c",str[i]);
		f=str[i]-'0'+f*10.0;
		i++;
	}
	i++;
    while(str[i]){
		f=(str[i]-'0')/p+f;
		i++;
		p*=10.0;
	}
	return f;
}

int stringToInteger(char *str)
{
	int i=0,ans=0;
	while(str[i]){
	    ans=str[i]-'0'+ans*10;
		i++;
	}
	return ans;
}

TokenInfo nextToken(){
	TokenInfo token = (TokenInfo)malloc(sizeof(struct tokenInfo));
	memset(token->Token,0,MAX_TOKEN);
	memset(token->lexeme,0,MAX_LEXEME);
	memset(temp,0,100);
	
	link tok;	

	/* INITIALIZE STATE AND TOKEN */
	int tInd=0;		 
	int state = 0;
	char c=getNextChar();
	int count=0;
	while(1){
		if(c==0)
			return NULL;
		switch(state){
			case 0:
				switch(c){
					case '%' : 						//move to state X and get next char
                        temp[tInd++] = c;
						state = 1;
						c=getNextChar();
						break;
					case 'a' ... 'z' :
                        temp[tInd++] = c;
						if(c>='b' && c<='d'){
							state = 4; 
							count++;
						}
						else
							state = 3; 
						c=getNextChar();
						break;
					
					case '0' ... '9':				
                        temp[tInd++] = c;
						state=7;
						c=getNextChar();
						break;
					case '_':
						count++;
                        temp[tInd++] = c;
					    state = 12;
						c=getNextChar();
					    break;
					case '#':
                        temp[tInd++] = c;
					    state = 16;
						c=getNextChar();
					    break;
				    case '&':
                        temp[tInd++] = c;
				        state = 19 ;
						c=getNextChar();
			            break;                 
					case '@':
                        temp[tInd++] = c;
					    state = 22;
						c=getNextChar();
					    break;
				    case  '<':
                        temp[tInd++] = c;
				        state = 25;
						c=getNextChar();
				        break;
			        case '>':
                        temp[tInd++] = c;
			            state = 31;
						c=getNextChar();
			            break;
		            case '=':
                        temp[tInd++] = c;
		                state = 34;
						c=getNextChar();
		                break;
	                case '!':
                        temp[tInd++] = c;
	                    state = 36;
						c=getNextChar();
	                    break;

                    case '[':					//rest all go to state 18 making single tokens
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_SQL");
						state = 18;
						break;
                    case ']':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_SQR");
						state = 18;
						break;
                    case ',':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_COMMA");
						state = 18;
						break;
                    case ';':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_SEM");
						state = 18;
						break;
                    case ':':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
  						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_COLON");
						state = 18;
						break;
                    case '.':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_DOT");
						state = 18;
						break;

                    case '(':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme, temp);
						strcpy(token->Token,"TK_OP");
						state = 18;
						break;
                    case ')':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_CL");
						state = 18;
						break;
                    case '+':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_PLUS");
						state = 18;
						break;
				    case '-':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_MINUS");
						state = 18;
						break;
                    case '*':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_MUL");
						state = 18;
						break;
					case '/':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_DIV");
						state = 18;
						break;
					case '~':
                        token->lineNo = lineNo;
                        temp[tInd++] = c;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						strcpy(token->Token,"TK_NOT");
						state = 18;
						break;                      

		/***\n \t ' ' -> remain in same state and getnextchar *****/

					case '\r':
					case '\n':
					case '\v':
						lineNo++;
					case ' ':
					case '\t':
						state=0;			//stay in same state
						c=getNextChar();
						break;

					/* EOF CASE->RETURN NULL */

					case '\0' : return NULL;						

			//****** return error if symbol not recognized , no getnextchar ********		

					default:							/* returns TK_ERROR */
                   	    token->lineNo = lineNo;
                   		temp[tInd++] = c;
                   	    temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						printf("Line %d:Unknown symbol %s\n",lineNo,token->lexeme);
						strcpy(token->Token,"TK_ERROR");
						return token;
				}
				break;

			case 1:
					temp[tInd++] = c;
					if(c=='\0')
						state=2;
					else if(c=='\n' || c=='\r' || c=='\v'){
						state=2;
						i--;
						tInd--;
					}
					else{
						c=getNextChar();
						state = 1;
					}
					break;

			case 2:
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_COMMENT");
					return token;	//return token TK_COMMENT

			case 3:
				switch(c){
					case 'a' ... 'z':
						temp[tInd++] = c;
						state = 3;
						c=getNextChar();
						break;
					case '(':
					case ')':
					case '*':
					case '/':
					case '~':
					case ',':
					case ':':
					case '+':	
					case '-':
					case ';':
					case '[':
					case ']':
					case '<':
					case '>':
					case '=':
					case '!':
					case '#':
					case '@':
					case '&':
					case '.':
					case '\n':
					case '\r':
					case '\v':
						i--;
					case ' ':
					case '\t':
					case '\0':
							token->lineNo = lineNo;
							strcpy(token->lexeme,temp);

						temp[tInd]='\0';
						tok = lookup(keywordsTable,temp,keywords);
						
						if(tok==NULL)								//TK_FIELD_ID
							strcpy(token->Token,"TK_FIELDID");
						else								//KEYWORD
							strcpy(token->Token,keywords_tokens[tok->index]);
						return token;


					default:							/* MAXIMAL MUNCH  && returns TK_ERROR */
						while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    		temp[tInd++] = c;
							c=getNextChar();
						}
                   	    token->lineNo = lineNo;
						if(c=='\n' || c=='\r' || c=='\v')
							i--;
                   	    temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
						strcpy(token->Token,"TK_ERROR");
						return token;
				}
					break;

			case 4:
					switch(c){
						case 'a' ... 'z': 
							temp[tInd++] = c;
							state=3;
							c=getNextChar();
							break;
						case '2' ... '7':
							count++;
							temp[tInd++] = c;
							state=5;
							c=getNextChar();
							break;
										//MAXIMAL MUNCH CASE and returns TK_ERROR
						default: 
							while(c!='\n' && c!='\r' &&  c !=' ' && c!='\t' && c!='\0'){
                   				temp[tInd++] = c;
								c=getNextChar();
							}
                   		    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
                   		    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							strcpy(token->Token,"TK_ERROR");
							return token;
					}
					break;

			case 5:	
					switch(c){
						case '2' ... '7':
							count++;
							temp[tInd++] = c;
							state=6;
							c=getNextChar();
							break;
						case 'b' ... 'd': 
							count++;
							temp[tInd++] = c;
							state=5;
							c=getNextChar();
							break;

					case '(':
					case ')':
					case '*':
					case '/':
					case '~':
					case ',':
					case ':':
					case '+':	
					case '-':
					case ';':
					case '[':
					case ']':
					case '<':
					case '>':
					case '=':
					case '!':
					case '#':
					case '@':
					case '&':
					case '.':
					case '\n':
					case '\r':
					case '\v':
						i--;
						case ' ':
						case '\t':
						case '\0':
        	           	    token->lineNo = lineNo;
							if(count>=21){
            	       	    	temp[tInd] = '\0';
								strcpy(token->lexeme,temp);
								strcpy(token->Token,"TK_ERROR");
								printf("Line %d:Identifier is longer than the prescribed length of 20 characters\n",lineNo);
								return token;
							}
							else{
        	           	    	temp[tInd] = '\0';
								strcpy(token->lexeme,temp);
								strcpy(token->Token,"TK_ID");
								return token;
							}

						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							strcpy(token->Token,"TK_ERROR");
							return token;
					}
					break;

			case 6:
					switch(c){
						case '2' ... '7' :
							count++;
							temp[tInd++] = c;
							state=6;
							c=getNextChar();
							break;
					case '(':
					case ')':
					case '*':
					case '/':
					case '~':
					case ',':
					case ':':
					case '+':	
					case '-':
					case ';':
					case '[':
					case ']':
					case '<':
					case '>':
					case '=':
					case '!':
					case '#':
					case '@':
					case '&':
					case '.':
					case '\n':
					case '\r':
					case '\v':
						i--;

						case ' ':
						case '\t':
						case '\0':
        	           	    token->lineNo = lineNo;

							if(count>=21){
            	       	    	temp[tInd] = '\0';
								strcpy(token->lexeme,temp);
								strcpy(token->Token,"TK_ERROR");
								printf("Line %d:Identifier is longer than the prescribed length of 20 characters\n",lineNo);
								return token;
							}
							else{
        	           	    	temp[tInd] = '\0';
								strcpy(token->lexeme,temp);
								strcpy(token->Token,"TK_ID");
								return token;
							}
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}
					break;

			case 7:		//switch to state 8 or 9
					switch(c){
						case '0' ... '9' :
							temp[tInd++] = c;
							state=7;
							c=getNextChar();
							break;
						case '.' :
							temp[tInd++] = c;
							state=9;
							c=getNextChar();
							break;
						default: 
							state = 8;
							break;
					}
					break;

			case 8:									//return token TK_NUM and retract
        	   	   	token->lineNo = lineNo;
        	   	   	temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_NUM");
					token->tkVal.intVal =  stringToInteger(temp);
					i--;
					return token;

			case 9:
					switch(c){
						case '0' ... '9' :
							temp[tInd++] = c;
							state=10;
							c=getNextChar();
							break;
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}
					break;
			case 10:
					switch(c){
						case '0' ... '9' :
							temp[tInd++] = c;
							state=11;
							break;
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}
					break;

			case 11:								//return token TK_RNUM
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_RNUM");
					token->tkVal.floatVal =  stringToFloat(temp);
					return token;

			case 12:
					switch(c){
						case 'a' ... 'z':
							count++;
							temp[tInd++] = c;
							state = 13;
							c=getNextChar();
							break;
						case 'A' ... 'Z':
							count++;
							temp[tInd++] = c;
							state = 13;
							c=getNextChar();
							break;
					
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}	
					break;

			case 13:
					switch(c){
						case 'a' ... 'z':
							temp[tInd++] = c;
							state = 13;
							count++;
							c=getNextChar();
							break;
						case 'A' ... 'Z':
							count++;
							temp[tInd++] = c;
							state = 13;
							c=getNextChar();
							break;
						case '0' ... '9' :
							count++;
							temp[tInd++] = c;
							state = 15;
							break;
							
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							state=14;
					}
					break;

			case 14:								//return TK_FUNID OR TK_MAIN and retract
					if(count>=30){
            	    	temp[tInd] = '\0';
				  		strcpy(token->lexeme,temp);
				   		strcpy(token->Token,"TK_ERROR");
						printf("identifier too long on line no %d\n",lineNo);
				   		printf("Funidentifier too long on line no %d\n",lineNo);
				   		return token;
				   	}
					else{
        	   		   	token->lineNo = lineNo;
        	   		   	temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						if(strcmp(token->lexeme,"_main")==0)
							strcpy(token->Token,"TK_MAIN");
						else
							strcpy(token->Token,"TK_FUNID");
						i--;
						return token;
					}

			case 15: 
					switch(c){
						case '0' ... '9' :
							count++;
							temp[tInd++] = c;
							state=15;
							c=getNextChar();
							break;

						case '\n':						  
						case '\v':
						case '\r':						  
							i--;	//will increase in next set

						case ' ':
						case '\t':
						case '\0':
        	           	    token->lineNo = lineNo;
							if(count>=30){
            	    			temp[tInd] = '\0';
				  				strcpy(token->lexeme,temp);
				   				strcpy(token->Token,"TK_ERROR");
								printf("Line %d:FunIdentifier is longer than the prescribed length of 30 characters\n",lineNo);
				   				return token;
				   			}
							else{
        	           			temp[tInd++] = c;
        	           		    temp[tInd] = '\0';
								strcpy(token->lexeme,temp);
								strcpy(token->Token,"TK_FUNID");
								return token;
							}
						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}

					break;
			case 16:
					switch(c){
						case 'a' ... 'z':
							temp[tInd++] = c;
							state = 17;
							break;

						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}
					break;

			case 17: 
					switch(c){
						case 'a' ... 'z' :
							temp[tInd++] = c;
							state=17;
							c=getNextChar();
							break;

						case '\n':
						case '\r':
						case '\v':
						case ' ':
						case '\t':
						case '\0':
							i--;
        	           	    token->lineNo = lineNo;

        	           	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_RECORDID");
							return token;

						default:						/* MAXIMAL MUNCH  && returns TK_ERROR */
							while(c!='\n' && c!='\r' && c !=' ' && c!='\v' && c!='\t' && c!='\0'){
               	    			temp[tInd++] = c;
								c=getNextChar();
							}
            	       	    token->lineNo = lineNo;
							if(c=='\n' || c=='\r' || c=='\v')
								i--;
            	       	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							return token;
					}

					break;
												//for case 18 token already made before
			case 18:	return token;			// return one letter tokens '[' ,';'etc

			case 19:		//switch to state 20
					switch(c){
						case '&' :
							temp[tInd++] = c;
							state=20;
							c=getNextChar();
							break;

				//*****NO MAXIMAL MUNCH FOR SYMBOLS******

						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 20:
					switch(c){
						case '&' :
							temp[tInd++] = c;
							state=21;
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;
						
			case 21:								//return token TK_AND
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_AND");
					return token;

			case 22:		//switch to state 23
					switch(c){
						case '@' :
							temp[tInd++] = c;
							state=23;
							c=getNextChar();
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 23:
					switch(c){
						case '@' :
							temp[tInd++] = c;
							state=24;
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;
						
			case 24:								//return token TK_OR
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_OR");
					return token;

			case 25:		//switch to state 26 or 29 or 30
					switch(c){
						case '=' :
							temp[tInd++] = c;
							state=30;
							break;
						case '-' :
							temp[tInd++] = c;
							state=26;
							c=getNextChar();
							break;
						default: 
							state = 29;
							break;
					}
					break;

			case 26:		//switch to state 27
					switch(c){
						case '-' :
							temp[tInd++] = c;
							state=27;
							c=getNextChar();
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 27:
					switch(c){
						case '-' :
							temp[tInd++] = c;
							state=28;
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 28:								//return token TK_ASSIGNOP
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_ASSIGNOP");
					return token;

			case 29:								//return TK_LT and retract
        	   	   	token->lineNo = lineNo;
        	   	   	temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_LT");
					i--;
					return token;

			case 30:								//return token TK_LE
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_LE");
					return token;

			case 31:		//switch to state 32 or 33
					switch(c){
						case '=' :
							temp[tInd++] = c;
							state=33;
							break;
						default: 
							state = 32;
							break;
					}
					break;

			case 32:								//return token TK_GT and retract
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_GT");
					i--;
					return token;

			case 33:								//return token TK_GE
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_GE");
					return token;

			case 34:		//switch to state 35
					switch(c){
						case '=' :
							temp[tInd++] = c;
							state=35;
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 35:
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_EQ");
					return token;

			case 36:		//switch to state 37
					switch(c){
						case '=' :
							temp[tInd++] = c;
							state=37;
							break;
						default:					//return error and retract
	                   	    token->lineNo = lineNo;
	                   	    temp[tInd] = '\0';
							strcpy(token->lexeme,temp);
							strcpy(token->Token,"TK_ERROR");
							printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
							i--;
							return token;
					}
					break;

			case 37:						//return TK_NE
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_NE");
					return token;
			default:	//NOT POSSIBLE
	                token->lineNo = lineNo;
	                temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					strcpy(token->Token,"TK_ERROR");
					printf("Line %d:Unknown pattern %s\n",lineNo,token->lexeme);
					return token;

		}
	}
}

void removeComments(){//char *testcaseFile, char *cleanFile){
	char c;
	int isCommment=0;//to check whether '\n' is comming from comment or is normal '\n'
	c=getNextChar();
	while(c!=0)
	{
		if(c=='%')
		{
			c=getNextChar();
			while(c && (c!='\n' && c!='\r' && c!='\v' ))c=getNextChar();
			isCommment=1;
		}
		if(isCommment && (c=='\n' || c=='\r' || c=='\v'))
		{
			isCommment=0;
			continue;
		}
		printf("%c", c);
		c=getNextChar();
	}
	i=0;//resetting buffer pointer
	fseek(fp, 0, SEEK_SET);//resetting file pointer to start of file
}

void printAllTokens()
{
	TokenInfo tk;
	int count=0;
	while(tk=nextToken())
	{
		printf("%d. %s %s\n",tk->lineNo,tk->lexeme,tk->Token);
		free(tk);
	}
}

void printFile(FILE *fp){
	char c=getNextChar();
	while(c!=0){
		c=getNextChar();
		printf("%c",c);
	}
}
