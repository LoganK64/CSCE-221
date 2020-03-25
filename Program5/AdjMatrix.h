//
// Created by sirlo on 11/25/2019.
//

#ifndef CSCE_221_ADJMATRIX_H
#define CSCE_221_ADJMATRIX_H
#include <vector>
#include <iostream>
using namespace std;
class AdjMatrix
{
    private:
        vector<vector<int>>* items;

    public:
        AdjMatrix();
        ~AdjMatrix();

        void addV();
        void addE(int begin, int end);
        void removeV(int v);
        void removeE(int begin, int end);
        bool checkE(int begin, int end);
        void getAllE(int v);
        vector<int> BFS(int s);
        void DFSHelper(int s, bool visited[]);
        vector<int> DFS(int s);
};

#endif //CSCE_221_ADJMATRIX_H
