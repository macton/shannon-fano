#include "main.h"

void
clear(tree *root)
{
	if (root->left != NULL)
		clear(root->left);
	if (root->right!= NULL)
		clear(root->right);
}

int
gototree(char c, tree *t)
{
	if (c == '0' && t->left != NULL)
		t = t->left;
	else if (c == '1' && t->right != NULL)
		t = t->right;

	return (t->data == EOF) ? EOF : t->data;
}
