#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

////////график capacity и size от i - числа итераций
using namespace std;

class subvector
{
private:

    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector()
    {
        mas = nullptr;
        capacity = 0;
        top = 0;
    }

    ~subvector()
    {
        delete[] mas;
        mas = nullptr;
    }

    bool push_back(int d)
    {
        if (capacity > top)
        {
            top++;
            mas[top - 1] = d;
        }
        else
        {
            expand(2 * ((capacity)+1));
            capacity = 2 * ((capacity)+1);
            top++;
            mas[top - 1] = d;
        }

        return true;
    }

    void expand(unsigned int new_cap)
    {
        int* new_mas = new int[new_cap];
        for (unsigned int i = 0; i < top; i++)
            new_mas[i] = (mas)[i];

        delete[] mas;
        mas = new_mas;
    }

    unsigned int get_cap()
    {
        return capacity;
    }

    unsigned int get_top()
    {
        return top;
    }
};




int main()
{
    ofstream out;
    unsigned int n = 2500000;

    subvector sv;

    srand(time(0));

    out.open("data.txt");
    for (unsigned int i = 0; i < n; i++)
    {
        sv.push_back(rand());
        out << sv.get_cap() << " " << sv.get_top() << endl;
    }

    return 0;
}