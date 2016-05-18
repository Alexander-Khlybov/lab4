#include "d-heap.hpp"
#include <vector>
#include <ctime>
void sort(vector<int>&);
int main(void) {
	int size = 10;
	srand((size_t)time(NULL));
	vector<int> v(size);
	for (int i = 0; i < size; i++) {
		v[i] = rand();
	}

	cout << "Original vector:\t";
	for (int x : v) {
		cout << x << "\t";
	}

	sort(v);

	cout << "\nSorted vector:\t\t";
	for (int x : v) {
		cout << x << "\t";
	}
	cout << endl;
	getchar();
    return 0;
}

void sort(vector<int>& v) {
	D_HEAP<int> heap(v.size(), 3);

	for (int x : v) {
		heap.insert(x, PROHIBIT_MEMORY_REALLOCATION);
	}

	for (size_t i = 0; i < v.size(); i++) {
		v[i] = heap.getNodeKey(0);
		heap.deleteMinElem();
	}
}
