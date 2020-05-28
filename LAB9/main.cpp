#include <time.h>
#include <iostream>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high);
void fillArrays(int[], int[], int[]);
void Quicksort_midpoint(int [], int, int);
int Partition_midpoint(int [], int, int);
void Quicksort_medianOfThree(int[], int, int);
int Partition_med(int[], int, int);
void InsertionSort(int[], int);

int main() {
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    
    fillArrays(arr1, arr2, arr3);
    clock_t Start = clock();
    //call sort function here
    InsertionSort(arr1, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "insertion sort: " << elapsedTime << endl;


    clock_t Start1 = clock();
    //call sort function here
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End1 = clock();
    elapsedTime = (End1 - Start1)/CLOCKS_PER_MS;
    cout << "Quicksort midpoint: " << elapsedTime << endl;
    


    clock_t Start2 = clock();
    //call sort function here
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    clock_t End2 = clock();
    elapsedTime = (End2 - Start2)/CLOCKS_PER_MS;
    cout << "Quicksort median of three: " << elapsedTime << endl;

}

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void InsertionSort(int arr[], int size){
    int i , j, key;

    for(i = 1; i < size; ++i){
        key = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
    int j;

    //base case: if k is index 0 or negative 1
    if(i >= k){
        return;
    }

    j = Partition_midpoint(numbers, i, k);

    Quicksort_midpoint(numbers, i, j);
    Quicksort_midpoint(numbers, j + 1, k);
}
int Partition_med(int numbers[], int i, int k){
    int l;
    int h;
    int pivot;
    int midpoint;
    int temp;
    bool done;

    midpoint = i + (k - 1) / 2;

    if((numbers[i] > numbers[k] && numbers[i] < numbers[midpoint]) ||
    (numbers[i] > numbers[midpoint] && numbers[i] < numbers[k])){
        pivot = i;
    } else if ((numbers[midpoint] > numbers[i] && numbers[midpoint] < numbers[k]) ||
    (numbers[midpoint] > numbers[k] && numbers[midpoint] < numbers[i])){
        pivot = midpoint;
    } else {
        pivot = k;
    }

    l = i;
    h = k;

    while(done){
        while(numbers[l] < pivot){
            ++l;
        }

        while(pivot < numbers[h]){
            --h;
        }

        if(l >= h){
            done = true;
        } else {
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }
    return h;
}

void Quicksort_midpoint(int numbers[], int i, int k){
    int j;

    //base case: if k is index 0 or negative 1
    if(i >= k){
        return;
    }

    j = Partition_midpoint(numbers, i, k);

    Quicksort_midpoint(numbers, i,j);
    Quicksort_midpoint(numbers, j + 1, k);
}
int Partition_midpoint(int numbers[], int i, int k){
    int l;
    int h;
    int midpoint;
    int pivot;
    int temp;
    bool done = false;

    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    l = i; //lower bound
    h = k; //upper bound

    while(!done){

        while(numbers[l] < pivot){
            ++l;
        }

        while(pivot < numbers[h]){
            --h;
        }

        if(l >= h){
            //zero elements remaining
            done = true;
        } else {
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}