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

typedef struct byte
{
	char v[9];
} byte;

typedef struct tree
{
  char data;
  struct tree *parent;
  struct tree *left;
  struct tree *right;
} tree;



ptab ptable[MAPSIZE];
char codes[MAPSIZE][129];

void pack(const char *input, const char *output);
void unpack(const char *input, const char *output);

void swap(ptab v[], int i, int j);
void encode(int li, int ri);
void quicksort(ptab v[], int left, int right);

void writebit(FILE *outfile, buffer *b, char bit);
byte readbit(char val);

void clear(tree *root);
