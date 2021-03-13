
#include <iostream>
#include <random>
#include <chrono>

using namespace std;


class subforwardlist
{

private:
	struct node 
	{
		node* next_;
		int data_;

		node(int data, node* next = nullptr) 
		{
			next_ = next;
			data_ = data;
		}
		
	};

	unsigned int size_;
	node* head;

public:

	subforwardlist();

	~subforwardlist();

	bool push_back(int d);

	void pop_front();

	int pop_back();

	bool push_forward(int d);

	int pop_forward();

	bool push_where(unsigned int where, int d);

	bool erase_where(unsigned int where);

	unsigned int get_size();

	void clear();

	int operator [](int i);


};

subforwardlist::subforwardlist()
{
	size_ = 0;
	head = nullptr;
}

subforwardlist::~subforwardlist()
{
	clear();
}

int subforwardlist::operator [](int i)
{
	node* cur = head;
	int counter = 0;
	while (cur != nullptr)
	{
		if (counter == i)
		{
			return cur->data_;
		}
		cur = cur->next_;
		counter++;
	}


}

//determine the size of the list

unsigned int subforwardlist::get_size()
{
	return size_;
}


//add an element to the end of the list
bool subforwardlist::push_back(int d) {

	if (head != nullptr)
	{
		node* temp = head;

		while (temp->next_ != nullptr)
		{
			temp = temp->next_;
		}
		temp->next_ = new node(d);
	}
	else
	{
		head = new node(d);
	}

	size_++;
	return true;
}

//for clear and destructor
//delete an element from the beginning of the list
void subforwardlist::pop_front() {

    if (head == nullptr)
        return;
    else
    {
        node* temp = head;
        head = head->next_;
        delete temp;
        size_--;
    }
}


//delete an element from the end of the list
int subforwardlist::pop_back() {

    if (head != nullptr)
    {
        node* cur = head;
        int l;

        if (cur->next_ != nullptr)
        {
            node* prev = nullptr;
            while (cur->next_ != nullptr)
            {
                prev = cur;
                cur = cur->next_;
            }

            l = cur->data_;

            prev->next_ = nullptr;
            delete cur;

            size_--;
            return l;
        }
        else
        {
            l = cur->data_;
            delete cur;
            head = nullptr;

            size_--;
            return l;
        }


    }
    else
        return 0;
}

//add an element to the top of the list
bool subforwardlist::push_forward(int d) {

	if (head == nullptr)
	{
		head = new node(d);
	}

	else
	{
		node* temp = new node(d, head);
		head = temp;
	}

	size_++;
	return true;
}




//delete an element from the beginning of the list and return data
int subforwardlist::pop_forward() {

	if (head != nullptr)
	{
		int f = head->data_;
		pop_front();
		return f;
	}
	else
		return 0;

}

//add the element number "where"

bool subforwardlist::push_where(unsigned int where, int d) {


    if (where == 0 || head == nullptr)
    {
        push_forward(d);
    }
    else
    {
        node* prev = nullptr;
        node* cur = head;

        for (unsigned int i = 0; i != where; i++)
        {
            prev = cur;
            cur = cur->next_;
        }

        node* new_el = new node(d, cur);
        //new_el->data = d;
        //new_el->next = cur;
        prev->next_ = new_el;
        cur = cur->next_;

        size_++;
    }

    return true;
}


//delete the element number "where"
bool subforwardlist::erase_where(unsigned int where) {

	if (where == 0)
	{
		pop_front();
	}
	else
	{
		node* prev = head;

		for (unsigned int i = 0; i < (where - 1); i++)
		{
			prev = prev->next_;
		}
		node* cur = prev->next_;
		prev->next_ = cur->next_;
		delete cur;
        size_--;
	}

	return true;
}


//clear the contents of the list
void subforwardlist::clear() {

	while (size_)
	{
		pop_front();
	}

}




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

    subforwardlist sv;

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


    if (sv.get_size()) //если размер не ноль, то не все удалилось!
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