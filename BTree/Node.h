#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class BTree;

private:
  string A = "";
  string B = "";
  string C = "";

  Node *left = nullptr;
  Node *middle1 = nullptr;
  Node *middle2 = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
public:
    Node();
    Node(const string &, Node*, Node *);
    Node(const string&, const string&, const string&);

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif