#include "symbolTableDef.h"
#include "parser.h"

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
funcTable insertFunc(funcTable t,char* name, int offset,int noInput, int noOutput, int* inputType, int* outputType,idTable localtable,int width){
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


void printIdTable(idTable t)
{
	int n=t->tableSize;
	ID* table=t->table;
	for(int i=0;i<n;i++)
	{
		ID temp=table[i];
		while(temp)
		{
			printf("%20s %20s %20s %20d\n",temp->name,temp->tname,"global",temp->offset);
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
			printf("%s %d %d %d\n",temp->name,temp->typeIndex,temp->width,temp->noField);
			temp=temp->next;
		}
	}
}


void printFuncTable(funcTable t)
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
					printf("%20s %20s %20s %20d\n",temp1->name,temp1->tname,temp->name,temp1->offset);
					temp1=temp1->next;
				}
			}
			temp=temp->next;
		}
	}
}

TreeNode getStmtChildren(TreeNode temp, int lim){
	int hops;
	TreeNode childNext = temp->children;

	for(hops=0;hops<lim;hops++){
		childNext = childNext->next;
	}
	return childNext->children;
}
TreeNode getNextNode(TreeNode temp, int lim){
	int hops;
	TreeNode childNext = temp;

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
	if(strcmp(keywords_tokens[index],"TK_INT")==0)return 2;
	else if(strcmp(keywords_tokens[index],"TK_REAL")==0)return 4;
	Rec temp=lookupRec(table,t->token_info->lexeme);
	if(temp==NULL)
		return -1;
	return temp->width;
}

int getChildrenNo(TreeNode node){
	TreeNode child = node->children;
	int count=0;
	while(child!=NULL){
		count++;
		child=child->next;
	}
	return count;
}

void symbolTablePopulate(funcTable func, recTable rec, idTable identifier, ParseTree pTree)
{
	TreeNode traverse = pTree->root;
	TreeNode childList = traverse->children;
	int gOffset=0;
	char* idname;
	int* typeOfField;
	char** idField;
	int RaiseError = 0;
	int width;
	int count;
	int tindex=1; //to store the index of each record type
	
	TreeNode tempStartChild = childList;

	while(childList->next!=NULL){

		//typedefinitions
		TreeNode temp = childList;
		
		TreeNode typeChild = getStmtChildren(temp, 3)->children;//pointer to children of typedefinitions

		
		while(typeChild!=NULL){
			count = 10;
			tindex++;
			width = 0;
			TreeNode tempChild = typeChild;
			idname = strdup(tempChild->children->token_info->lexeme);
			
			typeOfField = malloc(sizeof(int)*count);
			idField = malloc(sizeof(char*)*count);

			TreeNode iter1 = tempChild->children->next;//iter1 points to 1st fieldDef
			
			int index = 1;
			while(iter1!=NULL){

				if(index >= 3){
					TreeNode iter2 = tempChild->children->next;
					while(iter2->next!=iter1){

						if(strcmp(iter1->children->next->token_info->lexeme,iter2->children->next->token_info->lexeme)==0)
						{
							printf("Repetition of field name in line No %u \n",iter1->children->next->token_info->lineNo);
							RaiseError=-1;
						}

						iter2 = iter2->next;
					}	
				}
				
				if(index-1 < count)
				{
					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
					typeOfField[index-1]=(tokens[iter1->children->index]=="TK_INT")?0:1;

					if(typeOfField[index-1]==0)
						width += 4;
					else
						width += 8;	
				}
				else {
					count+=10;
					idField = realloc(idField,sizeof(char*)*count);
					typeOfField = realloc(typeOfField, sizeof(int)*count);

					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
					typeOfField[index-1]=(tokens[iter1->children->index]=="TK_INT")?0:1;

					if(typeOfField[index-1]==0)
						width += 4;
					else
						width += 8;
				}

				iter1 = iter1->next;
				index+=1;
			}
			
			if(lookupRec(rec, idname)==NULL)
				insertRec(rec, idname, tindex, width , index-1, typeOfField,idField); //noField
			else
			{
				printf("Error. Line No: %u  Same record defined before\n",tempChild->children->token_info->lineNo);
				RaiseError=-1;
			}

			typeChild = typeChild->next;
		}
		childList = childList->next;
	}


	//MAIN FUNCTION TYPERECORDS
	TreeNode main = childList;
	TreeNode typeDef = main->children->children;
	
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
				//required??
				if(index >= 3){
					TreeNode iter2 = tempChild->children->next;
					while(iter2->next!=iter1){

						if(strcmp(iter1->children->next->token_info->lexeme,iter2->children->next->token_info->lexeme)==0)
						{
							printf("Repetition of field name in line No %u \n",iter1->children->next->token_info->lineNo);
							RaiseError=-1;
						}

						iter2 = iter2->next;
					}	
				}
				
				if(index-1 < count)
				{
					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
					typeOfField[index-1]=(tokens[iter1->children->index]=="TK_INT")?0:1;

					if(typeOfField[index-1]==0)
						width += 4;
					else
						width += 8;	
				}
				else {
					count+=10;
					idField = realloc(idField,sizeof(char*)*count);
					typeOfField = realloc(typeOfField, sizeof(int)*count);

					idField[index-1]= strdup(iter1->children->next->token_info->lexeme);
					typeOfField[index-1]=(tokens[iter1->children->index]=="TK_INT")?0:1;

					if(typeOfField[index-1]==0)
						width += 4;
					else
						width += 8;
				}

				iter1 = iter1->next;
				index+=1;
			}
			
			if(lookupRec(rec, idname)==NULL)
				insertRec(rec, idname, tindex, width , index-1, typeOfField,idField); //noField
			else
			{
				printf("Error. Line No: %u  Same record defined before\n",tempChild->children->token_info->lineNo);
				RaiseError=-1;
			}

			typeDef = typeDef->next;
		}

			//checking for global declarations in other functions
		TreeNode temp2=NULL;
		idTable temp = identifier;
		while(tempStartChild->next !=NULL)
		{
			TreeNode temp1 = tempStartChild;
			TreeNode decChild = getStmtChildren(temp1,3)->children->next;
			while(decChild != NULL)
			{
				if(decChild->children != NULL)
					continue;
				ID id1 = lookupID(temp, decChild->children->children->next->token_info->lexeme);
				if(id1 == NULL)
				{
						int type = getType(decChild->children->children, rec);
						if(type == -1)
						{
							printf("Line = %d -> type not found for global variable: %s  \n", decChild->children->children->next->token_info->lineNo, decChild->children->children->next->token_info->lexeme);
							return;
						}
						int width = getWidth(decChild->children->children, rec);
						identifier = insertID(temp, decChild->children->children->next->token_info->lexeme, gOffset, type, width,decChild->children->children->token_info->lexeme);
						gOffset += width;
				}
				else
				{
					printf("Line = %d -> multipe declaration for global variable %s \n",decChild->children->children->next->token_info->lineNo, decChild->children->children->next->token_info->lexeme );
				}
				temp2 = decChild;
				decChild = decChild->children->next;
			}
			//checking for global declarations 	in main function
			decChild = temp2;

			while(decChild->children->next != NULL)
			{
				int type2 = getType(decChild->children->children, rec);
				if(type2 == -1)
				{
					printf("Line = %d -> type not found for global variable: %s  \n", decChild->children->children->next->token_info->lineNo, decChild->children->children->next->token_info->lexeme);
							return;
				}
				else
				{
					int width2 = getWidth(decChild->children->children, rec);
					identifier = insertID(temp, decChild->children->children->next->token_info->lexeme, gOffset,type2, width2 ,decChild->children->children->token_info->lexeme);
				}

			}
		}

		//VARIABLE DECLARATIONS IN OTHER FUNCTIONS
		childList = traverse->children;
		int noParam = 0; //number of parameters
		while(childList->next!=NULL)
		{
			noParam = 10;
			TreeNode tempfunc = childList;//points to the first function node
			if(lookupFunc(func,tempfunc->children->token_info->lexeme)==NULL)
			{
				int offsetBegin = 0;
				int NoInpPar = getChildrenNo(tempfunc->children->next)/2; //childrenNo is the  number of children of that node
				int NoOutPar = getChildrenNo(tempfunc->children->next->next)/2;
				int* inPar = (int*) malloc(sizeof(int)*NoInpPar); //inout parameter types
				int* outPar = (int*) malloc(sizeof(int)*NoOutPar); //output parameter types
				idTable idLocal = createID(41);

				//traverse inpar list and insert ids into symbol table
				TreeNode inTraverse = tempfunc->children->next->children;
				for(int ip = 0; ip<2*NoInpPar;ip+=2)
				{

					inPar[ip/2] = getType(inTraverse,rec);
					if(inPar[ip/2]==-1)
					{
						printf("Error. Line No: %u - No such type for %s \n",inTraverse->token_info->lineNo,inTraverse->token_info->lexeme);
						RaiseError=-1;
					}
					else if(lookupID(identifier, inTraverse->next->token_info->lexeme)!=NULL)
					{
						printf("Re-Declaration Error. Line No: %u  Variable <%s> is already declared globally\n",inTraverse->next->token_info->lineNo,inTraverse->next->token_info->lexeme);
					}
					else if(lookupID(idLocal, inTraverse->next->token_info->lexeme)==NULL)
					{
						int size = getWidth(inTraverse,rec);
						insertID(idLocal,inTraverse->next->token_info->lexeme, offsetBegin, inPar[ip/2], size, inTraverse->token_info->lexeme);
						offsetBegin+=size;
					}
					else
					{
						printf("Re-definition error. Line No: %u Identical input parameter already defined \n",inTraverse->next->token_info->lineNo);
						RaiseError = -1;
					}

					inTraverse = inTraverse->next->next;
				}

				//traverse output param list and add to symbol table[if not added]
				TreeNode outTraverse = tempfunc->children->next->next->children;
				for(int ip = 0; ip<2*NoOutPar;ip+=2)
				{

					outPar[ip/2] = getType(outTraverse,rec);
					if(inPar[ip/2]==-1)
					{
						printf("Error. Line No: %u - No such type for %s \n",outTraverse->token_info->lineNo,outTraverse->token_info->lexeme);
						RaiseError=-1;
					}
					else if(lookupID(idLocal, outTraverse->next->token_info->lexeme)==NULL)
					{
						int size = getWidth(outTraverse,rec);
						insertID(idLocal,outTraverse->next->token_info->lexeme, offsetBegin, outPar[ip/2], size, outTraverse->token_info->lexeme);
						offsetBegin+=size;
					}
					else
					{
						printf("Re-definition error. Line No: %u Identical input parameter already defined \n",outTraverse->next->token_info->lineNo);
						RaiseError = -1;
					}

					outTraverse = outTraverse->next->next;
				}

				//STMT DECLARATION

				TreeNode declare = getNextNode(tempfunc->children,3)->children->next->children; //pointing to 1st declaration node
				
				while(declare!=NULL){

					if(getChildrenNo(declare)==3) continue; //check
					if(lookupID(identifier,declare->children->next->token_info->lexeme)!=NULL)
					{
							printf("Error. Line No: %u Variable <%s> declared globally cannot have a local declaration \n", declare->children->next->token_info->lineNo,declare->children->next->token_info->lexeme);
							RaiseError=-1;
					}
					idTable tabTemp = idLocal;
					if(lookupID(tabTemp, declare->children->next->token_info->lexeme)==NULL)
					{
						int dtype =  getType(declare->children,rec);
						if(dtype==-1)
						{
							printf("Error. Line No: %u No such type for <%s> \n",declare->children->token_info->lineNo ,declare->children->token_info->lexeme);
							RaiseError=-1;
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
							printf("Re-declaration Error. Line No: %u Variable <%s> already declared \n",declare->children->next->token_info->lineNo, declare->children->next->token_info->lexeme);
							RaiseError=-1;
						}
					declare = declare->next;
					}
					insertFunc(func,tempfunc->children->token_info->lexeme,0, NoInpPar, NoOutPar, inPar, outPar,idLocal,offsetBegin); //check
				}
				else{
					printf("Error. Line No: %u Overloaded functions not allowed. <%s> already defined\n", childList->children->token_info->lineNo,childList->children->token_info->lexeme);
					RaiseError=-1;
				}
				childList = childList->next;
			}


		// Main Function Declarations
		if(lookupFunc(func,childList->children->token_info->lexeme)==NULL)
		{
			int offsetBegin = 0;
			idTable idLocal = createID(41);
			TreeNode declare = getNextNode(childList->children,3)->children->next->children; //pointing to 1st declaration node
				
			while(declare!=NULL){
				if(getChildrenNo(declare)==3) continue; //check
				
				if(lookupID(identifier,declare->children->next->token_info->lexeme)!=NULL)
				{
						printf("Error. Line No: %u Variable <%s> declared globally cannot have a local declaration \n", declare->children->next->token_info->lineNo,declare->children->next->token_info->lexeme);
						RaiseError=-1;
				}
				idTable tabTemp = idLocal;
				if(lookupID(tabTemp, declare->children->next->token_info->lexeme)==NULL)
				{
					int dtype =  getType(declare->children,rec);
					if(dtype==-1)
					{
						printf("Error. Line No: %u No such type for <%s> \n",declare->children->token_info->lineNo ,declare->children->token_info->lexeme);
						RaiseError=-1;
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
						printf("Re-declaration Error. Line No: %u Variable <%s> already declared \n",declare->children->next->token_info->lineNo, declare->children->next->token_info->lexeme);
						RaiseError=-1;
					}
				declare = declare->next;
				}
			insertFunc(func,"_main",0, 0,0, NULL,NULL,idLocal,offsetBegin); //check
		}
		else{
			printf("Main function defined twice.\n");
			RaiseError=-1;
		}

}

		
