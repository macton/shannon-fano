#include "main.h"

void
quicksort(ptab v[], int left, int right)
{
	int i, last;
	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i < right; ++i)
		if (v[i].p > v[left].p)
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last - 1);
	quicksort(v, last + 1, right);
}

void
swap(ptab v[], int i, int j)
{
	ptab temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
