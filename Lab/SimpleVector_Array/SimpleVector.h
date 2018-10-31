// SimpleVector class template
#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>   // Needed for the exit function
using namespace std;

#include "Link.h"

template <class T>
class SimpleVector
{
private:
   T *aptr;          // To point to the allocated array
   int arraySize;    // Number of elements in the array
   int maxArraySize;
   int occSize;
   void memError();  // Handles memory allocation errors
   void subError();  // Handles subscripts out of range

public:
   // Default constructor
   SimpleVector()
      { aptr = 0; arraySize = 0;}
      
   // Constructor declaration
   SimpleVector(int);
   
   // Copy constructor declaration
   SimpleVector(const SimpleVector &);
   
   // Destructor declaration
   ~SimpleVector();
   
   // Accessor to return the array size
   int size() const
      { return arraySize; }

   // Accessor to return a specific element
   T getElementAt(int position);

   // Overloaded [] operator declaration
   T &operator[](const int &);
   
   void push(T value, int& index);
   void pop();
   
   void setOccSize(int size) {
       this->occSize = size;
   }
   
   int getOccSize() {
       return this->occSize;
   }
};

//***********************************************************
// Constructor for SimpleVector class. Sets the size of the *
// array and allocates memory for it.                       *
//***********************************************************

template <class T>
SimpleVector<T>::SimpleVector(int s)
{
   arraySize = s;
   maxArraySize = s;
   occSize = s;
   // Allocate memory for the array.
   try {
      aptr = new T [s];
   } catch (bad_alloc) {
      memError();
   }

   // Initialize the array.
   for (int count = 0; count < arraySize; count++)
      *(aptr + count) = 0;
}

//*******************************************
// Copy Constructor for SimpleVector class. *
//*******************************************

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
   // Copy the array size.
   arraySize = obj.arraySize;
   
   // Allocate memory for the array.
   aptr = new T [arraySize];
   if (aptr == 0)
      memError();
      
   // Copy the elements of obj's array.
   for(int count = 0; count < arraySize; count++)
      *(aptr + count) = *(obj.aptr + count);
}

//**************************************
// Destructor for SimpleVector class.  *
//**************************************

template <class T>
SimpleVector<T>::~SimpleVector()
{
   if (arraySize > 0)
      delete [] aptr;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVector<T>::memError()
{
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVector<T>::subError()
{
   cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}

//*******************************************************
// getElementAt function. The argument is a subscript.  *
// This function returns the value stored at the sub-   *
// cript in the array.                                  *
//*******************************************************

template <class T>
T SimpleVector<T>::getElementAt(int sub)
{
   if (sub < 0 || sub >= arraySize)
      subError();
   return aptr[sub];
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************

template <class T>
T &SimpleVector<T>::operator[](const int &sub)
{
   if (sub < 0 || sub >= arraySize)
      subError();
   return aptr[sub];
}

template <class T>
void SimpleVector<T>::push(T value, int& index) {
    try {
        
        cout << "occSize: " << occSize << " maxArraySize: "
                << maxArraySize << endl;
        if (occSize == maxArraySize) {
            int old_size = occSize;
            int new_size = old_size;
            arraySize*=2;
            new_size = arraySize;
            maxArraySize*=2;
            T *newArr = new T[new_size];
            cout << "DOUBLING SIZE OF ARRAY FROM " << old_size << " TO "
                    << new_size << endl;
            
            for (int i = 0; i < maxArraySize; i++) {
                newArr[i] = aptr[i];
            }
            cout << endl;
            delete[] aptr;
            aptr = newArr;
            aptr[index++] = value;
            occSize++;
        } else {
            aptr[index++] = value;
            occSize++;
            //cout << "arraySize: " << arraySize << endl;
        }
    }
    catch (bad_alloc) {
        memError();
    }
}

template <class T>
void SimpleVector<T>::pop()
{
    if (occSize <= 0) {
        cout << "Skipping pop() because occSize <= 0..." << endl;
        return;
    }
    occSize--;
    cout << "occSize: " << occSize << " arraySize: " << arraySize << endl;
    try {
        int new_size = arraySize;
        if (occSize <= 0.25*arraySize) {
            new_size = occSize;
            cout << "FREEING ARRAYSIZE MEMORY FROM " << arraySize << " TO "
                    << new_size << "..." << endl << endl;
            arraySize = new_size;
        } else {
            new_size = arraySize-1;
        }
        
        T *newArr = new T[new_size];
        for (int i = 0; i < new_size; i++) {
            newArr[i] = aptr[i];
        }
        delete[] aptr;
        aptr = newArr;
    } catch (bad_alloc) {
        memError();
    }
}
#endif