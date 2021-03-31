#include <forward_list>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

//среднее время добавления  в начало односвязного списка
//в зависимости от size

int main()
{
    ofstream out1;
    ofstream out2;
    unsigned int n = 2500000;
    size_t size = 0;


    forward_list <int> f;

    ////////////////////// PUSH_FRONT //////////////////////

    out1.open("data_push.txt");

    out1 << 'x' << " " << 'y' << endl;

    srand(time(0));

    for (int i = 0; i < 2500000; i++)
    {
        auto begin = chrono::high_resolution_clock::now();

        f.push_front(rand());
        size++;

        auto end = chrono::high_resolution_clock::now();

        out1 << chrono::duration_cast <chrono::nanoseconds>(end - begin).count() << " " << size << endl;
    }


    ////////////////// POP_FRONT ///////////////////////////

    out2.open("data_pop.txt");

    out2 << 'x' << " " << 'y' << endl;

    srand(time(0));

    for (int i = 0; i < 2500000; i++)
    {
        auto begin = chrono::high_resolution_clock::now();

        f.pop_front();
        size--;

        auto end = chrono::high_resolution_clock::now();

        out2 << chrono::duration_cast <chrono::nanoseconds>(end - begin).count() << " " << size << endl;
    }


   return 0;
}


