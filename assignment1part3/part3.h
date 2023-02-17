#pragma once

#include <cmath>
#include <cctype>
#include <iostream>

using namespace std;

template<class T>
class set{
public:
    set();
    ~set();

    bool insert(T numIn);
    void remove(T item);
    bool find(T item);
    void deleteList();
    void display();
    int size();
    bool subset(set<T> lTwo);
    bool equality(set<T> lTwo);
    set<T> setUnion(set<T> lTwo);
    set<T> intersection(set<T> lTwo);
    set<T> setDifference(set<T> lTwo);
    set<T> symmetricDifference(set<T> lTwo);

private:
    struct node{
        T num;
        node* next;
    };
    node* headptr;

};

template<class T>
set<T>::set()
{
    headptr = nullptr;
}

template<class T>
set<T>::~set()
{
    /*node* temp;

    while( headptr != nullptr )
    {
        temp = headptr;
        headptr = temp->next;
        delete temp;
    }*/

    //leaving this commented out and deleting the lists
    //at the end of main so that there is no memory leak

    //for some reason, the deconstructor gets called after
    //every function and kills the lists that i still need
}

template<class T>
bool set<T>::insert(T numIn)
{

    node* prev;
    node* new_num = new(node);

    prev = headptr;
    new_num->num = numIn;
    new_num->next = nullptr;

    if(headptr == nullptr)
    {
        headptr = new_num;
        return true;
    }

    while(prev->next != nullptr)
    {
        if(prev->num == numIn)
        {
            cout << "Number already in list" << endl;
            return false;
        }
        prev = prev->next;
    }

    prev->next = new_num;
    return true;


}

template<class T>
void set<T>::remove(T item)
{
    node* curr = headptr;
    node* prev = headptr;
    while(curr->num != item && curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
    }

    if(curr == nullptr)
    {
        cout << "Number is not in the list" << endl;
    }

    else if(curr == headptr)
    {
        headptr = curr->next;
    }

    else
    {
        prev->next = curr->next;
        delete curr;
    }

}

template<class T>
bool set<T>::find(T item)
{
    node* temp = headptr;
    while(temp != nullptr && temp->num != item)
    {
        temp = temp->next;
    }

    if(temp == nullptr)
    {
        return false;
    }

    else
    {
        return true;
    }
}

template<class T>
void set<T>::deleteList()
{
    node* temp = headptr;

    while(headptr != nullptr)
    {
        temp = headptr;
        headptr = temp->next;
        delete temp;
    }
}

template<class T>
void set<T>::display()
{
    node* temp = headptr;
    cout << "{";
    while(temp != nullptr)
    {
        if(temp->next == nullptr)
        {
            cout << temp->num;
            temp = temp->next;
        }
        else
        {
            cout << temp->num << ", ";
            temp = temp->next;
        }

    }
    cout << "}";
}

template<class T>
int set<T>::size()
{
    node* temp = headptr;
    int count = 0;
    while(temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

template<class T>
bool set<T>::subset(set<T> lTwo)
{
    node* temp = headptr;
    node* tempTwo = lTwo.headptr;
    bool found = false;


    while(temp != nullptr) {
        tempTwo = lTwo.headptr;

        while (!found && tempTwo != nullptr) {
            if (temp->num == tempTwo->num) {
                found = true;
            }
            tempTwo = tempTwo->next;
        }

        if (!found)
        {

            return false;
        }

        temp = temp->next;

    }

    return true;
}

template<class T>
bool set<T>::equality(set<T> lTwo)
{
    bool sub = subset(lTwo);

    if(size() == lTwo.size() && sub)
    {
        return true;
    }

    return false;
}

template<class T>
set<T> set<T>::setUnion(set<T> lTwo)
{
    set<T> outHead;
    node* temp = headptr;
    node* tempTwo = lTwo.headptr;

    while(temp != nullptr)
    {
        outHead.insert(temp->num);
        temp = temp->next;
    }

    while(tempTwo != nullptr)
    {
        if(!outHead.find(tempTwo->num))
        {
            outHead.insert(tempTwo->num);
        }
        tempTwo = tempTwo->next;
    }

    return outHead;
}

template<class T>
set<T> set<T>::intersection(set<T> lTwo)
{
    set<T> outHead;
    node* temp = headptr;
    node* tempTwo = lTwo.headptr;

    while(temp != nullptr)
    {
        if(lTwo.find(temp->num))
        {
            outHead.insert(temp->num);
        }

        temp = temp->next;
    }

    return outHead;
}

template<class T>
set<T> set<T>::setDifference(set<T> lTwo)
{
    set<T> outHead;
    node* temp = headptr;
    node* tempTwo = lTwo.headptr;

    while(temp != nullptr)
    {
        if(!lTwo.find(temp->num))
        {
            outHead.insert(temp->num);
        }
        temp = temp->next;
    }

    return outHead;
}

template<class T>
set<T> set<T>::symmetricDifference(set<T> lTwo)
{
    set<T> outHead;
    node* temp = headptr;
    node* tempTwo = lTwo.headptr;

    while(temp != nullptr)
    {
        if(!lTwo.find(temp->num))
        {
            outHead.insert(temp->num);
        }
        temp = temp->next;
    }

    while(tempTwo != nullptr)
    {
        if(!find(tempTwo->num))
        {
            outHead.insert(tempTwo->num);
        }
        tempTwo = tempTwo->next;
    }

    return outHead;
}
