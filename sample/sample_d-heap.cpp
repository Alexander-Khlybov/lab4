#include <ctime>
#include "d-heap.h"

void start(KeyType*&, int);

int main(void) {
	KeyType* tree;
	int size = 20;

	start(tree, size);

	D_HEAP heap(tree, size, size, 3);
	cout << heap << endl;

    heap.sort();

	cout << heap << endl;
    system("pause");
    return 1;
}

void start(KeyType*& m, int size){
	srand(time(NULL));
	m = new KeyType[size];
	for (int i = 0; i < size; i++){
		m[i] = rand();
	}
}