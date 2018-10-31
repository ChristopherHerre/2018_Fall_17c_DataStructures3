/* 
 * File:   main.cpp
 * Author: Christopher K Herre
 *
 * Created on September 26, 2018, 12:04 AM
 */

#include <cstdlib>

#include "SimpleVector.h"

using namespace std;

template <class T>
void printArr(SimpleVector<T>&);

int main(int argc, char** argv) {
    // the initial size of our vector
    short size = 5;
    SimpleVector<short> vect(size);
    vect.setOccSize(size);
    cout << "Original:        ";
    printArr(vect);
    // change this value to the length of vals[]
    const int ARR_SIZE = 16;
    int index = size; // the index of the value we're adding
                      // this avoids having gaps in the array
                      // when memory space is doubled
    int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                    11, 12, 13, 14, 15, 16 };
    for (short i = 0; i < ARR_SIZE; i++) {
        vect.push(vals[i], index);
        cout << "Appended Array:  ";
        printArr(vect);
    }
    cout << endl << "Starting delete..." << endl << endl;
    for (int i = 0; i < 17; i++) {
        vect.pop();
        cout << "Element Deleted: ";
        printArr(vect);
    }
    return 0;
}

template <class T>
void printArr(SimpleVector<T>& vect) {
    for (short i = 0; i < vect.getOccSize(); i++) {
        cout << vect.getElementAt(i) << " ";
    }
    cout << endl;
}

