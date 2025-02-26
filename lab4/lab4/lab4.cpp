#include <iostream>
#include "BoolMatrix.h"
#include <vector>

using std::cout;
using std::endl;

int main() {
    std::vector<const char*> charMatrix = {
        "1010000",
        "0101111",
        "1111101",
        "0000010"
    };
    std::vector<const char*> charMatrix2 = {
        "1010110",
        "0101001",
        "1000101",
        "1110010"
    };
    BoolMatrix bm(charMatrix);
    BoolMatrix bm2(charMatrix2);
    bm = bm ^ bm2;

    cout << bm << endl;

    return 0;
}