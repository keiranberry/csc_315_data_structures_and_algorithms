#pragma once

#include <cmath>
#include <cctype>
#include <iostream>

using namespace std;

struct node
{
    int num;
    node* next;
};

bool insert(int numIn, node* &headptr);
void remove(int item, node* &headptr);
bool find(int item, node* headptr);
void deleteList(node* &headptr);
void display(node* headptr);
int size(node* headptr);
bool subset(node* headptr, node* headptrTwo);
bool equality(node* headptr, node* headptrTwo);
node* setUnion(node* headptr, node* headptrTwo);
node* intersection(node* headptr, node* headptrTwo);
node* setDifference(node* headptr, node* headptrTwo);
node* symmetricDifference(node* headptr, node* headptrTwo);


