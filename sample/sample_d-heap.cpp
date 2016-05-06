#include "d-heap.hpp"
#include <vector>

#ifndef _CTIME_
#include <ctime>
#endif

int main(void) {
	int size = 10;
	D_HEAP<int> heap(size, 3);
    srand((size_t)time(NULL));
    for (int i = 0; i < size; i++) {
        heap.insert(rand(), PROHIBIT_MEMORY_REALLOCATION);
    }
    heap.heapify();
	cout << heap << endl;

	vector<int> v(size);

	for (int& x : v) {
		x = heap.getNodeKey(0);
		heap.deleteMinElem();
	}

	for (int x : v) {
		cout << x << "\t";
	}

	cout << endl;
    system("pause");
    return 0;
}