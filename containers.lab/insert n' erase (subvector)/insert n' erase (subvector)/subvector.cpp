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
    std::cout << "new cap is: " << new_cap << std::endl;

    int* new_mas = new int[new_cap];
    for (int i = 0; i < top; i++)
        new_mas[i] = mas[i];

    delete[] mas;
    mas = new_mas;
}

void subvector:: insert(int data, int index)
{
	int oldSize = this->top;

	this->top = (this->top >= index) ? (++this->top) : (this->top + (index - this->top));

	int* _result = new int[this->top];

	int arrIndex = 0;

	for (int index2 = 0; index2 < this->top; index2++)
	{
		if (index2 == index)
		{
			_result[index2] = data;
			continue;
		}

		if (arrIndex != oldSize)
		{
			_result[index2] = this->mas[arrIndex++];
		}
	}
	delete[] this->mas;
	this->mas = _result;
}

void subvector:: erase(int index)
{
	int* _result = new int[--this->top];


	int resIndex = 0;

	for (int index2 = 0; index2 < this->top + 1; index2++)
	{
		int resItem;
		int item = this->mas[index2];

		if (index == index2)
		{
			resItem = item;
			continue;
		}
		_result[resIndex++] = this->mas[index2];
	}
	delete[] this->mas;
	this->mas = _result;

}

////add element with number a
//bool subvector::insert(int a, int d) //a - where, d - data
//{
//    if (a == top)
//    {
//        push_back(d);
//        return true;
//    }
//    else
//    {
//        if (capacity > top)
//        {
//            top++;
//            int* new_mas = new int[top];
//            for (int i = 0; i < top; i++)
//            {
//                if (i < a)
//                {
//                    new_mas[i] = mas[i];
//                }
//                else if (i == a)
//                {
//                    new_mas[i] = d;
//                }
//                else
//                {
//                    //new_mas[i] = mas[i + 1];
//                    new_mas[i] = mas[i];
//                }
//            }
//            delete[] mas;
//            mas = new_mas;
//            return true;
//        }
//        else
//        {
//            expand(2 * (capacity + 1));
//            capacity = 2 * (capacity + 1);
//            top++;
//            int* new_mas = new int[top];
//            for (int i = 0; i < top; i++)
//            {
//                if (i < a)
//                {
//                    new_mas[i] = mas[i];
//                }
//                else if (i == a)
//                {
//                    new_mas[i] = d;
//                }
//                else
//                {
//                    new_mas[i] = mas[i];
//                }
//            }
//            delete[] mas;
//            mas = new_mas;
//            return true;
//        }
//    }
//}
//
//
////delete element with number a
//bool subvector::erase(int a) // a - whete
//{
//    if (a == top - 1)
//    {
//        return pop_back_();
//    }
//    else
//    {
//        top--;
//        int* new_mas = new int[top];
//        for (int i = 0; i < top; i++)
//        {
//            if (i < a)
//            {
//                new_mas[i] = mas[i];
//            }
//            else
//            {
//                new_mas[i] = mas[i];
//            }
//        }
//        delete[] mas;
//        mas = new_mas;
//        return true;
//    }
//}
bool subvector::pop_back_()
{

    if (top == 0)
        return false;

    top--;
    return true;

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


