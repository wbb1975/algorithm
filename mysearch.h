#ifndef MYSEARCH_H_
#define MYSEARCH_H_

namespace wangbb
{
    template <typename T>
    int binarysearch(T *arr, int size, T val)
    {
        int left   = 0;
        int right  = size - 1;
        while (left <= right)
        {
            int mid    = (left + right) /2;
            if (arr[mid] == val)
            {
                return mid;
            }
            else if (arr[mid] < val)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
}
#endif

