//
// Created by sirlo on 10/21/2019.
//

#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include "HashMap.hpp"
#include "BSTMap.hpp"
using namespace std;

class charDistribution
{
    private:
        vector<int> *items;
        int total;
    public:
        charDistribution()
        {
            items = new vector<int>(27,0);
            total = 0;
        }

        void occurs(char c)
        {
            if(97 <= int(tolower(c)) <= 122)
            {
                char t = tolower(c);
                (*items)[int(t) - 97]++;
                total++;
            }
            else if(c==' ') {
                (*items)[26]++;
                total++;
            }
        }

        char getRandomChar()
        {
            int randNum = rand() % total + 1;
            int t = 0;
            int count = 0;
            while(t<randNum)
            {
                t+=(*items)[count];
                count++;
            }
            if(count<27)
                return char(count+96);
            else
                return ' ';
        }
};

int main()
{
    /*
    HashMap<int,string> h(11);
    if(h.empty()) {
        h.put(24, "test");
        pair<int, string> s = h.find(24);
        cout << s.first << ", " << s.second << endl;
        h.put(25, "test2");
        h.put(27, "test3");
        cout << h.find(25).first << "," << h.find(25).second << endl;
        cout << h.size() << endl;
        h.erase(25);
        cout << h.size() << endl;
        h.put(35, "test4");
        cout << h.find(35).first << "," << h.find(35).second << endl;
        h.erase(35);
    }
    BSTMap<int,string> z;
    if(z.empty())
    {
        z.put(24, "test");
        pair<int, string> m = z.find(24)->value;
        cout << m.first << ", " << m.second << endl;
        z.put(23, "test1");
        z.put(25, "test2");
        z.put(26, "test3");
        cout << z.find(23)->value.first << "," << z.find(23)->value.second << endl;
        cout << z.size() << endl;
        z.erase(24);
        cout << z.size() << endl;
        cout << z.find(25)->value.first << "," << z.find(25)->value.second << endl;
    }
    */

    charDistribution* h = new charDistribution();
    fstream test("Program3/merchant.txt", istream::in);
    string text;
    getline(test,text,'\0');
    string curr;
    int w = 0;
    cout << "Please Enter a Window Size: ";
    cin >> w;


    auto start_time = chrono::high_resolution_clock::now();


    HashMap<string,charDistribution>* m = new HashMap<string,charDistribution>(109);
    for (int i = 0; i+w < text.length()-1; i++)
    {
        curr = text.substr(i,w);
        pair<string,charDistribution> z = m->find(curr);
        if(z.first.compare(curr)==0)
        {
            z.second.occurs(text[i+w]);
        }
        else
        {
            charDistribution n;
            n.occurs(text[i+w]);
            m->put(curr,n);
        }
        //cout << curr << endl;
    }
    cout << "done" << endl;
    cout << "Now creating output" << endl;
    ofstream output;
    output.open("Program3/TheRealCase.txt");

    //Creation of output
    //Since I was unsure of exactly what was desired from the output,
    //I followed the directions, but replaced length with the length
    //of the input text and tried to recreate the input text using
    //the character distributions
    curr = text.substr(0,w);
    output << curr;
    for (int i = 0; i+w < text.length()-1; i++)
    {
        curr = text.substr(i, w);
        output << m->find(curr).second.getRandomChar();
    }
    cout << "done" << endl;


    /*
    BSTMap<string,charDistribution>* m = new BSTMap<string,charDistribution>();
    charDistribution n;
    n.occurs(text[w]);
    m->put(text.substr(0,w),n);
    for (int i = 1; i+w < text.length()-1; i++)
    {
        curr = text.substr(i,w);
        pair<string,charDistribution> z = m->find(curr)->value;
        if(z.first.compare(curr)==0)
        {
            z.second.occurs(text[i+w]);
        }
        else
        {
            charDistribution n;
            n.occurs(text[i+w]);
            m->put(curr,n);
        }
        //cout << curr << endl;
    }

    cout << "done" << endl;
    cout << "Now creating output" << endl;
    ofstream output;
    output.open("Program3/TheRealCase.txt");


    //Creation of output
    //Since I was unsure of exactly what was desired from the output,
    //I followed the directions, but replaced length with the length
    //of the input text and tried to recreate the input text using
    //the character distributions
    curr = text.substr(0,w);
    output << curr;
    for (int i = 0; i+w < text.length()-1; i++)
    {
        curr = text.substr(i, w);
        output << m->find(curr)->value.second.getRandomChar();
    }
    cout << "done" << endl;
    */
    cout << "Time taken to create output: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count() << endl;

 }
