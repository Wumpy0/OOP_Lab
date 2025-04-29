#include <iostream>

#include "List.h"

using std::cout;
using std::endl;

int main()
{
    int arr[] = { 1, 3, 5, 7, 8, 3, -56, 7, 3 };
    int arr2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    List<int> list(arr, 9);
    List<int> list2(arr2, 9);
    list.push_front(-348);
    list.pop_back();
    list.insert(3, 100);
    list.remove(8);
    list += list2;

    cout << list << endl;
    cout << list.getSize() << endl;
    cout << list.min();
}