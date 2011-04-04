#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAPSIZE 256

typedef struct ptab
{
	int ch;
	float p;
} ptab;

typedef struct buffer
{
	char v;
	int size;
} buffer;


typedef struct tree
{
  char data;
  struct tree *parent;
  struct tree *left;
  struct tree *right;
} tree;

typedef struct intbin
{
	char v[3];
} intbin;

typedef struct charbin
{
	char v[8];
} charbin;

ptab ptable[MAPSIZE];
char codes[MAPSIZE][129];

void pack(const char *input, const char *output);
void unpack(const char *input, const char *output);

void swap(ptab v[], int i, int j);
void encode(int li, int ri);
void quicksort(ptab v[], int left, int right);

void clear(tree *root);

//binary
void writebit(FILE *outfile, buffer *buff, char bit);
int readbit(FILE *infile, buffer *buff);

intbin inttobin(int val);
charbin chartobin(int val);

int bintoint(intbin val);
int bintochar(charbin val);
