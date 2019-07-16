#include <stdio.h>
#include <map>
#include <algorithm>
#include "Windows.h"
using namespace std;

const int PN = 23;
const int HASH_SIZE = 10000;

int table[HASH_SIZE][50];
int hash_size = 0;
char hash_raw[30000][100];

char input[30000][100];
map<char*, int> test;

unsigned int get_key(char str[]) {
	unsigned int key = 0, p = 1;

	for (int i = 0; str[i] != 0; ++i) {
		key += (str[i] * p);
		p *= PN;
	}

	return (key % HASH_SIZE);
}

int my_strcamp(char a[], char b[]) {
	int i = 0, j = 0;
	while (a[i]) {
		if (a[i++] != b[j++]) {
			--i, --j;
			break;
		}
	}
	return (a[i] - b[j]);
}

int contain(char str[]) {
	unsigned int key = get_key(str);
	int size = table[key][0];
	for (int i = 1; i <= size; ++i) {
		int pos = table[key][i];
		if (my_strcamp(hash_raw[pos], str) == 0) {
			return pos;
		}
	}
	return -1;
}

void add(char str[]) {
	int len = 0;
	for (len = 0; str[len] != 0; ++len) {
		hash_raw[hash_size][len] = str[len];
	}
	hash_raw[hash_size][len] = 0;

	unsigned int key = get_key(str);
	int& size = table[key][0];
	table[key][++size] = hash_size;

	++hash_size;
}

bool remove(char str[]) {
	unsigned int key = get_key(str);
	int& size = table[key][0];
	for (int i = 1; i <= size; ++i) {
		int pos = table[key][i];
		if (my_strcamp(hash_raw[pos], str) == 0) {
			for (int j = i + 1; j <= size; ++j) {
				table[key][j - 1] = table[key][j];
			}
			--size;
			return true;
		}
	}
	return false;
}

int make_int(int min, int max) {
	return (rand() % (max - min)) + min;
}

char make_char() {
	int val = rand() % 52;
	if (val < 26) {
		return static_cast<char>('a' + val);
	}
	return static_cast<char>('A' + val - 26);
}

int main()
{
	for (int i = 0; i < 30000; ++i) {
		int len = make_int(10, 100);
		for (int j = 0; j < len; ++j) {
			input[i][j] = make_char();
		}
		input[i][len] = 0;

		if (contain(input[i]) == -1) {
			add(input[i]);
		}
		test[input[i]] = i;


		if (i > 20000) {
			int cmd = make_int(0, 5);
			int index = make_int(0, i);
			if (cmd == 0) {
				if (contain(input[index]) != -1) {
					remove(input[index]);
				}

				test.erase(input[index]);
			}
			if (cmd == 1) {
				int my_pos = contain(input[index]);
				map<char*, int>::iterator iter = test.find(input[index]);
				int stl_pos = -1;
				if (iter != test.end()) {
					stl_pos = iter->second;
				}

				if (my_pos != stl_pos) {
					printf("find error!!!\n");
				}
			}
		}
	}

	int my_hash_size = 0;
	for (int i = 0; i < HASH_SIZE; ++i) {
		my_hash_size += table[i][0];
	}

	if (my_hash_size != test.size()) {
		printf("remove error!!!\n");
	}

	return 0;
}


