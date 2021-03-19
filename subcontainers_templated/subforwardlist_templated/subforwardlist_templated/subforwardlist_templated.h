#ifndef __SUBLIST__H__
#define __SUBLIST__H__


#include <iostream>
#include <random>
#include <chrono>

using namespace std;


template <typename T>
class subforwardlist
{

private:
	struct node
	{
		node* next_;
		T data_;

		node(T data, node* next = nullptr)
		{
			next_ = next;
			data_ = data;
		}

	};

	size_t size_;
	node* head;

public:

	subforwardlist();

	~subforwardlist();

	bool push_back(T d);

	void pop_front();

	T pop_back();

	bool push_forward(T d);

	T pop_forward();

	bool push_where(unsigned int where, T d);

	bool erase_where(unsigned int where);

	size_t get_size();

	void clear();

};




#endif __SUBLIST__H__
