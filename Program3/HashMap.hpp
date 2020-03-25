//
// Created by sirlo on 10/18/2019.
//

#ifndef _HASHMAP_
#define _HASHMAP_
//using namespace std;
#include <utility>
#include <cstring>

template <typename K,typename V>
class HashMap{
    private:
        int N;
        int n;

    public:
        HashMap(int);
        ~HashMap();

        int size();
        bool empty();
        std::pair<K,V> find(K);
        void put(K,V);
        void erase(K);
};

#include <iostream>
using namespace std;

template<typename K,typename V>
struct item{ //hold information in order to use separate chaining
    pair<K,V> value; //key,value pair
    item* next; //pointer to next value in chain
};


template<typename K>
bool isEqual(K k,K k2)
{
    return (k==k2);
}

template<typename K> inline
bool isEqual(string x, K y)
{
    return (x.compare("")==0);
}

template<typename K>
bool isEqual(int k,K k2)
{
    return (k==k2);
}


template<typename K,typename V>
item<K,V>* bucket; //array used to hold the values of the hashmap (hash table)

template<typename K,typename V>
HashMap<K,V>::HashMap(int g) //initialize variables
{
    n = 0;
    N = g;
    bucket<K,V> = new item<K,V>[N];
    for(int i = 0;i<N;i++)
    {
        item<K,V> h;
        pair<K,V> u;
        h.value = u;
        h.next = NULL;
        bucket<K,V>[i] = h;
    }
}

template<typename K,typename V>
HashMap<K,V>::~HashMap()
{

}

template<typename K>
int h(K k,int g) //hash function
{
    return k % g;
}

template<> inline
int h(string k,int g)
{
    int total = 0;
    for(int i = 0;i<k.length();i++)
    {
        total+=int(k[i]);
    }
    return total%g;
}

template<typename K,typename V>
int HashMap<K,V>::size() //returns number of entries in map
{
    return n;
}

template<typename K,typename V>
bool HashMap<K,V>::empty() //returns true if and only if there are not entries in the map
{
    return (n==0);
}

template<typename K,typename V>
pair<K,V> HashMap<K,V>::find(K k) //returns key,value pair associated with the key entered, returns NULL if key not found
{
    item<K,V>* current = &bucket<K,V>[h<K>(k,N)]; //go to the correct key location found with hash function
    while(current!=NULL) //check each value stored in the bucket
    {
        if(current->value.first == k)
            return current->value; //return if found
        current = current->next;
    }
    pair<K,V> h;
    return h;
}

template<typename K,typename V>
void HashMap<K,V>::put(K k,V v)
{
    int index = h(k,N);
    if(isEqual(bucket<K,V>[index].value.first,NULL))
    {
        item<K,V>* h = new item<K,V>;
        h->value = pair<K,V>(k,v);
        h->next = NULL;
        bucket<K,V>[index] = *h;
    }
    else if(isEqual(find(k).first,NULL))
    {
        item<K,V>* h = new item<K,V>;
        h->value = pair<K,V>(k,v);
        h->next = NULL;
        item<K,V>* curr = &(bucket<K,V>[index]);
        while(curr->next!=NULL)
        {
            curr = curr->next;
        }
        curr->next = h;
    }
    else
    {
        item<K,V>* current = &(bucket<K,V>[h<K>(k,N)]);
        while(current!=NULL)
        {
            if(current->value.first == k)
            {
                current->value.second = v;
                return;
            }
            current = current->next;
        }
    }
    n++;
}

template<typename K,typename V>
void HashMap<K,V>::erase(K k)
{
    item<K,V>* current = &bucket<K,V>[h<K>(k,N)]; //go to the correct key location found with hash function
    item<K,V>* prev = current;
    while(current!=NULL) //check each value stored in the bucket
    {
        if(current->value.first ==k)
        {
            prev->next = current->next;
            item<K,V> h;
            pair<K,V> u;
            h.value = u;
            h.next = NULL;
            *current = h;
            delete current;
            n--;
            return;
        }
        prev = current;
        current = current->next;
    }
    try{
        throw 0;
    }catch(int e)
    {
        cerr << "There is no value corresponding to key " << k << " in the map";
    }
    n--;
}


#endif //_HASHMAP_
