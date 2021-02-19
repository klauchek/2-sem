#ifndef __SUBSET_H__
#define __SUBSET_H__

#include <iostream>
#include <random>
#include <chrono>
#include <climits>


using std::cout;
using std::cin;
using std::max;
using std::endl;

class subset
{

private:
    //с private функцией внешний код работать не сможет -> 
    //функции из презенташки не должны быть private
    struct node
    {
        int key_;
        node* right_;
        node* left_;
        node* parent_;
        unsigned int height = 0;


        node(int key, node* right = nullptr, node* left = nullptr, node* parent = nullptr)
        {
            key_ = key;
            right_ = right;
            left_ = left;
            parent_ = parent;
        }

        ////find an element in the tree
        //node* find(int key);
        //bool insert(int key);
        //void del_elem(int key);
        //bool remove(int key);
        //void destructor();
        ////int* DFS();
        void correct_height()
        ///*unsigned int get_height();*/
        //
    };

    node* root;
    size_t size; 

public:

    subset(int key);
    ~subset();


bool find(int key);
bool insert(int key);
bool del_elem(int key);
bool remove(int key);
void destructor();
int* DFS();
void visit(int* a, int* i);
//void correct_height();
unsigned int get_height();
unsigned int get_size();



    
};

#endif