#include "main.h"

int
bintoint(intbin val)
{
	int i, temp = 0;
	for (i = 0; i < 3; ++i)
		temp += (val.v[i] == '1') ? (1 << i) : 0;
}

int
bintochar(charbin val)
{
	int i, temp = 0;
	for (i = 0; i < 8; ++i)
		temp += (val.v[i] == '1') ? (1 << i) : 0;
	return temp;
}

charbin
chartobin(int val)
{
	charbin temp;
	int i;
	for (i = 0; i < 8; ++i)
		{
			temp.v[8 - i] = (val % 2 == 1) ? '1' : '0';
			val /= 2;
		}
	return temp;
}

intbin
inttobin(int val)
{
	intbin temp;
	int i;
	for (i = 0; i < 3; ++i)
		{
			temp.v[3 - i] = (val % 2 == 1) ? '1' : '0';
			val /= 2;
		}
	return temp;
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
		buff->v |= (1 << (buff->size));
	else
		buff->v &= ~(1 << (buff->size));
	++(buff->size);
}

int
readbit(FILE *infile, buffer *buff)
{
	if (buff->size == 0)
		{
			if ((buff->v = getc(infile)) == EOF)
				return EOF;
			buff->size = 8;
		}
	
	--(buff->size);
	return (((buff->v & (1 << buff->size)) >> buff->size) == 1) ? '1' : '0'; 
}
