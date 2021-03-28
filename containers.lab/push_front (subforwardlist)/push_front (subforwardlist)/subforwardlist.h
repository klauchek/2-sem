#ifndef __SUBFORWARDLIST__H__
#define __SUBFORWARDLIST__H__

#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

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

	bool push_front(int d);

	unsigned int get_size();

	void clear();

	void pop_front();
};


#endif __SUBFORWARDLIST__H__
