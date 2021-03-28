#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

////////график capacity и size от i - числа итераций
//////по факту график capacity от size
using namespace std;


int main()
{
    ofstream out;
    unsigned int n = 2500000;

    vector <int> v;

    out.open("data.txt");

    out << 'x' << " " << 'y' << endl;

    srand(time(0));

    for (unsigned int i = 0; i < n; i++)
    {
       v.push_back(rand());
       out << v.capacity() << " " << v.size() << endl;
    }


    return 0;
}