#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

////График: среднее время доступа для vector и subvector от size. 
/*
рандомно сгенерить номера, к которым будет производиться доступ и записать в массив - так для каждого сайз
делать это вне измерения времени

замеряем время, записывая во временную переменную



не нужно большое кол-во чисел! но нужно большое кол-во итераций

*/
using namespace std;

class subvector
{
private:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    //create empty subvector
    subvector()
    {
        mas = nullptr;
        capacity = 0;
        top = 0;
    }

    //destructor
    ~subvector()
    {
        delete[] mas;
        mas = nullptr;
    }

    //! Reloaded operator [] for vector
    int operator [](int i)
    {
        return mas[i];
    }

    void expand(unsigned int new_cap)
    {
        int* new_mas = new int[new_cap];
        for (int i = 0; i < top; i++)
            new_mas[i] = (mas)[i];

        delete[] mas;
        mas = new_mas;
    }

    //add element to the end of the subvector
    bool push_back(int d)
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

    unsigned int get_top()
    {
        return top;
    }
};



int main()
{
    int n = 500000;

    srand(time(0));

    subvector sv; //создание векора на n рандомных чисел; в начале на 500000
    for (int i = 0; i < n; i++)
    {
        sv.push_back(rand());
    }

    int indexes[100] = {};//идексы элементов, к которым будет осуществляться доступ
    for (int i = 0; i < 100; i++)
    {
        indexes[i] = rand() % sv.get_top(); //имеют номера от 0 до n - размера векора
    }


    while (n <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        ////////////осуществим доступ к тем 100 эл записывая их во временный массив
        int temp[100] = {};
        for (int i = 0; i < 100; i++)
        {
            temp[i] = sv[indexes[i]]; //элемент вектора номер indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end = chrono::high_resolution_clock::now();

        cout << "Time of access to 100 random elements: " << chrono::duration_cast <chrono::microseconds>(end - begin).count() << "; size =" << sv.get_top() << endl;
        cout << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 50000

        for (unsigned int i = 0; i < 50000; i++)
        {
            sv.push_back(rand());
        }
        n += 50000; //увеличиваем размер на 50000, доходя до 2,5 млн
    }

    return 0;
}