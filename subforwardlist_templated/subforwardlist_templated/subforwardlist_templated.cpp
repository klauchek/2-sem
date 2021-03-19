#include "subforwardlist_templated.h"

template <typename T>
subforwardlist<T>::subforwardlist()
{
	size_ = 0;
	head = nullptr;
}

template <typename T>
subforwardlist<T>::~subforwardlist()
{
	clear();
}


//determine the size of the list
template <typename T>
size_t subforwardlist<T>::get_size()
{
	return size_;
}


//add an element to the end of the list
template <typename T>
bool subforwardlist<T>::push_back(T d) {

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
template <typename T>
void subforwardlist<T>::pop_front() {

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
template <typename T>
T subforwardlist<T>::pop_back() {

	if (head != nullptr)
	{
		node* cur = head;
		T l;

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
template <typename T>
bool subforwardlist<T>::push_forward(T d) {

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

template <typename T>
T subforwardlist<T>::pop_forward() {

	if (head != nullptr)
	{
		T f = head->data_;
		pop_front();
		return f;
	}
	else
		return 0;

}

//add the element number "where"
template <typename T>
bool subforwardlist<T>::push_where(unsigned int where, T d) {


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
		prev->next_ = new_el;
		cur = cur->next_;

		size_++;
	}

	return true;
}


//delete the element number "where"
template <typename T>
bool subforwardlist<T>::erase_where(unsigned int where) {

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
template <typename T>
void subforwardlist<T>::clear() {

	while (size_)
	{
		pop_front();
	}

}
