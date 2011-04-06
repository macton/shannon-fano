#include "main.h"

int
bittosize(char v[])
{
	int i, temp = 0;
	for (i = 0; i < CODESIZE; ++i)
		temp += (v[CODESIZE - 1 - i] == '1') ? (1 << i) : 0;
	return temp;
}

int
bittochar(char v[])
{
	int i, temp = 0;
	for (i = 0; i < SYMBSIZE; ++i)
		temp += (v[SYMBSIZE - 1 - i] == '1') ? (1 << i) : 0;
	return temp;
}

void
chartobit(int val, char v[])
{
	int i;
	for (i = SYMBSIZE - 1; i > -1; --i)
		{
			v[i] = (val % 2 == 1) ? '1' : '0';
			val /= 2;
		}
}

void
sizetobit(int val, char v[])
{
	int i;
	for (i = CODESIZE - 1; i > -1; --i)
		{
			v[i] = (val % 2 == 1) ? '1' : '0';
			val /= 2;
		}
}

void
writebit(FILE *outfile, buffer *buff, char bit)
{
	if (bit != '0' && bit != '1')
		return;
	if (buff->size == 8)
		{
			putc(buff->v, outfile);
			buff->v = buff->size = 0;
		}
	if (bit == '1')
		buff->v |= (1 << buff->size);
	else
		buff->v &= ~(1 << buff->size);
	++(buff->size);
}

int
readbit(FILE *infile, buffer *buff)
{
	if (buff->size == 0)
		{
			buff->v = getc(infile);
			buff->size = 8;
		}
	
	--(buff->size);
	return (((buff->v & (1 << (7 - buff->size))) >> (7 - buff->size)) == 1) ? '1' : '0'; 
}
