//
// Created by sirlo on 11/25/2019.
//

#ifndef CSCE_221_ADJLIST_H
#define CSCE_221_ADJLIST_H
#include <vector>
#include <iostream>
using namespace std;

struct item
{
    int index;
    int value;
    item* next;
};

class AdjList
{
    private:
        vector<item*>* items;

    public:
        AdjList();
        ~AdjList();

        void addV(int v);
        void addE(int begin, int end);
        void removeV(int v);
        void removeE(int begin, int end);
        bool checkE(int begin, int end);
        void getAllE(int v);
        int size();
        void DFSHelper( int pos, bool visited[]);
        vector<int> DFS(int start);
        vector<int> BFS(int start);
};



#endif //CSCE_221_ADJLIST_H
