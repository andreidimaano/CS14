#include "Node.h"
#include "AVLTree.h"
#include <iostream>
#include <fstream>
using namespace std;


AVLTree::AVLTree(){
    root = nullptr;
}

void AVLTree::insert(const string & s){
    Node* node = new Node(s);
    if(root == nullptr){
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* curr = root;
    while(curr != nullptr){
        if(node->data == curr->data){
            return;
        }
        if(node->data < curr->data){
            if(curr->left == nullptr){
                curr->left = node;
                node->parent = curr;
                curr = nullptr;
                break;
            } else {
                curr = curr->left;
            }
        } else{
            if(curr->right == nullptr){
                curr->right = node;
                node->parent = curr;
                curr = nullptr;
                break;
            } else{
                curr = curr->right;
            }
        }
    }

    node = node->parent;
    while(node != nullptr){
        treeRebalance(node);
        node = node->parent;
    }
}
void AVLTree::treeRebalance(Node* node){
    updateHeight(node);
    if(balanceFactor(node) == -2){
        if(balanceFactor(node->right) == 1){
            //double rotation R-L
            rotateRight(node->right);
        }//RR
        rotateLeft(node);
    } else if(balanceFactor(node) == 2){
        if(balanceFactor(node->left) == -1){
            //double rotation L-R
            rotateLeft(node->left);
        }//LR
        cout << "rotating right" << endl;
        rotateRight(node);
    }
}
void AVLTree::rotateRight(Node* node){
    Node* leftRightChild = node->left->right;
    if(node->parent != nullptr){
        replaceChild(node->parent, node, node->left);
    } else {
        root = node->left;
        root->parent = nullptr;
    }
    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);
}
void AVLTree::rotateLeft(Node* node){
    Node* rightLeftChild = node->right->left;
    if(node->parent != nullptr){
        replaceChild(node->parent, node, node->right);
    } else{
        root = node->right;
        root->parent = nullptr;
    }
    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
}
void AVLTree::updateHeight(Node* node){
    int leftHeight = -1;
    if(node->left){
        // leftHeight = heightRecursion(node->left);
        leftHeight = node->left->height;
    }
    int rightHeight = -1;
    if(node->right != nullptr){
        // cout << "right data: " << node->right->data << endl;
        // rightHeight = heightRecursion(node->right);
        // cout << "right:" << rightHeight << endl;
        rightHeight = node->right->height;
    }
    int maxHeight = leftHeight;
    if(rightHeight > maxHeight){
        maxHeight = rightHeight;
        // cout << maxHeight << endl;
    }
    // cout << "node: " << node->data << endl;
    // // cout << "nodeheight before: " << node->height << endl;
    node->height = maxHeight + 1;
    // cout << "nodeheight after: " << node->height << endl;
}
bool AVLTree::setChild(Node* parent, string whichChild, Node* child){
    if(whichChild != "left" && whichChild != "right"){
        return false;
    }

    if(whichChild == "left"){
        parent->left = child;
    } else {
        parent->right = child;
    }
    if(child != nullptr){
        child->parent = parent;
    }

    updateHeight(parent);
    return true;
}
bool AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild){
    if(parent->left == currentChild){
        return setChild(parent, "left", newChild);
    } else if(parent->right == currentChild){
        return setChild(parent, "right", newChild);
    }

    return false;
}
int AVLTree::balanceFactor(Node *node){
    int leftHeight = -1;
    if(node->left != nullptr){
        leftHeight = node->left->height;
        // leftHeight = heightRecursion(node->left);
        // cout << "left height: " << leftHeight << endl;
    }
    int rightHeight = -1;
    if(node->right != nullptr){
        rightHeight = node->right->height;
        // rightHeight = heightRecursion(node->right);
        // cout << "right height: " << rightHeight << endl;
    }
    return leftHeight - rightHeight;
}


//print
void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
}
void AVLTree::printBalanceFactors(Node* node){
    if(node != nullptr){
        printBalanceFactors(node->left);
        cout << node->data << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->right);
    }
}
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}


// int AVLTree::heightRecursion(Node* node){
//     if(node == nullptr){
//         return 0;
//     } else{  
//         /* compute the depth of each subtree */
//         int lDepth = heightRecursion(node->left);  
//         int rDepth = heightRecursion(node->right);  
//         if (lDepth > rDepth){
//             return(lDepth + 1);  
//         }else {
//             return(rDepth + 1); 
//         }  
//     }  
// }
