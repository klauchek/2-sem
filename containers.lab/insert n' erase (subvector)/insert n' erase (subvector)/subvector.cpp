#include "subvector.h"

//create empty subvector
subvector::subvector()
{
    mas = new int[top];
    capacity = 0;
    top = 0;
}

//destructor
subvector::~subvector()
{
    delete[] mas;
    mas = nullptr;
}

//increase capacity
void subvector::expand(unsigned int new_cap)
{
    int* new_mas = new int[new_cap];
   /* std::cout << "new cap is: " << new_cap << std::endl;*/
    for (int i = 0; i < top; i++)
        new_mas[i] = mas[i];

    delete[] mas;
    mas = new_mas;
}

//delete element from the end of the subvector

int subvector::pop_back() {

    if (top == 0)
        return 0;

    int last = mas[(top)-1];

    top--;

    return last;
}

//add element to the end of the subvector
bool subvector::push_back(int data)
{
    if (capacity > top)
    {
        top++;
        mas[top - 1] = data;
    }
    else
    {
        expand(2 * (capacity + 1));
        capacity = 2 * ((capacity)+1);
        top++;
        mas[top - 1] = data;
    }

    return true;
}


//for (int i = 0; i < (top - index - 1); i++)
//{
//    mas[index + i] = mas[index + i + 1];
//}
//
//top--;

//add element with number index
bool subvector::insert(int index, int data) //index - where
{
    if (index == top)
    {
        push_back(data);
        return true;
    }
    else
    {
        if (capacity > top)
        {
            //top++;
            //int* new_mas = new int[top + 1];
            mas[index] = data;
            for (int i = 1; i < (top - index + 1); i++)
            {   
                mas[index + i] = mas[index + i - 1];
            }
            top++;
            return true;
        }
        else
        {
            expand(2 * (capacity + 1));
            capacity = 2 * (capacity + 1);
            //top++;
            int* new_mas = new int[top + 1];
            for (int i = 0; i < (top + 1); i++)
            {
                if (i < index)
                {
                    new_mas[i] = mas[i];
                }
                else if (i == index)
                {
                    new_mas[i] = data;
                }
                else
                {
                    new_mas[i] = mas[i - 1];
                }
            }
            delete[] mas;
            mas = new_mas;
            top++;
            return true;
        }
    }
}


//delete element with number index
int subvector::erase(int index) // index - where
{
    if (index == (top - 1))
    {
        return pop_back();
    }
    else
    {
        int to_del = mas[index];

        for (int i = 0; i < (top - index - 1); i++)
        {
            mas[index + i] = mas[index + i + 1];
        }

         top--;
         return to_del;
        
    }
}


unsigned int subvector::get_top()
{
    return top;
}

unsigned int subvector:: get_cap()
{
    return capacity;
}

