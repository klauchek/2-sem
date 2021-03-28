#include "subforwardlist.h"

using namespace std;

//среднее время добавления  в начало односвязного списка
//в зависимости от size




int main()
{
    ofstream out;
 
    subforwardlist sf;

    out.open("data.txt");

    out << 'x' << " " << 'y' << endl;

    srand(time(0));

    for (int i = 0; i < 2500000; i++)
    {
        auto begin = chrono::high_resolution_clock::now();

        sf.push_front(rand());

        auto end = chrono::high_resolution_clock::now();

        out << chrono::duration_cast <chrono::nanoseconds>(end - begin).count() << " " << sf.get_size() << endl;
    }

    return 0;
}