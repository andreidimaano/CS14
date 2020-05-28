#include <iostream>
#include <fstream>
#include <string>
#include "JosepheusList.h"

using namespace std;

bool checkArguments(int argc);
void addParticipants(char* argv, Participants & town, int participantNumber);
string playGame(Participants & Town);

int main(int argc, char* argv [])
{
    Participants Salem;
    int numOfParticipants = 0;

    if(!(checkArguments(argc)))
    {
        return 1;
    }
    
    cout << "Enter number of participants: ";
    cin >> numOfParticipants; cout << endl;

    addParticipants(argv[1], Salem, numOfParticipants);

    cout << playGame(Salem);
    
    return 0;
}

bool checkArguments(int argc)
{
    if (argc != 2)
    {
        cout << "Usage: .exe .txt" << endl;
        return false;    
    }

    return true;
}
void addParticipants(char* filename, Participants & Town, int participantNumber)
{
    ifstream fin;
    string name;
    int counter = 1;

    fin.open(filename);
    
    if(!fin.is_open())
    {
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    while(getline(fin, name) && counter <= participantNumber)
    {
        Person* newParticipant = new Person(name);
        Town.formCircle(newParticipant);
        // Town.DisplayRemaining(); cout << endl;
        // Town.DisplayRemainingReverse(); cout << endl;
        counter ++;
    }
    fin.close();
}
string playGame(Participants & Town)
{
    int startingPerson = 1;
    int skipAmount = 0;
    string direction = "clockwise";
    Person* currPosition = Town.getHead();

    cout << "Enter the starting position: ";
    cin >> startingPerson; cout << endl;

    cout << "Enter the skip amount: ";
    cin >> skipAmount; cout << endl;
    
    cout << "Enter direction(clockwise or counter-clockwise): ";
    cin >> direction;
    
    int counter = 1;
    while(counter != startingPerson)
    {
        currPosition = currPosition->next;
        counter++;
    }
    //set to starting position

    while(Town.getHead() != Town.getTail())
    {
        Person* temp = currPosition;

        if(direction == "counter-clockwise")
        {
            currPosition = currPosition->prev;
        }
        else
        {
            currPosition = currPosition->next;
        }
        
        Town.executePerson(temp);

        for(int i = 0; i < (skipAmount-1); i++)
        {
            if(direction == "counter-clockwise")
            {
                currPosition = currPosition->prev;
            }
            else
            {
                currPosition = currPosition->next;
            }
        }
        cout << "Remaining villagers: "; 
        Town.DisplayRemaining(); cout << endl;
    }

    string survivor = Town.getHead()->name;

    return "Survivor: " + survivor;
}
