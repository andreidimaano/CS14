#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

 /*
    identifier
    vector of edges(adj list)
    string action
    bool known
*/
class Vertex {
    public:
        int jugA, jugB, distance;
        string action;
        Vertex* prev = nullptr;
        list<pair<const Vertex*, string>> actionList;
        list<pair<Vertex*, int>> adjlist;
        Vertex(int, int);
        // Vertex(int, int, string, Vertex*);
};


class Jug {
    private:
        int CapacityA, CapacityB, endGoal, costToFillA, costToFillB,
        costToEmptyA, costToEmptyB, costToPourA, costToPourB;
        vector<Vertex*> Vertices;
        queue<Vertex*> unvisitedQueue;
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //helper solve
        bool isValid()const;
        void buildGraph();
        void dijkstra();
        string makeSolution();    

        //helper dijsktra
        Vertex* findEnd() const;
        string findAction(Vertex *, Vertex*) const;


        //helper functions to build Graph
        bool isEndState(Vertex*) const;
        stack<pair<Vertex*, int>> createPossibilities(const Vertex*);
        pair<Vertex*,int> fillA(const Vertex*);
        pair<Vertex*,int> fillB(const Vertex*);
        pair<Vertex*,int> emptyA(const Vertex*);
        pair<Vertex*,int> emptyB(const Vertex*);
        pair<Vertex*,int> pourA(const Vertex*);
        pair<Vertex*,int> pourB(const Vertex*);
        Vertex* findState(const Vertex*) const;
        bool isValidState(const Vertex*) const;
        bool stateExists(const Vertex*) const;

        //debug print
        void printVertices() const;
};

        /*
        print shortest path 
        print vertices
        dijkstra
        findsolution
        */

#endif