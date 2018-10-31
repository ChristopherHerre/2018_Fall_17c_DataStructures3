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
int Oo,Oi,Oj,POs,tot;

//Function Prototypes Here
int *fillAry(int);
void prntAry(int *,int,int);
void mrkSort(int *,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables and initialize Here
    int size=16000;
    int mod=10;
    int *array=fillAry(size);
    
    //Print the resulting array
    //prntAry(array,size,mod);
    
    //Sort the array
    mrkSort(array,size);
    cout<<"Outer Operations    = "<<Oo<<endl;
    cout<<"i loop Operations   = "<<Oi<<endl;
    cout<<"j loop Operations   = "<<Oj<<endl;
    cout<<"Swap Operations     = "<<POs<<endl;
    tot=Oo+Oi+Oj+POs;
    cout<<"Total Number of ops = "<<tot<<endl;
    
    //Output Located Here
    //prntAry(array,size,mod);
    
    //Clean Memory
    delete []array;

    //Exit
    return 0;
}

void mrkSort(int *a,int n){
    int nm1=n-1;
    Oo+=3;
    for(int i=0;i<nm1;i++){
        Oi+=4;
        for(int j=i+1;j<n;j++){
            Oj+=3;
            if(a[i]>a[j]){
                POs+=6;
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