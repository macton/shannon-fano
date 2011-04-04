#include "main.h"

void
unpack(const char *input, const char *output)
{
	FILE *infile = fopen(input, "r");
	assert(infile);
	int i, ch, j, c;

	fseek(infile, -1L, SEEK_END);
	unsigned long last = ftell(infile);
	int lastsym = getc(infile);
	fseek(infile, 0, SEEK_SET);

	int size = getc(infile);
	int buffsize = getc(infile);
	
	tree root, *temp;
	root.data = EOF;
	root.parent = root.left = root.right = NULL;

	buffer buff;
	buff.v = buff.size = 0;

	charbin codebin;
	intbin codesize;
	int csize;

	for (i = 0; i < size; ++i)
		{
			for (j = 0; j < 8; ++j)
				codebin.v[j] = readbit(infile, &buff);
			ch = bintochar(codebin);

			for (j = 0; j < 3; ++j)
				codesize.v[j] = readbit(infile, &buff);
			csize = bintoint(codesize);

			temp = &root;
			for (j = 0; j < csize; ++j)
				{
					c = readbit(infile, &buff);
					if (c == '0')
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
					else if (c == '1')
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
	
	temp = &root;
	while ((c = readbit(infile, &buff)) != EOF)
		{
			if (ftell(infile) == last)
				{
					for (i = 0; i < buffsize; ++i)
						{
							c = (((buff.v & (1 << i)) >> i) == 1) ? '1' : '0';
							if (c == '0' && temp->left != NULL)
								temp = temp->left;
							else if (c == '1' && temp->right != NULL)
								temp = temp->right;
							if (temp->data != EOF)
								{
									putc(temp->data, outfile);
									temp = &root;
								}
						}
					break;
				}
			if (c == '0' && temp->left != NULL)
				temp = temp->left;
			else if (c == '1' && temp->right != NULL)
				temp = temp->right;
			if (temp->data != EOF)
				{
					putc(temp->data, outfile);
					temp = &root;
				}	
		}
	
	clear(&root);	
	fclose(outfile);
	fclose(infile);
}

