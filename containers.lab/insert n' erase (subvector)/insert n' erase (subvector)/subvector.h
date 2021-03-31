#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

const int epsilon = 3;

class subvector
{
private:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector();

    ~subvector();

    void insert(int data, int index);

    bool pop_back_();

    void erase(int index);

    void expand(unsigned int new_cap);

    bool push_back(int d);

    unsigned int get_top();
};


#endif __SUBVECTOR_H__










