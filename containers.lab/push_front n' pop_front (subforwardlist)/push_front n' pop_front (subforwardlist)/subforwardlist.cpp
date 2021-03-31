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
void subforwardlist::clear() {

    while (size_)
    {
        pop_front();
    }

}

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

bool subforwardlist::push_front(int d) {

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

unsigned int subforwardlist::get_size()
{
    return size_;
}
