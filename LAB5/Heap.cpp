#include "Heap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Heap::Heap()
{
    numItems = 0;
}

void Heap::enqueue(PrintJob* newPrintJob)
{
    try
    {
        if(numItems == MAX_HEAP_SIZE)
        {
            throw runtime_error("Queue has reached maximum capacity");
        }
    
        arr[numItems] = newPrintJob;
        trickleUp(numItems);
        numItems++;
    }
    catch(runtime_error& excpt)
    {
        cout << excpt.what() << endl;
    }
}
void Heap::trickleUp(int childPosition)
{
    if(childPosition == 0)
    {
        return;
    }

    int parentPosition = (childPosition - 1) / 2;

    if(arr[childPosition]->getPriority() > arr[parentPosition]->getPriority())
    {
        swap(childPosition, parentPosition);
        trickleUp(parentPosition);
    }

    return;
}
void Heap::dequeue()
{
    try
    {
        if(numItems == 0)
        {
            throw runtime_error("Nothing to dequeue");
        }

        swap(0, numItems - 1);
        numItems--;
        trickleDown(0);
    }
    catch(runtime_error& excpt)
    {
        cout << excpt.what();
    }
}

void Heap::trickleDown(int parentPosition)
{
    int leftChild = 2 * parentPosition + 1;
    int rightChild = 2 * parentPosition + 2;
    int largest = parentPosition;
    
    if(leftChild >= numItems || rightChild >= numItems)
    {
        return;
    }

    if(leftChild < numItems && arr[leftChild]->getPriority() > arr[parentPosition]->getPriority())
    {
        largest = leftChild;
    }
    if(rightChild < numItems && arr[rightChild]->getPriority() > arr[leftChild]->getPriority())
    {
        largest = rightChild;
    }
    if(largest != parentPosition)
    {
        swap(parentPosition, largest);
        trickleDown(largest);
    }
}
PrintJob* Heap::highest()
{
    return arr[0];
}

void Heap::print()
{
    cout << "Priority: " << arr[0]->getPriority() 
    << ", Job Number: " << arr[0]->getJobNumber() 
    << ", Number of Pages: " << arr[0]->getPages() << endl; 

   //debug
//    for(int i = 0; i < numItems; i++)
//    {
//        cout << "Priority: " << arr[i]->getPriority() 
//     << ", Job Number: " << arr[i]->getJobNumber() 
//     << ", Number of Pages: " << arr[i]->getPages()
//    << endl; 
//    }

}
void Heap::swap(int a, int b)
{  
    PrintJob* temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}


