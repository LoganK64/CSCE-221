//
// Created by sirlo on 11/25/2019.
//

#include "AdjMatrix.h"

AdjMatrix::AdjMatrix()
{
    items = new vector<vector<int>>;
}

AdjMatrix::~AdjMatrix()
{

}

void AdjMatrix::addV()
{
    vector<int> a(items->size(),0);
    items->push_back(a);
    for(int i = 0; i < items->size();i++)
        items->at(i).push_back(0);
}

void AdjMatrix::addE(int begin, int end)
{
    items->at(begin).at(end) = 1;
}

void AdjMatrix::removeV(int v)
{
    items->erase(items->begin()+v);
    for(int i = 0; i < items->size();i++)
        items->at(i).erase(items->at(i).begin()+v);
}

void AdjMatrix::removeE(int begin, int end)
{
    items->at(begin).at(end) = 0;
}

bool AdjMatrix::checkE(int begin,int end)
{
    if(items->at(begin).at(end))
        return true;
    return false;
}

void AdjMatrix::getAllE(int v)
{
        for(int j = 0; j < items->at(v).size();j++)
        {
            if(items->at(v).at(j))
                cout << "(" << v << "," << j << ");";
        }

    cout << endl;
}

vector<int> AdjMatrix::BFS(int s)
{
    bool* visited = new bool[items->size()];
    vector<int> q;
    vector<int> ret;
    q.push_back(s);

    visited[s] = true;

    int pos;
    while(!q.empty())
    {
        pos = q[0];
        ret.push_back(pos);
        q.erase(q.begin());

        for(int i = 0; i < items->size();i++)
        {
            if(items->at(pos).at(i) == 1 && !visited[i])
            {
                q.push_back(i);
                visited[i] = true;
            }
        }

    }
    return ret;
}

void AdjMatrix::DFSHelper(int s, bool *visited)
{
    visited[s] = true;
    for(int i = 0; i < items->size();i++)
    {
        if(items->at(s).at(i)==1 && !visited[i])
            DFSHelper(i,visited);
    }
}

vector<int> AdjMatrix::DFS(int s)
{
    bool* visited = new bool[items->size()];
    for (int i = 0; i < items->size(); i++)
        visited[i] = false;
    DFSHelper(s,visited);
    vector<int> ret;
    for (int i = 0; i < items->size(); i++)
    {
        if (visited[i])
            ret.push_back(i);
    }
    return ret;
}