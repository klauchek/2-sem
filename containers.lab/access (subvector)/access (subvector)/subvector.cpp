#include "subvector.h"

//create empty subvector
subvector::subvector()
{
    mas = nullptr;
    capacity = 0;
    top = 0;
}

//destructor
subvector::~subvector()
{
    delete[] mas;
    mas = nullptr;
}

//! Reloaded operator [] for vector
int subvector:: operator [](int i)
{
    return mas[i];
}

void subvector::expand(unsigned int new_cap)
{
    int* new_mas = new int[new_cap];
    for (int i = 0; i < top; i++)
        new_mas[i] = (mas)[i];

    delete[] mas;
    mas = new_mas;
}

//add element to the end of the subvector
bool subvector::push_back(int d)
{
    if (capacity > top)
    {
        top++;
        mas[top - 1] = d;
    }
    else
    {
        expand(2 * (capacity + 1));
        capacity = 2 * ((capacity)+1);
        top++;
        mas[top - 1] = d;
    }

    return true;
}

unsigned int subvector::get_top()
{
    return top;
}