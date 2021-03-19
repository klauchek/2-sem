﻿#include "subforwardlist_templated.cpp"
#include <string>

//PROFILER FOR SUBLIST!!

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

    //--------------SUBLIST FOR STRING ---------------------
    subforwardlist<string> sv_s;
    sv_s.push_back("abc");
    sv_s.push_back("def");
    sv_s.push_back("ghi");
    sv_s.push_back("hello");
    cout << "Cur size: " << sv_s.get_size() << endl;
    sv_s.pop_front();
    cout << "Cur size (after pop_front): " << sv_s.get_size() << endl;
    cout << sv_s.pop_back() << endl;
    cout << "Cur size (after pop_back): " << sv_s.get_size() << endl;
    sv_s.push_forward("hello2");
    cout << "Cur size (after push_forward): " << sv_s.get_size() << endl;
    sv_s.push_where(1," :) ");
    sv_s.erase_where(2);
    cout << "Cur size: " << sv_s.get_size() << endl;
    sv_s.clear();
    cout << "Cur size: " << sv_s.get_size() << endl;
    cout << endl;


    //-----------------SUBLIST FOR DOUBLE--------------------
    subforwardlist<double> sv_d;
    sv_d.push_back(0.1);
    sv_d.push_back(0.2);
    sv_d.push_back(0.3);
    sv_d.push_back(0.4);
    cout << "Cur size: " << sv_d.get_size() << endl;
    sv_d.pop_front();
    cout << "Cur size (after pop_front): " << sv_d.get_size() << endl;
    cout << sv_d.pop_back() << endl;
    cout << "Cur size (after pop_back): " << sv_d.get_size() << endl;
    sv_d.push_forward(-0.1);
    cout << "Cur size (after push_forward): " << sv_d.get_size() << endl;
    sv_d.push_where(1, -0.2);
    sv_d.erase_where(2);
    cout << "Cur size: " << sv_d.get_size() << endl;
    sv_d.clear();
    cout << "Cur size: " << sv_s.get_size() << endl;
    cout << endl;



    //-----------------SUBLIST FOR INT------------------------


    int n = 10000;
    int* test_sequence = new int[n], sum_for_O3 = 0, sum_check = 0, test_sequence_sum = 0, ongoing_sum = 0,
        * push_sequence = new int[n],
        * pop_sequence = new int[n],
        * pop_push_sequence_eq = new int[n],
        * pop_push_sequence_push = new int[n],
        * pop_push_sequence_pushpush = new int[n],
        * four_ways_test = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);

    //----------- Initialization

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        test_sequence[i] = rand_uns(0, n - 1);
        test_sequence_sum += test_sequence[i];
        push_sequence[i] = rand_uns(0, n - 1);
        pop_sequence[i] = rand_uns(0, n - 1);
        pop_push_sequence_eq[i] = rand_uns(0, 1);
        pop_push_sequence_push[i] = rand_uns(0, 5);
        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
        four_ways_test[i] = rand_uns(0, 3);
    }


    finish = get_time();

    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;

    subforwardlist<int> sv;

    //----------- Test 000 Straight push_back

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.push_back(test_sequence[i]);
    }
    finish = get_time();

    cout << "000 Straight push_back: \t\t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 001 Straight pop_forward

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (sv.pop_forward() != test_sequence[i])
        {
            cout << endl << "--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();

    if (sv.get_size())
    {
        cout << endl << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }

    cout << "001 Straight pop_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 002 Straight push_forward

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.push_forward(test_sequence[i]);
    }
    finish = get_time();

    cout << "002 Straight push_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 003 Straight pop_back

    start = get_time();

    for (int i = 0; i < n; i++)
    {
        if (sv.pop_back() != test_sequence[i])
        {
            cout << endl << "--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();


    if (sv.get_size()) //åñëè ðàçìåð íå íîëü, òî íå âñå óäàëèëîñü!
    {
        cout << endl << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }

    cout << "003 Straight pop_back: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 004 Random push_where

    for (int i = 0; i < n; i++)
    {
        sv.push_back(test_sequence[i]);
    }

    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.push_where(push_sequence[i], test_sequence[i]);
    }
    finish = get_time();

    if (sv.get_size() != 2 * n)
    {
        cout << endl << "--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }

    ongoing_sum = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        ongoing_sum += sv.pop_back();
    }

    if (sv.get_size())
    {
        cout << endl << "--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }

    if (ongoing_sum != 2 * test_sequence_sum)
    {
        cout << endl << "--- !!! Failed push/pop consistency, sum incoherent !!! ---" << endl;
        return 0;
    }

    cout << "004 Random push_where: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;

    //----------- Test 005 Random erase_where

    for (int i = 0; i < 2 * n; i++)
    {
        sv.push_back(test_sequence[i % n]);
    }

    sum_for_O3 = 0;
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sum_for_O3 += sv.erase_where(pop_sequence[i]);
    }
    finish = get_time();

    if (sv.get_size() != n)
    {
        cout << endl << "--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }

    sv.clear();

    if (sv.get_size())
    {
        cout << endl << "--- !!! Clear works wrongly !!! ---" << endl;
        return 0;
    }

    cout << "005 Random erase_where: \t\t\t\t" << finish - start << " \t\t" << sum_for_O3 << endl;
    total += finish - start;


    //----------- Test 006 Random pop/push back equal amount

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

    cout << "006 Random pop/push back equal amount: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 007 Random pop/push back more push

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

    cout << "007 Random pop/push back more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 008 Random pop/push back much more push

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

    sv.clear();

    cout << "008 Random pop/push back much more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 009 Random pop/push forward equal amount

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();

    sv.clear();

    cout << "009 Random pop/push forward equal amount: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 010 Random pop/push forward more push

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();

    sv.clear();

    cout << "010 Random pop/push forward more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 011 Random pop/push forward much more push

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();
    }
    finish = get_time();

    sv.clear();

    cout << "011 Random pop/push forward much more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- Test 012 Random pop/push four ways

    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (four_ways_test[i] == 0)
            sv.push_back(test_sequence[i]);
        else if (four_ways_test[i] == 1)
            sum_for_O3 += sv.pop_back();
        else if (four_ways_test[i] == 2)
            sv.push_forward(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_forward();

    }
    finish = get_time();

    sv.clear();

    cout << "012 Random pop/push four ways: \t\t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;

    //----------- End of tests
    //
    cout << "-----------" << endl << "Alltests finished, total time: \t" << total << endl;

    delete[] test_sequence;
    delete[] pop_push_sequence_eq;
    delete[] pop_push_sequence_push;
    delete[] pop_push_sequence_pushpush;
    delete[] push_sequence,
        delete[] pop_sequence,
        delete[] four_ways_test;


    return 0;
}