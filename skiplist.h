/*
 *  SkipList implementation
 *  History:
 *  2017-12-23   Initial Created
 *  TODO: add iterator support
 *
 */
#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <cstdlib>

namespace wangbb
{
    template <typename T>
    class SkipList
    {
    public:
        static const int MAX_HEIGHT = 31;

        struct Node
        {
            T       val;
            int     height;    // length of next (height + 1)
            Node    *next[];   // Node * array, how many appearances for this val, variant
        };

        SkipList(int maxHeight = MAX_HEIGHT): h(0), n(0)
        {
	        sentinel = newNode(T(0), maxHeight);
        }

        virtual ~SkipList()
        {
	        clear();
	        deleteNode(sentinel);
        }

        inline int height() const
        {
             return height;
        }

        inline size_t size() const
        {
             return n;
        }

        bool add(const T &x)
        {
            Node *update[MAX_HEIGHT+1];
	        Node *u = sentinel;
	        int r = h;
	        while (r >= 0)
	        {
		        while (u->next[r] != nullptr && u->next[r]->val < x)
		        {
			        u = u->next[r];
			    }
		        if (u->next[r] != nullptr && u->next[r]->val == x)
		        {
			        return false;
			    }
		        update[r--] = u;        // going down, store u
	        }

	        Node *w = newNode(x, randomHeight());
	        while (h < w->height)
	        {
		        update[++h] = sentinel; // height increased
		    }
	        for (int i = 0; i <= w->height; ++i)
	        {
		        w->next[i] = update[i]->next[i];
		        update[i]->next[i] = w;
	        }
	        n++;
	        return true;
        }

        bool remove(const T &x)
        {
	        bool removed = false;
	        Node *u   = sentinel;
	        Node *del = nullptr;
	        int r = h;
	        while (r >= 0)
	        {
		        while (u->next[r] != nullptr && u->next[r]->val < x)
		        {
			        u = u->next[r];
		        }
		        if (u->next[r] != nullptr && u->next[r]->val == x)
		        {
			        removed = true;
			        del = u->next[r];
			        u->next[r] = u->next[r]->next[r];
			        if (u == sentinel && u->next[r] == nullptr)
			        {
				        h--; // skiplist height has gone down
				    }
		        }
		        r--;
	        }
	        if (removed)
	        {
		        deleteNode(del);
		        n--;
	        }

	        return removed;
        }

        const Node* header() const
        {
            return sentinel->next[0];
        }

        static int randomHeight()    // 31 is max
        {
            int z = rand();
            int m = 1;
            int height = 0;
            while ((z & m) != 0)
            {
                height++;
                m <<= 1;
            }
            return height;
        }

        T* find(const T &x)
	    {
            Node *u = findPredNode(x);
	        return u->next[0] == nullptr ? nullptr: &(u->next[0]->val);
        }
    protected:
        Node* newNode(const T &x, int height)
        {
	        Node *u = (Node*)malloc(sizeof(Node)+(height + 1)*sizeof(Node*));
	        u->val = x;
	        u->height = height;
	        for (int i = 0; i <= height; ++i)
	        {
	            u->next[i] = nullptr;
	        }
	        return u;
        }

        void deleteNode(Node *u)
        {
	        free(u);
        }

        Node* findPredNode(const T &x)
        {
	        Node *u = sentinel;
	        int r = h;
	        while (r >= 0)
	        {
		        while (u->next[r] != nullptr && u->next[r]->val < x)
                {
			        u = u->next[r]; // go right in list r
			    }
		        --r;                // go down into list r-1
	        }
	        return u;
	    }

        void clear()
        {
	        Node *u = sentinel->next[0];
	        while (u != nullptr)
	        {
		        Node *n = u->next[0];
		        deleteNode(u);
		        u = n;
	        }
	        for (int i = 0; i <= h; ++i)
	        {
	            sentinel->next[i] = nullptr;
	        }
	        h = 0;
	        n = 0;
        }
	private:
	    Node     *sentinel;
	    int       h;         // the max height of the total skiplist
	    size_t    n;         // the total element in L0
    };
}

#endif
