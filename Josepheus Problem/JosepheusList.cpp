#include "JosepheusList.h"
#include <iostream>
#include <string>

using namespace std;

Participants::Participants()
{
    head = nullptr;
    tail = nullptr;
}
Person* Participants::getHead() const
{
    return head;
}
Person* Participants:: getTail() const
{
    return tail;
}
void Participants::formCircle(Person* newParticipant)
{
    if(noParticipants())
    {
        head = newParticipant;
        tail = newParticipant;

        tail->prev = head;
        head->next = tail;
        //needed for later access

        resetCircle();
        //sets up circular list

        return;
    }
    //when first participant shows up
    
    tail->next = newParticipant;
    newParticipant->prev = tail;
    //set up newParticpant's next and prev pointers to fit into the back

    tail = newParticipant;
    resetCircle();
    //circular list
}
//need to to delete functions
void Participants::executePerson(Person* personToEliminate)
{
    if(personToEliminate == head)
    {
        pop_front();
        return;
    }
    else if(personToEliminate == tail)
    {
        pop_back();
        return;
    }

    // Person* temp = personToEliminate;
    Person* preceedingPerson = personToEliminate->prev;
    Person* proceedingPerson = personToEliminate->next;

    preceedingPerson->next = proceedingPerson;
    proceedingPerson->prev = preceedingPerson;

    delete personToEliminate;
}

//display 6  functions
void Participants::DisplayRemaining() const
{
    Person* curr = head;
    do
    {
      if(curr->next == head)
        {
            cout << curr->name;
        }
        else
        {
            cout << curr->name << " ";
        }
        curr = curr->next;
    } while (curr != head);    
}
void Participants::DisplayRemainingReverse() const
{
    Person* curr = tail;
    do
    {
      if(curr->prev == tail)
        {
            cout << curr->name;
        }
        else
        {
            cout << curr->name << " ";
        }
        curr = curr->prev;
    } while (curr != tail); 
}

//helper functions
void Participants::pop_front()
{
    Person* temp = head;
    head = head->next;
    delete temp;
    resetCircle();
}
void Participants::pop_back()
{
    Person* temp = tail;
    tail = tail->prev;
    delete temp;
    resetCircle();
}
bool Participants::noParticipants() const
{
    if(head == nullptr)
    {
        return true;
    }
    return false;
}
void Participants::resetCircle()
{
    tail->next = head;
    head->prev = tail;
}