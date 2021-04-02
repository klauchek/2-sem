#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;


/// График: среднее время обхода vector, forward_list, list, map, set от размера контейнера.
/// простые арифм опреации за o(1) - увеличение каждого элемента контейнера на единицу



int main()
{

    srand(time(0));

//////////////////// VECTOR /////////////////////////////////
    //int n_v = 500000;

    //ofstream out_v;
    //out_v.open("vector.txt");

    //vector<int> v(n_v); //создание векора на n рандомных чисел; в начале на 500000
    //for (int i = 0; i < n_v; i++)
    //{
    //    v[i] = rand();
    //}

    //out_v << 'x' << " " << 'y' << endl;


    //while (n_v <= 2500000) {

    //    auto begin = chrono::high_resolution_clock::now();

    //    for (int i = 0; i < n_v; i++)
    //    {
    //        v[i]++; 
    //    }

    //    auto end = chrono::high_resolution_clock::now();

    //    out_v << (chrono::duration_cast <chrono::milliseconds>(end - begin).count()) << " " << v.size() << endl;

    //    //далее нужно увеличииь размер и проделать все то же самое
    //    //размер будем увеличивать push_back'ом на 50000

    //    for (unsigned int i = 0; i < 50000; i++)
    //    {
    //        v.push_back(rand());
    //    }
    //    n_v += 50000; //увеличиваем размер на 50000, доходя до 2,5 млн
    //}


    //////////////////// FORWARD_LIST /////////////////////////////////
    //int n_f = 500000;

    //ofstream out_f;
    //out_f.open("forward_list.txt");
    //size_t size = 0;

    //forward_list<int> f; //создание односвязного списка на n рандомных чисел; в начале на 500000
    //for (int i = 0; i < n_f; i++)
    //{
    //    f.push_front(rand());
    //    size++;
    //}

    //out_f << 'x' << " " << 'y' << endl;


    //while (n_f <= 2500000) {

    //    auto begin = chrono::high_resolution_clock::now();

    //    f.clear();

    //    auto end = chrono::high_resolution_clock::now();

    //    out_f << (chrono::duration_cast <chrono::milliseconds>(end - begin).count()) << " " << size << endl;

    //    //далее нужно увеличииь размер и проделать все то же самое
    //    //размер будем увеличивать push_back'ом на 50000

    //    for (unsigned int i = 0; i < n_f + 50000; i++)
    //    {
    //        f.push_front(rand());
    //    }
    //    n_f += 50000;//увеличиваем размер на 50000, доходя до 2,5 млн
    //    size += 50000;
    //}

    ///////////////// LIST ////////////////////////////////////

    int n_l = 500000;

    ofstream out_l;
    out_l.open("list.txt");
    size_t size_l = 0;

    list<int> l; //создание двусвязного списка на n рандомных чисел; в начале на 500000
    for (int i = 0; i < n_l; i++)
    {
        l.push_front(rand());
        size_l++;
    }

    out_l << 'x' << " " << 'y' << endl;


    while (n_l <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        l.clear();

        auto end = chrono::high_resolution_clock::now();

        out_l << (chrono::duration_cast <chrono::milliseconds>(end - begin).count()) << " " << size_l << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 50000

        for (unsigned int i = 0; i < n_l + 50000; i++)
        {
            l.push_front(rand());
        }
        n_l += 50000;//увеличиваем размер на 50000, доходя до 2,5 млн
        size_l += 50000;
    }

    ////////////////////// SET //////////////////////



    return 0;
}

