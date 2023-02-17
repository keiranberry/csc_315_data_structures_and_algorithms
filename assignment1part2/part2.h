#pragma once

#include <cmath>
#include <cctype>
#include <iostream>

using namespace std;

class set{
public:
    set();
    ~set();

    bool insert(int numIn);
    void remove(int item);
    bool find(int item);
    void deleteList();
    void display();
    int size();
    bool subset(set lTwo);
    bool equality(set lTwo);
    set setUnion(set lTwo);
    set intersection(set lTwo);
    set setDifference(set lTwo);
    set symmetricDifference(set lTwo);

private:
    struct node{
        int num;
        node* next;
    };
    node* headptr;

};