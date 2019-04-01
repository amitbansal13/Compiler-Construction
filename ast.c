#include "parserDef.h"

TreeNode createAST(TreeNode root)
{
	if(!root)return root;
	TreeNode children=root->children;
	while(children)
	{
		createAST(children);


		children=children->next;
	}
}
