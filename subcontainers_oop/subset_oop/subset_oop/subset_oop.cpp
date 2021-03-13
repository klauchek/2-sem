#include "subset_oop.h"
#include <stdio.h>


subset::subset()
{
   /* root = nullptr;
    size = 0;
  /*  root = new node(key);
    size = 1;*/
    
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
    if (size == 0)
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

                    //cur->correct_height();
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

                    //cur->correct_height();
                    size++;

                    break;
                }
                else cur = cur->left_;
            }
        }
       /* this->correct_height();*/
        return true;
    }
}



//delete the element from the tree

bool subset::remove(int key)
{
    if (size == 0 || root == nullptr) //subset is empty
        return false;

    else
    {
        node* cur = root;
        //node* prev = nullptr;
        //delete root (if key in the root)

        if (key == cur->key_)
        {
            node* tmp_right = cur->right_; //r branch
            node* tmp_left = cur->left_; //l branch
            delete cur;
            
            if (tmp_right)//есть правая ветка //my case 3
            {
                while (tmp_right->left_)
                {
                    tmp_right = tmp_right->left_;
                }
                root = tmp_right->left_;
                size--;
                return true;
            }
            else
            {
                root = tmp_left;
                size--;
                return true;
            }
        }
        else
        {
            node* tmp = root;
            while (tmp->left_ || tmp->right_) //has at least one child
            {
                if (key > cur->key_)
                {
                    if (tmp->right_->key_ = key)
                    {
                        node* tmp_right = tmp->right_->right_; //r branch
                        node* tmp_left = tmp->right_->left_; //l branch
                        delete tmp->right_;
                        if (tmp_right)//есть правая ветка //my case 3
                        {
                            while (tmp_right->left_)
                            {
                                tmp_right = tmp_right->left_;
                            }
                            tmp->right_ = tmp_right->left_;
                            size--;
                            return true;
                        }
                        else
                        {
                            tmp->right_ = tmp_left;
                            size--;
                            return true;
                        }
                    }

                }

                if (key < cur->key_)
                {
                    if (tmp->left_->key_ = key)
                    {
                        node* tmp_right = tmp->left_->right_; //r branch
                        node* tmp_left = tmp->left_->left_; //l branch
                        delete tmp->left_;
                        if (tmp_right)//есть правая ветка //my case 3
                        {
                            while (tmp_right->left_)
                            {
                                tmp_right = tmp_right->left_;
                            }
                            tmp->left_ = tmp_right->left_;
                            size--;
                            return true;
                        }
                        else
                        {
                            tmp->left_ = tmp_left;
                            size--;
                            return true;
                        }
                    }
                }
            }
        }
    }
}


//bool subset::del_elem(int key) {
//
//   if (size = 0)
//        return;
//   else
//   {
//       node* cur = root;
//      /* if (cur->left_)
//           cur->left_->del_elem(key);
//       if (cur->right_)
//           cur->right_->del_elem(key);*/
//       while (cur->key_ != key)
//       {
//           //сase 2: 
//           if (cur->left_ == nullptr)
//           {
//               node* right_leaf = cur->right_;
//               delete cur;
//               cur = right_leaf;
//           }
//           else if (cur->right_ == nullptr)
//           {
//               node* left_leaf = cur->left_;               
//               delete cur;
//               cur = left_leaf;
//           }
//
//           else
//           {
//
//               node* right = cur->right_;
//               if (right->left_ == NULL)
//               {
//                   cur->key_ = right->key_;
//                   cur->right_ = right->right_;
//                   delete right;
//               }
//               else
//               {
//                   node* min_parent = right;
//
//                   while (min_parent->left_->left_ != NULL)
//                   {
//                       min_parent = min_parent->left_;
//                   }
//                   node* min = min_parent->left_;
//                   min_parent->left_ = min->right_;
//                   delete min;
//               }
//           }
//       }
//   }
//}

//"del_elem" but for profiler
//
//bool subset::remove(int key) {
//
//    if (root->remove(key))
//
//        size--;
//
//    return root->remove(key);
//}
//
//
//bool subset::node::remove(int key) {
//
//    node* cur = this;
//
//    if (cur == NULL)
//        return false;
//    if (cur->key_ == key)
//    {
//        cur->del_elem(key);
//        return true;
//    }
//    if (key < cur->key_)
//        return cur->left_->remove(key);
//
//    return cur->right_->remove(key);
//
//}



unsigned int subset::get_height() {

    return height;
}



void subset::correct_height() {

    node* head = nullptr;
    node* cur = nullptr;
    node* prev = nullptr;
    int res = 0;
    int counter = 0;
    head = root;
    cur = root;
    while ((head->left_ && head->left_->visit) || (head->right_ && head->right_->visit))
    {
        while ((cur->left_ && cur->left_->visit) || (cur->right_ && cur->right_->visit))
        {
            if (cur->left_ && cur->left_->visit)
            {
                cur = cur->left_;
                counter++;
            }
            else if (cur->right_ && cur->right_->visit)
            {
                cur = cur->right_;
                counter++;
            }
        }
        prev = cur->parent_;
        if (prev->right_ == cur)
            prev->right_->visit = false;
        else
            prev->left_->visit = false;
        if (res < counter)
            res = counter;
        cur = prev;
        counter--;
    }
    head->visit = false;
    height = res;

}
////clear all memory used

void subset::destructor()
{
    node* prev = nullptr;
    node* head = root;
    node* cur = root;
    if (head == nullptr)
    {
        return;
    }
    else
    {
        while (head->left_ || head->right_)
        {
            while (cur->left_ || cur->right_)
            {
                if (cur->left_)
                    cur = cur->left_;
                else if (cur->right_)
                    cur = cur->right_;
            }
            prev = cur->parent_;
            if (prev->right_ == cur)
                prev->right_ = nullptr;
            else
                prev->left_ = nullptr;
            delete cur;
            cur = prev;
            size--;
        }
        delete head;
        size--;
        //cout << endl;
        //cout << get_size();
    }
}



unsigned int subset::get_size() {
    return size;
}



//for DFS
//void subset::visit(int* a, int* i) {
//
//    node* cur = root;
//
//    if (cur == nullptr)
//        return;
//
//    cur->left_->visit(a, i);
//    a[*i] = cur->key_;
//    (*i)++;
//    cur->right_->visit(a, i);
//}

////depth-first search
//
//int* subset::DFS(){
//
//    return root->DFS();
//}

//int* subset::DFS() {
//
//    node* cur = root;
//    int i = 0;
//    unsigned int s = size;
//    int* a = new int[s];
//    cur->visit(a, &i);
//    return a;
//}
//




