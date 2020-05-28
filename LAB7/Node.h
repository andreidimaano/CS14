#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node{
    friend class AVLTree;
    private:
        string data;
        Node* parent;
        Node* left;
        Node* right;
        int height;
    public:
        Node(const string &);
};

#endif