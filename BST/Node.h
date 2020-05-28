#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>

using namespace std;


class Node {
    private:
        // Node* left;
        // Node* right;
        string nodeString;
        int count;
    public:
        Node* left;
        Node* right;
        Node(const string &, const int &);
        string getString() const;
        int getCount() const;
        void setString(const string &s);
        void incrementCount();
        // Node* getLeft() const;
        // void setLeft(Node *);
        // Node* getRight() const;
        // void setRight(Node *);
        void setCount(const int &);

};

#endif
