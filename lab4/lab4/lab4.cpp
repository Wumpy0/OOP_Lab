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
    BoolMatrix bm(charMatrix);

    cout << bm << endl;

    return 0;
}