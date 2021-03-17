#include "subforwardlist.h"

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
