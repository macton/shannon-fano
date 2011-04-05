#include "main.h"

void
clear(tree *root)
{
	if (root->left != NULL)
		clear(root->left);
	if (root->right != NULL)
		clear(root->right);
	
	free(root);
}

int
gototree(char c, tree **t)
{
	if (c == '0')
		(*t) = (*t)->left;
	else if (c == '1')
		(*t) = (*t)->right;
	return (*t)->data;
}
