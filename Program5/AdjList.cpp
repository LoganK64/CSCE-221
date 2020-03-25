//
// Created by sirlo on 11/25/2019.
//

#include "AdjList.h"
AdjList::AdjList()
{
    items = new vector<item*>;
}

AdjList::~AdjList()
{

}

void AdjList::addV(int v)
{
    item* s = new item;
    s->index = items->size();
    s->value = v;
    s->next = nullptr;
    items->push_back(s);
}

void AdjList::addE(int begin, int end)
{
    item* curr = items->at(begin);
    while(curr->next!=nullptr)
        curr = curr->next;
    item* n = new item;
    n->next = nullptr;
    n->value = items->at(end)->value;
    n->index = end;
    curr->next = n;
}

void AdjList::removeV(int v)
{
    item* toDel = items->at(v);
    item* temp;
    while(toDel->next!=nullptr)
    {
        temp = toDel;
        toDel = toDel->next;
        delete temp;
    }
    items->erase(items->begin()+v);
}

void AdjList::removeE(int begin, int end)
{
    item* curr = items->at(begin);
    while(curr->next->index!=end)
    {
        curr = curr->next;
    }
    curr->next = curr->next->next;
}

bool AdjList::checkE(int begin,int end)
{
    item* curr = items->at(begin);
    while(curr!=nullptr)
    {
        if(curr->index == end)
            return true;
        curr = curr->next;
    }
    return false;
}

void AdjList::getAllE(int v)
{
    item* curr = items->at(v)->next;
    while(curr->next != nullptr)
    {
        cout << "(" << v << "," << curr->index<< ");";
        curr = curr->next;
    }
    cout << "(" <<  v << "," << curr->index << ")" << endl;
}

int AdjList::size()
{
    return items->size();
}

void AdjList::DFSHelper(int pos, bool visited[])
{
    visited[pos] = true;
    item* curr = items->at(pos);
    while(curr!=nullptr)
    {
        if (!visited[curr->index])
            DFSHelper(curr->index, visited);
        curr = curr->next;
    }
}

vector<int> AdjList::DFS(int start) {
    bool *visited = new bool[items->size()];
    for (int i = 0; i < items->size(); i++)
        visited[i] = false;
    DFSHelper(start, visited);
    vector<int> ret;
    for (int i = 0; i < items->size(); i++)
    {
        if (visited[i])
            ret.push_back(i);
    }
    return ret;
}

vector<int> AdjList::BFS(int s)
{
    bool* visited = new bool[items->size()];
    for (int i = 0; i < items->size(); i++)
        visited[i] = false;
    vector<int> q;
    vector<int> ret;
    visited[s] = true;
    q.push_back(s);
    while(!q.empty())
    {
        s = q.front();
        ret.push_back(s);
        q.erase(q.begin());

        item* curr = items->at(s);
        while(curr!=nullptr)
        {
            if (!visited[curr->index]) {
                visited[curr->index] = true;
                q.push_back(curr->index);
            }
            curr = curr->next;
        }
    }
    return ret;
}