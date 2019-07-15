#include <iostream>
#include <algorithm>
using namespace std;

int heap_size;
int heap[10000];

void push(int data) {
	int target = heap_size + 1;
	while (target != 1 && heap[target / 2] < data) { // 루트가 아닐때 && 부모<데이터
		// 부모를 자식에 대입
		heap[target] = heap[target / 2];
		target /= 2;
	}
	heap[target] = data;
	++heap_size;
}

void pop() {
	int parent = 1, child = 2;
	int temp = heap[heap_size];
	while (child < heap_size) {
		if (child + 1 < heap_size && heap[child] < heap[child + 1]) { // right child 있는지 && left<right
			// 큰 값이 child
			++child;
		}
		if (temp >= heap[child]) {  // 맨 마지막 값이 제일 큰 경우
			break;
		}
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	--heap_size;
}

bool comp(int a, int b) {
	return a > b;
}

int main() {
	int a[10000] = { 0, }, b[10000] = { 0, };
	for (int i = 0; i < 9999; i++) {
		a[i] = rand() % 1000;
		b[i] = a[i];
	}
	// push, pop 잘 됐는지 확인
	sort(a, a + 9999, comp);
	for (int i = 0; i < 9999; i++) {
		push(b[i]);
	}
	for (int i = 0; i < 9999; i++) {
		if (a[i] != heap[1])
			printf("not heap\n");
		pop();
	}
	return 0;
}