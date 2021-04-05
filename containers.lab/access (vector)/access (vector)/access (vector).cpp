#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>

////График: среднее время доступа для vector и subvector от size. 

using namespace std;


int main()
{
    int n = 1000;
    ofstream out;
    out.open("data_ac_v.txt");
    out << "time" << " " << "size" << endl;

    srand(time(0));

    vector<int> v(n); //создание векора на n рандомных чисел; в начале на 1000
    for (int i = 0; i < n; i++)
    {
        v[i] = rand();
    }

    int indexes[100] = {};//идексы элементов, к которым будет осуществляться доступ
    for (int i = 0; i < 100; i++)
    {
        indexes[i] = rand() % v.size(); //имеют номера от 0 до n - размера векора
    }


    while (n <= 2500000) {

        auto begin = chrono::high_resolution_clock::now();

        ////////////осуществим доступ к тем 100 эл записывая их во временный массив
        int temp[100] = {};
        for (int i = 0; i < 100; i++)
        {
            temp[i] = v[indexes[i]]; //элемент вектора номер indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end = chrono::high_resolution_clock::now();

        out << (chrono::duration_cast <chrono::nanoseconds>(end - begin).count())/100 << " " << v.size() << endl;

        //далее нужно увеличииь размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 50

        for (unsigned int i = 0; i < 50; i++)
        {
            v.push_back(rand());
        }
        n += 50; //увеличиваем размер на 50, доходя до 2,5 млн
    }

    return 0;
}