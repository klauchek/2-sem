﻿
////График: среднее время вставки и удаления  для vector и subvector от size. 

#include "subvector.h"

using namespace std;



int main()
{
    int n = 50000;

    srand(time(0));

    subvector sv; //создание векора на n рандомных чисел; в начале на 500000


    for (int i = 0; i < n; i++)
    {
        sv.push_back(rand());
    }

    int indexes[100] = {};//индексы элементов, на место которых будет производиться вставка /какие потом будут удаляться
    for (int i = 0; i < 100; i++)
    {
        indexes[i] = rand() % sv.get_top(); //имеют номера от 0 до n - размера векора
    }

    ofstream out_in;
    out_in.open("data_in_sv.txt");
    out_in << "time" << " " << "size" << endl;

    ofstream out_er;
    out_er.open("data_er_sv.txt");
    out_er << "time" << " " << "size" << endl;

    while (n <= 2500000) {

        /////////////// INSERT ///////////

        auto begin = chrono::high_resolution_clock::now();

        //////////вставим 100 эл по ранее сгненрированным индексам
        for (int i = 0; i < 100; i++)
        {
            sv.insert(rand(), indexes[i]); //вставить элемент с номером indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end = chrono::high_resolution_clock::now();

        out_in << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) / 100 << " " << sv.get_top() << endl;


        ////////////// ERASE ////////////////

        auto begin_ = chrono::high_resolution_clock::now();

        //////////удалим 100 эл по ранее сгненрированным индексам
        for (int i = 0; i < 100; i++)
        {
            sv.erase(indexes[i]); //удалить элемент с номером indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end_ = chrono::high_resolution_clock::now();

        out_er << (chrono::duration_cast <chrono::microseconds>(end_ - begin_).count()) / 100 << " " << sv.get_top() << endl;
 
        //далее нужно увеличить размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 1000

 
        for ( int i = 0; i < 5000; i++)
        {
            sv.push_back(rand());

        }

        n += 5000; //увеличиваем размер на 1000, доходя до 2,5 млн
    }

    return 0;
}