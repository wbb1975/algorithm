#include <iostream>

#include "skiplist.h"

using namespace std;
using namespace wangbb;

int main()
{
    SkipList<int>   skipList;
    skipList.add(1);
    skipList.add(4);
    skipList.add(6);
    skipList.add(7);
    skipList.add(9);
    skipList.add(11);
    skipList.add(70);

    cout << "initially list size = " << skipList.size() << endl;
    const SkipList<int>::Node *u = skipList.header();
    while (u != nullptr)
    {
	     cout << u->val << endl;
	     u = u->next[0];
	}
	cout << endl;

	int val = 70;
	int *found = skipList.find(val);
	if (found == nullptr)
	{
	    cout << "not found " << val << endl;
	}
	else
	{
        cout << "found " << *found <<endl;
	}

    skipList.remove(6);
    skipList.remove(1);
    cout << "after remove list size = " << skipList.size() << endl;
    const SkipList<int>::Node *v = skipList.header();
    while (v != nullptr)
    {
	     cout << v->val << endl;
	     v = v->next[0];
	}
    cout << endl;

    return 0;
}
