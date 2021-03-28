
////График: среднее время вставки и удаления  для vector и subvector от size. 
/*
рандомно сгенерить номера, к которым будет производиться доступ и записать в массив - так для каждого сайз
делать это вне измерения времени

нужно большое кол-во чисел! но нужно большое кол-во итераций

*/
#include "subvector.h"

using namespace std;



int main()
{
    int n = 500000;

    srand(time(0));

    subvector sv; //создание векора на n рандомных чисел; в начале на 500000


    for (int i = 0; i < n; i++)
    {
        sv.push_back(rand());
    }

    int indexes[100] = {};//индексы элементов, на место которых будет производиться вставка /какие потом будут удаляться
    for (int i = 0; i < 100; i++)
    {
        indexes[i] = rand() % sv.get_top(); //имеют номера от 0 до n - размера векора
    }


    while (n <= 2500000) {

        /////////////// INSERT ///////////

        auto begin = chrono::high_resolution_clock::now();

        //////////вставим 100 эл по ранее сгненрированным индексам
        for (int i = 0; i < 100; i++)
        {
            sv.insert(indexes[i], rand()); //вставить элемент с номером indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end = chrono::high_resolution_clock::now();

        cout << "Time of insert random element: " << (chrono::duration_cast <chrono::microseconds>(end - begin).count()) / 100 << "; size =" << sv.get_top() << endl;
        //cout << endl;


        ////////////// ERASE ////////////////

        auto begin_ = chrono::high_resolution_clock::now();

        //////////удалим 100 эл по ранее сгненрированным индексам
        for (int i = 0; i < 100; i++)
        {
            sv.erase(indexes[i]); //удалить элемент с номером indexes[i], т.е. элемент с заранее сгненрированным номером
        }

        auto end_ = chrono::high_resolution_clock::now();

        cout << "Time of erase random element: " << (chrono::duration_cast <chrono::microseconds>(end_ - begin_).count()) / 100 << "; size =" << sv.get_top() << endl;
        cout << endl << endl;


        //далее нужно увеличить размер и проделать все то же самое
        //размер будем увеличивать push_back'ом на 50000

        int cnter = 0;
 
        for ( int i = 0; i < 3; i++)
        {
            cnter++;
            std::cout << cnter << " ";
            sv.push_back(rand());

        }

        //sv.push_back(rand());
        //sv.push_back(rand());
        n += 50000; //увеличиваем размер на 50000, доходя до 2,5 млн
    }

    return 0;
}