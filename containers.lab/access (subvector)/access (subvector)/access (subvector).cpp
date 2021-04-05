#include "subvector.h"
////График: среднее время доступа для vector и subvector от size. 
using namespace std;

int main()
{
    int n = 1000;

    ofstream out;
    out.open("data_ac_sv.txt");
    out << "time" << " " << "size" << endl;

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

        out << chrono::duration_cast <chrono::nanoseconds>(end - begin).count()/100 << " " << sv.get_top() << endl;
        
        //далее нужно увеличить размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 50000

        for (unsigned int i = 0; i < 50; i++)
        {
            sv.push_back(rand());
        }
        n += 50; //увеличиваем размер на 50, доходя до 2,5 млн
    }

    return 0;
}