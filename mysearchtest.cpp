#include <iostream>
#include <string>
#include "mysearch.h"


using namespace std;
using namespace wangbb;


int main(int argc, char *argv[])
{
    cout <<"binarysearch: " << endl;
    const int size = 6;
    string arr[6] = {"jerry", "qingwen", "roger", "shawn", "wangbb", "yangyx"};
    string target = "yangyx";
    int idx = binarysearch(arr, 6, target);
    if (idx != -1)
    {
        cout << target << " found at " << idx << endl;
    }
    else
    {
        cout << target << " is not found" << endl;
    }
    
    return 0;
}

