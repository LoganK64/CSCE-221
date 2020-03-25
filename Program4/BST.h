//
// Created by sirlo on 11/4/2019.
//

#ifndef CSCE_221_BST_H
#define CSCE_221_BST_H
#include <utility>
#include <iostream>
using namespace std;

template<typename K,typename V>
struct node{
    node* parent;
    node* lChild;
    node* rChild;
    pair<K,V> value;
};

template <typename K,typename V>
class BST{
private:
    int s;
public:
    BST();
    ~BST();

    int size();
    bool empty();
    node<K,V>* search(K);
    void insert(K,V);
    void BSTdelete(K);
};

template<typename K, typename V>
node<K,V>* root;

template <typename K,typename V>
BST<K,V>::BST()
{
    s = 0;
    root<K,V> = nullptr;
}

template<typename K>
bool isLess(K k1 ,K k2)
{
    return (k1<k2);
}

template<typename K>
bool isGreater(K k1 ,K k2)
{
    return (k1>k2);
}

template<typename K>
bool isEqual(K k1,K k2)
{
    return (k1==k2);
}
template <typename K,typename V>
BST<K,V>::~BST()
{

}

template <typename K,typename V>
int BST<K,V>::size()
{
    return s;
}

template <typename K,typename V>
bool BST<K,V>::empty()
{
    return (s==0);
}

template<typename K, typename V>
node<K,V>* searchHelper(K k,node<K,V>* q) //go the the left child if k < q's values, go to the right child if k >,return q if k=q's values
{
    pair <K,V> dummyPair;
    if(q->value==dummyPair)
        return q;
    if(isLess(k,q->value.first))
        return searchHelper(k,q->lChild);
    else if(isGreater(k,q->value.first))
        return searchHelper(k,q->rChild);
    return q;
}

template <typename K,typename V>
node<K,V>* BST<K,V>::search(K k)
{
    if(root<K,V> == nullptr)
        return root<K,V>;
    return searchHelper(k,root<K,V>);
}

template<typename K, typename V>
void insertHelper(K k,V v, node<K,V>* q, BST<K,V> t)
{
    node<K,V> *toAdd = new node<K,V>;
    node<K,V> *lDummy = new node<K,V>;
    pair <K, V> dummyPair;;
    lDummy->lChild = nullptr;
    lDummy->rChild = nullptr;
    lDummy->value = dummyPair;
    node<K,V> *rDummy = new node<K,V>;
    rDummy->lChild = nullptr;
    rDummy->rChild = nullptr;
    rDummy->value = dummyPair;
    toAdd->lChild = lDummy;
    toAdd->rChild = rDummy;
    pair<K,V> h;
    h.first = k;
    h.second = v;
    toAdd->value = h;
    lDummy->parent = toAdd;
    rDummy->parent = toAdd;
    node<K,V> *w = t.search(k); // find where k should be inserted.
    if (!isEqual(w->value.first,dummyPair.first)) {
        if(q!=NULL)
            insertHelper(k, v, q->lChild,t); // go deeper if need be
        return;
    }
    toAdd->parent = w->parent;
    if(isLess(k,w->parent->value.first))
        w->parent->lChild = toAdd;
    else
        w->parent->rChild = toAdd;
    w = toAdd;
}

template <typename K,typename V>
void BST<K,V>::insert(K k,V v)
{
    node<K,V> *toAdd = new node<K,V>;
    node<K,V> *lDummy = new node<K,V>;
    pair <K,V> dummyPair;;
    lDummy->lChild = nullptr;
    lDummy->rChild = nullptr;
    lDummy->value = dummyPair;
    node<K, V> *rDummy = new node<K,V>;
    rDummy->lChild = nullptr;
    rDummy->rChild = nullptr;
    rDummy->value = dummyPair;
    toAdd->lChild = lDummy;
    toAdd->rChild = rDummy;
    pair<K,V> h;
    h.first = k;
    h.second = v;
    toAdd->value = h;
    lDummy->parent = toAdd;
    rDummy->parent = toAdd;
    if (s == 0) {
        root<K, V> = toAdd;
        s++;
    }
    else
    {
        insertHelper<K,V>(k,v,root<K,V>,*this);
        s++;
    }
}

template <typename K,typename V>
void BST<K,V>::BSTdelete(K k)
{
    node<K,V>* w = search(k);
    if(w->value.first == k)
    {
        if(w->lChild->lChild == NULL)
        {
            node<K,V>* z = w->lChild;
            delete z;
            w = w->rChild;
            return;
        }
        else if(w->rChild->lChild == NULL) {
            node<K, V> *z = w->rChild;
            delete z;
            w = w->lChild;
            return;
        }
        else
        {
            node<K,V>* curr = w->rChild;
            while(curr->lChild!=NULL) //find successor node to replace removed node.
            {
                curr = curr->lChild;
            }
            node<K,V>* x = curr;
            pair<K,V> hold = x->parent->value;
            w->value = hold;
            x->parent = x->parent->rChild;
            delete x;
        }
        s--;
    }
    else
    {
        cout <<"Cannot Remove a key that is not in the tree" << endl;
    }
}
#endif //CSCE_221_BST_H
