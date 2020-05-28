#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include "Node.h"

using namespace std;

class BTree {
    private:
        Node *root;
    public:
        BTree();
        ~BTree();
        Node* search(Node*, const string &);
        void insert(const string &);
    private:
        //insert
        void insert(Node*, const string &);
        Node* split(Node*);
        void insertKeyWithChildren(Node*, const string &, Node*, Node*);
        void insertIntoLeaf(Node*, const string &);
        bool isKeyInNode(Node *, const string &);
        bool isNodeFull(Node*);
        bool isLeaf(Node*);

        //delete

        //rotate
        Node* getLeftSibling(Node*)const;
        Node* getRightSibling (Node*)const;
        string getParentKeyLeftOfChild(Node*, Node*)const;
        string getParentKeyRighttOfChild(Node*, Node*)const;
        void setParentKeyLeftOfChild(Node*, Node* , const string &);
        void setParentKeyRightofChild(Node*, Node*, const string &);
        void addKeyAndChildLR(Node*, Node*, const string&);
        void addKeyAndChildRR(Node*, Node*, const string&);
        void removeKey(Node*, const int& );
        void rotateLeft(Node*);
        void rotateRight(Node*);

        //fuse
        void fuseRoot(Node*);
        void fuse(Node*, Node*);
        int getKeyIndex(Node*, const string &);
        void setChild(Node*, Node*, const int &);

};

#endif