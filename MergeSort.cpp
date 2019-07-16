#include <iostream>
#include "Windows.h"
#include <algorithm>
using namespace std;

const int MAX_SIZE = 500000;

int arr_size;
int ms[MAX_SIZE], qs[MAX_SIZE], stls[MAX_SIZE], buf[MAX_SIZE];

void merge_sort(int* p, int len) {
	if (len < 2) return;
	int i, j, k, mid;
	mid = (len / 2);
	i = 0, j = mid, k = 0;

	merge_sort(p, mid);
	merge_sort((p + mid), (len - mid));

	while (i < mid && j < len) {
		if (p[i] < p[j])
			buf[k++] = p[i++];
		else
			buf[k++] = p[j++];
	}
	while (i < mid)
		buf[k++] = p[i++];

	while (j < len)
		buf[k++] = p[j++];
	for (int i = 0; i < len; ++i)
		p[i] = buf[i];
}

void qsort(int* p, int left, int right) {
	if (left >= right)   return;
	int l = left - 1;
	int r = right + 1;
	int mid = p[(l + r) / 2];
	while (1) {
		while (p[++l] < mid);
		while (p[--r] > mid);
		if (l >= r)  break;
		int temp = p[l];
		p[l] = p[r];
		p[r] = temp;
	}
	qsort(p, left, l - 1);
	qsort(p, r + 1, right);
}


int main()
{
	arr_size = MAX_SIZE;

	for (int i = 0; i < arr_size; ++i) {
		ms[i] = rand();
		qs[i] = stls[i] = ms[i];
	}

	int quick_sort_begin = GetTickCount();
	qsort(qs, 0, arr_size - 1);
	int quick_sort_end = GetTickCount();

	int merge_sort_begin = GetTickCount();
	merge_sort(ms, arr_size);
	int merge_sort_end = GetTickCount();

	int stl_sort_begin = GetTickCount();
	sort(stls, stls + arr_size);
	int stl_sort_end = GetTickCount();

	printf("my quick sort : %d\n", (quick_sort_end - quick_sort_begin));
	printf("my merge sort : %d\n", (merge_sort_end - merge_sort_begin));
	printf("stl sort : %d\n", (stl_sort_end - stl_sort_begin));
	printf("=====================================\n");

	quick_sort_begin = GetTickCount();
	qsort(qs, 0, arr_size - 1);
	quick_sort_end = GetTickCount();

	merge_sort_begin = GetTickCount();
	merge_sort(ms, arr_size);
	merge_sort_end = GetTickCount();

	stl_sort_begin = GetTickCount();
	sort(stls, stls + arr_size);
	stl_sort_end = GetTickCount();

	printf("my quick sort : %d\n", (quick_sort_end - quick_sort_begin));
	printf("my merge sort : %d\n", (merge_sort_end - merge_sort_begin));
	printf("stl sort : %d\n", (stl_sort_end - stl_sort_begin));
	printf("=====================================\n");

	for (int i = 0; i < arr_size; ++i) {
		if (qs[i] != stls[i] || ms[i] != stls[i]) {
			printf("Error\n");
		}
	}

	return 0;
}

