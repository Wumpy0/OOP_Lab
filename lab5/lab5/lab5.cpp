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
    
    List<int>::Iterator it = list.end();

    cout << *it << endl;
}