#include <iostream>
#include "Array.h"

int main()
{
	int arr[6]{ 1, 3, 2, 2, 3, 2};
	Array<int> a(2);
	Array<int> b(arr, 6);
	Array<int> c;
	a += b;

	a.print();
	b.print();
	c.print();


	std::cout << b[3] <<std::endl;

	return 0;
}