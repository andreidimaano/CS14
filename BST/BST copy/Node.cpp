#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(const string & s, const int & n){
    left = nullptr;
    right = nullptr;
    nodeString = s;
    count = n;
}
int Node::getCount() const {
    return count;
}
void Node::setCount(const int &n) {
    count = n;
}
void Node::incrementCount(){
    count++;
}
string Node::getString() const {
    return nodeString;
}
void Node::setString(const string &s) {
    this->nodeString = s;
}
// Node* Node::getLeft() const {
//     return left;
// }
// Node* Node::getRight() const {
//     return right;
// }
// void Node::setLeft(Node * node) {
//     left = node;
// }
// void Node::setRight(Node* node) {
//     right = node;
// }