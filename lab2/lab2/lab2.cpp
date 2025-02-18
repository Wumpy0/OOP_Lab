#include <iostream>
#include "Array.h"

int main()
{
	int arr[6]{ 1, 2, 3, 4, 5, 6};
	Array<int> a(2);
	Array<int> b(arr, 6);
	Array<int> c(a);
	c += 3;
	b.print();
	b.insert(4, b.end());


	std::cout << b << std::endl;
	b.print();

	return 0;
}