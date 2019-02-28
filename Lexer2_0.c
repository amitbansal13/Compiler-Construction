#include "HashTable.h"
#include "library.h"

int lineNo = 1;
int state = 0;
char *keywords[] = {"with","parameters","end","while","type","_main", "global" ,"parameter", "list", "input", "output", "int", "real", "endwhile", "if", "then", "endif", "read", "write", "return", "call", "record", "endrecord", "else"};

Table keywordsTable=create(53);
int j=0,tInd = 0;
for(j=0;j<24;j++)//24 is keyword table size
insert(keywordsTable,keywords,j);
char temp[100];
#define BUF_SIZE 256
#define thresh 10

char* twinBuf1;
char* twinBuf2;
int i, end,flag=0,end1,end2,ans=1;
FILE *fp;
char* allocate(char* twinBuf)
{
    twinBuf = (char*)malloc(sizeof(char)*BUF_SIZE);
    return twinBuf;
}
char getNextChar()
{
// assuming memory for this is already allocated
        char temp1;
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
	    printf("%c",str[i]);
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

TokenInfo nextToken(){//char *buf,int *index,int end){
	// assuming fp = fopen("language.txt") is written in main before calling
	TokenInfo token = (TokenInfo)malloc(sizeof(struct tokenInfo));
	//end = fread(twinBuf0,sizeof(char),256,fp);//First fread is from here
	while(1){
	    char c=getNextChar();
	    if(c == '\n'){
	        i++;
	        lineNo++;
	    }
		switch(state){
		    
			case 0:
				temp[tInd] = c;
			    tInd++;
				switch(c){
					case '%' : 						//move to state 1
						state = 1;
						i++;
						break;
					case 'a' ... 'z' : 
						if(c>='b' && c<='d'){
							state = 4; i++; break;	
						}
						else{
							state = 3; i++; break;
						}
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
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SQL"); 
						i++;
						state = 18;
						break;
                    case ']':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SQR"); 
						i++;
						state = 18;
						break;
                    case ',':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_COMMA"); 
						i++;
						state = 18;
						break;						
                    case ';':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SEM"); 
						i++;
						state = 18;
						break;
                    case ':':
                        token->lineNo = lineNo;
  						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_COLON"); 
						i++;
						state = 18;
						break;
                    case '.':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_DOT"); 
						i++;
						state = 18;
						break;						

                    case '(':
                        token->lineNo = lineNo;
						strcpy(token->lexeme, temp);
						tInd = 0;
						strcpy(token->Token,"TK_OP"); 
						i++;
						state = 18;
						break;		
                    case ')':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_CP"); 
						i++;
						state = 18;
						break;
                    case '+':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_PLUS"); 
						i++;
						state = 18;
						break;
				    case '-':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_MINUS"); 
						i++;
						state = 18;
						break;
                    case '*':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_MUL"); 
						i++;
						state = 18;
						break;
					case '/':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_DIV"); 
						i++;
						state = 18;
						break;
					case '~':
                        token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_NOT"); 
						i++;
						state = 18;
						break;                      //'[', ']', '|'...etc. are handled below 
							
						default:;	
											//need to update
				}
			case 1:
				switch(c){
					case '\n': 							//create_token and move to state 2
						i++;
						lineNo++;
						state = 2;
						break;
	
					default:
						while(i<end && c!='\n')	//stay in state 1 while iterating the inputs
							c = getNextChar();
							temp[tInd] = c;
							tInd++;							
							i++;
						break;
				}
			case 2:
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_COMMENT");
					state = 0;
					return token;	//return token TK_COMMENT
            		
			case 3:	
				//yahan doubt hai 
				while(i<end && (c<='z' && c>='a'))
				{
						c = getNextChar();
						temp[tInd] = c;
						tInd++;						
						i++;
				}
					i--;
					char* arr;                                    // do we need to allocate memory here?
					strcpy(arr,temp);
					link tok = lookup(keywordsTable,arr,char *keywords[]);
					if(tok==NULL){
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_FIELDID");
						state = 0;  
						return token;			
					}
					else{
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,keywords[tok->index]);
						state = 0; 
						return token;
					}
				
			case 4:	
					temp[tInd] = c;
					tInd++;	
					switch(c){
						case 'a' ... 'z': state=3;i++;break;
						case '2' ... '7': state=5;i++;break;
						default: ;//error handling				
					}

			case 5:		/*if(c>='2' && c<='7'){
						state = 6; i++; break;					
					}	
					while(i<end && c<='d' && c>='b')
						i++;
					i--;
					state = 5;
					token->lineNo = lineNo;
					strncpy(token->lexeme,buf,i-*index+1);
					strcpy(token->Token,"TK_ID"); 
					*index=i;
					return token;*/
					
			case 6:		while(i<end && c<='7' && c>='2'){
						c = getNextChar();
						temp[tInd] = c;
						tInd++;
						i++;
					}
					i--;	
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd=0;
					strcpy(token->Token,"TK_ID"); 
                    state = 0;
					return token;	

			case 7:		//switch to state 8 or 9
					while(i<end && c<='9' && c>='0'){
						char ci = getNextChar();
						temp[tInd] = ci;
						tInd++;
						i++;}
					
					char ck = getNextChar();
					switch(ck){
						case '.':	i++;state = 9;
							break;
						case '\n':  	i++;lineNo++;state=8; //if \n encountered increase lineNo and goto st8
						default:	i++;state = 8;
									
					}
					break;	
			case 8:									//return token TK_NUM and retract
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_NUM"); 
					i--;
					state = 0;
					return token;	
			case 9:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case '0' ... '9':
						i++;
						state = 10;
						break;
					//case '\n':  i++;lineNo++;
					default:   	;						//error it is TK_ERROR
				}
			case 10:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case '0' ... '9':						//move to state 11
						i++;
						state = 11;
						break;
					default:	;							//error it is
				}

			case 11:								//return token TK_RNUM 
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_RNUM"); 
					state = 0;
					return token;
			
			case 12:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case 'a' ... 'z':
						i++;
						state = 13;
						break;
					case 'A' ... 'Z':
						i++;
						state = 13;
						break;
					//case '\n':  i++;lineNo++;
					default:   	;						//error it is TK_ERROR
					}

			case 13:	while(i<end && ((c<='z' && c>='a') || (c<='Z' && c>='A'))){
						c = getNextChar();
						temp[tInd] = c;
						tInd++;
						i++;}
					
					switch(c){
					case '0' ... '9':
						i++;
						state = 15;
						break;
					//case '\n':  i++;lineNo++;
					default:   i++;state = 14;
					}
			
			case 14:	
					char* arr;                                    // do we need to allocate memory here?
					strcpy(arr,temp);
					link tok = lookup(keywordsTable,arr,char *keywords[]);
					if(tok==NULL){
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_FUNID");
						state = 0;  
						i--; return token;			
					}
					else{
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,keywords[tok->index]);
						state = 0;  
						i--; return token;
					}

			case 15: 	while(i<end && c<='9' && c>='0'){
						c = getNextChar();
						temp[tInd] = c;
						tInd++;
						i++;}
					i--;
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_FUNID"); 
					state = 0;
					return token;

			case 16:
					temp[tInd] = c;
					tInd++;	
					switch(c){
						case 'a' ... 'z': i++; state=17;break;
						//case '\n':  i++;lineNo++;error
						default: ;//TK_ERROR				
					}
			case 17: 	while(i<end && c<='z' && c>='a'){
						c = getNextChar();
						temp[tInd] = c;
						tInd++;
						i++;}
					i--;
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd++;
					strcpy(token->Token,"TK_RECORDID");
					state = 0; 
					return token;

			case 18:	return token;			// return one letter tokens '[' ,';'etc
					
			case 19:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '&' :i++;state=20;	
							break;
						default:   ;						//error
					}
						
			case 20:
					temp[tInd] = c;
					tInd++;
					switch(c){						//return TK_AND
						case '&' :i++;	state=21;break;
						default:		;				//error
					}
			
			case 21:
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_AND"); 
						state = 0;
						return token;
				

			case 22:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '@' :i++;state=20;	
							break;
						default:	;					//error
					}
						
			case 23:
					temp[tInd] = c;
					tInd++;
					switch(c){								//return TK_OR
						case '@' :i++;	
							state=24;break;
						default:	;					//error
					}
			case 24:
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_OR"); 
						state = 0;
						return token;
			case 25:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '=' :i++;			
							state = 30;
							break;
						case '-' : i++;
							state=26;
							break;
		
					}

			case 26 :	
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '-' :i++;			
							state = 27;
							break;
						default:	;			//error
					}
			case 27:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '-' :i++;			
							state = 28;
							break;
						default:		;		//error
					}
			case 28:
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_ASSIGNOP"); 
						state = 0; 
						return token;

			case 29:					//return TK_LT
					token->lineNo = lineNo;
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_LT"); 
					i--;
					state = 0;
					return token;

			case 30:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '=' :i++;			//return TK_LE
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_LE"); 
						state = 0;
						return token;
					}

			case 31:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '=' :i++;			
						state=33;
						break;
						default:i++;		;				
						state=32;
					}
		
			case 32:
						token->lineNo = lineNo;			//return TK_GT and retract
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_GT"); 
						i--;
						state = 0;
						return token;

			case 33:
						token->lineNo = lineNo;			//return TK_GE
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_GE");
						state = 0;
						return token;

			case 34:
					temp[tInd] = c;
					tInd++;
					switch(c){							// move to state 35
						case '=':state = 35;i++;break;
						default:		;				//error
					}
			case 35:
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_EQ");
						state = 0;
						return token;
					
			case 36:
					temp[tInd] = c;
					tInd++;
					switch(c){						//return TK_NE
						case '=':i++;
							state=37;break;
						default:		;				//error
					}
			case 37:
						token->lineNo = lineNo;
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_NE");
						state = 0;
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

