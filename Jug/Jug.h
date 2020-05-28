#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <list>

using namespace std;

struct Vertex {
    int currentAmount;
    int distance;
    Vertex* predV;
    list<Edge> adjlist;
    Vertex(int);
};

struct Edge {
    int cost;
    Vertex* destination;
    Edge(int);
};
class Jug {
    private:
        int CapacityA, CapacityB, endGoal, costToFillA,
        costToFillB, costToEmptyA, costToEmptyB, 
        costToPourA, costToPourB;
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        
        //anything else you need
};

#endif JUG_H