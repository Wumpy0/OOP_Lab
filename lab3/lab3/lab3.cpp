#include <iostream>
#include "BoolVector.h"

int main() {
    BoolVector bv("111100001111000011");
    std::cout << "Original: " << bv << std::endl;

    bv <<= 11;
    std::cout << "After <<=: " << bv << std::endl;

    return 0;
}