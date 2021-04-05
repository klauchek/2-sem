#include "subvector.h"


subvector:: subvector()
{
    mas = nullptr;
    capacity = 0;
    top = 0;
}

subvector:: ~subvector()
{
    delete[] mas;
    mas = nullptr;
}

bool subvector:: push_back(int d)
{
    if (capacity > top)
    {
        top++;
        mas[top - 1] = d;
    }
    else
    {
        expand(2 * ((capacity)+1));
        capacity = 2 * ((capacity)+1);
        top++;
        mas[top - 1] = d;
    }

    return true;
}

void subvector:: expand(unsigned int new_cap)
{
    int* new_mas = new int[new_cap];
    for (unsigned int i = 0; i < top; i++)
        new_mas[i] = (mas)[i];

    delete[] mas;
    mas = new_mas;
}

unsigned int subvector:: get_cap()
{
    return capacity;
}

unsigned int subvector:: get_top()
{
    return top;
}