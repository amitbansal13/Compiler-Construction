/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog     ID Number - 2016A7PS0004P*/
#include "symbolTableDef.h"


int checkType(TreeNode head, recTable table1)
{
	int firstType, secondType;//stores the type of operands
	int error = 0;
	TreeNode childList = head->children;
	if(head->tNt == 1)
	{
		//assignmentStmts
		if(head->index == 22)
		{
			firstType = checkType(head->children, table1);
			secondType = checkType(head->children->next, table1);
			if(firstType == -2 || secondType == -2) return -2;
			else if(secondType != firstType)
			{
				printf("Line %d: Type of left variable <%s> not equal to type of right expression\n",head->children->children->token_info->lineNo, head->children->children->token_info->lexeme);
				return -2;
			}
			else return secondType; 
		}
		//singleOrRecID
		else if (head->index == 27)
		{
			if(head->children->next == NULL && head->children->children == NULL)
					return checkType(head->children, table1);
			else
			{
				if(head->children->tableEntry == NULL)
					return -2;
				Rec r1 = lookupRec(table1, head->children->tableEntry->name);
				if(r1 == NULL) return -2;
				for(int i=0; i<r1->noField; i++)
				{
					if(strcmp(r1->fieldid[i], head->children->next->token_info->lexeme) == 0)
						return r1->fieldtype[i];
				}
			}
		}
		else
		{
			while(childList!=NULL)
			{
					firstType = checkType(childList, table1);
					if(firstType == -2)
						error = 1;
					childList = childList->next;
				}
				if(error) return -2;	
		}

	}
	else //if(head->tNt == 0)
	{
		if(head->index == 3)//TK_ID
		{
			if(head->tableEntry == NULL) return -2;
					return head->tableEntry->type;
		}
		else if(head->index == 4)//TK_NUM
		{
			return 0;
		}
		else if(head->index == 5)//TK_RNUM
		{
			return 1;
		}
		else if(head->index >= 36 && head->index <= 37)//TK_PLUS or TK_MINUS
		{
			firstType = checkType(head->children,table1);//get the type of first operand
			if(firstType==-2)//check if it is an error type
				return -2;

			secondType = checkType(head->children->next,table1);//get the type of first operand
			if(secondType==-2)
				return -2;

			if(firstType!=secondType)
			{
				printf("Line %d: Type Mismatch. Different operand types: ",head->token_info->lineNo);
				printf("%s:", head->children->children->token_info->lexeme);
				if(firstType==0){
					printf("<int> and ");
				}
				else if(firstType==1){
					printf("<real> and ");
				}
				else{
					printf("<%s> and ", head->children->children->tableEntry->tname);
				}
				printf("%s:", head->children->next->children->token_info->lexeme);
				if(secondType==0){
					printf("<int>\n");
				}
				else if(secondType==1){
					printf("<real>\n");
				}
				else{
					printf("<%s>\n", head->children->next->children->tableEntry->tname);
				}
				return -2;
			}	

			if(firstType==-1 || secondType==-1)
			{
				printf("Line %u: Addition or subtraction is not allowed for boolean expressions \n", head->token_info->lineNo);
				return -2;
			}	
				
			return firstType; 
		}
		else if(head->index == 38)//TK_MUL
		{
			firstType = checkType(head->children,table1);
			if(firstType==-2)
				return -2;

			secondType = checkType(head->children->next,table1);
			if(secondType==-2)
				return -2;

			if((firstType > 1 && (secondType==0||secondType==1))||(secondType>1 &&(firstType==0||firstType==1)))
				return firstType>secondType?firstType:secondType; //return the type of record
			
			if(firstType==-1||secondType==-1)
			{
				printf("Line %u: Multiplication not allowed on boolean expressions\n", head->token_info->lineNo);
				return -2;
			}
			
			if(firstType > 1 && secondType > 1)
			{
				printf("Line %u: Multiplication not allowed on record types\n",head->token_info->lineNo);
				return-2;
			}

			if(firstType!=secondType)
			{
				printf("Line %u: Type Mismatch. Different operand types: ",head->token_info->lineNo);
				printf("%s:", head->children->children->token_info->lexeme);
				if(firstType==0){
					printf("<int> and ");
				}
				else if(firstType==1){
					printf("<real> and ");
				}
				printf("%s:", head->children->next->children->token_info->lexeme);
				if(secondType==0){
					printf("<int>\n");
				}
				else if(secondType==1){
					printf("<real>\n");
				}
				return -2;
			}
				
			
			return firstType;
		}
		else if(head->index == 39)//TK_DIV
		{
			firstType = checkType(head->children,table1);
			if(firstType==-2)
				return -2;
			
			secondType = checkType(head->children->next, table1);
			if(secondType==-2)
				return -2;
			
			if(secondType > 1)
			{
				printf("Line %u: Divisor <%s> cannot be a record type\n",head->token_info->lineNo, head->children->next->token_info->lexeme);
				return -2;
			}
			if(firstType ==-1||secondType ==-1)
			{
				printf("Line %u: Division not allowed on boolean expressions\n", head->token_info->lineNo);
				return -2;
			}
			if(firstType > 1 && (secondType==0||secondType==1))
				return firstType;

			if(firstType != secondType)
			{
				printf("Line %u: Type Mismatch. Different Operand types: ",head->token_info->lineNo);
				printf("%s:", head->children->children->token_info->lexeme);
				if(firstType==0){
					printf("<int> and ");
				}
				else if(firstType==1){
					printf("<real> and ");
				}
				printf("%s:", head->children->next->children->token_info->lexeme);
				if(secondType==0){
					printf("<int>\n");
				}
				else if(secondType==1){
					printf("<real>\n");
				}
				return -2;
			}

			return firstType;//no errors-both are of same valid types
		}
		else if(head->index >= 44 && head->index<= 45)//TK_AND , TK_OR
		{
			firstType = checkType(head->children,table1);

			if(firstType != -1)
			{
				printf("Line %u: Logical Operators are only applicable to boolean variables\n", head->token_info->lineNo);
				return -2;
			}

			secondType = checkType(head->children->next, table1);
			
			if(secondType != -1)
			{
				printf("Line %u: Logical Operators are only applicable to boolean variables\n", head->token_info->lineNo);
				return -2;
			}
			return -1;
		}
		else if(head->index == 46 )//TK_NOT
		{
			firstType = checkType(head->children, table1);
			if(firstType==-2)
				return -2;

			if(firstType!=-1)
			{
				printf("Line %u: NOT operator is applicable only on boolean variables \n",head->token_info->lineNo);
			}
			return -1;
		}
		else if(head->index >= 47 && head->index <= 52)//TK_LE, TK_LT, TK_EQ, TK_GT, TK_GE, TK_NE
		{
			firstType = checkType(head->children,table1);
			secondType = checkType(head->children->next,table1);
			

			if(firstType>1 || secondType>1)
			{
				printf("Line %u: Relational operators can be applied only on int and real\n", head->token_info->lineNo);
				return -2;
			}
			if(firstType != secondType)
			{
				printf("Line %u: Type Mismatch. Different operand types: ",head->token_info->lineNo);
				printf("%s:", head->children->children->token_info->lexeme);
				if(firstType==0){
					printf("<int> and ");
				}
				else if(firstType==1){
					printf("<real> and ");
				}
				printf("%s:", head->children->next->children->token_info->lexeme);
				if(secondType==0){
					printf("<int>\n");
				}
				else if(secondType==1){
					printf("<real>\n");
				}
				return -2;
			}
			return -1;	
		}
		else 
		{
			while(childList!=NULL)
			{
				firstType = checkType(childList, table1);
				if(firstType == -2)
					error = 1;
				childList = childList->next;
			}
			if(error) return -2;
			
		}
	}


}
