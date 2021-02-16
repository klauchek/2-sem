#include "subset_oop.h"



subset::subset()
{
    root = nullptr;
    size = 0;
   /* root = new node(key);
    size = 1;*/
}

subset::~subset()
{
    destructor();
}


/*  subset my_tree .... my_tree.root->find(key) */

//! Example
//! subset my_tree .... node* cur = my_tree.find();

//! Method for seraching in my tree
subset::node* subset:: find(int key)
{
    return root->find(key);
}

//! Hepler method for searching in my tree
subset::node* subset::node::find(int key)
{
    node* cur = this;

    if (cur == nullptr)
        return cur;

    if (key > cur->key_)
        return cur->right_->find(key);

    if (key < cur->key_)
        return cur->left_->find(key);

}



//! tree.insert();

bool subset::insert(int key)
{
    if (root->insert(key))
        size++;

    return root->insert(key);


}

//add the element to the tree, ignore doubles
bool subset::node::insert(int key) 
{
    node* cur = this;

    if (!cur)
    {
        cur = new node(key);
        cur->correct_height();

        return true;
    }


    if (cur->find(key) != nullptr)
        return false;

    if (key < cur->key_)
        return cur->left_->insert(key);
    else if (key > cur->key_)
        return cur->right_->insert(key);
}

//if insert == true
// ++size

////delete the element from the tree
//
//void subset::del_elem(int key)
//{
//    return root->del_elem(key);
//}

void subset::node::del_elem(int k) {

    node* cur = this;
    if (cur == NULL)
        /*height = correct_height();*/
        return;
    if (cur->left_)
        cur->left_->del_elem(k);
    if (cur->right_)
        cur->right_->del_elem(k);

    if (cur->left_ == NULL)
    {
        node* right = cur->right_;
        delete cur;
        cur = right;
    }
    else if (cur->right_== NULL)
    {
        node* left = cur->left_;
        delete cur;
        cur = left;
    }
    else
    {

        node* right = cur->right_;
        if (right->left_ == NULL)
        {
            cur->key_ = right->key_;
            cur->right_ = right->right_;
            delete right;
        }
        else
        {
            node* min_parent = right;
           
            while (min_parent->left_->left_ != NULL)
            {
                min_parent = min_parent->left_;
            }
            node* min = min_parent->left_;
            min_parent->left_ = min->right_;
            delete min;
        }
    }

}

//"del_elem" but for profiler

bool subset::remove(int key) {

    if (root->remove(key))
        size--;

    return root->remove(key);
}


bool subset::node::remove(int key) {

    node* cur = this;

    if (cur == NULL)
        return false;
    if (cur->key_ == key)
    {
        cur->del_elem(key);
        return true;
    }
    if (key < cur->key_)
        return cur->left_->remove(key);

    return cur->right_->remove(key);

}


//number of elements in the tree  // ok!




//the height of the tree // 

unsigned int subset::get_height() {

    return root->height;
}

//
//unsigned int subset::correct_height() {
//
//    return root->correct_height();
//}


void subset::node::correct_height() {

    int h_r = 0;
    int h_l = 0;

    if (this == nullptr)
       this->height = 0;
    if (this->right_ != nullptr)
    {
        h_r = this->right_->height;
    }
    else h_r = 0;

    if (this->left_ != nullptr)
    {
        h_l = this->left_->height;
    }
    else h_l = 0;

    height = (max(h_r, h_l) + 1);

}

//clear all memory used

void subset::destructor() {

    return root->destructor();
    size = 0;
}

void subset::node::destructor()
{
    node* cur = this;
    if (cur == nullptr)
    return;
    if (cur->left_)
        cur->left_->destructor();
    if (cur->right_)
        cur->right_->destructor();

    cur->right_ = nullptr;
    cur->left_ = nullptr;
    cur = nullptr;

    delete cur;
}

unsigned int subset::get_size() {
    return size;
}

//for DFS
void subset::node::visit(int* a, int* i) {

    node* cur = this;

    if (cur == nullptr)
        return;

    cur->left_->visit(a, i);
    a[*i] = cur->key_;
    (*i)++;
    cur->right_->visit(a, i);
}

////depth-first search
//
//int* subset::DFS(){
//
//    return root->DFS();
//}

int* subset::DFS() {

    node* cur = root;
    int i = 0;
    unsigned int s = size;
    int* a = new int[s];
    cur->visit(a, &i);
    return a;
}





