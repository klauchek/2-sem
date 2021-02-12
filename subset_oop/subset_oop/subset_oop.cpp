#include <iostream>
#include <random>
#include <chrono>
#include <climits>

using namespace std;

//binary search tree
class subset
{

public:

    subset();
    ~subset();
    
    
    void destructor();
    void insert(int key);


private:

    struct node
    {
        int key_;
        node* right_;
        node* left_;
    };

    node(node* right = nullptr, node* left = nullptr, int key)
    {
        key_ = key;
        right_ = right;
        left_ = left;
    }

    node* root;


    //find an element in the tree
    node* find(node* leaf, int k)
    {
        if (leaf == nullptr)
            return nullptr;
        if (leaf->key_ == k)
            return leaf;
        if (k < leaf->key_)
            return find(leaf->left_, k);
        else if (k > leaf->key)
            return find(leaf->right_, k);
    }

    

};

subset::subset()
{
    node* root = nullptr;
}

subset::~subset()
{
    destructor();
}



//add the element to the tree, ignore doubles
bool subset::insert(int k) {

    if (!root)
    {
        root = new node();
        return true;
    }

    if (find(*root, k) != NULL)
        return false;

    if (k < (*sn)->key)
        return insert(&(*sn)->left, k);
    else if (k > (*sn)->key)
        return insert(&(*sn)->right, k);
}

//delete the element from the tree
void del_elem(node** sn, int k) {

    if (*sn == NULL)
        return;
    if ((*sn)->left)
        del_elem(&(*sn)->left, k);
    if ((*sn)->right)
        del_elem(&(*sn)->right, k);

    if ((*sn)->left == NULL)
    {
        node* right = (*sn)->right;
        delete* sn;
        *sn = right;
    }
    else if ((*sn)->right == NULL)
    {
        node* left = (*sn)->left;
        delete* sn;
        (*sn) = left;
    }
    else
    {

        node* right = (*sn)->right;
        if (right->left == NULL)
        {
            (*sn)->key = right->key;
            (*sn)->right = right->right;
            delete right;
        }
        else
        {
            node* min_parent = right;
            while (min_parent->left->left != NULL)
            {
                min_parent = min_parent->left;
            }
            node* min = min_parent->left;
            min_parent->left = min->right;
            delete min;
        }
    }

}

//"del_elem" but for profiler
bool remove(node** sn, int k) {

    if (*sn == NULL)
        return false;
    if ((*sn)->key == k)
    {
        del_elem(&(*sn), k);
        return true;
    }
    if (k < (*sn)->key)
        return remove(&(*sn)->left, k);

    return remove(&(*sn)->right, k);

}


//number of elements in the tree
unsigned int size(node* sn) {
    unsigned int s = 0;

    if (sn == nullptr)
        return 0;

    else
        return size(sn->left) + size(sn->right) + 1;
}

//the height og the tree
unsigned int height(node* sn) {
    if (sn == NULL)
        return 0;
    return (max(height(sn->right), height(sn->left)) + 1);

}

//clear all memory used
void subset::destructor()
{
    if (leaf == nullptr);
    return;
    if (leaf->left)
        destructor(leaf->left);
    if (leaf->right)
        destructor(leaf->right);

    leaf->right = nullptr;
    leaf->left = nullptr;
    leaf = nullptr;

    delete leaf;
}

//for DFS
void visit(node* sn, int* a, int* i) {
    if (sn == NULL)
        return;

    visit(sn->left, a, i);
    a[*i] = sn->key;
    (*i)++;
    visit(sn->right, a, i);
}

//depth-first search
int* DFS(node* sn) {
    int i = 0;
    unsigned int s = size(sn);
    int* a = new int[s];
    visit(sn, a, &i);
    return a;
}




//double get_time()
//{
//    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() / 1e6;
//}
//
//int rand_uns(int min, int max)
//{
//    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
//    static std::default_random_engine e(seed);
//    std::uniform_int_distribution<int> d(min, max);
//    return d(e);
//}
//
//int main()
//{
//    int n = 1000;
//    int sum_for_O3 = 0, sum_check = 0, test_sequence_sum = 0, ongoing_sum = 0,
//        * sequent_sequence = new int[n],
//        * rand_sequence_10 = new int[n],
//        * rand_sequence_100 = new int[n],
//        * rand_sequence_n = new int[n],
//        * rand_sequence_unique = new int[n],
//        * sorted_sequence_unique = new int[n];
//    double start = 0, finish = 0, total = 0;
//    cout << std::fixed;
//    cout.precision(4);
//
//    //----------- Initialization
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        sequent_sequence[i] = i;
//        rand_sequence_10[i] = rand_uns(0, 10);
//        rand_sequence_100[i] = rand_uns(0, 100);
//        rand_sequence_n[i] = rand_uns(0, n);
//    }
//    for (int i = 0; i < n; i++)
//    {
//        rand_sequence_unique[i] = rand_uns(0, INT_MAX);
//        for (int j = 0; j < i; j++)
//            if (rand_sequence_unique[i] == rand_sequence_unique[j])
//            {
//                i--;
//                break;
//            }
//    }
//    for (int i = 0; i < n; i++)
//        sorted_sequence_unique[i] = rand_sequence_unique[i];
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < n - i - 1; j++)
//            if (sorted_sequence_unique[j] > sorted_sequence_unique[j + 1])
//            {
//                int tmp = sorted_sequence_unique[j];
//                sorted_sequence_unique[j] = sorted_sequence_unique[j + 1];
//                sorted_sequence_unique[j + 1] = tmp;
//            }
//
//
//    finish = get_time();
//
//    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
//
//    node* sn;
//    init(&sn);
//
//    //----------- Test 000 Insert of a sequent sequence
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        insert(&sn, sequent_sequence[i]);
//    }
//    finish = get_time();
//
//    if (size(sn) != n)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != n)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, wrong height !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "000 Insert of a sequent sequence: \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 001 Finding of a sequent sequence
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!find(sn, sequent_sequence[i]))
//        {
//            cout << endl << "--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
//            return 0;
//        }
//    }
//    if (find(sn, n + 1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//    if (find(sn, -1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//
//    finish = get_time();
//
//    cout << "001 Finding of a sequent sequence: \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 002 Remove of a sequent sequence
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        remove(&sn, sequent_sequence[i]);
//    }
//
//    finish = get_time();
//
//    if (size(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "002 Remove of a sequent sequence: \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 003 Insert of a random sequence (0 - 10)
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        insert(&sn, rand_sequence_10[i]);
//    }
//    finish = get_time();
//
//    auto content = DFS(sn);
//    auto size_content = size(sn);
//    for (int i = 0; i < size_content; i++)
//        cout << content[i] << " ";
//    cout << endl;
//    delete[] content;
//
//    cout << "003 Insert of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 004 Finding of a random sequence (0 - 10)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!find(sn, rand_sequence_10[i]))
//        {
//            cout << endl << "--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
//            return 0;
//        }
//    }
//    if (find(sn, n + 1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//    if (find(sn, -1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//
//    finish = get_time();
//
//    cout << "004 Finding of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 005 Remove of a random sequence (0 - 10)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        remove(&sn, rand_sequence_10[i]);
//    }
//
//    finish = get_time();
//
//    if (size(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "005 Remove of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 006 Insert of a random sequence (0 - 100)
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        insert(&sn, rand_sequence_100[i]);
//    }
//    finish = get_time();
//
//    content = DFS(sn);
//    size_content = size(sn);
//    for (int i = 0; i < size_content; i++)
//        cout << content[i] << " ";
//    cout << endl;
//    delete[] content;
//
//    cout << "006 Insert of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 007 Finding of a random sequence (0 - 100)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!find(sn, rand_sequence_100[i]))
//        {
//            cout << endl << "--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
//            return 0;
//        }
//    }
//    if (find(sn, n + 1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//    if (find(sn, -1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//
//    finish = get_time();
//
//    cout << "007 Finding of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 008 Remove of a random sequence (0 - 100)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        remove(&sn, rand_sequence_100[i]);
//    }
//
//    finish = get_time();
//
//    if (size(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "008 Remove of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 009 Insert of a random sequence (0 - n)
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        insert(&sn, rand_sequence_n[i]);
//    }
//    finish = get_time();
//
//    cout << "009 Insert of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 010 Finding of a random sequence (0 - n)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!find(sn, rand_sequence_n[i]))
//        {
//            cout << endl << "--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
//            return 0;
//        }
//    }
//    if (find(sn, n + 1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//    if (find(sn, -1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//
//    finish = get_time();
//
//    cout << "010 Finding of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 011 Remove of a random sequence (0 - n)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        remove(&sn, rand_sequence_n[i]);
//    }
//
//    finish = get_time();
//
//    if (size(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "011 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 012 Insert of an unique sequence (0 - n)
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        insert(&sn, rand_sequence_unique[i]);
//    }
//    finish = get_time();
//
//    cout << "012 Insert of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 013 Finding of an unique sequence (0 - n)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!find(sn, rand_sequence_unique[i]))
//        {
//            cout << endl << "--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
//            return 0;
//        }
//    }
//    if (find(sn, n + 1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//    if (find(sn, -1))
//    {
//        cout << endl << "--- !!! Failed find, an extra element was found !!! ---" << endl;
//        return 0;
//    }
//
//    finish = get_time();
//
//    cout << "013 Finding of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 014 Checking the searchiness of the tree
//
//    content = DFS(sn);
//    size_content = size(sn);
//
//    if (size_content != n)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
//        return 0;
//    }
//
//    for (int i = 0; i < size_content; i++)
//    {
//        if (content[i] != sorted_sequence_unique[i])
//        {
//            cout << endl << "--- !!! Failed order, DFS is supposed to sort the data !!! ---" << endl;
//            return 0;
//        }
//    }
//    delete[] content;
//
//    cout << "014 Checking the searchiness of the tree: \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//    //----------- Test 015 Remove of an unique sequence (0 - n)
//
//    start = get_time();
//
//    for (int i = 0; i < n; i++)
//    {
//        remove(&sn, sorted_sequence_unique[i]);
//    }
//
//    finish = get_time();
//
//    if (size(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
//        return 0;
//    }
//    if (height(sn) != 0)
//    {
//        cout << endl << "--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "011 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
//    total += finish - start;
//
//
//    //----------- End of tests
//    //
//    cout << "-----------" << endl << "Alltests finished, total time: \t" << total << endl;
//
//    delete[] sequent_sequence;
//    delete[] rand_sequence_10;
//    delete[] rand_sequence_100;
//    delete[] rand_sequence_n;
//    delete[] rand_sequence_unique;
//    delete[] sorted_sequence_unique;
//
//    return 0;
//}