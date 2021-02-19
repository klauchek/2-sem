#include "subset_oop.h"



subset::subset(int key)
{
   /* root = nullptr;
    size = 0;*/
    root = new node(key);
    size = 1;
    
}

subset::~subset()
{
    destructor();
}


bool subset::find(int key)  //?? ok
{
    node* cur = root;

    while (cur != nullptr)
    {
        if (key == cur->key_)
            return true;
        if (key > cur->key_)
            cur = cur->right_;
        if (key < cur->key_)
            cur = cur->left_;
    }

    return false;
}



//add the element to the tree, ignore doubles
bool subset::insert(int key)  //?? ok
{
    if (size = 0)
    {
        node* root = new node(key);
        size++;

        return true;
    }
    else
    {
        node* cur = root;
        while (cur->key_ != key)
        {
            if (key > cur->key_)
            {
                if (cur->right_ == nullptr)
                {
                    node* right_leaf = new node(key, nullptr, nullptr, cur);
                    cur->right_ = right_leaf;

                    cur->correct_height();
                    size++;

                    break;
                }

                else cur = cur->right_;
            }
            else if (key < cur->key_)
            {
                if (cur->left_ == nullptr)
                {
                    node* left_leaf = new node(key, nullptr, nullptr, cur);
                    cur->left_ = left_leaf;

                    cur->correct_height();
                    size++;

                    break;
                }
                else cur = cur->left_;
            }
        }
        return true;
    }
}

//if insert == true
// ++size

////delete the element from the tree
//
//void subset::del_elem(int key)
//{
//    return root->del_elem(key);
//}

bool subset::del_elem(int key) {

   if (size = 0)
        return;
   else
   {
       node* cur = root;
      /* if (cur->left_)
           cur->left_->del_elem(key);
       if (cur->right_)
           cur->right_->del_elem(key);*/
       while (cur->key_ != key)
       {
           //сase 2: 
           if (cur->left_ == nullptr)
           {
               node* right_leaf = cur->right_;
               delete cur;
               cur = right_leaf;
           }
           else if (cur->right_ == nullptr)
           {
               node* left_leaf = cur->left_;               
               delete cur;
               cur = left_leaf;
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



unsigned int subset::get_height() {

    return root->node::height;
}



void subset::node::correct_height() {

    int h_r = 0;
    int h_l = 0;

    if (this == nullptr)
       this->height = 0;
    if (this->right_ != nullptr)
    {
        h_r = this->right_->height;
    }


    if (this->left_ != nullptr)
    {
        h_l = this->left_->height;
    }
 

    height = (max(h_r, h_l) + 1);

}

//clear all memory used

void subset::destructor() {

    return root->destructor();
    size = 0;
}

void subset::destructor()
{
    node* cur = root;
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
void subset::visit(int* a, int* i) {

    node* cur = root;

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





