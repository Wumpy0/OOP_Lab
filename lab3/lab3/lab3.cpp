#include <iostream>
#include "BoolVector.h"

int main() {
    BoolVector bv("100100001111011011110000000000000000");
    std::cout << "Original:  " << bv << std::endl;

    bv >>= 11;
    std::cout << "After >>=: " << bv << std::endl;

    return 0;
}