#include <iostream>
#include <string>
#include "mysort.h"
#include "concurrency.h"

using namespace std;
using namespace wangbb;


int main(int argc, char *argv[])
{
    cout <<"inertSort: " << endl;
    const int size = 6;
    string arr[6] = {"wangbb", "qingwen", "jerry", "wangyx", "roger", "shawn"};
    insertSort(arr, 6);
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
    
    cout << "heapSort: " << endl;
    int intArr[] = {23, 120, 98, 85, 6, 1, 100, 10, 101, 400, 800, 10000, 43, 90, 2, 234, 567, 875, 543, 980, 129};
    //int intArr[] = {23, 120, 98, 85, 6, 1, 100, 10, 101, 400, 800, 10000};
    //int newPivotIndx = partition(intArr, 0, 9, 1);
    //cout << "newPivotIndx = " << newPivotIndx << endl;
    //int kTH = selectKth(intArr, 0, 9, (9-0+1)/2+1);
    //cout << "kTH = " << kTH << endl;
    int arraySize = sizeof(intArr)/sizeof(intArr[0]);
    //buildMaxHeap(intArr, arraySize);
    heapSort(intArr, arraySize);    
    for (int i = 0; i < arraySize; ++i)
    {
        cout << intArr[i] << ", ";
    }
    cout << endl;
    
    cout << "medianSort: " << endl;
    float fArray[] = {1.0f, 0.8f, 2.2f, 100.76f, 3.1412f, 0.01f, 2000.01f};
    int   fArraySize = sizeof(fArray)/sizeof(fArray[0]);
    medianSort(fArray, fArraySize);
    for (int i = 0; i < fArraySize; ++i)
    {
        cout << fArray[i] << ", ";
    }
    cout << endl;
    
    cout << "quickSort: " << endl;
    short  sArray[] = {10, 0, 2, 100, 3, 99, 1};
    int    sArraySize = sizeof(sArray)/sizeof(sArray[0]);
    quickSort(sArray, sArraySize);
    for (int i = 0; i < sArraySize; ++i)
    {
        cout << sArray[i] << ", ";
    }
    cout << endl;
    
    cout << "mergeSort: " << endl;
    double dArray[] = {1.0, 0.8, 2.2, 100.76, 3.1412};
    int    dArraySize = sizeof(dArray)/sizeof(dArray[0]);
    mergeSort(dArray, dArraySize);
    for (int i = 0; i < dArraySize; ++i)
    {
        cout << dArray[i] << ", ";
    }
    cout << endl;
    
    // http://www.cs.rochester.edu/research/synchronization/pseudocode/queues.html
    // Queue<int> queue;
    
    cout << "BFPRT(Top n): " << endl;
    int    bfprtArray[] = {10, 0, 2, 100, 3, 99, 1, 11, 24, 46, 31, 35, 40, 38, 51, 57, 68, 71, 83, 91, 13, 26};
    int    bfprtArraySize = sizeof(bfprtArray)/sizeof(bfprtArray[0]);
    cout << "Original Array:" << endl;
    for (int i = 0; i < bfprtArraySize; ++i)
    {
        cout << bfprtArray[i] << ", ";
    }
    cout << endl;
    int bfprtIndex = bfprt(bfprtArray, bfprtArraySize, 10);
    cout << "The 10th value is " << bfprtArray[bfprtIndex] << endl;
    cout << "Original Array:" << endl;
    for (int i = 0; i < bfprtArraySize; ++i)
    {
        cout << bfprtArray[i] << ", ";
    }    
    cout << endl;
    
    return 0;
}

