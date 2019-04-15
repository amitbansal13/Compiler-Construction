/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/

#include "symbolTableDef.h"
#include "parser.h"
#include "parserDef.h"
#define WIDTH_OF_INT 2
#define WIDTH_OF_REAL 4

int hash(char arr[],int a,int tableSize){
	long int key=0,i=0,prod=1;
	while(arr[i])
	{
		key=arr[i]+key*prod;
		prod*=a;
		prod%=tableSize;
		key%=tableSize;
		i++;
	}
	return key%tableSize;
}

/////////////////// IDENTIFIER TABLE

idTable createID(int tableSize){
	idTable t=(idTable)malloc(sizeof(struct idtable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(ID*)malloc(tableSize*sizeof(ID));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL;
	}
	return t;
}
ID newID( char* name, int offset, int type, int width, char *tname){
	ID id=(ID)malloc(sizeof(struct id));
	id->name=strdup(name);
	id->offset=offset;
	id->type=type;
	id->width=width;
	id->tname=strdup(tname);
	id->next=NULL;
	return id;
}
idTable insertID(idTable t,char* name, int offset, int type, int width, char *tname){
	int i=hash(name,t->a,t->tableSize);
	ID temp=newID(name,offset,type,width,tname);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

ID lookupID(idTable t,char arr[]){
	ID res=NULL;
	int i=hash(arr,t->a,t->tableSize);
	ID temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}


//////////////////FUNCTION TABLE

funcTable createFunc(int tableSize){
	funcTable t=(funcTable)malloc(sizeof(struct functable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(Func*)malloc(tableSize*sizeof(Func));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL;
	}
	return t;
}
Func newFunc( char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localTable,int width){
	Func f=(Func)malloc(sizeof(struct func));
	f->name=strdup(name);
	f->offset=offset;
	f->noOutput=noOutput;
	f->noInput=noInput;
	f->width=width;
	f->inputType=inputType;
	f->outputType=outputType;
	f->localTable=localTable;
	f->next=NULL;
	return f;
}
funcTable insertFunc(funcTable t,char* name,int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width){
	int i=hash(name,t->a,t->tableSize);
	Func temp=newFunc(name,offset,noInput, noOutput, inputType, outputType,localtable,width);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

Func lookupFunc(funcTable t,char arr[]){
	Func res=NULL;
	int i=hash(arr,t->a,t->tableSize);
	Func temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}


/////////////// Record Table

recTable createRec(int tableSize){
	recTable t=(recTable)malloc(sizeof(struct rectable));
	t->tableSize=tableSize;
	t->a=31;//setting a to some prime number to be used for horner rule
	t->table=(Rec*)malloc(tableSize*sizeof(Rec));
	int i=0;
	for(i=0;i<tableSize;i++){
		(t->table)[i]=NULL;
	}
	return t;
}
Rec newRec(char* name, int type, int width, int noField, int* fieldtype, char** fieldid){
	Rec r=(Rec)malloc(sizeof(struct rec));
	r->name=strdup(name);
	r->typeIndex=type;
	r->width=width;
	r->noField=noField;
	r->fieldtype=fieldtype;
	r->fieldid=fieldid;
	r->next=NULL;
	return r;
}
recTable insertRec(recTable t,char* name, int type, int width, int noField, int* fieldtype, char** fieldid){
	int i=hash(name,t->a,t->tableSize);
	Rec temp=newRec(name,  type,width, noField, fieldtype, fieldid);
	temp->next=t->table[i];
	t->table[i]=temp;
	return t;
}

Rec lookupRec(recTable t,char arr[]){
	Rec res=NULL;
	int i=hash(arr,t->a,t->tableSize);
	Rec temp=t->table[i];
	while(temp)
	{
		if(strcmp(temp->name,arr)==0)return temp;
		temp=temp->next;
	}
	return res;
}

char* printType(recTable t,char *idname)//return a string containing the type of idname 
{
	if(strcmp("int",idname)==0)return idname;
	if(strcmp("real",idname)==0)return idname;
	Rec r=lookupRec(t,idname);
	int n=r->noField;
	int *fieldtype=r->fieldtype;
	char *arr=(char*)malloc(1000*sizeof(char));
	int l=0;
	for(int i=0;i<n-1;i++)
	{
		if(fieldtype[i]==0)
		{
			arr[l++]='i';arr[l++]='n';arr[l++]='t';
		}
		else{
			arr[l++]='r';arr[l++]='e';arr[l++]='a';arr[l++]='l';	
		}
		arr[l++]=' '; 
		arr[l++]='x';
		arr[l++]=' ';
	}
	if(fieldtype[n-1]==0)
	{
		arr[l++]='i';arr[l++]='n';arr[l++]='t';
	}
	else{
		arr[l++]='r';arr[l++]='e';arr[l++]='a';arr[l++]='l';	
	}
	arr[l]='\0';
	return arr;
}

void printGlobalTable(idTable t,recTable rec)
{
	int n=t->tableSize;
	ID* table=t->table;
	for(int i=0;i<n;i++)
	{
		ID temp=table[i];
		while(temp)
		{
			if(temp->name)
			printf("%20s %20s %20s %20s\n",temp->name,printType(rec,temp->tname),"global","-");
			temp=temp->next;
		}
	}
}

void printRecTable(recTable t)
{
	int n=t->tableSize;
	Rec* table=t->table;
	for(int i=0;i<n;i++)
	{
		Rec temp=table[i];
		while(temp)
		{
			if(temp->name)
			printf("%s %d %d %d\n",temp->name,temp->typeIndex,temp->width,temp->noField);
			temp=temp->next;
		}
	}
}


void printFuncTable(funcTable t,recTable rec)
{
	int n=t->tableSize;
	Func* table=t->table;
	for(int i=0;i<n;i++)
	{
		Func temp=table[i];
		while(temp)
		{
			idTable localTable =temp->localTable;
			for(int j=0;j<localTable->tableSize;j++)
			{
				ID temp1=localTable->table[j];
				while(temp1)
				{
					if(temp1->name)
					printf("%20s %20s %20s %20d\n",temp1->name,printType(rec,temp1->tname),temp->name,temp1->offset);
					temp1=temp1->next;
				}
			}
			temp=temp->next;
		}
	}
}

TreeNode getStmt(TreeNode temp, int lim){	//get limNumber children
	int hops;
	TreeNode childNext = temp->children;

	for(hops=0;hops<lim;hops++){
		childNext = childNext->next;
	}
	return childNext;
}

int getType(TreeNode t,recTable table)
{
	int index=t->index;
	if(strcmp(tokens[index],"TK_INT")==0)return 0;
	else if(strcmp(tokens[index],"TK_REAL")==0)return 1;
	Rec temp=lookupRec(table,t->token_info->lexeme);
	if(temp==NULL)
	return -1;
	return temp->typeIndex;
}

int getWidth(TreeNode t, recTable table)
{
	int index=t->index;
	if(strcmp(tokens[index],"TK_INT")==0)return WIDTH_OF_INT;
	else if(strcmp(tokens[index],"TK_REAL")==0)return WIDTH_OF_REAL;
	Rec temp=lookupRec(table,t->token_info->lexeme);
	if(temp==NULL)return -1;
	return temp->width;
}

int getChildrenNo(TreeNode node){//returns no of children of node
	TreeNode child = node->children;
	int count=0;
	while(child!=NULL){
		count++;
		child=child->next;
	}
	return count;
}

int symbolTablePopulate(funcTable func, recTable rec, idTable identifier, ParseTree pTree)
{
	TreeNode root = pTree->root;
	TreeNode childList = root->children;
	int gOffset=0;//global offset value
	char* idname;
	int* typeOfField;
	char** idField;
	int err = 0;//-1 for error 
	int width;
	int count;//number of fields
	int tindex=1; //to store the index of each record type



	//populating typerecords of other functions
	while(childList->next!=NULL)
	{

		TreeNode temp = childList;
		
		TreeNode typeChild = getStmt(temp, 3)->children->children;//pointer to children of typedefinitions
		
		while(typeChild!=NULL)
		{
			count = 10;
			tindex++;
			width = 0;
			TreeNode tempChild = typeChild;
			idname = strdup(tempChild->children->token_info->lexeme);//name of recordid
			
			typeOfField = malloc(sizeof(int)*count);
			idField = malloc(sizeof(char*)*count);

			TreeNode iter1 = tempChild->children->next;//iter1 points to 1st fieldDef
			
			int index = 1;
			while(iter1!=NULL)
			{

				if(index >= 2){
					//start comparing the field ids to check if there is any redunant declarations
					TreeNode iter2 = tempChild->children->next;
					while(iter2!=iter1){

						if(strcmp(iter1->children->next->token_info->lexeme,iter2->children->next->token_info->lexeme)==0)
						{
							printf("Line %u: Repetition of field names\n",iter1->children->next->token_info->lineNo);
							err=-1;
						}

						iter2 = iter2->next;
					}	
				}
				//count is the size of idField and typeoOfField
				if(index-1 < count)
				{
					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);//fieldid of <fieldDefinition>
					typeOfField[index-1]=strcmp(tokens[iter1->children->index],"TK_INT")==0?0:1;

					if(typeOfField[index-1]==0)
						width += WIDTH_OF_INT;//increment width of record by WIDTH_OF_INT
					else
						width += WIDTH_OF_REAL;	
				}
				//index-1==count, i.e. more number of field ids present->increment the size of idField and typeField
				else {
					count+=10;
					idField = realloc(idField,sizeof(char*)*count);
					typeOfField = realloc(typeOfField, sizeof(int)*count);

					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
					typeOfField[index-1]=strcmp(tokens[iter1->children->index],"TK_INT")==0?0:1;

					if(typeOfField[index-1]==0)
						width += WIDTH_OF_INT;
					else
						width += WIDTH_OF_REAL;
				}

				iter1 = iter1->next;
				index++;
			}
			//insert a record into the record table with the field ids obtained
			if(lookupRec(rec, idname)==NULL)
				insertRec(rec, idname, tindex, width , index-1, typeOfField,idField); 
			else
			{
				printf("Line %u: Record <%s> defined before\n",tempChild->children->token_info->lineNo, idname);
				err=-1;
			}

			typeChild = typeChild->next;
		}
		childList = childList->next;
	}


	//MAIN FUNCTION TYPERECORDS
	TreeNode main = childList;
	TreeNode typeDef = main->children->children->children;
	
	while(typeDef!=NULL){
		count = 10;
		tindex++;
		width = 0;
		TreeNode tempChild = typeDef;
		idname = strdup(tempChild->children->token_info->lexeme);
		
		typeOfField = malloc(sizeof(int)*count);
		idField = malloc(sizeof(char*)*count);

		TreeNode iter1 = tempChild->children->next;//iter1 points to 1st fieldDef
		
		int index = 1;
		while(iter1!=NULL){
			
			if(index >= 2){
				TreeNode iter2 = tempChild->children->next;
				while(iter2!=iter1){

					if(strcmp(iter1->children->next->token_info->lexeme,iter2->children->next->token_info->lexeme)==0)
					{
						printf("Line %u: Repetition of field names \n",iter1->children->next->token_info->lineNo);
						err=-1;
					}

					iter2 = iter2->next;
				}	
			}
			
			if(index-1 < count)
			{
				idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
				typeOfField[index-1]=strcmp(tokens[iter1->children->index],"TK_INT")==0?0:1;

				if(typeOfField[index-1]==0)
					width += WIDTH_OF_INT;
				else
					width += WIDTH_OF_REAL;	
			}
			else {
				count+=10;
				idField = realloc(idField,sizeof(char*)*count);
				typeOfField = realloc(typeOfField, sizeof(int)*count);

				idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
				typeOfField[index-1]=strcmp(tokens[iter1->children->index],"TK_INT")==0?0:1;

				if(typeOfField[index-1]==0)
					width += WIDTH_OF_INT;
				else
					width += WIDTH_OF_REAL;
			}

			iter1 = iter1->next;
			index+=1;
		}
		
		if(lookupRec(rec, idname)==NULL)
			insertRec(rec, idname, tindex, width , index-1, typeOfField,idField); //noField
		else
		{
			printf("Line %u: Record <%s> defined before\n",tempChild->children->token_info->lineNo, idname);
			err=-1;
		}

		typeDef = typeDef->next;
	}


	//checking for global declarations in other functions
	childList=root->children;
	while(childList->next)//looping through function list
	{
		TreeNode declarations=getStmt(childList,3)->children->next;
		TreeNode declaration=declarations->children;
		while(declaration)
		{
			if(getChildrenNo(declaration)==2){
				declaration=declaration->next;
				continue;
			}
			ID temp=lookupID(identifier,declaration->children->next->token_info->lexeme);
			if(temp==NULL)
			{
				int type=getType(declaration->children,rec);
				if(type==-1)
				{
					printf("Line %d: Type not found for global variable <%s>  \n", declaration->children->next->token_info->lineNo, declaration->children->next->token_info->lexeme);
					return -1;
				}
				int width=getWidth(declaration->children,rec);
				
				insertID(identifier,declaration->children->next->token_info->lexeme,gOffset,type,width,declaration->children->token_info->lexeme);
				
				gOffset+=width;
			}
			else{
				printf("Line %d: Multipe declaration for global variable <%s> \n",declaration->children->next->token_info->lineNo, declaration->children->next->token_info->lexeme );
			}
			declaration=declaration->next;
		}
		childList=childList->next;
	}

	main=childList;
	TreeNode declaration=main->children->children->next->children;
	while(declaration)
	{
		if(getChildrenNo(declaration)==2){
			declaration=declaration->next;
			continue;
		}
		ID temp=lookupID(identifier,declaration->children->next->token_info->lexeme);
		if(temp==NULL)
		{
			int type=getType(declaration->children,rec);
			if(type==-1)
			{
				printf("Line %d: Type not found for global variable <%s>  \n", declaration->children->next->token_info->lineNo, declaration->children->next->token_info->lexeme);
				return -1;
			}
			int width=getWidth(declaration->children,rec);
			
			insertID(identifier,declaration->children->next->token_info->lexeme,gOffset,type,width,declaration->children->token_info->lexeme);
				
		}
		else{
			printf("Line %d: Multipe declaration for global variable <%s> \n",declaration->children->next->token_info->lineNo, declaration->children->next->token_info->lexeme );
		}
		declaration=declaration->next;
	}

	//VARIABLE DECLARATIONS IN OTHER FUNCTIONS
	childList = root->children;
	int noParam = 0; //number of parameters
	while(childList->next!=NULL)
	{
		noParam = 10;
		TreeNode tempfunc = childList;//points to the first function node
		char* funid=tempfunc->children->token_info->lexeme;
		if(lookupFunc(func,funid)==NULL)
		{
			int offsetBegin = 0;
			int NoInpPar = getChildrenNo(tempfunc->children->next)/2; //number of TK_ID are half of total children(excluding <dataType>)
			int NoOutPar = getChildrenNo(tempfunc->children->next->next)/2;
			int* inPar = (int*) malloc(sizeof(int)*NoInpPar); //inout parameter types
			int* outPar = (int*) malloc(sizeof(int)*NoOutPar); //output parameter types
			idTable idLocal = createID(41);

			//root inpar list and insert ids into symbol table
			TreeNode inTraverse = tempfunc->children->next->children;//points to first children of in parameter list
			int ip=0;
			//traverse the complete list. 2*NoInPar => include the dataType nodes as well
			while(ip<2*NoInpPar)
			{
				inPar[ip/2] = getType(inTraverse,rec);
				if(inPar[ip/2]==-1)
				{
					printf("Line %u: No such type for <%s> \n",inTraverse->token_info->lineNo,inTraverse->token_info->lexeme);
					err=-1;
				}
				//check global table if the variable is already declared
				else if(lookupID(identifier, inTraverse->next->token_info->lexeme)!=NULL)
				{
					printf("Line %u: Variable <%s> is already declared globally\n",inTraverse->next->token_info->lineNo,inTraverse->next->token_info->lexeme);
				}
				else if(lookupID(idLocal, inTraverse->next->token_info->lexeme)==NULL)
				{
					int size = getWidth(inTraverse,rec);
					insertID(idLocal,inTraverse->next->token_info->lexeme, offsetBegin, inPar[ip/2], size, inTraverse->token_info->lexeme);
					offsetBegin+=size;
				}
				else
				{
					printf("Line %u: Input parameter <%s> already defined \n",inTraverse->next->token_info->lineNo, inTraverse->next->token_info->lexeme);
					err = -1;
				}

				inTraverse = inTraverse->next->next;
				ip+=2;
			}

			//root output param list and add to symbol table[if not added]
			TreeNode outTraverse = tempfunc->children->next->next->children;//points to first children of outpar list
			ip = 0;
			while(ip<2*NoOutPar)
			{
				
				outPar[ip/2] = getType(outTraverse,rec);
				if(outPar[ip/2]==-1)
				{
					printf("Line %u: No such type for <%s> \n",outTraverse->token_info->lineNo,outTraverse->token_info->lexeme);
					err=-1;
				}
				else if(lookupID(idLocal, outTraverse->next->token_info->lexeme)==NULL)
				{
					int size = getWidth(outTraverse,rec);
					insertID(idLocal,outTraverse->next->token_info->lexeme, offsetBegin, outPar[ip/2], size, outTraverse->token_info->lexeme);
					offsetBegin+=size;
				}
				else
				{
					printf("Line %u: Output parameter <%s> already defined \n",outTraverse->next->token_info->lineNo, outTraverse->next->token_info->lexeme);
					err = -1;
				}

				outTraverse = outTraverse->next->next;
				ip+=2;
			}

			//STMT DECLARATION

			TreeNode declare = getStmt(tempfunc,3)->children->next->children; //pointing to 1st declaration node
			
			while(declare!=NULL)
			{
				//traverse till we don't get local variables
				if(getChildrenNo(declare)==3){
					declare=declare->next;
					continue; 
				}
				//check if the local variable already has been globally declared
				if(lookupID(identifier,declare->children->next->token_info->lexeme)!=NULL)
				{
						printf("Line %u: Variable <%s> declared globally cannot have a local declaration \n", declare->children->next->token_info->lineNo,declare->children->next->token_info->lexeme);
						err=-1;
						declare=declare->next;
						continue;
				}
				idTable tabTemp = idLocal;
				if(lookupID(tabTemp, declare->children->next->token_info->lexeme)==NULL)
				{
					int dtype =  getType(declare->children,rec);//declare->children is <dataType>
					if(dtype==-1)
					{
						printf("Line %u: No such type for <%s> \n",declare->children->token_info->lineNo ,declare->children->token_info->lexeme);
						err=-1;
					}
					else
					{
						//get the size of the datatype of the variable and insert into id table
						int size = getWidth(declare->children,rec);
						insertID(tabTemp,declare->children->next->token_info->lexeme,offsetBegin, dtype, size, declare->children->token_info->lexeme);
						offsetBegin+=size;//update the offset by the size of the variables
					}
							
				}
					else
					{
						printf("Line %u: Variable <%s> already declared \n",declare->children->next->token_info->lineNo, declare->children->next->token_info->lexeme);
						err=-1;
					}
				declare = declare->next;
			}
				//insert the function into the function table alongwith its local table 
				insertFunc(func,tempfunc->children->token_info->lexeme,0, NoInpPar, NoOutPar, inPar, outPar,idLocal,offsetBegin); 
		}
		else{
			printf("Line %u: Overloaded functions not allowed. <%s> already defined\n", childList->children->token_info->lineNo,childList->children->token_info->lexeme);
			err=-1;
		}
		childList = childList->next;
	}


	// Main Function Declarations
	if(lookupFunc(func,"_main")==NULL)
	{
		int offsetBegin = 0;
		idTable idLocal = createID(41);
		TreeNode declare = childList->children->children->next->children; //pointing to 1st declaration node
			
		while(declare!=NULL){
			if(getChildrenNo(declare)==3){
				declare=declare->next;
			 	continue; 
			}
			if(lookupID(identifier,declare->children->next->token_info->lexeme)!=NULL)
			{
					printf("Line %u: Variable <%s> declared globally cannot have a local declaration \n", declare->children->next->token_info->lineNo,declare->children->next->token_info->lexeme);
					err=-1;
					declare=declare->next;
					continue;
			}
			idTable tabTemp = idLocal;
			if(lookupID(tabTemp, declare->children->next->token_info->lexeme)==NULL)
			{
				int dtype =  getType(declare->children,rec);
				if(dtype==-1)
				{
					printf("Line %u: No such type for <%s> \n",declare->children->token_info->lineNo ,declare->children->token_info->lexeme);
					err=-1;
				}
				else
				{
					int size = getWidth(declare->children,rec);
					insertID(tabTemp,declare->children->next->token_info->lexeme,offsetBegin, dtype, size, declare->children->token_info->lexeme);
					offsetBegin+=size;
				}
						
			}
				else
				{
					printf("Line %u: Variable <%s> already declared \n",declare->children->next->token_info->lineNo, declare->children->next->token_info->lexeme);
					err=-1;
				}
			declare = declare->next;
			}
		insertFunc(func,"_main",0, 0,0, NULL,NULL,idLocal,offsetBegin); 
	}
	else{
		printf("Main function defined twice.\n");
		err=-1;
	}
	return err==-1?err:gOffset;
}

		



