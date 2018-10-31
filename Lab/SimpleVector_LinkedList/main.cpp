/* 
 * File:   main.cpp
 * Author: Christopher K Herre
 *
 * Created on September 26, 2018, 12:04 AM
 */

#include <cstdlib>

#include "SimpleVector.h"

using namespace std;

int main(int argc, char** argv)
{
    const short SIZE = 5;
    SimpleVector<short> vect(SIZE);
    vect.push(-99);
    vect.printVect();
    vect.push(-999);
    vect.printVect();
    vect.pop();
    vect.printVect();
    vect.pop();
    vect.pop();
    vect.pop();
    vect.printVect();
   
    cout << "vect.getElementAt(2) "<< vect.getElementAt(2) << endl;
    cout << "vect[2]: " << vect[2] << endl;
    
    cout << "Printing a copy-constructed SimpleVector..." << endl;
    SimpleVector<short> vect2(vect);
    cout << "vect2.size(): " << vect2.size() << endl;
    return 0;
}

