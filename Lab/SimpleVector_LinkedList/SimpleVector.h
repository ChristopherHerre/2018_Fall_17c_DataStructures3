// SimpleVector class template
#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>

#include "Link.h"   // Needed for the exit function
using namespace std;

template <class T>
class SimpleVector
{
private:
   Link<T>* head;
   void memError();  // Handles memory allocation errors
   void subError();  // Handles subscripts out of range

public:
   // Default constructor
   SimpleVector()
   {
       
   }
      
   // Constructor declaration
   SimpleVector(int);
   
   // Copy constructor declaration
   SimpleVector(const SimpleVector &);
   
   // Destructor declaration
   ~SimpleVector();
   
   // Accessor to return the array size
   int size() const;

   // Accessor to return a specific element
   T getElementAt(int position);

   // Overloaded [] operator declaration
   T &operator[](const int &);
   
   void push(T value);
   void pop();
   
   Link<T>* fillLst(int n);
   void printVect();
};

//***********************************************************
// Constructor for SimpleVector class. Sets the size of the *
// array and allocates memory for it.                       *
//***********************************************************
template <class T>
SimpleVector<T>::SimpleVector(int s)
{
    head = fillLst(s);
    this->printVect();
}

//*******************************************
// Copy Constructor for SimpleVector class. *
//*******************************************

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
    head = obj.head;
    this->printVect();
}

//**************************************
// Destructor for SimpleVector class.  *
//**************************************

template <class T>
SimpleVector<T>::~SimpleVector()
{
    if(head==NULL)return;
    do{
        Link<T> *temp=head->next;
        delete head;
        head=temp;
    }while(head!=NULL);
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
    Link<T>* curr = this->head;
    for (int i = 0; i < sub; i++) {
        curr = curr->next;
    }
    return curr->data;
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************

template <class T>
T &SimpleVector<T>::operator[](const int &sub)
{
    Link<T>* curr = this->head;
    for (int i = 0; i < sub; i++) {
        curr = curr->next;
    }
    return curr->data;
}

template <class T>
void SimpleVector<T>::push(T value)
{
    Link<T>* curr = this->head;
    Link<T>* add = new Link<T>;
    do {
        curr = curr->next;
    } while (curr->next != NULL);
    add->data = value;
    add->next = NULL;
    curr->next = add;
    cout << "curr->next val is : " << curr->next->data << endl;
}

template <class T>
void SimpleVector<T>::pop()
{
    cout << "Popping back of linkedlist..." << endl;
    Link<T>* curr = this->head;
    do {
        curr = curr->next;
    } while (curr->next->next != NULL);
    curr->next = NULL;
    delete curr->next;
}

template <class T>
Link<T>* SimpleVector<T>::fillLst(int n){
    //Think of this part as the constructor
    Link<T> *front=new Link<T>;//Allocate a link at the front of the list
    front->data=n;       //Initialize with data
    front->next=NULL; //At the moment not pointing it to anything
    Link<T> *next=front;    //Create a pointer to progress through the list

    //Fill the rest of the list with decreasing data down to 1
    n--;
    do{
       Link<T> *temp=new Link<T>; //Allocate a new link
       temp->data=n;        //Fill with data
       temp->next=NULL;  //Place at the end
       next->next=temp;  //Hook the new link to the end of the list
       next=temp;           //Move the pointer to the end
    }while(--n>0);          //Continue till you count down to Zero
    //Exit by return the original link pointer
    return front;           //Return the front pointer to the list
}

template <class T>
void SimpleVector<T>::printVect() {
    Link<T>* curr = this->head;
    do {
        cout << curr->data << endl;
        curr = curr->next;
        
    } while (curr != NULL);
}

template <class T>
int SimpleVector<T>::size() const
{
    Link<T>* curr = head;
    int index = 0;
    do
    {
        curr = curr->next;
        index++;
    } while (curr != NULL);
    return index;
}
#endif