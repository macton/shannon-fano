#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAPSIZE 256

typedef struct ptab
{
	char ch;
	float p;
} ptab;

typedef struct buffer
{
	char v;
	int size:3;
} buffer;

ptab ptable[MAPSIZE];
char codes[MAPSIZE][128];


void pack(const char *input, const char *output);
void unpack(const char *input, const char *output);
void swap(ptab v[], int i, int j);
void encode(int li, int ri);

void writebit(FILE *outfile, buffer *b, char bit);

int
main(int argc, char *argv[])
{
	if (argc != 4 || argv[1][0] != '-' || strlen(argv[1]) != 2)
		return -1;

	switch (argv[1][1])
		{
	case 'p':
			pack(argv[2], argv[3]);
			break;
		case 'u':
			unpack(argv[2], argv[3]);
			break;
		default:
			return -1;
		}

	return 0;
}

void
pack(const char *input, const char *output)
{

	int freq_table[MAPSIZE], c, i, j;

	FILE *infile = fopen(input, "r");
	assert(infile);

	unsigned total = 0;
	for (i = 0; i < MAPSIZE; ++i)
		{
			freq_table[i] = 0;
		}
	while ((c = getc(infile)) != EOF)
		{
			freq_table[c]++;
			total++;
		}

	float ftot = (float)total;

	int size = 0;
	for (i = 0; i < MAPSIZE; ++i)
		{
			if (!freq_table[i])
				continue;

			ptable[size].ch = i;
			ptable[size].p = (float)freq_table[i] / ftot;
			size++;
		}



	for (i = 0; i < size; ++i)
		{
			for (j = i; j < size; ++j)
				{
					if (ptable[i].p < ptable[j].p)
						swap(ptable, i, j);
				}
		}

	encode(0, size - 1);


	for (i = 0; i < size; ++i)
		{
				printf("%d, %s\n", ptable[i].ch, codes[i]);
		}

	FILE *outfile = fopen(output, "wb");
	assert(outfile);

	fprintf(outfile, "%i\t", size);
	for (i = 0; i < size; ++i)
		{
			fprintf(outfile, "%c\t%s\t", ptable[i].ch, codes[ptable[i].ch]);
		}

	fseek(infile, SEEK_SET, 0);

	buffer buff;
	char *ch;
	while ((c = getc(infile)) != EOF)
		{
			ch = codes[c];
			while (ch++ != '\0')
				writebit(outfile, &buff, *ch);
		}


	fclose(outfile);
	fclose(infile);
}

void
encode(int li, int ri)
{
	if (li == ri)
		return;

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
					p += ptable[i].p;
					if(p <= phalf)
						strcat(codes[ptable[i].ch], "0");
					else
						{
							strcat(codes[ptable[i].ch], "1");
							if(isp < 0)
								isp = i;
						}
				}

			if (isp < 0)
				isp = li + 1;

			encode(li, isp - 1);
			encode(isp, ri);
		}

}
void
writebit(FILE *outfile, buffer *buff, char bit)
{
	if (bit != '0' && bit != '1')
		return;

	int b = (bit == '1') ? 1 : 0;
	if (buff->size == 8)
		{
			putc(buff->v, outfile);
			buff->v = 0;
			buff->size = 0;
		}
	else
		{
			buff->v |= (b << (buff->size));
			++(buff->size);
		}
}

void
swap(ptab v[], int i, int j)
{
	ptab temp;
	temp.ch = v[i].ch;
	temp.p = v[i].p;
	v[i].ch = v[j].ch;
	v[i].p = v[j].p;
	v[j].ch = temp.ch;
	v[j].p = temp.p;
}

void
unpack(const char *input, const char *output)
{

}

