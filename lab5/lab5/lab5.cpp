#include <iostream>

#include "List.h"

using std::cout;
using std::endl;

int main()
{
    int arr[] = { 1, 3, 4, 7, 8, 3, -56, 7, 3 };
    int arr2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    List<int> list(arr, 9);
    const List<int> list2(arr2, 9);
    
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it = list.begin();
    it++;
    it++;
    it++;
    it++;
    it1++;
    list.remove(it, it1);

    cout << list << endl;
    cout << list[2] << endl;
}