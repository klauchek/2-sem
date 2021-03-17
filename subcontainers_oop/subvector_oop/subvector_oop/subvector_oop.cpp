#include "subvector.h"


subvector::subvector()
{
    this->mas = nullptr;
    this->capacity = 0;
    this->top = 0;
}

subvector::~subvector()
{
    delete[] this->mas;
    this->mas = nullptr;
}

void subvector::clear()
{
    this->top = 0;
}

void subvector::expand(unsigned int new_cap)
{
    int* new_mas = new int[new_cap];
    for (int i = 0; i < this->top; i++)
        new_mas[i] = (this->mas)[i];

    delete[] this->mas;
    this->mas = new_mas;
}

//добавление элемента в конец недовектора
//с выделением дополнительной памяти при необходимости 
bool subvector::push_back(int d)
{
    if (this->capacity > this->top)
    {
        this->top++;
        this->mas[this->top - 1] = d;
    }
    else
    {
        expand(2 * ((this->capacity) + 1));
        this->capacity = 2 * ((this->capacity) + 1);
        this->top++;
        this->mas[this->top - 1] = d;
    }

    return true;
}

//удаление элемента с конца недовектора

int subvector::pop_back() {

    if (this->top == 0)
        return 0;

    int last = this->mas[(this->top) - 1];

    this->top--;

    return last;
}

//увеличить емкость недовектора

bool subvector::resize(unsigned int new_capacity) {

    int* new_mas = new int[new_capacity];
    for (int i = 0; i < this->top; i++)
    {
        new_mas[i] = (this->mas)[i];
    }

    this->capacity = new_capacity;

    delete[] this->mas;
    this->mas = new_mas;
    return true;
}

//очистить неиспользуемую память

void subvector::shrink_to_fit() {

    if (this->capacity == this->top)
        return;

    if (this->capacity > this->top)
    {
        expand(this->top);
        this->capacity = this->top;
    }

}
//! Reloaded operator [] for vector
int subvector::operator [](int i)
{
    return mas[i];
}

unsigned int subvector::get_cap()
{
    return this->capacity;
}

unsigned int subvector::get_top()
{
    return this->top;
}

