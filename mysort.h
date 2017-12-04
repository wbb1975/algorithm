#ifndef MYSORT_H_
#define MYSORT_H_

#include <iostream>

namespace wangbb
{
    template <typename T>
    void insertSort(T *arr, int left, int right)
    {
        if (right <= left) return;

        for (int i = left + 1; i <= right; ++i)
        {
            T value = arr[i];
            int j = i -1;
            while (j >= 0 && value < arr[j] )
            {
                arr[j+1] = arr[j];
                j--;
            }
            // if the inserting position is just before the inserted item
            if (++j != i)
            {
                arr[j] = value;
            }
        }
    }
    
    template <typename T>
    void insertSort(T *arr, int size)
    {
        insertSort(arr, 0, size-1);
    }
    

    /**
     *  In linear time, re-arrage the sequence arr[left, right]. 
     *  Store pivot at the proper place so that the elements in subsequence arr[left, store)
     *  are all less than or equal to pivot and all elements in subsequence arr[[store+1, right] are all bigger than pivot.
     *  
     */
    template <typename T>
    int partition(T *arr, int left, int right, int pivotIndex)
    {
        T pivot = arr[pivotIndex];
    
        // switch the pivot to the tail
        T tmp = arr[right];
        arr[right] = pivot;
        arr[pivotIndex] = tmp;
    
        int store = left;
        int idx   = left;
        for (; idx < right; ++idx)
        {
            if (arr[idx] <= pivot)
            {
                if (idx == store)
                {
                    store++;
                    continue;
                }
                tmp = arr[store];
                arr[store] = arr[idx];
                arr[idx] = tmp;
                store++;
            }
        }
    
        tmp = arr[store];
        arr[store] = pivot;
        arr[right] = tmp;
        
        return store;
    }
    
    template <typename T>
    int selectPivotIndex(T *arr, int left, int right)
    {
        return left;
    }
    
    /**
     *  Search the Kth element is the array
     *  1 <= k <= (right-left+1)
     */
    template <typename T>
    int selectKth(T *arr, int left, int right, int k)
    {
         int idx = selectPivotIndex(arr, left, right);
         int pivotIndex = partition(arr, left, right, idx);
         if (k+left-1 == pivotIndex) return pivotIndex;
         
         if (k+left-1 < pivotIndex)
         {
             return selectKth(arr, left, pivotIndex-1, k);
         }
         else
         {
             return selectKth(arr, pivotIndex+1, right, k - (pivotIndex-left+1));
         }
    }
    
    template <typename T>
    void medianSort(T *arr, int left, int right)
    {      
        // return if only the sorting element is not bigger than 1
        if (right <= left) return;
        
        int mid = (right-left+1)/2;
        int me = selectKth(arr, left, right, mid+1);
        medianSort(arr, left, left+mid-1);
        medianSort(arr, left+mid+1, right);
    }
    
    template <typename T>
    void medianSort(T *arr, int size)
    {
        return medianSort(arr, 0, size -1);
    }
    
    
    template <typename T>
    void quickSort(T *arr, int left, int right)
    {
        const int minSize = 4;
        // return if only the sorting element is not bigger than 1
        if (right <= left) return;
        
        int pivotIndex = selectPivotIndex(arr, left, right);
        pivotIndex = partition(arr, left, right, pivotIndex);
        
        if (pivotIndex-1-left <= minSize)
        {
            insertSort(arr, left, pivotIndex-1);
        }
        else
        {
            quickSort(arr, left, pivotIndex-1);
        }
        
        if (right-pivotIndex-1 <= minSize)
        {
            insertSort(arr, pivotIndex+1, right);
        }
        else
        {
            quickSort(arr, pivotIndex+1, right);
        }
    }
    
    template <typename T>
    void quickSort(T *arr, int size)
    {
        quickSort(arr, 0, size-1);
    }
    
    
    
    template <typename T>
    void merge(T *arr, int first, int mid, int last)
    {
        int size = last - first + 1;
        T *temp = new T[size];
        int begin1 = first;
        int begin2 = mid + 1;
        
        int k = 0;
        for (; begin1 <= mid && begin2 <= last; ++k)
        {
            if (arr[begin1] <= arr[begin2])
                temp[k] = arr[begin1++];
            else
                temp[k] = arr[begin2++];       
        }
        while (begin1 <= mid)
        {
            temp[k++] = arr[begin1++];
        }
        while (begin2 <= last)
        {
            temp[k++] = arr[begin2++];
        }
        // copy values back t original array
        for (int i = first; i <= last; ++i)
        {
            arr[i] = temp[i-first];
        }
        delete [] temp;
    }
    
    template <typename T>
    void mergeSort(T *arr, int first, int last)
    {
        if (first < last)
        {
            int mid = (last+first-1)/2;
            mergeSort(arr, first, mid);
            mergeSort(arr, mid+1, last);
            merge(arr, first, mid, last);
        }
    }
 
    template <typename T>
    void mergeSort(T *arr, int size)
    {
        mergeSort(arr, 0, size-1);
    }
    
    
    /**
     * Heap related structures
     *  If the following functions are inlined, the result will be undefined. Tricky!!!
     */
    int leftIdx(int i)
    {
        return 2 * i + 1;
    }
    
    int rightIdx(int i)
    {
        return 2 * i + 2;
    }
    
    int parentIdx(int i)
    {
        return i/2;
    }
    
    template <typename T>
    void maxHeapify(T *arr, int size, int idx)
    {
        if (idx >= size - 1)
        {
            return;
        }
        int left  = leftIdx(idx);
        int right = rightIdx(idx);
        int largest = idx;
        if (left < size && arr[left] > arr[idx])
        {
            largest = left;
        }
        if (right < size && arr[right] > arr[largest])
        {
            largest = right;
        }
        if (largest == idx)
        {
            return;
        }
        else
        {
            T tmp = arr[idx];
            arr[idx] = arr[largest];
            arr[largest] = tmp;
            maxHeapify(arr, size, largest);
        }
    }
    
    template <typename T>
    void buildMaxHeap(T *arr, int size)
    {
        using namespace std;
        
        for (int i = size/2 - 1; i >= 0; --i)
        {
            maxHeapify(arr, size, i);
        }
    }
    
    template <typename T>
    void minHeapify(T *arr, int size, int idx)
    {
        if (idx >= size - 1)
        {
            return;
        }
        int left  = leftIdx(idx);
        int right = rightIdx(idx);
        int minimum = idx;
        if (left <= size && arr[left] < arr[idx])
        {
            minimum = left;
        }
        if (right <= size && arr[right] < arr[minimum])
        {
            minimum = right;
        }
        if (minimum == idx)
        {
            return;
        }
        else
        {
            T tmp = arr[idx];
            arr[idx] = arr[minimum];
            arr[minimum] = tmp;
            minHeapify(arr, size, minimum);
        }
    }
    
    template <typename T>
    void buildMinHeap(T *arr, int size)
    {
        for (int i = size/2 - 1; i >= 0; --i)
        {
            minHeapify(arr, size, i);
        }
    }    
    
    template <typename T>
    void heapSort(T *arr, int size)
    {
        buildMaxHeap(arr, size);
        for (; size >= 1;)
        {
            T tmp = arr[size-1];
            arr[size-1] = arr[0];
            arr[0] = tmp;
            maxHeapify(arr, --size, 0);
        }
    }
    
    
    template <typename T>
    void mySwap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
    
    template <typename T>
    int bfprt_getMedianMedian(T *arr, int left, int right)
    {
        if ((right - left) < 5)
        {
            insertSort(arr, left, right);
            return ((right - left) >> 1) + left;
        }
        
        int subscript = left - 1;
        for (int i = left; (i + 4) <= right; i += 5)
        {
            insertSort(arr, i, i+4);
            mySwap(arr[++subscript], arr[i+2]);
        }
        
        return bfprt_getMedianMedian(arr, left, subscript);
    }
    
    // reorder the array to make all top n elements are the first n elements
    template <typename T>
    int bfprt(T *arr, int left, int right, const int n)
    {
        // return subscript of the median of the medians
        int pivotIndex  = bfprt_getMedianMedian(arr, left, right);
        int devideIndex = partition(arr, left, right, pivotIndex);
        
        int num = devideIndex - left + 1;
        if (num == n)
        {
            return devideIndex;
        }
        else if (num < n)
        {
            return bfprt(arr, devideIndex + 1, right, n - num);
        }
        else
        {
            return bfprt(arr, left, devideIndex - 1, n);
        }
    }
    
    // n: how many elements for this top n issue
    template <typename T>
    int bfprt(T *arr, int size, const int n)
    {
        return bfprt(arr, 0, size - 1, n);
    }    
} // end of namespace

#endif

