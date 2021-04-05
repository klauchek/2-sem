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
    int n_v = 10000;

    ofstream out_v;
    out_v.open("vector.txt");

    vector<int> v(n_v); //создание векора на n рандомных чисел; в начале на 10000
    for (int i = 0; i < n_v; i++)
    {
        v[i] = rand();
    }

    out_v << "time" << " " << "size" << endl;


    while (n_v <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        for (int i = 0; i < n_v; i++) {}

        auto end = chrono::high_resolution_clock::now();

        out_v << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) << " " << v.size() << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 5000

        for (unsigned int i = 0; i < 5000; i++)
        {
            v.push_back(rand());
        }
        n_v += 5000; //увеличиваем размер на 5000, доходя до 2,5 млн
    }


    //////////////////// FORWARD_LIST /////////////////////////////////
    int n_f = 10000;

    ofstream out_f;
    out_f.open("forward_list.txt");
    size_t size = 0;

    forward_list<int> f; //создание односвязного списка на n рандомных чисел; в начале на 10000
    for (int i = 0; i < n_f; i++)
    {
        f.push_front(rand());
        size++;
    }

    out_f << "time" << " " << "size" << endl;


    while (n_f <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        for (auto it = f.begin(); it != f.end(); it++) {}

        auto end = chrono::high_resolution_clock::now();

        out_f << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) << " " << size << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 5000

        for (unsigned int i = 0; i < 5000; i++)
        {
            f.push_front(rand());
        }
        n_f += 5000;//увеличиваем размер на 5000, доходя до 2,5 млн
        size += 5000;
    }

    ///////////////// LIST ////////////////////////////////////

    int n_l = 10000;

    ofstream out_l;
    out_l.open("list.txt");
    size_t size_l = 0;

    list<int> l; //создание двусвязного списка на n рандомных чисел; в начале на 10000
    for (int i = 0; i < n_l; i++)
    {
        l.push_front(rand());
        size_l++;
    }

    out_l << "time" << " " << "size" << endl;


    while (n_l <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        for (auto it = l.begin(); it != l.end(); it++) {}

        auto end = chrono::high_resolution_clock::now();

        out_l << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) << " " << size_l << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 5000

        for (unsigned int i = 0; i < 5000; i++)
        {
            l.push_front(rand());
        }
        n_l += 5000;//увеличиваем размер на 50000, доходя до 2,5 млн
        size_l += 5000;
    }

    //////////////////////// SET //////////////////////

    int n_s = 10000;

    ofstream out_s;
    out_s.open("set.txt");

    set<int> s; //создание дерева на n рандомных чисел; в начале на 500000
    for (int i = 0; i < n_s; i++)
    {
        s.insert(rand());
    }

    out_s << "time" << " " << "size" << endl;


    while (n_s <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        for (auto it = s.begin(); it != s.end(); it++) {}

        auto end = chrono::high_resolution_clock::now();

        out_s << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) << " " << s.size() << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 5000

        for (unsigned int i = 0; i < 5000; i++)
        {
            s.insert(rand());
        }
        n_s += 5000;//увеличиваем размер на 5000, доходя до 2,5 млн
    }



    /////////////////////// MAP //////////////////////

    int n_m = 10000;

    ofstream out_m;
    out_m.open("map.txt");

    map<int,int> m; //создание map на n рандомных чисел; в начале на 10000
    for (int i = 0; i < n_m; i++)
    {
        m.insert(make_pair(i, rand()));
    }

    out_m << "time" << " " << "size" << endl;

    while (n_m <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        for (auto it = m.begin(); it != m.end(); it++) {}

        auto end = chrono::high_resolution_clock::now();

        out_m << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) << " " << m.size() << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 5000

        for (int i = 0; i < 5000; i++)
        {
            m.insert(make_pair(n_m + i, rand()));
        }
        n_m += 5000;//увеличиваем размер на 5000, доходя до 2,5 млн
    }


    return 0;
}

