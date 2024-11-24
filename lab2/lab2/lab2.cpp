#include <iostream>
#include "Array.h"

int main()
{
	int arr[6]{ 1, 3, 2, 2, 3, 2};
	Array<int> a(2);
	Array<int> b(arr, 6);
	Array<int> c(a);
	c += 3;

	a.print();
	b.print();
	c.print();


	std::cout << b << std::endl;

	return 0;
}