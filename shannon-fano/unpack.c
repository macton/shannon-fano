#include "main.h"

void
unpack(const char *input, const char *output)
{
	FILE *infile = fopen(input, "r");
	assert(infile);
	int size,  i, ch, j, c;

	fscanf(infile, "%i", &size);
	char code[128];

	tree root;
	root.data = EOF;
	root.parent = root.left = root.right = NULL;
	tree *temp;
	getc(infile);
	//Binary tree character building
	for (i = 0; i < size; i++)
	{
		ch = getc(infile);
		j = -1;
		while ((code[++j] = getc(infile)) != '\n');
		code[j] = '\0';
		//printf("%s\n", code);
		j = -1;
		temp = &root;
		while (code[++j] != '\0')
			{
				if (code[j] == '0')
					{
						if (temp->left == NULL)
							{
								temp->left = (tree*) malloc(sizeof(tree));
								temp->left->data = EOF;
								temp->left->right = temp->left->left = NULL;
								temp->left->parent = temp;
							}
						else
								temp = temp->left;
					}
				else if (code[j] == '1')
					{
						if (temp->right == NULL)
							{
								temp->right = (tree*) malloc(sizeof(tree));
								temp->right->data = EOF;
								temp->right->right = temp->right->left = NULL;
								temp->right->parent = temp;
							}
						else
							temp = temp->right;
					}
			}
		temp->data = ch;
	}


	FILE *outfile = fopen(output, "w");
	assert(outfile);

	byte buff;

	temp = &root;
	while ((ch = getc(infile)) != EOF)
		{
			
			buff = readbit(ch);
			for (i = 0; i < 8; ++i)
				{
					putchar(buff.v[i]);
					if (buff.v[i] == '0' && temp->left != NULL)
						temp = temp->left;
					else if (buff.v[i] == '1' && temp->right != NULL)
						temp = temp->right;
					if (temp->data != EOF)
						{
							putc(temp->data, outfile);
							temp = &root;
						}
				}
		}

	clear(&root);	
	fclose(outfile);
	fclose(infile);
}

