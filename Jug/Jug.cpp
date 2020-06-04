#include "Jug.h"
#include <iostream>
#include <string>

using namespace std;


Vertex::Vertex(int A, int B): jugA(A), jugB(B) {}
// Vertex::Vertex(int A, int B, string s, Vertex* v): jugA(A), jugB(B), action(s), prev(v) {}

Jug::Jug(int a,int b,int c,int d,int e,int f,int g, int h, int i){
    CapacityA = a; 
    CapacityB = b;
    endGoal = c; 
    costToFillA = d;
    costToFillB = e;
    costToEmptyA = f; 
    costToEmptyB = g;
    costToPourA = h;
    costToPourB = i;
}
Jug::~Jug(){}

int Jug::solve(string &solution){
    if(!isValid()){
        solution = "";
        return -1;
    }

    buildGraph();
    if(findEnd() == nullptr){
        solution = "";
        return 0;
    }

    dijkstra();
    // printVertices();
    solution = makeSolution();

    return 1;
}
bool Jug::isValid() const{
    if(CapacityA <= CapacityB && (0 < CapacityA && CapacityA <= CapacityB) && (endGoal <= CapacityB && CapacityB <= 1000)){
        return true; 
    }

    return false;
}
string Jug::makeSolution(){
    string finalString = "";
    Vertex* currV = findEnd();
    string distance = to_string(currV->distance);
    string s = "success " + distance;

    stack<string> stackOfStrings;
    stackOfStrings.push(s);
    while(currV->prev){
        stackOfStrings.push(currV->action + "\n");
        currV = currV->prev;
    }
    while(!stackOfStrings.empty()){
        finalString += stackOfStrings.top();
        stackOfStrings.pop();
    }

    return finalString;
}




Vertex* Jug::findEnd() const{
    for(unsigned i = Vertices.size() - 1; i > 0; i--){
        if(Vertices.at(i)->jugA == 0 && Vertices.at(i)->jugB == endGoal){
            return Vertices.at(i);
        }
    }

    return nullptr;
}

void Jug::dijkstra() {
    for(unsigned i = 0; i < Vertices.size(); ++i){
        Vertices.at(i)->distance = 99999;
        Vertices.at(i)->prev = 0;
        unvisitedQueue.push(Vertices.at(i));
    }

    //start has a distance of 0 from itself
    Vertices.at(0)->distance = 0;

    Vertex* currV;
    while(!unvisitedQueue.empty()){
        currV = unvisitedQueue.front();
        unvisitedQueue.pop();

        for(list<pair<Vertex*, int>>::iterator j = currV->adjlist.begin(); j != currV->adjlist.end(); j++){
            int weight = (*j).second;
            int altPathDistance = currV->distance + weight;

            /* if shorter path from startV to adjV is found,
            update adjV distance and predecessor*/

            if(altPathDistance < (*j).first->distance){
                (*j).first->action = findAction(currV, (*j).first);
                (*j).first->distance = altPathDistance;
                (*j).first->prev = currV;
            }
        } 
    }
}

string Jug::findAction(Vertex * parent, Vertex* child)const {
    // if(n == costToFillA){
    //     return "fill A";
    // } else if(n == costToFillB){
    //     return "fill B";
    // } else if(n == costToEmptyA){
    //     return "empty A";
    // } else if(n == costToEmptyB){
    //     return "empty B";
    // } else if(n == costToPourA){
    //     return "pour A B";
    // }
    // return "pour B A";
    string s = "";
    for(list<pair<const Vertex*, string>>::iterator i = child->actionList.begin(); i != child->actionList.end(); ++i){
        if((*i).first == parent){
            s = (*i).second;
            break;
        }
    }

    return s;
}

void Jug::buildGraph(){
    //starting vector
    //vertices hold all of the discovered states
    Vertex* source = new Vertex(0,0);
    Vertices.push_back(source);

    //populate the graph
    for(unsigned i = 0; i < Vertices.size(); ++i){
        Vertex* currV = Vertices.at(i);
        if(!isEndState(currV)){
            /*  populate the graph
                1. create jug state possibiliites in stack (possible solutions are unique and valid states)
                2. update adjacency list of current vector by peeking and popping the stack
            */
           stack<pair<Vertex*, int>> possibleStates = createPossibilities(currV);
           while(!possibleStates.empty()){
               Vertex* v1 = possibleStates.top().first;
               if(!stateExists(v1)){
                   Vertices.push_back(v1);
               }
                currV->adjlist.push_back(possibleStates.top());
                possibleStates.pop();
           }
        }
    }
}

//debug print
void Jug::printVertices() const{
    for(unsigned i = 0; i < Vertices.size(); ++i){
        cout << "i: " << i << endl;
        cout << "Vertex: (" << Vertices.at(i)->jugA << ", " << Vertices.at(i)->jugB << ")" << endl;
        cout << "action: " << Vertices.at(i)->action << endl;
        if(Vertices.at(i)->prev){
             cout << "prev: " << Vertices.at(i)->prev->jugA << " " << Vertices.at(i)->prev->jugB << endl;
        }
        cout << "distance: " << Vertices.at(i)->distance << endl;
        cout << "adjacent Vertices: ";
        for(list<pair<Vertex*, int>>::iterator j = Vertices.at(i)->adjlist.begin(); j != Vertices.at(i)->adjlist.end(); ++j){
            cout << "(" << (*j).first->jugA << ", " << (*j).first->jugB << ") ";
        }
        cout << endl << endl;
    }
}

//helper functions
bool Jug::isEndState(Vertex* v) const{
    if(v->jugA == 0 && v->jugB == this->endGoal){
        return true;
    }
    
    return false;
}
stack<pair<Vertex*, int>> Jug::createPossibilities(const Vertex * v){
    pair<Vertex*, int> p1 = fillA(v);
    pair<Vertex*, int> p2 = fillB(v);
    pair<Vertex*, int> p3 = emptyA(v);
    pair<Vertex*, int> p4 = emptyB(v);
    pair<Vertex*, int> p5 = pourA(v);
    pair<Vertex*, int> p6 = pourB(v);
    stack<pair<Vertex*, int>> s;

    pair<Vertex*, int> arr[6] = {p1, p2, p3, p4, p5, p6};
    for(int i = 0; i < 6; i++){
        if(isValidState(arr[i].first)){
            s.push(arr[i]);
        }
    }

    return s;
}
bool Jug::isValidState(const Vertex* v) const{
    // invalid if not withing the capacity constraints or if the state already exists
    // if(v->jugA > CapacityA || v->jugB > CapacityB || stateExists(v)){
    //     return false;
    // }
    if(v->jugA > CapacityA || v->jugB > CapacityB){
        return false;
    }

    return true;
}
bool Jug::stateExists(const Vertex* v) const{
    //check the jug-state container to see if it exists
    //we know it exists if the state matches up
    for(unsigned i = 0; i < Vertices.size(); i++){
        if(Vertices.at(i)->jugA == v->jugA &&
        Vertices.at(i)->jugB == v->jugB){
            return true;
        }
    }

    return false;
}
Vertex* Jug::findState(const Vertex* v) const{
    for(unsigned i = 0; i < Vertices.size(); i++){
        if(Vertices.at(i)->jugA == v->jugA &&
        Vertices.at(i)->jugB == v->jugB){
            return Vertices.at(i);
        }
    }

    return nullptr;
}
pair<Vertex*,int>Jug::fillA(const Vertex* v){
    // Vertex* v1 = new Vertex(CapacityA, v->jugB,"fillA", v);
    Vertex* v1 = new Vertex(CapacityA, v->jugB);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "fill A");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToFillA);
    return p1;
}
pair<Vertex*,int> Jug::fillB(const Vertex* v){
    // Vertex* v1 = new Vertex(v->jugA, CapacityB, "fillB", v);
    Vertex* v1 = new Vertex(v->jugA, CapacityB);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "fill B");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToFillB);
    return p1;
}
pair<Vertex*,int> Jug::emptyA(const Vertex* v){
    // Vertex* v1 =  new Vertex(0, v->jugB, "emptyA", v);
    Vertex* v1 =  new Vertex(0, v->jugB);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "empty A");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToEmptyA);
    return p1;
}
pair<Vertex*,int> Jug::emptyB(const Vertex* v){
    // Vertex* v1 = new Vertex(v->jugA, 0,"emptyB", v);
    Vertex* v1 = new Vertex(v->jugA, 0);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "empty B");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToEmptyB);
    return p1;
}
pair<Vertex*,int> Jug::pourA(const Vertex* v){
    int newA = v->jugA;
    int newB = v->jugB;

    while(newA != 0 && newB != CapacityB){
        newA--;
        newB++;
    }

    // Vertex* v1 = new Vertex(newA, newB, "pourA", v);
    Vertex* v1 = new Vertex(newA, newB);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "pour A B");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToPourA);
    return p1;
}
pair<Vertex*,int> Jug::pourB(const Vertex* v){
    int newA = v->jugA;
    int newB = v->jugB;

    while(newB != 0 && newA != CapacityA){
        --newB;
        ++newA;
    }

    // Vertex* v1 = new Vertex(newA, newB, "pourB", v);
    Vertex* v1 = new Vertex(newA, newB);

    if(stateExists(v1)){
        Vertex* v2 = findState(v1);
        v1 = v2;
    }

    pair<const Vertex*, string> p(v, "pour B A");
    v1->actionList.push_back(p);

    pair<Vertex*, int> p1(v1, costToPourB);
    return p1;
}