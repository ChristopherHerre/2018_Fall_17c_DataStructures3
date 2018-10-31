/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 19th, 2018, 9:07 PM
 * Purpose:  Mode Setup
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//User Libraries Here
#include "Link.h"


//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
Link *fillLst(int);
void prntLst(Link *,int);
void dstLst(Link *);

Link *endLst(Link *);
void addLnk(Link *&, int);
void delLnk(Link *&);
int  findLnk(Link *, int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables and initialize Here
    Link *lnkList;
    int howMany=100;
    int perLine=10;
    
    //Print the resulting array
    lnkList=fillLst(howMany);
    
    //Print the list
    prntLst(lnkList,perLine);
    cout << "The end of the list has a value of: " << endLst(lnkList)->data
            << endl;
    addLnk(lnkList, 101);
    prntLst(lnkList, perLine);
    delLnk(lnkList);
    prntLst(lnkList, perLine);
    
    int find = findLnk(lnkList, 22);
    cout << find << endl;
    
    //Clean Memory
    dstLst(lnkList);
    
    

    //Exit
    return 0;
}
Link *fillLst(int n){
    Link *front=new Link;
    Link *prev=front;
    prev->data=n--;
    prev->linkPtr=NULL;
    do{
        Link *end=new Link;
        end->data=n--;
        end->linkPtr=NULL;
        prev->linkPtr=end;
        prev=end;
    }while(n>0);
    return front;
}
void prntLst(Link *front,int perLine){
    cout << "Printing list..." << endl;
    int colCnt=0;
    Link *next=front;
    cout<<endl;
    do{
        cout<<setw(4)<<next->data<<" ";
        if(colCnt++%perLine==(perLine-1))
            cout<<endl;
        next=next->linkPtr;
    }while(next!=NULL);
    cout<<endl;
}
void dstLst(Link *front){
    if(front==NULL)return;
    do{
        Link *temp=front->linkPtr;
        delete front;
        front=temp;
    }while(front!=NULL);
}

Link *endLst(Link *head)
{
    Link *curr = head;
    do
    {
        curr = curr->linkPtr;
    } while (curr->linkPtr != NULL);
    return curr;
}
void addLnk(Link *&head, int value)
{
    Link* newHead = new Link;
    newHead->data = value;
    newHead->linkPtr = head;
    head = newHead;
}
void delLnk(Link *&head)
{
    Link* newHead = new Link;
    newHead->data = head->linkPtr->data;
    newHead->linkPtr = head->linkPtr->linkPtr;
    head = newHead;
}
int  findLnk(Link *head, int value)
{
    Link *curr = head;
    do
    {
        curr = curr->linkPtr;
    } while (curr->data != value);
    cout << "I found " << value << " at index ";
    return curr->data;
}