#ifndef __SUBVECTOR__H__
#define __SUBVECTOR__H__


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <fstream>


class subvector
{
private:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector();

    ~subvector();
    
    int operator [](int i);
 
    void expand(unsigned int new_cap);
  
    bool push_back(int d);

    unsigned int get_top();
};


#endif __SUBVECTOR__H__
