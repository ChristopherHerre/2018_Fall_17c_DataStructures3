/* 
 * File:   main.cpp
 * Author: mlehr
 * Created on September 10, 2018, 10:19 AM
 * Purpose:  Create an array of Simple Objects
 */

//System Libraries
#include <iostream>//Standard I/O
#include <cstdlib> //Rand
#include <ctime>   //Time
using namespace std;

//User Libraries
#include "SimpleClass.h"

//Global Constants  Physics/Math/Conversions/2D Dimensions

//Function Prototypes
Simple **fillObj(int);
void prntObj(Simple **,int,int);
void destroy(Simple **,int);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Simple Object array
    int size=100;
    
    //Create a dynamic array of simple objects
    Simple **simple=fillObj(size);
    
    //Output the results
    prntObj(simple,size,10);
    
    //Recover Allocated Memory
    destroy(simple,size);
    
    return 0;
}

void destroy(Simple **s,int n){
    for(int i=0;i<n;i++){
        delete s[i];//Destruction of individual objects
    }
    delete []s;//Destruction of the array of pointers of the Objects
}

void prntObj(Simple **s,int n,int perLine){
    cout<<endl<<endl;
    for(int i=0;i<n;i++){
        cout<<s[i]->getIn()<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}



Simple **fillObj(int n){
    Simple **simple=new Simple*[n];
    for(int i=0;i<n;i++){
        simple[i]=new Simple(rand()%90+10);//Randomly Fill with 2 Digit numbers
    }
    return simple;
}