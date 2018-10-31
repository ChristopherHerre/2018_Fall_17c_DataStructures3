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
void fillObj(Simple *,int);
void prntObj(Simple *,int,int);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Simple Object array
    const int SIZE=100;
    Simple simple[SIZE];
    
    //Create a dynamic array of simple objects
    fillObj(simple,SIZE);
    
    //Output the results
    prntObj(simple,SIZE,10);
    
    return 0;
}

void prntObj(Simple *s,int n,int perLine){
    cout<<endl<<endl;
    for(int i=0;i<n;i++){
        cout<<s[i].getIn()<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}



void fillObj(Simple *simple,int n){
    for(int i=0;i<n;i++){
        simple[i].setIn(rand()%90+10);//Randomly Fill with 2 Digit numbers
    }
}