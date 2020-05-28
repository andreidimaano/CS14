#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Node.h"

using namespace std;
class AVLTree {
    private:
        Node* root;
    public:
        AVLTree();
        void insert(const string&);
        int balanceFactor(Node*);
        void visualizeTree(const string &);
        void printBalanceFactors();
    private:
        void rotateRight(Node*);
        void rotateLeft(Node*);
        bool replaceChild(Node*, Node*, Node*);
        bool setChild(Node*, string , Node*);
        void treeRebalance(Node*);
        void updateHeight(Node*);
        void visualizeTree(ofstream &, Node *);
        int heightRecursion(Node*);
        void printBalanceFactors(Node*);
};

#endif