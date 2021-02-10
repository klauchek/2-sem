#include <iostream>
#include <random>
#include <chrono>

using namespace std;

class subvector
{
private:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector();

    ~subvector();

    void clear();

    void expand(unsigned int new_cap);

    bool push_back(int d);

    int pop_back();

    bool resize(unsigned int new_capacity);

    void shrink_to_fit();

    //! Reloaded operator [] for vector
    int operator [](int i);

    unsigned int get_cap();

    unsigned int get_top();

};

subvector:: subvector()
    {
        this->mas = nullptr;
        this->capacity = 0;
        this->top = 0;
    }

subvector::~subvector()
    {
        delete[] this->mas;
        this->mas = nullptr;
    }

void subvector::clear()
    {
        this->top = 0;
    }

void subvector::expand(unsigned int new_cap)
    {
        int* new_mas = new int[new_cap];
        for (int i = 0; i < this->top; i++)
            new_mas[i] = (this->mas)[i];

        delete[] this->mas;
        this->mas = new_mas;
    }

    //добавление элемента в конец недовектора
    //с выделением дополнительной памяти при необходимости 
bool subvector::push_back(int d)
    {
        if (this->capacity > this->top)
        {
            this->top++;
            this->mas[this->top - 1] = d;
        }
        else
        {
            expand(2 * ((this->capacity) + 1));
            this->capacity = 2 * ((this->capacity) + 1);
            this->top++;
            this->mas[this->top - 1] = d;
        }

        return true;
    }

    //удаление элемента с конца недовектора

int subvector::pop_back() {

        if (this->top == 0)
            return 0;

        int last = this->mas[(this->top) - 1];

        this->top--;

        return last;
    }

    //увеличить емкость недовектора

bool subvector::resize(unsigned int new_capacity) {

        int* new_mas = new int[new_capacity];
        for (int i = 0; i < this->top; i++)
        {
            new_mas[i] = (this->mas)[i];
        }

        this->capacity = new_capacity;

        delete[] this->mas;
        this->mas = new_mas;
        return true;
    }

    //очистить неиспользуемую памят

void subvector::shrink_to_fit() {

        if (this->capacity == this->top)
            return;

        if (this->capacity > this->top)
        {
            expand(this->top);
            this->capacity = this->top;
        }

    }
//! Reloaded operator [] for vector
int subvector::operator [](int i)
  {
    return mas[i];
  }

unsigned int subvector::get_cap()
{
    return this->capacity;
}

unsigned int subvector::get_top()
{
    return this->top;
}



//!PROFILER FOR SUBVECTOR

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 1e6;
}

int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

int main()
{
    int n = 100000;
    int* test_sequence = new int[n], sum_for_O3 = 0, sum_check = 0,
        * pop_push_sequence_eq = new int[n],
        * pop_push_sequence_push = new int[n],
        * pop_push_sequence_pushpush = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);

    //----------- Initialization

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        test_sequence[i] = rand_uns(0, n - 1);
        pop_push_sequence_eq[i] = rand_uns(0, 1);
        pop_push_sequence_push[i] = rand_uns(0, 5);
        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
    }
    finish = get_time();

    cout << "Test sequence initialization: \t\t" << finish - start << endl;

    subvector sv;

    //----------- Test 000 Straight push_back


    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.push_back(i);
    }

    finish = get_time();

    for (int i = 0; i < n; i++)   //!!! This is a hack to bamboozle the O3 optimization.
        sum_for_O3 += sv[i]; // I might as well use it to test push/pop.

    cout << "000 Straight push_back: \t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 001 Straight pop_back



    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sum_check += sv.pop_back();
    }
    finish = get_time();



    if (sum_check != sum_for_O3)
    {
        cout << endl << "--- !!! Failed push/pop consistency !!! ---" << endl;
        return 0;
    }

    cout << "001 Straight pop_back: \t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 002 Straight resize up

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.resize(i);
    }
    finish = get_time();

    sv.shrink_to_fit();
    if (sv.get_cap())   
    {
        cout << endl << "--- !!! Failed resize/shrink consistency !!! ---" << endl;
        return 0;
    }

    cout << "002 Straight resize up: \t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 003 Random pop/push equal amount

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();

    sv.clear();
    sv.shrink_to_fit();
    if (sv.get_top())
    {
        cout << endl << "--- !!! Falied clear !!! ---" << endl;
        return 0;
    }
    if (sv.get_cap())
    {
        cout << endl << "--- !!! Falied shrink_to_fit !!! ---" << endl;
        return 0;
    }

    cout << "003 Random pop/push equal amount: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 004 Random pop/push more push

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();

    sv.clear();
    sv.shrink_to_fit();

    cout << "004 Random pop/push more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 005 Random pop/push much more push

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();

    cout << "005 Random pop/push much more push: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- End of tests
    sv.~subvector();
    cout << "-----------" << endl << "Alltests finished, total time: \t" << total << endl;

    delete[] test_sequence;
    delete[] pop_push_sequence_eq;
    delete[] pop_push_sequence_push;
    delete[] pop_push_sequence_pushpush;

    return 0;
}














//
//struct subvector {
//
//    int* mas;
//    unsigned int top;
//    unsigned int capacity;
//
//};

// â bool âîçðàùàòü true, åñëè âñå êîððåêòíî
//èíèöèàëèçàöèÿ ïóñòîãî íåäîâåêòîðà
//bool init(subvector* qv) {
//
//    qv->mas = NULL;
//    qv->top = 0;
//    qv->capacity = 0;
//
//    return true;
//}

//void expand(int** mas, unsigned int top, unsigned int new_cap)
//{
//    int* new_mas = new int[new_cap];
//    for (int i = 0; i < top; i++)
//        new_mas[i] = (*mas)[i];
//
//    delete[] * mas;
//    *mas = new_mas;
//}


//äîáàâëåíèå ýëåìåíòà â êîíåö íåäîâåêòîðà
//ñ âûäåëåíèåì äîïîëíèòåëüíîé ïàìÿòè ïðè íåîáõîäèìîñòè

//bool push_back(subvector* qv, int d) {
//
//    if (qv->capacity > qv->top)
//    {
//        qv->top++;
//        qv->mas[qv->top - 1] = d;
//    }
//    else
//    {
//        expand(&(qv->mas), qv->top, 2 * ((qv->capacity) + 1));
//        qv->capacity = 2 * ((qv->capacity) + 1);
//        qv->top++;
//        qv->mas[qv->top - 1] = d;
//    }
//
//    return true;
//}

//
//int pop_back(subvector* qv) {
//
//    if (qv->top == 0)
//        return 0;
//
//    int last = qv->mas[(qv->top) - 1];
//
//    qv->top--;
//
//    return last;
//}



//bool resize(subvector* qv, unsigned int new_capacity) {
//
//    int* new_mas = new int[new_capacity];
//    for (int i = 0; i < qv->top; i++)
//    {
//        new_mas[i] = (qv->mas)[i];
//    }
//
//    qv->capacity = new_capacity;
//
//    delete[] qv->mas;
//    qv->mas = new_mas;
//    return true;
//}

//î÷èñòèòü íåèñïîëüçóåìóþ ïàìÿòü
//void shrink_to_fit(subvector* qv) {
//
//    if (qv->capacity == qv->top)
//        return;
//
//    if (qv->capacity > qv->top)
//    {
//        expand(&(qv->mas), qv->top, qv->top);
//        qv->capacity = qv->top;
//    }
//
//}


////î÷èñòèòü ñîäåðæèìîå íåäîâåêòîðà; çàíèìàåìîå ìåñòî ïðè ýòîì íå ìåíÿåòñÿ
//void clear(subvector* qv) {
//    qv->top = 0;
//}
//
////î÷èñòèòü âñþ èñïîëüçóåìóþ ïàìÿòü; èíèöèàëèçèðîâàòü íåäîâåêòîð êàê ïóñòîé
//void destructor(subvector* qv) {
//    delete[] qv->mas;
//    init(qv);
//}