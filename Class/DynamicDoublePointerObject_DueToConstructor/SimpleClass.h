/* 
 * File:   SimpleClass.h
 * Author: mlehr
 * Created on September 10, 2018, 10:20 AM
 * Purpose:  Simple class to use in Double Pointer dynamic array creation
 * 
 */

#ifndef SIMPLECLASS_H
#define SIMPLECLASS_H

class Simple{
    private:
        int input;
    public:
        Simple(int i){
            input=i;
        }
    int getIn(){return input;}
};


#endif /* SIMPLECLASS_H */

