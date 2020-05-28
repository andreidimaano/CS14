#include <iostream>
#include "IntList.h"

using namespace std;

int main()
{
    IntList l1;

    l1.push_front(3);
    cout << "l1: " << l1 << endl;
    //expecting: 3;

    l1.push_back(5);
    cout << "l1: " << l1 << endl;
    //expecting: 3 5
    cout << "Reverse: ";
    l1.printReverse();
    cout << endl;
    //expecting 5 3
    l1.push_front(20);
    l1.push_back(14);
    cout << "l1: " << l1 << endl;
    cout << "reverse: ";
    l1.printReverse();
    cout << endl;
    //expecting 20 3 5 14
    //expecting 14 5 3 20
    l1.pop_front();
    cout << "l1: " << l1 << endl;
    cout << "reverse: ";
    l1.printReverse();
    cout << endl;
    //expecting 3 5 14
    //14 3 5
    l1.pop_back();
    cout << "l1: " << l1 << endl;
    cout << "reverse: "; l1.printReverse(); cout << endl;
    //expecting 3 5 
    //5 3
    l1.pop_back();
    cout << "l1: " << l1 << endl;
    cout << "reverse: "; l1.printReverse(); cout << endl;

    l1.pop_back();
    cout << "l1: " << l1 << endl;
    cout << "reverse: "; l1.printReverse(); cout << endl;
    


    return 0;
}