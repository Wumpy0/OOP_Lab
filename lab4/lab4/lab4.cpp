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
    bm.setValue(3, 5, true, 2);

    cout << bm << endl;

    return 0;
}