#include <iostream>
#include <chrono>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T>
class PQHeapTree
{
    struct treeNode{ //store items in treeNodes
        treeNode *parent;
        treeNode *lChild;
        treeNode *rChild;
        T key;
    };
    private:
        int s; //size
        treeNode *root; //root of tree
        vector<treeNode*> nodes; //vector storing all nodes in the tree
    public:
        PQHeapTree()
        {
            s = 0;
            root = NULL;
        }

        ~PQHeapTree()
        {
            for(int i = 0;i<nodes.size();i++)
            {
                delete nodes[i];
            }
        }

        void insert(T e)
        {
            if(root==NULL) //if tree empty create new node, assign it to root and add to nodes
            {
                root = new treeNode;
                root->parent = NULL;
                root->lChild = NULL;
                root->rChild = NULL;
                root->key = e;
                nodes.push_back(root);
            }
            else
            {
                //create new node with no children and parent of next suitable insert location
                treeNode *temp = new treeNode;
                temp->parent = nodes[(s-1)/2];
                temp->lChild = NULL;
                temp->rChild = NULL;
                temp->key = e;
                nodes.push_back(temp);
                if((s-1) % 2 == 0)//decide whether to make new node left or right child
                {
                    nodes[(s-1)/2]->lChild = temp;
                }
                else
                {
                    nodes[(s-1)/2]->rChild = temp;
                }
                //bubble up new node if necessary
                while(temp != root && temp->parent->key > temp->key)
                {
                    T t = temp->key;
                    temp->key = temp->parent->key;
                    temp->parent->key = t;
                    temp = temp->parent;
                }
            }
            s++;
        }

        treeNode* min() //returns minimum value in tree
        {
            if(s>=1)
                return root;
            else{
                try
                {
                    throw 0;
                }
                catch(int e)
                {
                    cout << "Cannot call min() on an empty heap" << endl;

                }
            }
        }

        void removeMin() //removes node and fixes heap order after
        {
            //if more nodes than just root/empty
            if(s>1) {
                //swap value of last node and root
                root->key = nodes[s - 1]->key;
                if (nodes[s - 1]->key == nodes[s - 1]->parent->lChild->key)
                    nodes[s - 1]->parent->lChild = NULL;
                else
                    nodes[s - 1]->parent->rChild = NULL;
                nodes.pop_back(); //remove last node
                treeNode *temp = root;
                //bubble down new root node to proper position
                while (temp->lChild != NULL || temp->rChild != NULL) {
                    T t = temp->key;
                    //complicated series of if/elses to make sure that there isn't a segfault
                    //probably should have been a switch case statement
                    if (temp->lChild != NULL && temp->rChild != NULL) {
                        if (temp->key > temp->rChild->key && temp->key > temp->lChild->key) {
                            if (temp->lChild->key < temp->rChild->key) {
                                temp->key = temp->lChild->key;
                                temp->lChild->key = t;
                                temp = temp->lChild;
                            } else {
                                temp->key = temp->rChild->key;
                                temp->rChild->key = t;
                                temp = temp->rChild;
                            }
                        } else if (temp->key > temp->rChild->key) { //check whether to swap with left/right child or not
                            temp->key = temp->rChild->key;
                            temp->rChild->key = t;
                            temp = temp->rChild;
                        } else if (temp->key > temp->lChild->key) {
                            temp->key = temp->lChild->key;
                            temp->lChild->key = t;
                            temp = temp->lChild;
                        } else
                            break;
                    } else if (temp->lChild != NULL) { //check if left child can be swapped
                        if (temp->key > temp->lChild->key) {
                            temp->key = temp->lChild->key;
                            temp->lChild->key = t;
                            temp = temp->lChild;
                        } else
                            break;
                    } else if (temp->rChild != NULL) { //check if right child can be swapped
                        if (temp->key > temp->rChild->key) {
                            temp->key = temp->rChild->key;
                            temp->rChild->key = t;
                            temp = temp->rChild;
                        } else
                            break;
                    } else
                        break;
                }
            } else //only runs if only root
                root = NULL;
            s--;
        }



        int size() //returns size of tree
        {
            return s;
        }

        bool empty() //returns true iff empty
        {
            return (s==0);
        }

        void preOrder(treeNode* p) //used to check if heap order property was held
        {
            cout << p->key << "\t";
            if(p->lChild != NULL)
                preOrder(p->lChild);
            if(p->rChild != NULL)
                preOrder(p->rChild);
        }
};

template <typename T>
class PQHeapArray
{
    private:
        int s; // size
        T* items; //array for storing heap items
    public:
        PQHeapArray(int n)
        {
            s = 0;
            items = new T[n];
        }

        ~PQHeapArray()
        {
            delete items;
        }

        void insert(T e) //insert e and correct heap order
        {
            items[s] = e; //add new item to end of the array
            int i = s;
            while(items[i] < items[(i-1)/2] && i > 0) //while the heap order is not being held bubble up the new item
            {
                T temp = items[i];
                items[i] = items[(i-1)/2];
                items[(i-1)/2] = temp;
                i = (i-1)/2;
            }
            s++;
        }

        T min() //return first index of the array
        {
            if(s>=1)
                return items[0];
            else
            {
                try
                {
                    throw 0;
                }
                catch(int e)
                {
                    cout << "Cannot call min() on an empty heap" << endl;

                }
            }
        }

        void removeMin() //swaps front value and back value then fixes order
        {
            if(s>=1) {
                items[0] = items[s - 1];
                items[s - 1] = INT8_MAX; //value  that is obviously incorrect
                int i = 0;
                while ((items[i] > items[2 * i + 1] || items[i] > items[2 * i + 2]) && 2*i+2 < s) { //while order not being held
                    T temp = items[i];
                    if (items[2 * i + 1] < items[2 * i + 2]) {//swap new root with smaller child
                        items[i] = items[2 * i + 1];
                        items[2 * i + 1] = temp;
                        i = 2 * i + 1;
                    } else {
                        items[i] = items[2 * i + 2];
                        items[2 * i + 2] = temp;
                        i = 2 * i + 2;
                    }
                }
            } else
                items[0] = 0;
            s--;
        }

        int size() //returns size of heap
        {
            return s;
        }

        bool empty() //returns true iff heap is empty
        {
            return (s==0);
        }

        PQHeapArray<T>* heapify(T arr[],int n,int curr) //turn a portion of an array into a heap
        {
            int small = curr;
            int left = 2*curr+1;
            int right = 2*curr+2;
            if(right < n && arr[right] < arr[small]) //check to see if left or right child is smaller
                small = right;
            if(left < n && arr[left] < arr[small])
                small = left;

            if(small!=curr) //recursively fix small heap if one child is smaller
            {
                T temp = arr[curr];
                arr[curr] = arr[small];
                arr[small] = temp;
                heapify(arr,n,small);
            }

            PQHeapArray<T>* ret = new PQHeapArray<T>(2*n); //used to return a heap after heapifying
            ret->s = n; //is currently the reason that heapify sort is running in n^2 time
            for(int i = 0;i<n;i++) //TA could not figure out how to help fix and ran out of time
            {
                ret->items[i] = arr[i];
            }
            return ret;
        }
};

template <typename T>
void heapSortT(T arr[],int n) //sort arr using PQHeapTree
{
    PQHeapTree<T>* s = new PQHeapTree<T>();
    for(int i = 0; i < n; i++) //insert all values into heap which orders on its own
        s->insert(arr[i]);
    int count = 0;
    while(!s->empty()) //pop off all values in least to greatest order
    {
        arr[count] = s->min()->key;
        s->removeMin();
        count++;
    }
}

template <typename T>
void heapSortA(T arr[],int n) //sort arr using PQHeapArray
{
    PQHeapArray<T>* s = new PQHeapArray<T>(2*n);
    for(int i = 0; i < n; i++) //insert all values into heap which orders on its own
        s->insert(arr[i]);
    int count = 0;
    while(!s->empty()) //pop off all values in least to greatest order
    {
        arr[count] = s->min();
        s->removeMin();
        count++;
    }
}

template <typename T>
void heapSortH(T arr[],int n) //sort arr using PQHeapArray Heapify
{
    PQHeapArray<T>* s = new PQHeapArray<T>(2*n);
    for(int i = n/2-1;i>=0;i--) //sort the array by repeatedly calling heapify
        s = s->heapify(arr,n,i);
    int count = 0;
    while(!s->empty()) //remove values which are now in sorted order
    {
        arr[count] = s->min();
        s->removeMin();
        count++;
    }
}

int main()
{

    //test all functions of PQHeapTree to verify that they work
    PQHeapTree<int>* T = new PQHeapTree<int>();
    if(T->empty())
        cout<< "empty works" << endl;
    T->insert(7);
    cout << T->min()->key << endl;
    T->insert(4);
    cout << T->min()->key << endl;
    cout << T->size() << endl;
    T->removeMin();
    cout << T->min()->key << endl;
    cout << T->size() << endl;
    T->insert(3);
    cout << T->min()->key << endl;
    T->insert(18);
    cout << T->min()->key << endl;
    T->insert(5);
    cout << T->min()->key << endl;
    T->insert(6);
    cout << T->min()->key << endl;
    T->preOrder(T->min());
    cout << endl;
    while(!T->empty()) //make sure that the heap order property put them into min->max order
    {
        cout << T->min()->key  << endl;
        T->removeMin();
    }

    //test all functions of PQHeapArray to verify that they work
    PQHeapArray<int>* A = new PQHeapArray<int>(100);
    if(A->empty())
        cout << "empty works" << endl;
    A->insert(7);
    cout << A->min() << endl;
    A->insert(4);
    cout << A->min() << endl;
    cout << A->size() << endl;
    A->removeMin();
    cout << A->min() << endl;
    cout << A->size() << endl;
    A->insert(3);
    cout << A->min() << endl;
    A->insert(18);
    cout << A->min() << endl;
    A->insert(5);
    cout << A->min() << endl;
    A->insert(6);
    cout << A->min() << endl;
    cout << endl;
    while(!A->empty()) //make sure that the heap order property put them into min->max order
    {
        cout << A->min()  << endl;
        A->removeMin();
    }
    int test[] = {7,3,4,2,1,0,6,5};
    for(int i = 3;i>=0;i--) //test to make sure that heapify works
        A = A->heapify(test,8,i);
    while(!A->empty())
    {
        cout << A->min()  << endl;
        A->removeMin();
    }

    int test2[] = {0,4,5,3,6,7,1,2};
    for(int i = 0;i<8;i++) //test to make sure heapSort for Arrays works
        cout << test2[i] << "\t";
    cout << endl;
    heapSortA(test2,8);
    for(int i = 0;i<8;i++)
        cout << test2[i] << "\t";
    cout << endl;

    int test3[] = {0,4,5,3,6,7,1,2};
    for(int i = 0;i<8;i++) //test to make sure that heapsort for Trees works
        cout << test3[i] << "\t";
    cout << endl;
    heapSortT(test3,8);
    for(int i = 0;i<8;i++)
        cout << test3[i] << "\t";
    cout << endl;

    int test4[] = {0,4,5,3,6,7,1,2};
    for(int i = 0;i<8;i++) //test to make sure that heapsort with heapify works
        cout << test4[i] << "\t";
    cout << endl;
    heapSortH(test4,8);
    for(int i = 0;i<8;i++)
        cout << test4[i] << "\t";
    cout << endl;


    //all tests used to find runtime of algorithms
    //commented out all not currently in use so as to save time and memory
    //tested increasing, decreasing, and random
    //test in use denoted by printing to screen first
    int elems = 10;
    auto start_time = chrono::high_resolution_clock::now();


    /*
    cout << "--------PQSortT Increasing--------" << endl;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortT(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }


    cout << "--------PQSortA Increasing--------" << endl;
    elems = 10;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortA(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }


    cout << "--------PQSortH Increasing--------" << endl;
    elems = 10;
    while(elems <= 10000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortH(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }


    cout << "--------PQSortT Decreasing--------" << endl;
    elems = 10;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = elems; i > 0;i--)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortT(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }

    cout << "--------PQSortA Decreasing--------" << endl;
    elems = 10;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = elems; i > 0;i--)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortA(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }

    cout << "--------PQSortTH Decreasing------" << endl;
    elems = 10;
    while(elems <= 10000) {
        int *s = new int[elems];
        for(int i = elems; i > 0;i--)
            s[i] = i;
        start_time = chrono::high_resolution_clock::now();
        heapSortH(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }

    cout << "--------PQSortT Random--------" << endl;
    elems = 10;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = int(rand()*100);
        start_time = chrono::high_resolution_clock::now();
        heapSortT(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }

    cout << "--------PQSortA Random--------" << endl;
    elems = 10;
    while(elems <= 10000000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = int(rand()*100);
        start_time = chrono::high_resolution_clock::now();
        heapSortA(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }
    */
    cout << "--------PQSortH Random--------" << endl;
    elems = 10;
    while(elems <= 10000) {
        int *s = new int[elems];
        for(int i = 0; i < elems;i++)
            s[i] = int(rand()*100);
        start_time = chrono::high_resolution_clock::now();
        heapSortH(s,elems);
        cout << "Time Used for " << elems << " elements:" << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        elems*=10;
        delete s;
    }

}
