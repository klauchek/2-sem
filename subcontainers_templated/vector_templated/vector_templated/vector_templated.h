#ifndef __SUBVECTOR_H__
#define __SUBVECTOR_H__

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

template <typename T>
subvector<T>::subvector()
{
    mas = nullptr;
    capacity = 0;
    top = 0;
}

template <typename T>
subvector<T>::~subvector()
{
    delete[] mas;
    mas = nullptr;
}

template <typename T>
void subvector<T>::clear()
{
    top = 0;
}

template <typename T>
void subvector<T>::expand(size_t new_cap)
{
    T* new_mas = new T[new_cap];
    for (int i = 0; i < top; i++)
        new_mas[i] = mas[i];

    delete[] mas;
    mas = new_mas;
}

//добавление элемента в конец недовектора
//с выделением дополнительной памяти при необходимости 
template <typename T>
bool subvector<T>::push_back(T d)
{
    if (capacity > top)
    {
        top++;
        mas[top - 1] = d;
    }
    else
    {
        expand(2 * ((capacity) + 1));
        capacity = 2 * ((capacity) + 1);
        top++;
        mas[top - 1] = d;
    }

    return true;
}

//удаление элемента с конца недовектора
template <typename T>
T subvector<T>::pop_back() {

    if (top == 0)
        return 0;

    T last = mas[top - 1];

    top--;

    return last;
}

//увеличить емкость недовектора

template <typename T>
bool subvector<T>::resize(size_t new_capacity) {

    T* new_mas = new T[new_capacity];
    for (int i = 0; i < top; i++)
    {
        new_mas[i] = mas[i];
    }

    capacity = new_capacity;

    delete[] mas;
    mas = new_mas;
    return true;
}

//очистить неиспользуемую памят

template <typename T>
void subvector<T>::shrink_to_fit() {

    if (capacity == top)
        return;

    if (capacity > top)
    {
        expand(top);
        capacity = top;
    }

}
//! Reloaded operator [] for vector

template <typename T>
T subvector<T>::operator [](int i)
{
    return mas[i];
}

template <typename T>
size_t subvector<T>::get_cap()
{
    return capacity;
}

template <typename T>
size_t subvector<T>::get_top()
{
    return top;
}


#endif __SUBVECTOR_H__
