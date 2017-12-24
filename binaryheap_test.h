#include <iostream>
#include <vector>

#include "binaryheap.h"

using namespace std;
using namespace wangbb;

int main()
{
    vector<int>         vals;
    vals.push_back(1);
    vals.push_back(10);
    vals.push_back(2);
    vals.push_back(99);
    vals.push_back(5);
    vals.push_back(100);
    vals.push_back(39);
    vals.push_back(64);

    BinaryMinHeap<int>::sort(vals);
    cout << " sorted val: " << endl;
    for (auto it = vals.begin(); it != vals.end(); ++it)
    {
        cout << *it << endl;
    }


    return 0;
}
