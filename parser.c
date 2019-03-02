#include "parser.h"
#include "HashTable.h"


char *tokens[]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR","TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL","TK_COMMA", "TK_SEM","TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL", "TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE","eps","DOLLAR"};  
char *nonterminals[]={
	"program",
	"mainFunction",
	"otherFunctions",
	"function",
	"input_par",
	"output_par",
	"parameter_list",
	"dataType",
	"primitiveDatatype",
	"constructedDatatype",
	"remaining_list",
	"stmts",
	"typeDefinitions",
	"typeDefinition",
	"fieldDefinitions",
	"fieldDefinition",
	"moreFields",
	"declarations",
	"declaration",
	"global_or_not",
	"otherStmts",
	"stmt",
	"assignmentStmt",
	"iterativeStmt",
	"conditionalStmt",
	"ioStmt",
	"funCallStmt",
	"singleOrRecId",
	"new_24",
	"outputParameters",
	"inputParameters",
	"elsePart",
	"allVar",
	"arithmeticExpression",
	"expPrime",
	"term",
	"termPrime",
	"factor",
	"highPrecedenceOperator",
	"lowPrecedenceOperators",
	"all",
	"all_t",
	"temp",
	"booleanExpression",
	"var",
	"logicalOp",
	"relationalOp",
	"returnStmt",
	"optionalReturn",
	"idList",
	"more_ids"};


Table terminals=NULL;//HashTable to store Terminals
Table nonTerminals=NULL;//HashTable to store non Terminals
void initializeTNT()
//initializes both Terminals and Non Terminals hash tables
{
	int i=0;
	if(terminals==NULL){
		terminals=create(97);
		for(i=0;i<terminalsSize;i++)//54 is terminals size
			insert(terminals,tokens,i);
	}
	if(nonTerminals==NULL){
		nonTerminals=create(97);
		for(i=0;i<nonTerminalsSize;i++)
			insert(nonTerminals,nonterminals,i);
	}
}

grammar* newNode(char *temp)			//new grammar node
//returns a new grammar node
{
	grammar* g=(grammar*)malloc(sizeof(grammar));
	strcpy(g->name,temp);
	g->more=NULL;
	g->next=NULL;
	return g;
}

grammar* makeNewRule(FILE* fp,int d)		//makes a new grammar rule and returns grammar*
//makes a new Rule by scanning d space separated strings in a line
{
	int i=0;
	char temp[30];
	fscanf(fp,"%s",temp);
	grammar* head=newNode(temp),*curr;
	curr=head;
	for(i=0;i<d-1;i++)
	{
		fscanf(fp,"%s",temp);
		curr->next=newNode(temp);
		curr=curr->next;
	}
	return head;
}

Grammar* makeGrammar(char* fileName){			// making the Grammar data structures
	FILE* f=fopen(fileName,"r");
	if(f==NULL)
	{
		printf("File Not opened\n");
		return NULL;
	}
	
	initializeTNT();
	

	Grammar *g=(Grammar *)malloc(sizeof(Grammar));
	g->arr=(grammar**)malloc(sizeof(grammar*)*nonTerminalsSize);
	g->size=nonTerminalsSize;//initial size for array of Grammar rules
	grammar** arr=g->arr;//using arr as temp pointer
	
	int d=0,i=0;
	for(i=0;i<nonTerminalsSize;i++)
	//	arr[i]=(grammar*)malloc(sizeof(grammar));
		arr[i]=NULL;
	char temp[30];
	link check=NULL;
	while(fscanf(f,"%s %d",temp,&d)!=-1)//scan till EOF
	{
	//	printf("%s %d\n",temp,d);
		check=lookup(nonTerminals,temp,nonterminals);
		grammar* head;
	//	if(arr[check->index]->more==NULL)//if this is the first rule to be added 
	//		arr[check->index]->more=makeNewRule(fp,d);
		if(arr[check->index]==NULL){//if this is the first rule to be added 
			arr[i]=(grammar*)malloc(sizeof(grammar));
			arr[check->index]=makeNewRule(f,d);
		}
		else
		{
			head=makeNewRule(f,d);
			head->more=arr[check->index]->more;
			arr[check->index]->more=head;
		}
	}
	fflush(f);
	return g;
}

void printGrammar(Grammar *g)		//prints the already made grammar
{
    int size=g->size;
    grammar** arr=g->arr,*temp,*temp1,*temp2;
    int i=0;
    for(i=0;i<size;i++)
    {
        temp=arr[i];
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
} 
