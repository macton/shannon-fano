#include "main.h"

void
pack(const char *input, const char *output)
{
	extern ptab ptable[MAPSIZE];
	extern char codes[MAPSIZE][129];
	int freq_table[MAPSIZE], c, i, j;

	FILE *infile = fopen(input, "r");
	assert(infile);

	unsigned total = 0;
	for (i = 0; i < MAPSIZE; ++i)
			freq_table[i] = 0;
	
	while ((c = getc(infile)) != EOF)
		{
			freq_table[c]++;
			total++;
		}

	float ftot = (float)total;

	unsigned char size = 0;
	for (i = 0; i < MAPSIZE; ++i)
		{
			if (!freq_table[i])
				continue;
			ptable[size].ch = i;
			ptable[size].p = (float)freq_table[i] / ftot;
			size++;
		}

	quicksort(ptable, 0, size);
	encode(0, size - 1);
	
	for (i = 0; i < size; ++i)
		printf("%c, %s\n", ptable[i].ch, codes[ptable[i].ch]);
	
	FILE *outfile = fopen(output, "wb");
	assert(outfile);
	
	putc(size, outfile);

	buffer buff;
	buff.size = buff.v = 0;

	char codesize[3], codebit[8];
	char *ch;
	for (i = 0; i < size; ++i)
		{
			c = ptable[i].ch;
			chartobit(c, codebit);
			for (j = 0; j < 8; ++j)
				writebit(outfile, &buff, codebit[j]); // 8 bits of the code

			sizetobit(strlen(codes[c]), codesize);
			//for (j = 0; j < 8; ++j)
			//	printf("%c", codesize[j]);
			//putchar('\n');
			for (j = 0; j < 3; ++j)
				writebit(outfile, &buff, codesize[j]); // size of code
			
			j = -1;
			ch = codes[c];
			while (ch[++j] != '\0')
				writebit(outfile, &buff, ch[j]); // code
		}

	fseek(infile, 0, SEEK_SET);
	
	while ((c = getc(infile)) != EOF)
		{
			ch = codes[c];
			//printf("%s", ch);
			j = -1;
			while (ch[++j] != '\0')
				writebit(outfile, &buff, ch[j]);
		}
	if (buff.size != 8)
		putc(buff.v, outfile);
	
	putc(buff.size, outfile);
	
	fclose(outfile);
	fclose(infile);
}

void
encode(int li, int ri)
{
	if (li == ri)
		return;

	extern ptab ptable[MAPSIZE];
	extern char codes[MAPSIZE][129];

	int i, isp;
	float p, phalf;

	if (ri - li == 1)
		{
			strcat(codes[ptable[li].ch], "0");
			strcat(codes[ptable[ri].ch], "1");
		}
	else
		{
			phalf = 0;
			for(i = li; i <= ri; ++i)
				phalf += ptable[i].p;

			p = 0;
			isp = -1;
			phalf *= 0.5f;
			for(i = li; i <= ri; ++i)
				{
					if(p <= phalf)
						strcat(codes[ptable[i].ch], "0");
					else
						{
							strcat(codes[ptable[i].ch], "1");
							if(isp < 0)
								isp = i;
						}
					p += ptable[i].p;
				}

			if (isp < 0)
				isp = li + 1;

			encode(li, isp - 1);
			encode(isp, ri);

		}

}

