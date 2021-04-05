#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class subvector
{
private:

    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector();
    ~subvector();

    bool push_back(int d);

    void expand(unsigned int new_cap);

    unsigned int get_cap();

    unsigned int get_top();
};

#endif __SUBVECTOR_H__