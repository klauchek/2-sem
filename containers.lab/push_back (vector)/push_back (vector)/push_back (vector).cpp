#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>

////////график capacity и size от i - числа итераций
using namespace std;


int main()
{
    int n = 1000;

    while (n <= 100000) {

        vector <int> v;

        srand(time(0));

        auto begin = chrono::high_resolution_clock::now();

        ////////////
        for (unsigned int i = 0; i < n; i++)
        {
            v.push_back(rand());
        }

        auto end = chrono::high_resolution_clock::now();
        cout << "Time of " << n << " iterations: " << chrono::duration_cast <chrono::milliseconds>(end - begin).count() << ";" << endl;
        cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;
        cout << endl;
        n += 1000;


        /*for (int i = 0; i < n; i++){
             cout << arr[i] << " ";*/
    }

    return 0;
}