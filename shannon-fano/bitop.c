#include "main.h"

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
//printf("[%d]", buff->v);
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

byte
readbit(char val)
{
	byte temp;

	int i;
	char tempr;
	for (i = 0; i < 8; ++i)
	{
		tempr = 1 << i;
		temp.v[i] = ((val & tempr) == tempr) ? '1' : '0';
		//printf("[%c]", temp.v[i]);
	}
	temp.v[8] = '\0';
	return temp;
}
