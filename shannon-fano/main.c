#include "main.h"

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
