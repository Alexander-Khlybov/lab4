#include <ctime>
#include "d-heap.h"

int main(void) {
	int size = 10;
	D_HEAP heap(size, 3);
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        heap.insert(rand(), PROHIBIT_MEMORY_REALLOCATION);
    }
    heap.heapify();
	cout << heap << endl;

    heap.sort();

	cout << heap << endl;
    system("pause");
    return 1;
}