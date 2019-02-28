#include "lexer.h"

int main()
{
	FILE* fp=fopen("sample.txt","r");
	initialize(fp);
	return 0;
}
