#include "typeCheckingDef.h"
char *nonterminals[]={
	"program",//0
	"mainFunction",//1
	"otherFunctions",//2
	"function",//3
	"input_par",//4
	"output_par",//5
	"parameter_list",//6
	"dataType",//7
	"primitiveDatatype",//8
	"constructedDatatype",//9
	"remaining_list",//10
	"stmts",//11
	"typeDefinitions",//12
	"typeDefinition",//13
	"fieldDefinitions",//14
	"fieldDefinition",//15
	"moreFields",//16
	"declarations",//17
	"declaration",//18
	"global_or_not",//19
	"otherStmts",//20
	"stmt",//21
	"assignmentStmt",//22
	"iterativeStmt",//23
	"conditionalStmt",//24
	"ioStmt",//25
	"funCallStmt",//26
	"singleOrRecId",//27
	"new_24",//28
	"outputParameters",//29
	"inputParameters",//30
	"elsePart",//31
	"allVar",//32
	"arithmeticExpression",//33
	"expPrime",//34
	"term",//35
	"termPrime",//36
	"factor",//37
	"highPrecedenceOperator",//38
	"lowPrecedenceOperators",//39
	"booleanExpression",//40
	"logicalOp",//41
	"relationalOp",//42
	"returnStmt",//43
	"optionalReturn",//44
	"idList",//45
	"more_ids"//46};
	char *terminals[]= {
		"TK_ASSIGNOP",//0
		 "TK_COMMENT",//1
		 "TK_FIELDID",//2
		 "TK_ID",//3
		 "TK_NUM", //4
		 "TK_RNUM", //5
		 "TK_FUNID", //6
		 "TK_RECORDID",//7
		 "TK_WITH",//8
		 "TK_PARAMETERS",//9
		 "TK_END",//10
		 "TK_WHILE",//11
		 "TK_TYPE",//12
		 "TK_MAIN",//13
		 "TK_GLOBAL",//14
		 "TK_PARAMETER",//15
		 "TK_LIST",//16
		 "TK_SQL", //17
		 "TK_SQR",//18
		 "TK_INPUT", //19
		 "TK_OUTPUT", //20
		 "TK_INT", //21
		 "TK_REAL",//22
		 "TK_COMMA", //23
		 "TK_SEM",//24
		 "TK_COLON", //25
		 "TK_DOT", //26
		 "TK_ENDWHILE",//27 
		 "TK_OP",//28
		 "TK_CL",//29
		 "TK_IF",//30
		 "TK_THEN",//31
		 "TK_ENDIF",//32
		 "TK_READ",//33
		 "TK_WRITE",//34
		 "TK_RETURN",//35
		 "TK_PLUS",//36
		 "TK_MINUS",//37
		 "TK_MUL",//38
		 "TK_DIV",//39
		 "TK_CALL", //40
		 "TK_RECORD",//41
		 "TK_ENDRECORD",//42
		 "TK_ELSE",//43
		 "TK_AND",//44
		 "TK_OR", //45
		 "TK_NOT", //46
		 "TK_LT", //47
		 "TK_LE", //48
		 "TK_EQ", //49
		 "TK_GT", //50
		 "TK_GE", //51
		 "TK_NE",//52
		 "eps",//53
		 "DOLLAR",//54
		 "TK_ERROR"//55};


int TypeChecker(TreeNode root, recTable table)
{
	int type1, type2;
	int i, error=0;
	if(root->tNt == 1)
	{
		switch(root->index)
		{
			case 22://assignmentStmt
				type1 = TypeChecker(root->children, table);
				type2 = TypeChecker(root->children->next, table);
				if(type == -2 || type1 == -2) return -2;
				else if(type2 != type1)
				{
					printf("line no: %d type of left variable <%s> not equal to type of right expression\n",root->children->children->token_info->lineNo, root->children->children->token_info->lexeme);
					return -2;
				}
				else return type2;

			case 27://singleOrRecID
				if(root->children->next == NULL && root->children->children == NULL)
					return TypeChecker(root->children, table);
			default:
			
			for(i=0;i<root)
		}
	}
	else if(root->tNt == 0)
	{
		switch(terminals[root->index])
		{
			case 3://"TK_ID"

			case 4://"TK_NUM"

			case 5://"TK_RNUM"

			case 36://"TK_PLUS"
			case 37://"TK_MINUS"

			case 38://"TK_MUL"

			case 39://"TK_DIV"


			case 44://"TK_AND"
			case 45://"TK_OR"


			case 46://"TK_NOT"

			

			case 47://"TK_LT"
			case 48://"TK_LE"
			case 49://"TK_EQ"
			case 50://"TK_GT"
			case 51://"TK_GE"
			case 52://"TK_NE"
			



			default:
			
		}
	}
	// switch(nonTerminal)


}