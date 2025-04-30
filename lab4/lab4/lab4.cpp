#include <iostream>
#include "BoolMatrix.h"
#include <vector>

using std::cout;
using std::endl;

int main() {
    std::vector<const char*> charMatrix = {
        "1010000",
        "0101111",
        "1111001",
        "0000110"
    };
    std::vector<const char*> charMatrix2 = {
        "10101101",
        "01010011",
        "10001011",
        "11100101"
    };
    BoolMatrix bm(charMatrix);
    BoolMatrix bm2(charMatrix2);
    bm = bm ^ bm2;


    cout << bm << endl;
    cout << bm.weight() << endl;
    cout << bm.conjunction() << endl;
    cout << bm.disjunction() << endl;

    return 0;
}