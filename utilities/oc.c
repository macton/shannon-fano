#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int
main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	int count[256], i;

	for (i = 0; i < 256; ++i)
		count[i] = 0;

	FILE *input = fopen(argv[1], "r");
	assert(input);

	fseek(input, -1L, SEEK_END);
	unsigned long d = ftell(input);
	fseek(input, 0, SEEK_SET);
	
	char ch;
	unsigned long c = 0;
	bool ind;

	while (ch = getc(input))
	{
		ind = false;
		++c;
		count[ch]++;
		if (ftell(input) == d)
			break;
	}

	double e = 0;
	double tmp;
	printf("Symbol\t\t\tSymbol Count\t\t\tProbability\n");
	for (i = 0; i < 256; ++i)
	{
		if (!count[i])
			continue;
		tmp = (double)count[i]/(double)c;
		printf("\"%c\"\t\t\t%i\t\t\t%f\n", (char)i, count[i], tmp);
		e -= tmp * log2(tmp);
	}
	
	printf("Entropy: %f\n", e);

	return 0;
}
