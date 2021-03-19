#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__

#include <iostream>
#include <random>
#include <chrono>

template <typename T>
class subvector
{
private:
    T* mas;
    size_t top;
    size_t capacity;

public:

    subvector();

    ~subvector();

    void clear();

    void expand(size_t new_cap);

    bool push_back(T d);

    T pop_back();

    bool resize(size_t new_capacity);

    void shrink_to_fit();       

    //! Reloaded operator [] for vector
    T operator [](int i);

    size_t get_cap();

    size_t get_top();

};



#endif __SUBVECTOR_H__
