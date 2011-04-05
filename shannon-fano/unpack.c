#include "main.h"

void
unpack(const char *input, const char *output)
{
	FILE *infile = fopen(input, "r");
	assert(infile);
	int i, ch, j, c;

	fseek(infile, -1L, SEEK_END);
	unsigned long last = ftell(infile) - 2;
	int buffsize = getc(infile);
	fseek(infile, 0, SEEK_SET);

	int size = getc(infile);
		
	tree root, *temp;
	root.data = EOF;
	root.parent = root.left = root.right = NULL;

	buffer buff;
	buff.v = buff.size = 0;

	char codebit[8], codesize[3];
	int csize;

	for (i = 0; i < size; ++i)
		{
			for (j = 0; j < 8; ++j)
			{
				codebit[j] = readbit(infile, &buff);
				//putchar(codebit[j]);
			}
			//putchar('\n');
			ch = bittochar(codebit);
			for (j = 0; j < 3; ++j)
				codesize[j] = readbit(infile, &buff);
			csize = bittosize(codesize);

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
			if ((ch = gototree(c, temp)) != EOF)
				{
					putc(ch, outfile);
					temp = &root;
				}

			if (ftell(infile) == last && buff.size == 8)
				{
					for (i = 0; i < buffsize; ++i)
						{
							c = readbit(infile, &buff);
							if ((ch = gototree(c, temp)) != EOF)
								{
									putc(ch, outfile);
									temp = &root;
								}	
						}
					break;	
				}	
		}
	
	clear(&root);	
	fclose(outfile);
	fclose(infile);
}

