#ifndef JOSEPHEUSLIST_H
#define JOSEPHEUSLIST_H

#include <iostream>
#include <string>

using namespace std;

struct Person
{
    string name;
    Person* prev;
    Person* next;
    Person(string nameOfPerson): name(nameOfPerson), prev(0), next(0) {}
};

class Participants
{
    private:
        Person* head;
        Person* tail;
    public:
        Participants();
        void formCircle(Person*);
        void pop_front();
        void pop_back();
        void executePerson(Person*);
        void DisplayRemaining() const;
        void DisplayRemainingReverse() const;
        bool noParticipants() const;
        void resetCircle();
        Person* getHead() const;
        Person* getTail() const;
};

#endif