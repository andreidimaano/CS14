#ifndef WORD_LADDER_H
#define WORD_LADDER_H

#include <iostream>
#include <list>
#include <stack>
#include <queue>
using namespace std;

class WordLadder
{
    private:
        list<string> dict;
        int comparisons = 0;
        bool optimization = false;
    public:
        WordLadder(const string &);
        void outputLadder(const string &start, const string &end, const string &outputfile);
        int getComparisons() const;
        void setOptimization(bool);
    private:
        bool wordExists(const string &);
        stack<string> createWordStack(const stack<string> &, const string &);
        void enqueueStack(queue<stack<string>> &, const stack<string> &currentStack);
        void createQueue(queue<stack<string>> &, const string &start, const string &end);
        void outputQueue(const queue<stack<string>> &)const;
        void outputStack(const stack<string> &)const;
        void removeWords(list<string> &dict, stack<string> &removeStack);
};

//you can optimize the solution by checking if a word is one letter off from the targeted word
//this limits the amount of checks because we don't have to keep going through the dictionary again

//you can also stop checking the character comparisons after you have more than 1 character difference
#endif