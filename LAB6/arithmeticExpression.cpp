#include "arithmeticExpression.h"
#include <iostream>
#include <stack>
#include <sstream>
#include <fstream>

using namespace std;
arithmeticExpression::arithmeticExpression(const string &infixExpression){
    this->infixExpression = infixExpression;
}

void arithmeticExpression::infix(){
    infix(root);
}

void arithmeticExpression::prefix(){
    prefix(root);
}

void arithmeticExpression::postfix(){
    postfix(root); 
}

 /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree(){
    string postfixExpression = infix_to_postfix();

    stack<TreeNode *> treeNodeStack;
    TreeNode *tempTree1, *tempTree2, *tempTree3;
    char key = 'a';

    for (unsigned i = 0; i < postfixExpression.size(); i++){
        if(priority(postfixExpression.at(i)) == 0){
            tempTree1 = new TreeNode(postfixExpression.at(i), key);
            treeNodeStack.push(tempTree1);
            key++;
        }
        else{
            tempTree1 = new TreeNode(postfixExpression.at(i), key);
            tempTree2 = treeNodeStack.top();
            treeNodeStack.pop();
            tempTree3 = treeNodeStack.top();
            treeNodeStack.pop();

            tempTree1->right = tempTree2;
            tempTree1->left = tempTree3;

            treeNodeStack.push(tempTree1);
        }
    }
    
    root = treeNodeStack.top();
    treeNodeStack.pop();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

//helper
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::infix(TreeNode *node){
    //  int priorityOfNode = priority(node->data);

    //  if(priorityOfNode >= 1 && priorityOfNode < 3){
    //      int priorityOfLeftNode = priority(node->left->data);

    //      if(priorityOfLeftNode == 0){
    //          cout << "(";
    //      } else if(priorityOfLeftNode == 1){
    //          cout << ")";
    //      }
    //  }

     if(node == nullptr){
         return;
     }
    
    if(!(node->left == nullptr || node->right == nullptr)){
        cout << "(";
    }
    infix(node->left);
    cout << node->data;
    infix(node->right);
    if(!(node->left == nullptr || node->right == nullptr)){
        cout << ")";
    }
    
 }

void arithmeticExpression:: prefix(TreeNode *node){
    if(node == nullptr){
        return;
    }

    cout << node->data;
    prefix(node->left);
    prefix(node->right);
}

void arithmeticExpression::postfix(TreeNode *node){
    if(node == nullptr){
        return;
    }

    postfix(node->left);
    postfix(node->right);
    cout << node->data;
}

//TODO: /* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream & out, TreeNode *node){
    if(node == nullptr){
        return;
    }

    char data = node->data;
    char key = node->key;
    // string rootString = "\"data: " + data + " key: " + "\" ";


    // if(node->left != nullptr){
    //     char leftChildData = node->left->data;
    //     char leftChildKey = node->left->key;
    //     out << "\"" << "data: " << data << " key: " << key << "\" " << "-> ";
    //     out << "\"" << "data: " << leftChildData << " key: "<< leftChildKey << "\";\n";
    // }
    // if(node->right != nullptr){
    //     char rightChildData = node->right->data;
    //     char rightChildKey = node->right->key;
    //     out << "\"" << "data: "<< data << " key: "<< key << "\" " << "-> ";
    //     out << "\"" << "data: "<< rightChildData << " key: "<< rightChildKey << "\";\n";
    // }

    if(node->left != nullptr){
        char leftChildData = node->left->data;
        char leftChildKey = node->left->key;
        out << "\"" << data << "\" " << "-> ";
        out << "\"" << leftChildData << "\";\n";
    }
    if(node->right != nullptr){
        char rightChildData = node->right->data;
        char rightChildKey = node->right->key;
        out << "\"" << data << "\" " << "-> ";
        out << "\"" << rightChildData <<  "\";\n";
    }
    
    visualizeTree(out, node->left);
    visualizeTree(out, node->right);
}

