#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

WordLadder::WordLadder(const string &filename)
{
    ifstream fin(filename);
    try
    {
        if(!fin.is_open())
        {
            throw runtime_error("Could not open file");
        }
        string word;
        while(fin >> word)
        {
            try
            {
                if(word.length() != 5)
                {
                    throw logic_error("Word does not contain 5 letters");
                }
                dict.push_back(word);
            }
            catch(logic_error& excpt)
            {
                cout << excpt.what() << endl; 
            }
        }
    }
    catch(runtime_error& excpt)
    {
        cout << excpt.what() << endl;
    }
    fin.close();
}
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    ofstream fout(outputFile);
    queue<stack<string>> queueOfStacks;
    // stack<string> baseStack;

    //2.
    //If either word passed in does not exist in the dictionary (dict),
    //this function should output an error message and return.
    //Otherwise, this function outputs to the file the word
    if(!(wordExists(start) && wordExists(end)))
    {
        throw runtime_error("Word(s) does/do not exist in dictionary");
    }

    //create queue
    createQueue(queueOfStacks, start, end);
    // enqueueStack(queueOfStacks, createWordStack(baseStack,start));

    //1.
    //Outputs to this file a word ladder that starts from the first word passed in
    // and ends with the second word passed in.
    //or outputs
    // to the file, the message, "No Word Ladder Found."
    
    if(queueOfStacks.back().top() != end)
    {
        fout << "No Word Ladder Found.";
        return;
    }
    else
    {
        stack<string> finalStack;
        while(!queueOfStacks.back().empty())
        {
            finalStack.push(queueOfStacks.back().top());
            queueOfStacks.back().pop();
        }

        string currentWord;
        while(!finalStack.empty())
        {
            currentWord = finalStack.top();
            fout << currentWord;
            if(finalStack.size() != 1)
            {
                fout << " ";
            }
            finalStack.pop();
        }
    }
    
    fout.close();
}

//helper functions
void WordLadder::createQueue(queue<stack<string>> &queueofStacks, const string &start, const string &end)
{
    stack<string> baseStack;
    stack<string> removeStack;
    string currentWord;
    string pendingWord;

    //1.
    //create the first stack
    //take away first word
    enqueueStack(queueofStacks, createWordStack(baseStack, start));
    removeStack.push(start);
    removeWords(dict, removeStack);

    //2.
    //populate the queue
    while(!(queueofStacks.empty()))
    {
        //1.
        //find words that are one letter off the top of the current stack
        //then create new stack and enqueue
        currentWord = queueofStacks.front().top();
        for(std::list<string>::iterator it = dict.begin(); it != dict.end(); it++)
        {
            this->comparisons++;
            int characterDifferences = 0;
            int endCharacterDifferences = 0;
            pendingWord = *it;

            //1.check character differences from current word
            //O(1) runtime because iterating range is constant 0 - 5
            for(unsigned i = 0; i < 5; i++)
            {
                this->comparisons++;
                if(pendingWord.at(i) != currentWord.at(i))
                {
                    characterDifferences++;
                }
                if(optimization)
                {
                    if(characterDifferences > 1)
                    {
                        break;
                    }
                    
                    if(endCharacterDifferences < 2)
                    {
                        this->comparisons++;
                        if(pendingWord.at(i) != end.at(i))
                        {
                            endCharacterDifferences++;
                        }
                    }
                }
            }

            //2. enqueue all the neighbor words
            if(characterDifferences == 1)
            {
                stack<string> pendingStack = createWordStack(queueofStacks.front(), pendingWord);
                enqueueStack(queueofStacks, pendingStack);
                
                //optimize
                if(optimization)
                {
                    if(endCharacterDifferences == 1)
                    {
                        stack<string> lastStack = createWordStack(queueofStacks.back(), end);
                        enqueueStack(queueofStacks, lastStack);
                        return;
                    }
                }
                
                //enqueue word to delete
                removeStack.push(pendingWord);
            }
        }

        //2.
        //dequeue the front stack
        //remove word from list
        queueofStacks.pop();
        removeWords(dict, removeStack);
    }
}
void WordLadder::setOptimization(bool b)
{
    this->optimization = b;
}
int WordLadder::getComparisons() const
{
    return this->comparisons;
}
bool WordLadder::wordExists(const string &targetWord)
{
    for(auto it = dict.begin(); it != dict.end(); ++it)
    {
        if(*it == targetWord)
        {
            return true;
        }
    }

    return false;
}
stack<string> WordLadder::createWordStack(const stack<string> &baseStack, const string &wordToAdd)
{
    stack<string> newStack = baseStack;
    newStack.push(wordToAdd);

    return newStack;
}
void WordLadder::enqueueStack(queue<stack<string>> &queueOfStacks, const stack<string> &currentStack)
{
    queueOfStacks.push(currentStack);
}
void WordLadder::removeWords(list<string> &dict, stack<string> &removeStack)
{
    string wordToRemove;
    while(!removeStack.empty())
    {
        wordToRemove = removeStack.top();
        dict.remove(wordToRemove);
        removeStack.pop();
    }
}

//debugging purposes
void WordLadder::outputQueue(const queue<stack<string>> &queueOfStacks) const
{
    queue<stack<string>> temp = queueOfStacks;
    int counter = 1;
    while(!temp.empty())
    {
        stack<string> tempstack = temp.front();
        cout << "tempstack " << counter << ": ";
        while(!tempstack.empty())
        {
            cout<< tempstack.top() << " ";
            tempstack.pop();
        }
        temp.pop();
        cout << endl;
        counter++;
    }
}
void WordLadder::outputStack(const stack<string> & stacked) const
{
    stack<string> temp = stacked;
    cout << "stack: "; 
    while(!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}