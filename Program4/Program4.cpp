//
// Created by sirlo on 11/4/2019.
//
#include "BST.h"
#include "TFT.h"
#include <chrono>
#include <iostream>
using namespace std;

int main()
{

    BST<int,string> c;
    c.insert(10,"a");
    c.insert(9,"z");
    c.insert(11,"b");
    cout << c.search(10)->value.first << ", " << c.search(10)->value.second << endl;
    cout << c.search(11)->value.first << ", " << c.search(11)->value.second << endl;
    cout << c.search(9)->value.first << ", " << c.search(9)->value.second << endl;
    c.BSTdelete(10);
    cout << c.search(10)->value.first << ", " << c.search(10)->value.second << endl;
    c.insert(10,"a");
    cout << c.search(10)->value.first << ", " << c.search(10)->value.second << endl;



    TFT<int,string> d;
    d.insert(10,"a");
    cout << d.search(10).first << ", " << d.search(10).second << endl;
    d.insert(11,"b");
    cout << d.search(11).first << ", " << d.search(11).second << endl;
    d.insert(9,"c");
    cout << d.search(9).first << ", " << d.search(9).second << endl;
    d.insert(12,"d");
    cout << d.search(12).first << ", " << d.search(12).second << endl;
    d.TFTdelete(12);
    cout << d.search(12).first << ", " << d.search(12).second << endl;

    BST<int,int>* a = new BST<int,int>;
    TFT<int,int>* b = new TFT<int,int>;
    auto start_time = chrono::high_resolution_clock::now();
    cout << "Tests for Binary Search Tree" << endl;

    cout << "Increasing" << endl;

    for(int i = 1; i <= 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        a->insert(i,i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;


    cout <<"Delete Increasing" << endl;
    for(int i = 1; i <= 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        a->BSTdelete(i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
    delete a;
    a = new BST<int,int>;
    cout << "Decreasing" << endl;
    for(int i = 0; i < 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        a->insert(10000-i,1);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    cout <<"Delete Decreasing" << endl;
    for(int i = 0; i < 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        a->BSTdelete(10000-i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    delete a;
    a = new BST<int,int>;
    int hold[10000];
    cout << "Random" << endl;
    for(int i = 0; i < 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        hold[i] = rand()%10000+1;
        a->insert(hold[i],1);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
/*
    cout << "Delete Random" << endl;
    for(int i = 1; i <= 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        a->BSTdelete(hold[i]);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
*/
    cout << "Tests for 2-4 Tree" << endl;
    delete a;

    cout << "Increasing" << endl;
    for(int i = 1; i <= 100000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        b->insert(i,i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==10000)
            cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 100000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
/*
    cout << "Delete Increasing" << endl;
    for(int i = 1; i <= 100000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        b->TFTdelete(i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==10000)
            cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 100000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
*/
    delete b;
    b = new TFT<int,int>;
    cout << "Decreasing" << endl;
    for(int i = 0; i < 100000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        b->insert(100000-i,i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==10000)
            cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 100000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
/*
    cout << "Delete Decreasing" << endl;
    for(int i = 0; i < 100000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        b->TFTdelete(100000-i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==10000)
            cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    }
    cout << "Time for 100000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
*/
    cout << "Random" << endl;
    for(int i = 0; i < 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        hold[i] = rand()%10000+1;
        b->insert(hold[i],i);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

    cout << "Delete Random" << endl;
    for(int i = 0; i < 10000;i++)
    {
        start_time = chrono::high_resolution_clock::now();
        b->TFTdelete(hold[i]);
        if(i == 10)
            cout << "Time for 10th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==100)
            cout << "Time for 100th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
        else if(i==1000)
            cout << "Time for 1000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
    }
    cout << "Time for 10000th: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;
}