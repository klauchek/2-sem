#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__

#include <iostream>
#include <random>
#include <chrono>
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

    void clear();

    void expand(unsigned int new_cap);

    bool push_back(int d);

    int pop_back();

    bool resize(unsigned int new_capacity);

    void shrink_to_fit();

    bool insert(int a, int d);

    bool erase(int a);

    bool pop_back_();

    //! Reloaded operator [] for vector
    int operator [](int i);

    unsigned int get_cap();

    unsigned int get_top();

};



#endif __SUBVECTOR_H__