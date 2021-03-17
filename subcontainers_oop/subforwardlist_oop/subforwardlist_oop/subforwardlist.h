#ifndef __SUBFORWARDLIST__H__
#define __SUBFORWARDLIST__H__


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



#endif // !__SUBFORWARDLIST__H__

