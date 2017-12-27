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

    vector<int>         vals2 = vals;

    BinaryMinHeap<int> minHeap(vals);
    cout << "Data extraction from heap:" << endl;
    while (minHeap.size())
    {
        cout << minHeap.remove() << endl;
    }

    vals2.push_back(33);
    BinaryMinHeap<int>::sort(vals2);
    cout << "sorted vectors: " << endl;
    for (auto it = vals2.begin(); it != vals2.end(); ++it)
    {
        cout << *it <<endl;
    }

    return 0;
}
