#include "main.h"

void clear(tree *root)
{
	if (root->left != NULL)
		clear(root->left);
	if (root->right!= NULL)
		clear(root->right);
}
