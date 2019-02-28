#include "lexer.h"
#define BUF_SIZE 256

int lineNo = 1,state = 0,j=0,tInd = 0;
char* twinBuf1,*twinBuf2;
Table keywordsTable;
char temp[100];
int i=0, end,flag=0,end1,end2,ans=1;
FILE *fp;
void initialize(FILE *f)
{
	int tableSize=53;
	twinBuf1 = (char*)malloc(sizeof(char)*BUF_SIZE);
    twinBuf2 = (char*)malloc(sizeof(char)*BUF_SIZE);

	keywordsTable=create(tableSize);
	for(j=0;j<24;j++)//24 is keyword table size
		insert(keywordsTable,keywords,j);
	fp=f;
}
char getNextChar()
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
	link tok;
	//end = fread(twinBuf0,sizeof(char),256,fp);//First fread is from here
	while(1){
	    char c=getNextChar();
	    while(c == '\n'){
	        c=getNextChar();
	        lineNo++;
	    }
	    if(c=='\0')return NULL;
		switch(state){

			case 0:
				temp[tInd] = c;
			    tInd++;
				switch(c){
					case '%' : 						//move to state 1
						state = 1;
						break;
					case 'a' ... 'z' :
						if(c>='b' && c<='d'){
							state = 4; break;
						}
						else{
							state = 3;  break;
						}
					case '0' ... '9':				// move to state 7
						state=7;
						break;
					case '_':
					    state = 12;
					    break;
					case '#':
					    state = 16;
					    break;
				    case '&':
				        state = 18 ;
			            break;                 //'[', ']', '|'...etc. are handled below
					case '@':
					    state = 21;
					    break;
				    case  '<':
				        state = 24;
				        break;
			        case '>':
			            state = 30;
			            break;
		            case '=':
		                state = 33;
		                break;
	                case '!':
	                    state = 35;
	                    break;
                    case '[':					//rest all go to state 18 making single tokens
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SQL");
						state = 18;
						break;
                    case ']':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SQR");
						state = 18;
						break;
                    case ',':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_COMMA");
						state = 18;
						break;
                    case ';':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_SEM");
						state = 18;
						break;
                    case ':':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
  						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_COLON");
						state = 18;
						break;
                    case '.':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_DOT");
						state = 18;
						break;

                    case '(':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme, temp);
						tInd = 0;
						strcpy(token->Token,"TK_OP");
						state = 18;
						break;
                    case ')':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_CP");
						state = 18;
						break;
                    case '+':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_PLUS");
						state = 18;
						break;
				    case '-':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_MINUS");
						state = 18;
						break;
                    case '*':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_MUL");
						state = 18;
						break;
					case '/':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_DIV");
						state = 18;
						break;
					case '~':
                        token->lineNo = lineNo;
                        temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_NOT");
						state = 18;
						break;                      //'[', ']', '|'...etc. are handled below

						default:;
											//need to update
				}
			case 1:
				switch(c){
					case '\n': 							//create_token and move to state 2
						lineNo++;
						state = 2;
						break;

					default:
						while(i<end && c!='\n')	//stay in state 1 while iterating the inputs
							c = getNextChar();
							if(c=='\0')return NULL;
							temp[tInd] = c;
							tInd++;
						if(c=='\0')return NULL;
						break;
				}
			case 2:
					token->lineNo = lineNo;
					temp[tInd] = '\0';
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
						if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
				}
					i-=2;
					// char* arr;                                    // do we need to allocate memory here?
					// strcpy(arr,temp);
					temp[tInd]='\0';
					tok = lookup(keywordsTable,temp,keywords);
					if(tok==NULL){
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_FIELDID");
						state = 0;
						return token;
					}
					else{
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,keywords_tokens[tok->index]);
						state = 0;
						return token;
					}

			case 4:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case 'a' ... 'z': state=3;break;
						case '2' ... '7': state=5;break;
						default: ;//error handling
					}

			case 5:	
					if(c>='2' && c<='7'){
						state = 6; break;
					}
					while( c<='d' && c>='b')
					{
						c = getNextChar();
						if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
					}	
					i-=2;
					state = 5;
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_ID");
					return token;

			case 6:		while(i<end && c<='7' && c>='2'){
						c = getNextChar();
						if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
					}
					i-=2;
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd=0;
					strcpy(token->Token,"TK_ID");
                    state = 0;
					return token;

			case 7:		//switch to state 8 or 9
					while(i<end && c<='9' && c>='0'){
						c = getNextChar();
						if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
					}

				 	c = getNextChar();
				 	if(c=='\0')return NULL;
					switch(c){
						case '.':	state = 9;
							break;
						case '\n':  	lineNo++;state=8; //if \n encountered increase lineNo and goto st8
						default:	state = 8;

					}
					break;
			case 8:									//return token TK_NUM and retract
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_NUM");
					token->tkVal.intVal = stringToInteger(temp);
					i-=2;
					state = 0;
					return token;
			case 9:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case '0' ... '9':
						state = 10;
						break;
					//case '\n':  lineNo++;
					default:   	;						//error it is TK_ERROR
				}
			case 10:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case '0' ... '9':						//move to state 11
						state = 11;
						break;
					default:	;							//error it is
				}

			case 11:								//return token TK_RNUM
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_RNUM");
					token->tkVal.floatVal =  stringToFloat(temp);
					state = 0;
					return token;

			case 12:
					temp[tInd] = c;
					tInd++;
				switch(c){
					case 'a' ... 'z':
						state = 13;
						break;
					case 'A' ... 'Z':
						state = 13;
						break;
					//case '\n':  lineNo++;
					default:   	;						//error it is TK_ERROR
					}

			case 13:	while(i<end && ((c<='z' && c>='a') || (c<='Z' && c>='A'))){
						c = getNextChar();
				    	if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
					}

					switch(c){
					case '0' ... '9':
						state = 15;
						break;
					//case '\n':  lineNo++;
					default:   state = 14;
					}

			case 14:
					temp[tInd]='\0';
					tok = lookup(keywordsTable,temp,keywords);
					if(tok==NULL){
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_FUNID");
						state = 0;
						i-=2; return token;
					}
					else{
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,keywords_tokens[tok->index]);
						state = 0;
						i-=2; return token;
					}

			case 15: 	while(i<end && c<='9' && c>='0'){
						c = getNextChar();
					    if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
						}
					i -= 2;
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_FUNID");
					state = 0;
					return token;

			case 16:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case 'a' ... 'z':  state=17;break;
						//case '\n':  lineNo++;error
						default: ;//TK_ERROR
					}
			case 17: 	while(i<end && c<='z' && c>='a'){
						c = getNextChar();
					    if(c=='\0')return NULL;
						temp[tInd] = c;
						tInd++;
						}
					i -=2;
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_RECORDID");
					state = 0;
					return token;

			case 18:	return token;			// return one letter tokens '[' ,';'etc

			case 19:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '&' :state=20;
							break;
						default:   ;						//error
					}

			case 20:
					temp[tInd] = c;
					tInd++;
					switch(c){						//return TK_AND
						case '&' :	state=21;break;
						default:		;				//error
					}

			case 21:
						token->lineNo = lineNo;
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_AND");
						state = 0;
						return token;


			case 22:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '@' :state=20;
							break;
						default:	;					//error
					}

			case 23:
					temp[tInd] = c;
					tInd++;
					switch(c){								//return TK_OR
						case '@' :
							state=24;break;
						default:	;					//error
					}
			case 24:
						token->lineNo = lineNo;
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_OR");
						state = 0;
						return token;
			case 25:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '=' :
							state = 30;
							break;
						case '-' :
							state=26;
							break;

					}

			case 26 :
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '-' :
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
						temp[tInd] = '\0';
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_ASSIGNOP");
						state = 0;
						return token;

			case 29:					//return TK_LT
					token->lineNo = lineNo;
					temp[tInd] = '\0';
					strcpy(token->lexeme,temp);
					tInd = 0;
					strcpy(token->Token,"TK_LT");
					i -=2;
					state = 0;
					return token;

			case 30:
					temp[tInd] = c;
					tInd++;
					switch(c){
						case '=':			//return TK_LE
						token->lineNo = lineNo;
						temp[tInd] = '\0';
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
						case '=':
						state=33;
						break;
						default:;		;
						state=32;
					}

			case 32:
						token->lineNo = lineNo;
						temp[tInd] = '\0';			//return TK_GT and retract
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_GT");
						i -=2;
						state = 0;
						return token;

			case 33:
						token->lineNo = lineNo;
						temp[tInd] = '\0';			//return TK_GE
						strcpy(token->lexeme,temp);
						tInd = 0;
						strcpy(token->Token,"TK_GE");
						state = 0;
						return token;

			case 34:
					temp[tInd] = c;
					tInd++;
					switch(c){							// move to state 35
						case '=':state = 35;break;
						default:		;				//error
					}
			case 35:
						token->lineNo = lineNo;
						temp[tInd] = '\0';
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
						temp[tInd] = '\0';
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