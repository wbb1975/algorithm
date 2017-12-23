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

	int val1 = 70;
	int *found1 = skipList.find(val1);
	if (found1 == nullptr)
	{
	    cout << "not found " << val1 << endl;
	}
	else
	{
        cout << "find " << val1 << " return " << *found1 <<endl;
	}

	int val2 = 10;
	int *found2 = skipList.find(val2);
	if (found2 == nullptr)
	{
	    cout << "not found " << val2 << endl;
	}
	else
	{
        cout << "find " << val2 << " return " << *found2 <<endl;
	}

	int val3 = 80;
	int *found3 = skipList.find(val3);
	if (found3 == nullptr)
	{
	    cout << "not found " << val3 << endl;
	}
	else
	{
        cout << "find " << val3 << " return " << *found3 <<endl;
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
