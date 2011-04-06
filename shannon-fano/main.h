#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAPSIZE 256
#define SYMBSIZE 8
#define CODESIZE 7

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
  struct tree *left;
  struct tree *right;
} tree;



// pack.c
void pack(const char *input, const char *output);
void encode(int li, int ri);
void charcat(char s[], char t);

// unpack.c
void unpack(const char *input, const char *output);

// sort.c
void swap(ptab v[], int i, int j);
void quicksort(ptab v[], int left, int right);

// bintree.c
void clear(tree *root);
int gototree(char c, tree **t);

// bitop.c
void writebit(FILE *outfile, buffer *buff, char bit);
int readbit(FILE *infile, buffer *buff);

void sizetobit(int val, char v[]);
void chartobit(int val, char v[]);

int bittosize(char v[]);
int bittochar(char v[]);
