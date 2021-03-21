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

//cleaк the contents
void subvector::clear()
{
    top = 0;
}

//increase capacity
void subvector::expand(unsigned int new_cap)
{
    int* new_mas = new int[new_cap];
    for (int i = 0; i < top; i++)
        new_mas[i] = (mas)[i];

    delete[] mas;
    mas = new_mas;
}

//add element with number a
bool subvector::insert(int a, int d) //a - where, d - data
{
    if (a == top)
    {
        push_back(d);
        return true;
    }
    else
    {
        if (capacity > top)
        {
            top++;
            int* new_mas = new int[top];
            for (int i = 0; i < top; i++)
            {
                if (i < a)
                {
                    new_mas[i] = mas[i];
                }
                else if (i == a)
                {
                    new_mas[i] = d;
                }
                else
                {
                    new_mas[i] = mas[i + 1];
                }
            }
            delete[] mas;
            mas = new_mas;
            return true;
        }
        else
        {
            expand(2 * (capacity + 1));
            capacity = 2 * (capacity + 1);
            top++;
            int* new_mas = new int[top];
            for (int i = 0; i < top; i++)
            {
                if (i < a)
                {
                    new_mas[i] = mas[i];
                }
                else if (i == a)
                {
                    new_mas[i] = d;
                }
                else
                {
                    new_mas[i] = mas[i + 1];
                }
            }
            delete[] mas;
            mas = new_mas;
            return true;
        }
    }
}

//delete element with number a
bool subvector::erase(int a) // a - whete
{
    if (a == top-1)
    {
        return pop_back_();
    }
    else
    {
        top--;
        int* new_mas = new int[top];
        for (int i = 0; i < top; i++)
        {
            if (i < a)
            {
                new_mas[i] = mas[i];
            }
            else
            {
                new_mas[i] = mas[i + 1];
            }
        }
        delete[] mas;
        mas = new_mas;
        return true;
    }
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
        capacity = 2 * ((capacity) + 1);
        top++;
        mas[top - 1] = d;
    }

    return true;
}

//delete element from the end of the subvector

int subvector::pop_back() {

    if (top == 0)
        return 0;

    int last = mas[(top) - 1];

    top--;

    return last;
}

bool subvector::pop_back_()
{

    if (top == 0)
        return false;

    top--;
    return true;

}

//increase top

bool subvector::resize(unsigned int new_capacity) {

    int* new_mas = new int[new_capacity];
    for (int i = 0; i < top; i++)
    {
        new_mas[i] = (mas)[i];
    }

    capacity = new_capacity;

    delete[] mas;
    mas = new_mas;
    return true;
}

//очистить неиспользуемую память

void subvector::shrink_to_fit() {

    if (capacity == top)
        return;

    if (capacity > top)
    {
        expand(top);
        capacity = top;
    }

}
//! Reloaded operator [] for vector
int subvector::operator [](int i)
{
    return mas[i];
}

unsigned int subvector::get_cap()
{
    return capacity;
}

unsigned int subvector::get_top()
{
    return top;
}

