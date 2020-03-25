//
// Created by sirlo on 11/4/2019.
//

#ifndef CSCE_221_TFT_H
#define CSCE_221_TFT_H
#include <utility>
#include <vector>
using namespace std;



template<typename K,typename V>
struct Tnode
{
    pair<K,V> a;
    pair<K,V> b;
    pair<K,V> c;
    Tnode* n1; //left of a
    Tnode* n2; // right of a, left of b
    Tnode* n3; //right of b, left of c
    Tnode* n4; //right of c
};

template<typename K, typename V>
class TFT
{
    private:
        int s;
        Tnode<K,V>* Troot;
    public:
        TFT();
        ~TFT();

        int size();
        bool empty();
        pair<K,V> search(K);
        void insert(K,V);
        void TFTdelete(K);
};

template<typename K, typename V>
bool  TisLeaf(Tnode<K,V>* q)
{
    return (q->n1 == NULL && q->n2 == NULL && q->n3 == NULL && q->n4 == NULL);
}

template<typename K>
bool TisLess(K k1 ,K k2)
{
    return (k1<k2);
}

template<typename K>
bool TisGreater(K k1 ,K k2)
{
    return (k1>k2);
}

template<typename K>
bool TisEqual(K k1,K k2)
{
    return (k1==k2);
}

template<typename K, typename V>
int numValues(Tnode<K,V>* q)
{
    if(q==NULL)
        return 0;
    int ret = 0;
    pair<K,V> dummyPair;
    if(q->a!=dummyPair)
        ret++;
    if(q->b!=dummyPair)
        ret++;
    if(q->c!=dummyPair)
        ret++;
    return ret;
}
template<typename K, typename V>
Tnode<K,V>* Troot;

template <typename K,typename V>
TFT<K,V>::TFT()
{
    s = 0;
    Troot = nullptr;
}

template <typename K,typename V>
TFT<K,V>::~TFT()
{

}

template <typename K,typename V>
int TFT<K,V>::size()
{
    return s;
}

template <typename K,typename V>
bool TFT<K,V>::empty()
{
    return (s==0);
}

template<typename K, typename V>
pair<K,V> searchHelper(K k,Tnode<K,V>* q)
{
    pair<K,V> dummyPair;
    if(q==NULL) //check if not in tree
        return dummyPair;
    //check if any of the values are the one being looked for
    if(TisEqual(k,q->a.first))
        return q->a;
    else if(TisEqual(k,q->b.first))
        return q->b;
    else if(TisEqual(k,q->c.first))
        return q->c;
    else
    {
        //decide which branch to search
        if(q->c!=dummyPair && TisLess(q->c.first,k))
            return searchHelper(k,q->n4);
        else if(q->b!=dummyPair && TisLess(q->b.first,k))
            return searchHelper(k,q->n3);
        else if(q->a!=dummyPair && TisLess(q->a.first,k))
            return searchHelper(k,q->n2);
        else
            return searchHelper(k,q->n1);

    }
}

template <typename K,typename V>
pair<K,V> TFT<K,V>::search(K k)
{
    pair<K,V> dummyPair;
    if(s==0)
        return dummyPair;
    return searchHelper(k,Troot);
}

template <typename K,typename V>
void TFT<K,V>::insert(K k,V v)
{
    pair<K,V> dummyPair;
    pair<K,V> toAdd;
    toAdd.first = k;
    toAdd.second = v;
    if(Troot == NULL) //if node is empty then just make a new node and make it the root
    {
        pair<K,V> n;
        n.first = k;
        n.second = v;
        Tnode<K,V>* r = new Tnode<K,V>;
        r->a = n;
        r->b = r->c = dummyPair;
        r->n1 = r->n2 = r->n3 = r->n4 = nullptr;
        Troot = r;
        s++;
        return;
    }
    Tnode<K,V>* r = Troot;
    Tnode<K,V>* z = Troot;


    //find the right spot for the key in the tree and make transformations to correct the structure if need be
    while(r!=NULL)
    {
        if(r->a.first == k || r->b.first == k || r->c.first == k)
            return;
        if(numValues(r)==3)
        {
            if(numValues(z) == 1)
            {
                if(TisLess(z->a.first,r->b.first))
                {
                    z->b = r->b;
                    Tnode<K,V>* l = new Tnode<K,V>;
                    Tnode<K,V>* ri = new Tnode<K,V>;
                    l->a = r->a;
                    l->n1 = r->n1;
                    l->n2 = r->n2;
                    ri->a = r->c;
                    ri->n1 = r->n3;
                    ri->n2 = r->n4;
                    z->n2 = l;
                    z->n3 = ri;
                }
                else
                {
                    z->b = z->a;
                    z->n3 = z->n2;
                    z->a = r->b;
                    Tnode<K,V>* l = new Tnode<K,V>;
                    Tnode<K,V>* ri = new Tnode<K,V>;
                    l->a = r->a;
                    l->n1 = r->n1;
                    l->n2 = r->n2;
                    ri->a = r->c;
                    ri->n1 = r->n3;
                    ri->n2 = r->n4;
                    z->n1 = l;
                    z->n2 = ri;
                }

                delete r;
                if(TisLess(k,z->a.first))
                    r = z->n1;
                else if(TisLess(k,z->b.first))
                    r = z->n2;
                else if(TisGreater(k,z->b.first))
                    r = z->n3;
                else
                    return;
            }
            else if(numValues(z)==2)
            {
                if(TisLess(z->b.first,r->b.first))
                {
                    z->c = r->b;
                    Tnode<K,V>* l = new Tnode<K,V>;
                    Tnode<K,V>* ri = new Tnode<K,V>;
                    l->a = r->a;
                    l->n1 = r->n1;
                    l->n2 = r->n2;
                    ri->a = r->c;
                    ri->n1 = r->n3;
                    ri->n2 = r->n4;
                    z->n3 = l;
                    z->n4 = ri;
                }
                else if(TisLess(z->a,r->b))
                {
                    z->c = z->b;
                    z->n4 = z->n3;
                    z->b = r->b;
                    Tnode<K,V>* l = new Tnode<K,V>;
                    Tnode<K,V>* ri = new Tnode<K,V>;
                    l->a = r->a;
                    l->n1 = r->n1;
                    l->n2 = r->n2;
                    ri->a = r->c;
                    ri->n1 = r->n3;
                    ri->n2 = r->n4;
                    z->n2 = l;
                    z->n3 = ri;
                }
                else
                {
                    z->c = z->b;
                    z->b = z->a;
                    z->a = r->b;
                    z->n4 = z->n3;
                    z->n3 = z->n2;
                    Tnode<K,V>* l = new Tnode<K,V>;
                    Tnode<K,V>* ri = new Tnode<K,V>;
                    l->a = r->a;
                    l->n1 = r->n1;
                    l->n2 = r->n2;
                    ri->a = r->c;
                    ri->n1 = r->n3;
                    ri->n2 = r->n4;
                    z->n1 = l;
                    z->n2 = ri;
                }

                delete r;
                if(TisLess(k,z->a.first))
                    r = z->n1;
                else if(TisLess(k,z->b.first))
                    r = z->n2;
                else if(TisLess(k,z->c.first))
                    r = z->n3;
                else if(TisGreater(k,z->c.first))
                    r = z->n4;
                else
                    return;

            }
            else
            {
                Tnode<K,V>* w = new Tnode<K,V>;
                w->a = r->b;
                Tnode<K,V>* l = new Tnode<K,V>;
                Tnode<K,V>* ri = new Tnode<K,V>;
                l->a = r->a;
                l->n1 = r->n1;
                l->n2 = r->n2;
                ri->a = r->c;
                ri->n1 = r->n3;
                ri->n2 = r->n4;
                w->n1 = l;
                w->n2 = ri;
                Troot = w;
                delete r;
                z = Troot;

                if(TisLess(k,Troot->a.first))
                    r = Troot->n1;
                else if(TisGreater(k,Troot->a.first))
                    r = Troot->n2;
                else
                    return;
            }
        }

        if(TisLeaf(r))
        {
            if(numValues(r)==1)
            {
                if(TisGreater(k,r->a.first))
                {
                    r->b = toAdd;
                    s++;
                    return;
                }
                else if(TisLess(k,r->a.first))
                {
                    r->b = r->a;
                    r->a = toAdd;
                    s++;
                    return;
                }
            }
            else if(numValues(r)==2)
            {
                if(TisGreater(k,r->b.first))
                {
                    r->c = toAdd;
                    s++;
                    return;
                }
                else if(TisGreater(k,r->a.first))
                {
                    r->c = r->b;
                    r->b = toAdd;
                    s++;
                    return;
                }
                else if(TisLess(k,r->a.first))
                {
                    r->c = r->b;
                    r->b = r->a;
                    r->a = toAdd;
                    s++;
                    return;
                }
            }
        }
        else
        {
            z = r;
            if(numValues(r)==1)
            {
                if(TisLess(k,r->a.first))
                    r = r->n1;
                else
                    r = r->n2;
            }
            else if(numValues(r)==2)
            {
                if(TisLess(k,r->a.first))
                    r = r->n1;
                else if(TisLess(k,r->b.first))
                    r = r->n2;
                else
                    r = r->n3;
            }
        }
    }
}

template <typename K,typename V>
void TFT<K,V>::TFTdelete(K k)
{
    pair<K,V> dummyPair;
    if(s==0)
        return;
    Tnode<K,V>* r = Troot; //node being looked at
    Tnode<K,V>* z = Troot; //node to represent it's parent later.
    pair<K,V> item; //item being looked for
    Tnode<K,V>* n = nullptr; //node where it's held
    while(r!=NULL) //if this loop is left, k is not in the tree.
    {
        if(r == Troot && numValues(r) == 1 && numValues(r->n1)==1 && numValues(r->n2)==1)
        {
            Tnode<K,V>* right = r->n2;
            r->c = right->a;
            r->n3 = right->n1;
            r->n4 = right->n2;
            delete right;
            r->b = r->a;
            Tnode<K,V>* left = r->n1;
            r->a= left->a;
            r->n1 = left->n1;
            r->n2 = left->n2;
            delete left;

            z = Troot;
            r = Troot;
        }

        if(numValues(r)==1)
        {
            if(z->n1 == r)
            {
                if (numValues(r->n2) == 1)
                {
                    z->n2->c = z->n2->a;
                    z->n2->n4 = z->n2->n2;
                    z->n2->n3 = z->n2->n1;

                    z->n2->b = z->a;

                    z->n2->a = r->a;
                    z->n2->n1 = r->n1;
                    z->n2->n2 = r->n2;

                    delete z->n1;
                    z->a = z->b;
                    z->b = z->c;
                    z->c = dummyPair;
                    z->n1 = z->n2;
                    z->n2 = z->n3;
                    z->n3 = z->n4;
                    z->n4 = nullptr;

                    r = z->n1;
                }
                else if (numValues(z->n2) >= 2)
                {
                    r->b = z->a;
                    r->n3 = z->n2->n1;

                    z->a = z->n2->a;

                    z->n2->a = z->n2->b;
                    z->n2->b = z->n2->c;
                    z->n2->c = dummyPair;
                    z->n2->n1 = z->n2->n2;
                    z->n2->n2 = z->n2->n3;
                    z->n2->n3 = z->n2->n4;
                    z->n2->n4 = nullptr;
                }
            }
            else if(z->n2 == r)
            {
                if(numValues(z->n1)==1 && numValues(z->n3)==1)
                {
                    r->c = r->a;
                    r->n4 = r->n2;
                    r->n3 = r->n1;

                    r->b = z->a;

                    r->a = z->n1->a;
                    r->n2 = z->n1->n2;
                    r->n1 = z->n1->n1;

                    delete z->n1;
                    z->a = z->b;
                    z->b = z->c;
                    z->c = dummyPair;
                    z->n1 = z->n2;
                    z->n2 = z->n3;
                    z->n3 = z->n4;
                    z->n4 = nullptr;
                }
                else if(numValues(z->n1)<numValues(z->n2))
                {
                    r->b = z->b;
                    r->n3 = z->n3->n1;

                    z->b = z->n3->a;

                    z->n3->a = z->n3->b;
                    z->n3->b = z->n3->c;
                    z->n3->c = dummyPair;
                    z->n3->n1 = z->n3->n2;
                    z->n3->n2 = z->n3->n3;
                    z->n3->n3 = z->n3->n4;
                    z->n3->n4 = nullptr;
                }
                else
                {
                    r->b = r->a;
                    r->n3 = r->n2;
                    r->n2 = r->n1;

                    r->a = z->a;
                    if(z->n1->c==dummyPair)
                    {
                        r->n1 = z->n1->n4;
                        z->a = z->n1->c;
                        z->n1->c = dummyPair;
                        z->n1->n4 = nullptr;
                    }
                    else
                    {
                        r->n1 = z->n1->n3;
                        z->a = z->n1->b;
                        z->n1->b = dummyPair;
                        z->n1->n3 = nullptr;
                    }
                }
            }
            else if(z->n3 == r)
            {
                if(z->n4!=NULL && numValues(z->n2)==1 &&
                    numValues(z->n4)==1)
                {
                    r->b = z->c;
                    z->c = dummyPair;

                    r->c = z->n4->a;
                    r->n3 = z->n4->n1;
                    r->n4 = z->n4->n2;
                }
                else if(z->n4!=NULL &&
                        numValues(z->n4) >= numValues(z->n2))
                {
                    r->b = z->c;
                    r->n3 = z->n4->n1;

                    z->c = z->n4->a;

                    z->n4->a = z->n4->b;
                    z->n4->b = z->n4->c;
                    z->n4->c = dummyPair;
                    z->n4->n1 = z->n4->n2;
                    z->n4->n2 = z->n4->n3;
                    z->n4->n3 = z->n4->n4;
                    z->n4->n4 = nullptr;
                }
                else
                {
                    r->b = r->a;
                    r->n3 = r->n1;
                    r->n2 = r->n1;

                    r->a = z->b;
                    if(z->n2->c!=dummyPair)
                    {
                        r->n1 = z->n2->n4;
                        z->b = z->n2->c;
                        z->n2->n4 = nullptr;
                        z->n2->c = dummyPair;
                    }
                    else
                    {
                        r->n1 = z->n2->n3;
                        z->b = z->n2->b;
                        z->n2->n3 = nullptr;
                        z->n2->b = dummyPair;
                    }
                }
            }
            else if(z->n4 == r)
            {
                if(numValues(z->n3)==1)
                {
                    z->n3->b = z->c;
                    z->c = dummyPair;

                    z->n3->c = r->a;
                    z->n3->n3 = r->n1;
                    z->n3->n4 = r->n2;

                    r->a = dummyPair;
                    r->n1 = nullptr;
                    r->n2 = nullptr;
                    delete z->n4;

                    r = z->n3;
                }
                else if(numValues(z->n3)>=2)
                {
                    r->b = r->a;
                    r->n3 = r->n2;
                    r->n2 = r->n1;

                    r->a = z->c;
                    if(z->n3->c!=dummyPair)
                    {
                        r->n1 = z->n3->n4;
                        z->c = z->n3->c;
                        z->n3->n4 = nullptr;
                        z->n3->c = dummyPair;
                    }
                    else
                    {
                        r->n1 = z->n3->n3;
                        z->c = z->n3->b;
                        z->n3->n3 = nullptr;
                        z->n3->c = dummyPair;
                    }
                }
            }
        }

        if(item==dummyPair && (TisEqual(k,r->a.first) || TisEqual(k,r->b.first) || TisEqual(k,r->c.first)) && !TisLeaf(r))
        {
            z = r;
            n = r;
            if(r->c!=dummyPair && TisEqual(z->c.first,k))
            {
                item = r->c;
                r = r->n4;
            }
            else if(r->b!=dummyPair && TisEqual(z->b.first,k))
            {
                item = r->b;
                r = r->n3;
            }
            else
            {
                item = r->a;
                r = r->n2;
            }
        }
        else if((item!=dummyPair && (TisEqual(k,r->a.first) || TisEqual(k,r->b.first) || TisEqual(k,r->c.first))) ||
                ((TisEqual(k,r->a.first) || TisEqual(k,r->b.first) || TisEqual(k,r->c.first)) && TisLeaf(r)))
        {
            while(400)
            {
                if(numValues(r) >=2)
                {
                    if(r->c!=dummyPair && TisEqual(k,r->c.first))
                    {
                        r->c = dummyPair;
                    }
                    else if(r->b!=dummyPair && TisEqual(k,r->b.first))
                    {
                        r->b = r->c;
                        r->c = dummyPair;
                    }
                    else
                    {
                        r->a = r->b;
                        r->b = r->c;
                        r->c = dummyPair;
                    }
                    s--;
                    return;
                }
                else if(z->n4!=NULL && z->n4 == r)
                {
                    if(numValues(z->n3) == 1 && numValues(z->n4))
                    {
                        z->n3->b = z->c;
                        z->n3->c = r->a;
                        r->a = dummyPair;
                        delete z->n4;
                        z->n4 = nullptr;
                        z->c = dummyPair;
                        r = z->n3;
                    }
                    else
                    {
                        r->b = r->a;
                        r->a = z->c;
                        if(z->n3->c!=dummyPair)
                        {
                            z->c = z->n3->c;
                            z->n3->c = dummyPair;
                        }
                        else
                        {
                            z->c = z->n3->b;
                            z->n3->b = dummyPair;
                        }
                    }
                }
                else if(z->n3 != NULL && z->n3 == r)
                {
                    if((numValues(z->n1)==1 &&
                        numValues(z->n3)==1 && z->c == dummyPair) ||
                        (z->n4!=NULL && numValues(z->n2)==1 &&
                        numValues(z->n3)==1 && numValues(z->n4)==1))
                    {
                        r->b = z->c;
                        r->c = z->n4->a;
                        z->n4->a = dummyPair;
                        delete z->n4;
                        z->n4 = nullptr;
                        z->c = dummyPair;
                    }
                    else if(z->n4!=NULL && numValues(z->n4) >= numValues(z->n2))
                    {
                        r->b = z->c;
                        z->c = z->n4->a;
                        z->n4->a = z->n4->b;
                        z->n4->b = z->n4->c;
                        z->n4->c = dummyPair;
                    }
                    else
                    {
                        r->b = r->a;
                        r->a = z->b;
                        if(z->n2->c !=dummyPair)
                        {
                            z->b = z->n2->c;
                            z->n2->c = dummyPair;
                        }
                        else
                        {
                            z->b = z->n2->b;
                            z->n2->b = dummyPair;
                        }
                    }
                }
                else if(z->n2!=NULL && z->n2 == r)
                {
                    if(numValues(z->n1) == 1 && numValues(z->n2) == 1 && numValues(z->n3) == 1)
                    {
                        r->c = r->a;
                        r->b = z->a;
                        r->a = z->n1->a;
                        z->n1->a = dummyPair;
                        z->a = z->b;
                        z->b = z->c;
                        z->n1 = z->n2;
                        z->n2 = z->n3;
                        z->n3 = z->n4;
                        z->n4 = nullptr;
                    }
                    else if(numValues(z->n1) < numValues(z->n3))
                    {
                        r->b = z->b;
                        z->b = z->n3->a;
                        z->n3->a = z->n3->b;
                        z->n3->b = z->n3->c;
                        z->n3->c = dummyPair;
                    }
                    else
                    {
                        r->b = r->a;
                        r->a = z->a;
                        if(z->n1->c!=dummyPair)
                        {
                            z->a = z->n1->c;
                            z->n1->c = dummyPair;
                        }
                        else
                        {
                            z->a = z->n1->b;
                            z->n1->b = dummyPair;
                        }
                    }
                }
                else
                {
                    if(numValues(z->n1) == 1 && numValues(z->n2) == 1)
                    {
                        z->n2->c = z->n2->a;
                        z->n2->b = z->a;
                        z->n2->a = z->n1->a;
                        z->n1->a = dummyPair;
                        delete z->n1;
                        z->a = z->b;
                        z->b = z->c;
                        z->n1 = z->n2;
                        z->n2 = z->n3;
                        z->n3 = z->n4;
                        z->n4 = nullptr;
                        r = z->n2;
                    }
                    else
                    {
                        r->b = z->a;
                        z->a = z->n2->a;
                        z->n2->a = z->n2->b;
                        z->n2->b = z->n2->c;
                        z->n2->c = dummyPair;
                    }
                }
            }
        }
        if(item == dummyPair)
        {
            z = r;
            if(r->c !=dummyPair && TisGreater(k,r->c.first))
                r = r->n4;
            else if(r->b !=dummyPair && TisGreater(k,r->b.first))
                r = r->n3;
            else if(TisGreater(k,r->a.first))
                r = r->n2;
            else
                r = r->n1;
        }
        else
        {
            if(r->n1 == NULL)
            {
                if(n->a == item)
                {
                    n->a = r->a;
                }
                else if(n->b == item)
                {
                    n->b = r->a;
                }
                else
                {
                    n->c = r->a;
                }
                k = r->a.first;
            }
            else
            {
                z = r;
                r = r->n1;
            }
        }
    }
}
#endif //CSCE_221_TFT_H
