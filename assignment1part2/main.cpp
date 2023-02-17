#include <iostream>
#include "part2.h"

int main()
{
    set head;
    set headTwo;
    set temp;
    int numCheck = 5;
    int sizeOne;
    int sizeTwo;
    head.insert(10);
    head.insert(34);
    head.insert(4);
    head.insert(7);
    head.insert(8);
    headTwo.insert(3);
    headTwo.insert(5);
    headTwo.insert(11);
    headTwo.insert(8);

    sizeOne = head.size();
    sizeTwo = headTwo.size();

    cout << "A: ";
    head.display();
    cout << endl << "B: ";
    headTwo.display();
    cout << endl;

    if(head.find(numCheck))
    {
        cout << numCheck << " is a member of A" << endl;
    }

    else
    {
        cout << numCheck << " is not a member of A" << endl;
    }

    if(headTwo.find(numCheck))
    {
        cout << numCheck << " is a member of B" << endl;
    }

    else
    {
        cout << numCheck << " is not a member of B" << endl;
    }

    cout << "Size of A is " << sizeOne << endl;
    cout << "Size of B is " << sizeTwo << endl;

    if(sizeOne == sizeTwo)
    {
        cout << "A and B are the same size!" << endl;
    }

    else
    {
        cout << "A and B are not the same size!" << endl;
    }

    if(head.subset(headTwo))
    {
        cout << "A is a subset of B" << endl;
    }

    else
    {
        cout << "A is not a subset of B" << endl;
    }

    if(headTwo.subset(head))
    {
        cout << "B is a subset of A" << endl;
    }

    else
    {
        cout << "B is not a subset of A" << endl;
    }

    if(head.equality(headTwo))
    {
        cout << "A and B are equal" << endl;
    }

    else
    {
        cout << "A and B are not equal" << endl;
    }

    temp = head.setUnion(headTwo);

    cout << "Union of A and B: ";
    temp.display();
    cout << endl << "Intersection of A and B: ";

    temp = head.intersection(headTwo);
    temp.display();

    cout << endl << "Difference of A and B: ";
    temp = head.setDifference(headTwo);
    temp.display();

    cout << endl << "Symmetric Difference of A and B: ";
    temp = head.symmetricDifference(headTwo);
    temp.display();

    head.deleteList();
    headTwo.deleteList();

    return 0;
}

set::set()
{
    headptr = nullptr;
}

set::~set()
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

bool set::insert(int numIn)
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

void set::remove(int item)
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

bool set::find(int item)
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

void set::deleteList()
{
    node* temp = headptr;

    while(headptr != nullptr)
    {
        temp = headptr;
        headptr = temp->next;
        delete temp;
    }
}

void set::display()
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

int set::size()
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

bool set::subset(set lTwo)
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

bool set::equality(set lTwo)
{
    bool sub = subset(lTwo);

    if(size() == lTwo.size() && sub)
    {
        return true;
    }

    return false;
}

set set::setUnion(set lTwo)
{
    set outHead;
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

set set::intersection(set lTwo)
{
    set outHead;
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

set set::setDifference(set lTwo)
{
    set outHead;
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

set set::symmetricDifference(set lTwo)
{
    set outHead;
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