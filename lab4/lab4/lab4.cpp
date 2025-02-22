#include <iostream>
#include "BoolMatrix.h"

using std::cout;
using std::endl;

int main() {
    BoolMatrix bm(5, 5, true);
    BoolMatrix bm2(2, 3);
    bm.swap(bm2);
    cout << bm2 << endl;
    cout << bm.rowWeight(1);

    return 0;
}