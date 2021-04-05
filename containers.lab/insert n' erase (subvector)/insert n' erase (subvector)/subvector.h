#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__


#include <fstream>
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

    bool insert(int index, int data);

    int pop_back();

    int erase(int index);

    void expand(unsigned int new_cap);

    bool push_back(int data);

    unsigned int get_top();

    unsigned int get_cap();
};


#endif __SUBVECTOR_H__










