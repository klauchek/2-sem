#include "subforwardlist.h"

using namespace std;

//среднее время добавления  в начало односвязного списка и удаления из начала
//в зависимости от size




int main()
{
    ofstream out1;
    ofstream out2;

    subforwardlist sf;

////////////// PUSH_FRONT ///////////////

    out1.open("data_push_sf.txt");
    out1 << "time" << " " << "size" << endl;

    srand(time(0));

    for (int i = 0; i < 2500000; i++)
    {
        auto begin = chrono::high_resolution_clock::now();

        sf.push_front(rand());

        auto end = chrono::high_resolution_clock::now();

        out1 << chrono::duration_cast <chrono::nanoseconds>(end - begin).count() << " " << sf.get_size() << endl;
    }

 /////////// POP_FRONT /////////////////

    out2.open("data_pop_sf.txt");
    out2 << "time" << " " << "size" << endl;

    srand(time(0));

    for (int i = 0; i < 2500000; i++)
    {
        auto begin = chrono::high_resolution_clock::now();

        sf.pop_front();

        auto end = chrono::high_resolution_clock::now();

        out2 << chrono::duration_cast <chrono::nanoseconds>(end - begin).count() << " " << sf.get_size() << endl;
    }

    return 0;
}