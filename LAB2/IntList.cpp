#include "IntList.h"
#include <iostream>

using namespace std;

IntList::IntList()
{
    dummyHead = new IntNode(-1);
    dummyTail = new IntNode(-2);

    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}
IntList::~IntList()
{
    IntNode* curr = dummyHead;
    while(curr != nullptr)
    {
        IntNode* temp = curr;
        curr = curr->next;
        delete temp;
    } 
    //start at the dummy head
    //create a temp of curr then set curr to it's next value
    //delete the temp and continue untill curr == null
}
void IntList::push_front(int value)
{
    IntNode* newNode = new IntNode(value);
    IntNode* temp = dummyHead->next;
    dummyHead->next->prev = newNode;
    //create temp of the front node
    //sets front node prev = newNode

    dummyHead->next = newNode;
    newNode->prev = dummyHead;
    newNode->next = temp;
    //sets first real node to the new one
    //then adjusts the new front node's next and prev nodes
    //also works when list is empty
}
void IntList::pop_front()
{
    if(this->empty())
    {
        return;
    }
    //if the list is empty, do nothing
    
    IntNode* temp = dummyHead->next;
    dummyHead->next = dummyHead->next->next;
    dummyHead->next->prev = dummyHead;
    delete temp;
    //links head's next node to the second real node
    //links new first node prev to dummyHead;
    //deletes the old first node
}
void IntList::push_back(int value)
{
    IntNode* newNode = new IntNode(value);
    newNode->next = dummyTail;
    newNode->prev = dummyTail->prev;
    //instantiate the node, set its prev and next pointers
    //also works when list is empty

    IntNode* temp = dummyTail->prev;
    dummyTail->prev = newNode;
    temp->next = newNode;
    //store the last real node in a variable so we do not lose access
    //set dummytail's prev to the new node
    //set the predecessor last node to the successor real node
}
void IntList::pop_back()
{
    if(this->empty())
    {
        return;
    }
    //if list empty do nothing

    IntNode* temp = dummyTail->prev;
    dummyTail->prev = dummyTail->prev->prev;
    dummyTail->prev->next = dummyTail;
    delete temp;
    //create placeholder for last real node
    // set dummyTail prev to the second to last node
    // set the new last node's next to the dummyTail
    //delete the predecessor last node
}
bool IntList::empty() const
{
    if(dummyHead->next == dummyTail)
    {
        return true;
    }

    return false;
}
ostream & operator <<(ostream & out, const IntList &rhs)
{
    IntNode* curr = rhs.dummyHead->next;
    while(curr != rhs.dummyTail)
    {
        if(curr->next == rhs.dummyTail)
        {
            out << curr->data;
        }
        else
        {
            out << curr->data << " ";
        }
        curr = curr->next;
    }
    
    return out;
}
void IntList::printReverse() const
{
    IntNode* curr = dummyTail->prev;

    while(curr != dummyHead)
    {
        if(curr->prev == dummyHead)
        {
            cout << curr->data;
        }
        else
        {
            cout << curr->data << " ";
        }
        curr = curr->prev;
    }
}