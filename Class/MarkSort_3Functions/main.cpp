/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 10th, 2018, 9:07 AM
 * Purpose:  Mode Setup
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int *fillAry(int,int);
void prntAry(int *,int,int);
void swap(int &,int &);
void smlLst(int *,int,int);
void mrkSort(int *,int);
void shuffle(int *,int,int);


//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables and initialize Here
    int size=95;
    int mod=10;
    int *array=fillAry(size,mod);
    
    //Print the resulting array
    prntAry(array,size,mod);
    
    //Shuffle the array
    shuffle(array,size,7);
    
    //Print the shuffled array
    prntAry(array,size,mod);
    
    //Sort the array
    mrkSort(array,size);
    
    //Output Located Here
    prntAry(array,size,mod);
    
    //Clean Memory
    delete []array;

    //Exit
    return 0;
}

void shuffle(int *a,int n,int nShuf){
    for(int shuf=1;shuf<=nShuf;shuf++){
        for(int i=0;i<n;i++){
            int temp=rand()%n;
            if(i!=temp)swap(a[i],a[temp]);
        }
    }
}

void mrkSort(int *a,int n){
    for(int i=0;i<n-1;i++){
        smlLst(a,n,i);
    }
}

void smlLst(int *a,int n,int pos){
    for(int i=pos+1;i<n;i++){
        if(a[pos]>a[i])swap(a[pos],a[i]);
    }
}

void swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void prntAry(int *a,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int *fillAry(int n,int m){
    int *array=new int[n];
    for(int i=0;i<n;i++){
        array[i]=i%m;
    }
    return array;
}