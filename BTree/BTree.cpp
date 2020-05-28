#include "BTree.h"
#include <iostream>

using namespace std;

BTree::BTree() : root(nullptr){}

Node* BTree::search(Node* node, const string & key){
    if(!node){
        if(key == node->A || key == node->B || key == node->C){
            return node;
        }

        if(key < node->A){
            return search(node->left, key);
        } else if(key < node->B){
            return search(node->middle1, key);
        } else if(key < node->C){
            return search(node->middle2, key);
        } else {
            return search(node->right, key);
        }
    }

    return nullptr;
}

void BTree::insert(const string &key){
    insert(root, key);
}
void BTree::insert(Node* node, const string& key){
    if(isKeyInNode){
        return;
    }
    if(isNodeFull(node)){
        node = split(node);
    }
    if(!isLeaf(node)){
        if(key < node->A){
            return insert(node->left, key);
        } else if(node->B == "" || key < node->B){
            return insert(node->middle1, key);
        } else if(node->C == "" || key < node->C){
            return insert(node->middle2, key);
        } else{
            return insert(node->right, key);
        }
    } else {
        insertIntoLeaf(node, key);
    }
}
void BTree::insertIntoLeaf(Node* node, const string & key){
    if(key < node->A){
        node->C = node->B;
        node->B = node->A;
        node->A = key;
    } else if (node->B == "" || key < node->B) {
        node->C = node->B;
        node->B = key;
    } else {
        node->C = key;
    }
}
Node* BTree::split(Node* node){
    if(!isNodeFull(node)){
        return nullptr;
    }

    Node* nodeParent = node->parent;
    Node* splitLeft = new Node(node->A, node->left, node->middle1);
    Node* splitRight = new Node(node->C, node->middle2, node->right);

    if(nodeParent){
        insertKeyWithChildren(nodeParent, node->B, splitLeft, splitRight);
    } else {
        nodeParent = new Node(node->B, splitLeft, splitRight);
        root = nodeParent;
    }

    return nodeParent;
}
void BTree::insertKeyWithChildren(Node* parent, const string & key, Node* leftChild, Node* rightChild){
    if(key < parent->A){
        parent->C = parent->B;
        parent->B = parent->A;
        parent->A = key;
        parent->right = parent->middle2;
        parent->middle2 = parent->middle1;
        parent->middle1 = rightChild;
        parent->left = leftChild;
    } else if(parent->B == "" || key < parent->B){
        parent->C = parent->B;
        parent->B = key;
        parent->right = parent->middle2;
        parent->middle2 = rightChild;
        parent->middle1 = leftChild;
    } else {
        parent->C = key;
        parent->middle2 = leftChild;
        parent->right = rightChild;
    }
}
bool BTree::isKeyInNode(Node* node, const string &key){
    if(node->A && node->A == key){
        return true;
    } else if(node->B && node->B == key){
        return true;
    } else if(node->C && node->C == key) {
        return true;
    }

    return false;
}
bool BTree::isNodeFull(Node* node){
    if((node->A == "") || (node->B == "") || (node->C == "")){
        return false;
    }

    return true;
}
bool BTree::isLeaf(Node* node){
    if(!(node->left ||node->middle1 || node->middle2 || node->right)){
        return true;
    }

    return false;
}


//rotate
void BTree::rotateLeft(Node* node){
    Node* leftSibling = getLeftSibling(node);
    string keyForLeftSibling = getParentKeyLeftOfChild(node->parent, node);
    addKeyAndChildLR(leftSibling, node->left, keyForLeftSibling);
    setParentKeyLeftOfChild(node->parent, node, node->A);
    removeKey(node, 0);
}
void BTree::rotateRight(Node* node){
    Node* rightSibling = getRightSibling(node);
    string keyForRightSibling = getParentKeyRighttOfChild(node->parent, node);
    if(node->right){
         addKeyAndChildRR(rightSibling, node->right, keyForRightSibling);
    } else if(node->middle2) {
        addKeyAndChildRR(rightSibling, node->middle2, keyForRightSibling);
    }
    if(node->C != ""){
        setParentKeyRightofChild(node->parent, node, node->C);
        removeKey(node, 2);
    }else {
        setParentKeyRightofChild(node->parent, node, node->B);
        removeKey(node, 1);
    }
    
}
Node* BTree::getLeftSibling(Node* node)const{
    Node* leftSibling = nullptr;
    if(node->parent->right && node->parent->right == node){
        leftSibling = node->middle2;
    } else if(node->parent->middle2 && node->parent->middle2 == node){
        leftSibling = node->middle1;
    } else if(node->parent->middle1 && node->parent->middle1 == node){
        leftSibling = node->left;
    }
    return leftSibling;
}
Node* BTree::getRightSibling (Node* node)const{
    Node* rightSibling = nullptr;
    if(node->parent->left && node->parent->left == node){
        rightSibling = node->middle1;
    } else if(node->parent->middle1 && node->parent->middle1 == node){
        rightSibling = node->middle2;
    } else if(node->parent->middle2 && node->parent->middle2 == node){
        rightSibling = node->right;
    }
    return rightSibling;
}
string BTree::getParentKeyLeftOfChild(Node* parent, Node* child)const{
    if(parent->C != "" && parent->C < child->A){
        return parent->C;
    } else if(parent->B != "" && parent->B < child->A){
        return parent->B;
    }

    return parent->A;
}
string BTree::getParentKeyLeftOfChild(Node* parent, Node* child)const{
    if(parent->A != "" && parent->A > child->C){
        return parent->A;
    } else if(parent->B != "" && parent->B > child->C){
        return parent->B;
    }

    return parent->C;
}
void BTree::setParentKeyLeftOfChild(Node* parent, Node* child, const string & key){
    string parentRightOfChild = getParentKeyRighttOfChild(parent, child);
    if(parent->A == parentRightOfChild){
        parent->A = key;
        return;
    } else if(parent->B == parentRightOfChild) {
        parent->B = key;
    } else {
        parent->C = key;
    }
}
void BTree::setParentKeyRightofChild(Node* parent, Node* child, const string & key){
    string parentRightOfChild = getParentKeyRighttOfChild(parent, child);
    if(parent->A == parentRightOfChild){
        parent->A = key;
        return;
    } else if(parent->B == parentRightOfChild){
        parent->B = key;
    } else {
        parent->C = key;
    }
}
void BTree::addKeyAndChildLR(Node* parent, Node* child, const string& key){
    if(parent->B == "" && key > parent->A){
        parent->C = parent->B;
        parent->B = key;
        parent->right = parent->middle2;
        parent->middle2 = child;
        return;
    } else if(parent->C == "" && key > parent->B) {
        parent->C = key;
        parent->right = child;
        return;
    }
}
void BTree::addKeyAndChildRR(Node* parent, Node* child, const string& key){
    if(key < parent->A){
        parent->C = parent->B;
        parent->B = parent->A;
        parent->A = key;
        parent->right = parent->middle2;
        parent->middle2 = parent->middle1;
        parent->middle1 = parent->left;
        parent->left = child;
    }
}
void BTree::removeKey(Node* node, const int& keyIndex){
    if(keyIndex == 0){
        node->A = node->B;
        node->B = node->C;
        node->C = "";
        node->left = node->middle1;
        node->middle1 = node->middle2;
        node->middle2 = node->right;
        node->right = nullptr;
    } else if(keyIndex == 1){
        node->B = node->C;
        node->C = "";
        node->middle2 = node->right;
        node->right = nullptr;
    } else if(keyIndex == 2){
        node->C = "";
        node->right = nullptr;
    }
}

//fuse
void BTree::fuseRoot(Node* root){
    //only happens when the root and root's 2 children each have 1 key
    Node* oldLeft = root->left;
    Node* oldMiddle1 = root->middle1;

    root->B = root->A;
    root->A = oldLeft->A;
    root->C = oldMiddle1->A;
    root->left = oldLeft->left;
    root->middle1 = oldLeft->middle1;
    root->middle2 = oldMiddle1->left;
    root->right = oldMiddle1->middle1;
}
void BTree::fuse(Node* leftNode, Node* rightNode){
    Node* parent =leftNode->parent;
    if(root == parent && parent->B == ""){
        return fuseRoot(parent);
    }

    string middleKey = getParentKeyLeftOfChild(parent, rightNode);
    Node* fusedNode = new Node(leftNode->A, middleKey, rightNode->A);
    fusedNode->left = leftNode->left;
    fusedNode->middle1 = leftNode->middle1;
    fusedNode->middle2 = rightNode->left;
    fusedNode->right = rightNode->middle1;

    int keyIndex = getKeyIndex(parent, middleKey);
    removeKey(parent, keyIndex);
    setChild(parent, fusedNode, keyIndex);
}
int BTree::getKeyIndex(Node* parent, const string& middleKey){
    if(middleKey == parent->A){
        return 0;
    } else if(middleKey == parent->B){
        return 1;
    }

    return 2;
}
void BTree::setChild(Node* parent, Node* fusedNode, const int & keyIndex){
    Node* oldRight = parent->right;
    Node* oldMiddle2 = parent->middle2;
    Node* oldMiddle1 = parent->middle1;
    if(keyIndex == 0){
        parent->middle2 = oldRight;
        parent->middle1 = oldMiddle2;
        parent->left = fusedNode;
    } else if(keyIndex == 1){
        parent->middle2 = oldRight;
        parent->middle1 = fusedNode;
    } else if(keyIndex == 2){
        parent->middle2 = fusedNode;
    }
}