#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(const string & s){
    left = nullptr;
    right = nullptr;
    data = s;
    parent = nullptr;
    height = 0;
}