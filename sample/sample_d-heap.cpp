#include "algorithms.h"
#include <vector>
#include <ctime>

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
	ALGORITHM::sort(v);
	cout << "\nSorted vector:\t\t";
	for (int x : v) {
		cout << x << "\t";
	}
	cout << endl;
	getchar();
    return 0;
}