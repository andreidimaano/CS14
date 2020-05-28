#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"
#include <stdexcept>
#include <fstream>

using namespace std;

BSTree::BSTree(){
    root = nullptr;
}
BSTree::~BSTree(){
    // cout << "destructor called";
}
// void BSTree::clear(Node * n) const{
//     if(n == nullptr){
//         return;
//     }

//     clear(n->left);
//     clear(n->right);
//     delete n;
// }
void BSTree::insert(const string &newString){
    if(root == nullptr){
        // cout << "root insert" << endl;
        root = new Node(newString, 1);
        // cout << root->getString();
    }else {
        Node* currNode = root;
        while(true){
            if(newString == currNode->getString()){
                currNode->incrementCount();
                break;
            } else if(newString < currNode->getString()){
                // cout << "left";
                if(currNode->left == nullptr){
                    // cout << "good left insert" << endl;
                    Node* parent = currNode;
                    Node* newNode = new Node(newString, 1);
                    parent->left = newNode;
                    // cout << parent->left->getString() << endl;
                    break;
                } else{
                    // cout << "changing node" << endl;
                    currNode = currNode->left;
                }
            } else if(newString > currNode->getString()){
                // cout << "right";
                if(currNode->right == nullptr){
                    // cout << "good insert right";
                    Node* parent = currNode;
                    Node* newNode = new Node(newString, 1);
                    parent->right = newNode;
                    // cout << parent->right->getString() << endl;
                    break;
                } else {
                    // cout << "changing node" << endl;
                    currNode = currNode->right;
                }
            }
        }
    }
}

void BSTree::remove(const string &key){
    //1. DNE
    // Node* parentNode = nullptr;
    // cout << curr << endl;

     if(search(key)){  
        Node* curr = findNode(key);
        Node* parent = findParent(key);

        if (curr->getCount() > 1) {
            curr->setCount(curr->getCount() - 1);
            return;
        }

        while(curr){
            if(!curr->left && !curr->right) {
                //2. leafnode
                if(curr != root) {
                    if(parent->left && parent->left->getString() == key){
                        delete parent->left;
                        parent->left = nullptr;
                        return;
                    } else {
                        delete parent->right;
                        parent->right = nullptr;
                        return;
                    }
                } else {
                    delete root;
                    root = nullptr;
                    return;
                }
            } else if(curr->left) {
                Node* succ = curr->left;
                //finding successor
                while (succ->right) {
                    succ = succ->right;
                }
                string succString = succ->getString();
                int count = succ->getCount();
                for(int i = 0; i < count; i++){
                    remove(succ->getString());
                }
                curr->setString(succString);
                curr->setCount(count);
                return;
            } else if(curr->right) {
                Node* succ = curr->right;
                //finding successor
                while (succ->left){
                    succ = succ->left;
                }
                string succString = succ->getString();
                int count = succ->getCount();
                for(int i = 0; i < count; i++){
                    remove(succ->getString());
                }
                curr->setString(succString);
                curr->setCount(count);
                return;
            }
            //  else if(curr->left && !curr->right){
            //     if(curr != root) {
            //         //left children only
            //         if(parent->left && parent->left->getString() == key){
            //             parent->left = curr->left;
            //             delete curr;
            //             return;
            //         } else {
            //             parent->right = curr->left;
            //             delete curr;
            //             return;
            //         }
            //     } else {
            //         root = curr->left;
            //         delete curr;
            //         return;
            //     }
            // } else {
            //     if(!curr->left){
            //         Node* succ = curr->right;
            //     }
            //     Node* succ = curr->left;

            //     //finding successor
            //     while (succ->right) {
            //         succ = succ->right;
            //     }
            //     string succString = succ->getString();
            //     int count = succ->getCount();
            //     for(int i = 0; i < count; i++){
            //         remove(succ->getString());
            //     }
            //     curr->setString(succString);
            //     curr->setCount(count);
            //     return;
            // }
            // }
            // else if (curr->right && !curr->left) {
            //     if(curr != root) {
            //         if(parent->left && parent->left->getString() == key) {
            //             parent->left = curr->right;
            //             delete curr;
            //             return;
            //         } else {
            //             parent->right = curr->right;
            //             delete curr; 
            //             return;
            //         }
            //     } else {
            //         root = curr->right;
            //         delete curr;
            //         return;
            //     }
            // } 
            // else if(curr->left && curr->right) {
            //     Node* succ = curr->left;

            //     //finding successor
            //     while (succ->right) {
            //         succ = succ->right;
            //     }
            //     string succString = succ->getString();
            //     int count = succ->getCount();
            //     for(int i = 0; i < count; i++){
            //         remove(succ->getString());
            //     }
            //     curr->setString(succString);
            //     curr->setCount(count);
            //     return;
            // }
        }
     }        
}


int BSTree::height(const string &s) const{
    if(!search(s)){
        return -1;
    }
    
    Node* node = findNode(s);
    return heightRecursion(node) - 1; 
}
int BSTree::heightRecursion(const Node *currNode) const { 
    if (currNode == nullptr){
        return 0;
    } else {  
        /* compute the depth of each subtree */
        int lDepth = heightRecursion(currNode->left);  
        int rDepth = heightRecursion(currNode->right);  
      
        /* use the larger one */
        if (lDepth > rDepth){
            return(lDepth + 1);  
        }else {

        } return(rDepth + 1);  
    }  
}
// int BSTree::heightRecursion(const Node *currNode) const {
    // if(currNode->getString() == s){
    //     return 0;
    // }

    // if(s < currNode->getString()){
    //     currNode = currNode->left;
    // } else {
    //     currNode = currNode->right;
    // }

//     // return 1 + heightRecursion(currNode, s);
// }




bool BSTree::search(const string &key) const{
    Node* curr = root;
    string currString;

    while(curr != nullptr){
        currString = curr->getString();
        if(currString == key){
            return true;
        }

        if(key < currString){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return false;
}
string BSTree::largest() const{
    Node* currNode = root;
    string s = "";
    while(currNode!= nullptr){
        if(currNode->right == nullptr){
            s = currNode->getString();
        }

        currNode = currNode->right;
    }
    return s;
}
string BSTree::smallest() const{
    Node* currNode = root;
    string s = "";
    while(currNode != nullptr){
        if(currNode->left == nullptr){
            s = currNode->getString();
        }

        currNode = currNode->left;
    }

    return s;
}

//print
// void BSTree::visualizeTree(const string &outputFilename){
//     ofstream outFS(outputFilename.c_str());
//     if(!outFS.is_open()){
//         cout<<"Error opening "<< outputFilename<<endl;
//         return;
//     }
//     outFS<<"digraph G {"<<endl;
//     visualizeTree(outFS,root);
//     outFS<<"}";
//     outFS.close();
//     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
//     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//     system(command.c_str());
// }
// void BSTree::visualizeTree(ofstream & out, Node *node){
//     if(node == nullptr){
//         return;
//     }

//     string data = node->getString();
//     int key = node->getCount();

//     if(node->left != nullptr){
//         string leftChildData = node->left->getString();
//         int leftChildKey = node->left->getCount();
//         out << "\"" << data << "\" " << "-> ";
//         out << "\"" << leftChildData << "\";\n";
//     }
//     if(node->right != nullptr){
//         string rightChildData = node->right->getString();
//         int rightChildKey = node->right->getCount();
//         out << "\"" << data << "\" " << "-> ";
//         out << "\"" << rightChildData <<  "\";\n";
//     }
    
//     visualizeTree(out, node->left);
//     visualizeTree(out, node->right);
// }

Node* BSTree::findNode(const string & s)const {
    Node* curr = root;
    while (curr) {
        if (s == curr->getString()) {
            return curr;
        }
        else if (s < curr->getString()) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return nullptr;
}
Node* BSTree::findParent(const string& string) const{
    Node* parent = nullptr;
    Node* curr = root;
    while (curr) {
        if (string == curr->getString()) {
            return parent;
        }
        else if (string < curr->getString()) {
            parent = curr;
            curr = curr->left;
        }
        else {
            parent = curr;
            curr = curr->right;
        }
    }
    return nullptr;
}
void BSTree::preOrder() const{
    preOrder(root);
}
void BSTree::preOrder(const Node *node) const{
    if(node == nullptr){
        return;
    }

    cout << node->getString() << "(" << node->getCount() << "), ";
    preOrder(node->left);
    preOrder(node->right);
}
void BSTree::inOrder() const {
    inOrder(root);
}
void BSTree::inOrder(const Node *node) const{
    if(node == nullptr){
        return;
    }

    inOrder(node->left);
    cout << node->getString() << "(" << node->getCount() << "), ";
    inOrder(node->right);
}
void BSTree::postOrder() const {
    postOrder(root);
}
void BSTree::postOrder(const Node *node) const{
    if(node == nullptr){
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    cout << node->getString() << "(" << node->getCount() << "), ";
}