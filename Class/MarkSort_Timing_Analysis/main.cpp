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
int *fillAry(int);
void prntAry(int *,int,int);
void mrkSort(int *,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables and initialize Here
    int size=320000;
    int mod=10;
    int *array=fillAry(size);
    
    //Print the resulting array
    //prntAry(array,size,mod);
    
    //Sort the array
    int beg=time(0);
    mrkSort(array,size);
    int end=time(0);
    cout<<"Size of Array  = "<<size<<endl;
    cout<<"Execution time = "<<end-beg<<" secs"<<endl;
    
    //Output Located Here
    //prntAry(array,size,mod);
    
    //Clean Memory
    delete []array;

    //Exit
    return 0;
}

void mrkSort(int *a,int n){
    int nm1=n-1;
    for(int i=0;i<nm1;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]>a[j]){
                a[i]=a[i]^a[j];
                a[j]=a[i]^a[j];
                a[i]=a[i]^a[j];
            }
        }
    }
}

void prntAry(int *a,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int *fillAry(int n){
    int *array=new int[n];
    for(int i=0;i<n;i++){
        array[i]=rand();
    }
    return array;
}