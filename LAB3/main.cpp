#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>

using namespace std;


//Part A
// template<typename T>
// void populateVector(vector<T> &vals, string filename)
// {
//     ifstream fin(filename);
//     T item;

//     while(getline(fin, item))
//     {
//         vals.push_back(item);
//     }

//     fin.close();
// }

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{
    unsigned minIndex = index;
    //minIndex assigned to index passed in

    for(unsigned i = minIndex + 1; i < vals.size(); ++i)
    {
        if(vals.at(i) < vals.at(minIndex))
        {
            minIndex = i;
        }
    }

    return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals)
{
    unsigned swapIndex;
    for(unsigned i = 0; i < vals.size(); i++)
    {
        swapIndex = min_index(vals, i);
        swap(vals.at(i), vals.at(swapIndex));
    }
}


//PART B
vector<char> createVector()
{
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
T getElement(vector<T> vals, int index)
{
    T value;
    try
    { 
        value = vals.at(index);
    }
    catch(const out_of_range& excpt)
    {
        cerr << "Out of Range error: " << excpt.what() << endl;
    }
    return value;
}
int main()
{
    srand(20);
    // string intFilename = argv[1];
    // string doubleFilename = argv[2];
    // string stringFilename = argv[3];
    // vector<int> intVector;
    // vector<double> doubleVector;
    // vector<string> stringVector;
    vector<char> charVector;

    // populateVector(intVector, intFilename);
    // populateVector(doubleVector, doubleFilename);
    // populateVector(stringVector, stringFilename);
    charVector = createVector();
    char currChar;

    int index;
    do
    {
        cout << "Enter an index: "; cin >> index; cout << endl;
        currChar = getElement(charVector, index);
        cout << "Element located at " << index << " is: " << currChar << endl;
    }
    while(index != -1);
    return 0;
}
