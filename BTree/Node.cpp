#include "Node.h"
#include <iostream>

Node::Node(): A(""), B(""), C(""), left(0), middle1(0), middle2(0), right(0), parent(0){};
Node::Node(const string & s, Node* node1, Node* node2){
    A = s;
    left = node1;
    middle1 = node2;
}
Node::Node(const string & s, const string &s1, const string &s2){
    A = s;
    B = s1;
    C = s2;
}