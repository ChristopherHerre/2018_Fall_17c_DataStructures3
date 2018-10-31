/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 19th, 2018, 9:07 PM
 * Purpose:  Mode Setup
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

#include "Link.h"

int  findLnk(Link *,int);
Link *findLnk2(Link *,int);
void findSwap(Link *,int,int);
Link *fillLst(int);
void dstLst(Link *);
void prntLst(Link *,int);
void prntLstRev(Link*,int);
Link *endLst(Link *);
// these functions add in sorted order
// an element after what comes before
// it numerically, therefore maintaining
// a sorted linkedlist.
void srtAddLst(Link *,int,int);
void srtAddEnd(Link *,int);
void srtAddFrnt(Link *,int);
void srtAddAfter(Link *,int);

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    Link *lnkList;
    int howMany=100;
    int perLine=10;
    lnkList=fillLst(howMany);
    cout << "Original: " << endl;
    prntLst(lnkList,perLine);
    const short ARR_SIZE = 12;
    // add an unordered array to the linkedlist and sort
    short toAdd[] = { -91, 900, -92, -93, 55, 27, 2, 3, 77, 43, 36, -888 };
    for (short i = 0; i < ARR_SIZE; i++)
        srtAddLst(lnkList, toAdd[i], toAdd[i]);
    cout << "All linkedlist elements will be sorted except the head..." << endl;
    prntLst(lnkList,perLine);
    prntLstRev(lnkList, perLine);
    for (short i = 0; i < ARR_SIZE; i++)
        findSwap(lnkList, perLine, toAdd[i]);
    //prntLstRev(lnkList, perLine);
    dstLst(lnkList);
    return 0;
}

void prntLstRev(Link* lnkList, int perLine) {
    Link *curr = endLst(lnkList);
    short colCnt = 0;
    cout << endl << "Printing doubly-linkedlist in reverse..." << endl;
    cout << setw(5) << curr->data;
    do {
        if(colCnt++%perLine==(perLine-1))
            cout<<endl;
        cout << setw(5) << curr->prev->data;
        curr = curr->prev;
    } while (curr->prev != NULL);
}

void findSwap(Link* head, int perLine, int value) {
    int index = findLnk(head, value);
    cout << "I found " << value << " at index " << index << "." << endl;
    prntLst(head,perLine);
    cout << "Attempting swap of " << value << " after element "
            << head->next->data << "..." << endl;
    if (index > 0) {
        Link* found = findLnk2(head, value);
        Link* found_nxt = found->next;
        Link* curr = head;
        found->next = head->next;
        head->next = found;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
            if (i == index-1) {
                
                curr->next = NULL;
            }
        }
        curr->next = found_nxt;
        prntLst(head,perLine);
    } else {
        cout << value << " not in list! Nothing to do..." << endl;
    }
}

Link *fillLst(int n){
    Link *front=new Link;
    front->prev = NULL;
    Link *prev=front;
    prev->data=n--;
    prev->next=NULL;
    prev->prev = front;
    do{
        Link *end=new Link;
        end->data=n--;
        end->next=NULL;
        prev->next=end;
        end->prev = prev;
        prev=end; 
    }while(n>0);
    return front;
}

void prntLst(Link *front,int perLine){
    int colCnt=0;
    Link *next=front;
    do{
        cout<<setw(4)<<next->data<<" ";
        if(colCnt++%perLine==(perLine-1))cout<<endl;
        next=next->next;
    }while(next!=NULL);
    cout<<endl;
}

void dstLst(Link *front){
    if(front==NULL)return;
    do{
        Link *temp=front->next;
        delete front;
        front=temp;
    }while(front!=NULL);
}

Link *endLst(Link *front){
    Link *temp=front,*next;
    do{
        next=temp;
        temp=temp->next;
    }while(temp!=NULL);
    return next;
}

int findLnk(Link *head, int value)
{
    cout << endl;
    Link* curr = head;
    short index = 0;
    do {
        index++;
        curr = curr->next;
        if (curr == NULL) return -1;
    } while (curr->data != value);
    return index;
}

Link* findLnk2(Link *head, int value)
{
    cout << endl;
    Link* curr = head;
    short index = 0;
    do {
        index++;
        curr = curr->next;
        if (curr == NULL) return NULL;
    } while (curr->data != value);
    return curr;
}

void srtAddLst(Link *front, int data, int weight) {
    // all elements are sorted g to l but the head link
    if (front->next->data <= data && weight == data) {
        cout << "input " << data << " is greater than front of list..." << endl;
        srtAddFrnt(front, data);
        return;
    } else if (endLst(front)->data >= data && weight == data) {
        cout << "input " << data << " is less than the end of list..." << endl;
        srtAddEnd(front, data);
        return;  
    } else {
        Link* toAddAfter = front;
        do {
            toAddAfter = toAddAfter->next;
        } while (toAddAfter->data != weight);
        if (toAddAfter->next == NULL) {
            cout << "addLst: You can't add to the end with this function!"
                    << endl;
            cout << "Calling addEnd..." << endl;
            srtAddEnd(front, data);
            return;
        }
        srtAddAfter(toAddAfter, data);
    }
}

void srtAddAfter(Link* toAddAfter, int data) {
    Link *add=new Link;
    add->data=data;
    add->next=toAddAfter->next;
    add->prev = toAddAfter->prev;
    cout << "input " << data << " being inserted next to "
            << toAddAfter->prev->data << "..." << endl;
    toAddAfter->next=add;
    toAddAfter->prev = add;
}

void srtAddEnd(Link *front,int data){
    Link *last=endLst(front);
    Link *add=new Link;
    add->data=data;
    add->next=NULL;
    add->prev = last;
    last->next=add;
}

void srtAddFrnt(Link *head,int data){
    Link *add = new Link;
    add->data = data;
    add->next = head->next;
    head->prev = NULL;
    head->next->prev = add;
    head->next->prev->prev = head;
    head->next = add;
}