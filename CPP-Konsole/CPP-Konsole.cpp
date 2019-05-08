
#include <iostream>

int main() {
	int array[10];

	int* begin = array;
	int* end = &array[9];

	for (int* iterator = begin; iterator <= end; iterator++) {
		*iterator = function();
	}
	// ...
}

int function() {

	int stack = 0;

	int* heap = new int();

	delete heap;

}