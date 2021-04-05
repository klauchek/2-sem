#include "subvector.h"

////////график capacity и size от i - числа итераций


int main()
{
    ofstream out;
    unsigned int n = 2500000;

    subvector sv;

    srand(time(0));

    out.open("data_sv.txt");

    out << "cap" << " " << "size" << " " << "i" << endl;

    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_back(rand());
        out << sv.get_cap() << " " << sv.get_top() << " " << i << endl;
    }

    return 0;
}