#include <iostream>
#include "BoolVector.h"

int main()
{
	BoolVector bv = "1010101111011";
	bv.invert();
	bv[6] = true;
	std::cout << bv[6];
}