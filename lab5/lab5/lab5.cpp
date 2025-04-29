#include <iostream>

#include "List.h"

using std::cout;
using std::endl;

int main()
{
    int arr[] = {1, 3, 5, 7, 8, 3, 56, 7, 3};
    List<int> list(arr, 9);
    list.push_front(348);
    list.pop_back();

    cout << list << endl;
    cout << list.getSize() << endl;
    cout << list.min();
}