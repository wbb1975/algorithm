/*
 *  Heap implementation
 *  Reference: http://opendatastructures.org/ods-cpp/10_Heaps.html
 *  History:
 *  2017-12-24   Initial Created
 *
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include <algorithm>

namespace wangbb
{
    template<class T>
    class BinaryMinHeap
    {
    protected:
	    std::vector<T> arr;
	    void bubbleUp(int i)
	    {
	        int p = parent(i);
	        while (i > 0 && arr[i] < arr[p])
	        {
		        std::swap(arr[i], arr[p]);
		        i = p;
		        p = parent(i);
	        }
        }

	    void trickleDown(int i)
	    {
	        int n = size();
	        do
	        {
		        int j = -1;
		        int r = right(i);
		        if (r < n && arr[r] < arr[i])
		        {
			        int l = left(i);
			        if (arr[l] < arr[r])
			        {
				        j = l;
			        }
			        else
			        {
				        j = r;
			        }
		        }
		        else
		        {
			        int l = left(i);
			        if (l < n && arr[l] < arr[i])
			        {
				        j = l;
			        }
		        }
		        if (j >= 0)
		        {
		            std::swap(arr[i], arr[j]);
		        }
		        i = j;
	        } while (i >= 0);
	    }

	    static int left(int i)
	    {
		    return 2*i + 1;
	    }
	    static int right(int i)
	    {
		    return 2*i + 2;
	    }
	    static int parent(int i)
	    {
		    return (i-1)/2;
	    }

    public:
	    BinaryMinHeap()
	    {
	    }
	    BinaryMinHeap(const T *pArr, int size)
	    {
	        arr.assign(pArr, pArr + size);
            for (int i = size/2 - 1; i >= 0; --i)
            {
                trickleDown(i);
            }
	    }
	    BinaryMinHeap(const std::vector<T> &vec)
	    {
	        arr = vec;
            for (int i = size()/2 - 1; i >= 0; --i)
            {
                trickleDown(i);
            }
	    }
	    virtual ~BinaryMinHeap()
	    {
	    }
	    bool add(const T &x)
	    {
	        arr.push_back(x);
	        bubbleUp(size()-1);
	        return true;
	    }

	    T findMin()
	    {
		    return arr[0];
	    }
	    T remove()
	    {
	        T x = arr[0];
	        arr[0] = arr[size()-1];
	        arr.erase(arr.rbegin());
	        trickleDown(0);
	        return x;
	    }
	    int size()
	    {
		    return static_cast<int>(arr.size());
	    }

	    static void sort(std::vector<T>& vals)
	    {
	        BinaryMinHeap heap(vals);
	        int size = heap.size();
	        while (size > 1)
	        {
		        std::swap(heap.arr[--size], heap.arr[0]);
		        heap.trickleDown(0);
            }
            vals.swap(heap.arr);
	    }

	    // just for debugging
        const std::vector<T>& getArr(void) const
        {
            return arr;
        }
    };
}
#endif
