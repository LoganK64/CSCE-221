//
// Created by sirlo on 10/18/2019.
//

#ifndef _BSTMAP_
#define _BSTMAP_
using namespace std;
#include <utility>

template<typename K,typename V>
struct node{
    node* parent;
    node* lChild;
    node* rChild;
    pair<K,V> value;
};

template <typename K,typename V>
class BSTMap{
    private:
        int s;
    public:
        BSTMap();
        ~BSTMap();

        int size();
        bool empty();
        node<K,V>* find(K);
        void put(K,V);
        void erase(K);
};

#include <iostream>



template<typename K,typename V>
node<K,V>* root;

template<typename K,typename V>
BSTMap<K,V>::BSTMap()
{
    s = 0;
    root<K,V> = nullptr;
}

template<typename K,typename V>
BSTMap<K,V>::~BSTMap()
{

}

template<typename K,typename V>
int BSTMap<K,V>::size()
{
    return s;
}

template<typename K,typename V>
bool BSTMap<K,V>::empty()
{
    return (s==0);
}

template<typename K,typename V>
node<K,V>* findHelper(K k,node<K,V>* q)
{
    pair <K, V> dummyPair;
    if(q->value == dummyPair)
        return q;
    if(k<q->value.first)
        return findHelper(k,q->lChild);
    else if(k>q->value.first)
        return findHelper(k,q->rChild);
    return q;
}

template<typename V> inline
node<string,V>* findHelper(string k,node<string,V>* q)
{
    pair <string, V> dummyPair;
    if(q->value.first.compare(dummyPair.first)==0)
        return q;
    if(k.compare(q->value.first)<0)
        return findHelper(k,q->lChild);
    else if(k.compare(q->value.first)>0)
        return findHelper(k,q->rChild);
    return q;
}

template<typename K,typename V>
node<K,V>* BSTMap<K,V>::find(K k)
{
    if(root<K,V>!=NULL)
        return findHelper(k,root<K,V>);
    return root<K,V>;
}

template<typename K,typename V>
void putHelper(K k, V v, node<K,V> *q,BSTMap<K,V> m)
{
    node<K,V> *toAdd = new node<K,V>;
    node<K,V> *lDummy = new node<K,V>;
    pair <K, V> dummyPair;;
    lDummy->lChild = NULL;
    lDummy->rChild = NULL;
    lDummy->value = dummyPair;
    node<K,V> *rDummy = new node<K,V>;
    rDummy->lChild = NULL;
    rDummy->rChild = NULL;
    rDummy->value = dummyPair;
    toAdd->lChild = lDummy;
    toAdd->rChild = rDummy;
    pair<K,V> h;
    h.first = k;
    h.second = v;
    toAdd->value = h;
    lDummy->parent = toAdd;
    rDummy->parent = toAdd;
    node<K,V> *w = m.find(k);
    if (w->value.first != dummyPair.first) {
        putHelper(k, v, q->lChild,m);
        return;
    }
    toAdd->parent = w->parent;
    if(k<w->parent->value.first)
        w->parent->lChild = toAdd;
    else
        w->parent->rChild = toAdd;
    w = toAdd;
}

template<typename V>
void putHelper(string k, V v, node<string,V> *q,BSTMap<string,V> m)
{
    node<string,V> *toAdd = new node<string,V>;
    node<string,V> *lDummy = new node<string,V>;
    pair <string, V> dummyPair;;
    lDummy->lChild = NULL;
    lDummy->rChild = NULL;
    lDummy->value = dummyPair;
    node<string,V> *rDummy = new node<string,V>;
    rDummy->lChild = NULL;
    rDummy->rChild = NULL;
    rDummy->value = dummyPair;
    toAdd->lChild = lDummy;
    toAdd->rChild = rDummy;
    pair<string,V> h;
    h.first = k;
    h.second = v;
    toAdd->value = h;
    lDummy->parent = toAdd;
    rDummy->parent = toAdd;
    node<string,V> *w = m.find(k);
    if (w->value.first != dummyPair.first) {
        putHelper(k, v, q->lChild,m);
        return;
    }
    toAdd->parent = w->parent;
    if(k.compare(w->parent->value.first)<0)
        w->parent->lChild = toAdd;
    else
        w->parent->rChild = toAdd;
    w = toAdd;
}

template<typename K,typename V>
void BSTMap<K,V>::put(K k ,V v)
{
    node<K,V> *toAdd = new node<K,V>;
    node<K,V> *lDummy = new node<K,V>;
    pair <K,V> dummyPair;;
    lDummy->lChild = NULL;
    lDummy->rChild = NULL;
    lDummy->value = dummyPair;
    node<K, V> *rDummy = new node<K,V>;
    rDummy->lChild = NULL;
    rDummy->rChild = NULL;
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
        putHelper<K,V>(k,v,root<K,V>,*this);
        s++;
    }
}

template<typename K,typename V>
void BSTMap<K,V>::erase(K k)
{
    node<K,V>* w = find(k);
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
            while(curr->lChild!=NULL)
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
        cout <<"Cannot Remove a key that is not in the map" << endl;
    }
}
#endif //_BSTMAP_
