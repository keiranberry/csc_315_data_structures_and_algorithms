#include <iostream>
#include "part1.h"

int main() {
    node* head = nullptr;
    node* headTwo = nullptr;
    node* temp;
    int numCheck = 5;
    insert(10, head);
    insert(34, head);
    insert(4, head);
    insert(7, head);
    insert(8, head);
    insert(3, headTwo);
    insert(5, headTwo);
    insert(11, headTwo);
    insert(8, headTwo);

    cout << "A: ";
    display(head);
    cout << endl << "B: ";
    display(headTwo);
    cout << endl;

    if(find(numCheck, head))
    {
        cout << numCheck << " is a member of A" << endl;
    }

    else
    {
        cout << numCheck << " is not a member of A" << endl;
    }

    if(find(numCheck, headTwo))
    {
        cout << numCheck << " is a member of B" << endl;
    }

    else
    {
        cout << numCheck << " is not a member of B" << endl;
    }

    cout << "Size of A is " << size(head) << endl;
    cout << "Size of B is " << size(headTwo) << endl;

    if(size(head) == size(headTwo))
    {
        cout << "A and B are the same size!" << endl;
    }

    else
    {
        cout << "A and B are not the same size!" << endl;
    }

    if(subset(head, headTwo))
    {
        cout << "A is a subset of B" << endl;
    }

    else
    {
        cout << "A is not a subset of B" << endl;
    }

    if(subset(headTwo, head))
    {
        cout << "B is a subset of A" << endl;
    }

    else
    {
        cout << "B is not a subset of A" << endl;
    }

    if(equality(head, headTwo))
    {
        cout << "A and B are equal" << endl;
    }

    else
    {
        cout << "A and B are not equal" << endl;
    }

    temp = setUnion(head, headTwo);

    cout << "Union of A and B: ";
    display(temp);
    cout << endl << "Intersection of A and B: ";

    temp = intersection(head, headTwo);
    display(temp);

    cout << endl << "Difference of A and B: ";
    temp = setDifference(head, headTwo);
    display(temp);

    cout << endl << "Symmetric Difference of A and B: ";
    temp = symmetricDifference(head, headTwo);
    display(temp);

    deleteList(head);
    deleteList(headTwo);


    return 0;
}

bool insert(int numIn, node* &headptr)
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

void remove(int item, node* &headptr)
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


bool find(int item, node* headptr)
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



void deleteList(node* &headptr)
{
    node* temp = headptr;

    while(headptr != nullptr)
    {
        temp = headptr;
        headptr = temp->next;
        delete temp;
    }
}

void display(node* headptr)
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

int size(node* headptr)
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

bool subset(node* headptr, node* headptrTwo)
{
    node* temp = headptr;
    node* tempTwo = headptrTwo;
    bool found = false;

    while(temp != nullptr)
    {
        tempTwo = headptrTwo;
        while(!found && tempTwo != nullptr)
        {
            if(temp->num == tempTwo->num)
            {
                found = true;
            }
            tempTwo = tempTwo->next;
        }

        if(!found)
        {
            return false;
        }

        temp = temp->next;

    }

    return true;
}

bool equality(node* headptr, node* headptrTwo)
{
    int sizeOne = size(headptr);
    int sizeTwo = size(headptrTwo);
    bool sub = subset(headptr, headptrTwo);

    if(sizeOne == sizeTwo && sub)
    {
        return true;
    }

    return false;

}

node* setUnion(node* headptr, node* headptrTwo)
{
    node* outHead = nullptr;
    node* temp = headptr;
    node* tempTwo = headptrTwo;

    while(temp != nullptr)
    {
        insert(temp->num, outHead);
        temp = temp->next;
    }

    while(tempTwo != nullptr)
    {
        if(!find(tempTwo->num, outHead))
        {
            insert(tempTwo->num, outHead);
        }
        tempTwo = tempTwo->next;
    }

    return outHead;
}

node* intersection(node* headptr, node* headptrTwo)
{
    node* outHead = nullptr;
    node* temp = headptr;
    node* tempTwo = headptrTwo;

    while(temp != nullptr)
    {
        if(find(temp->num, headptrTwo))
        {
            insert(temp->num, outHead);
        }

        temp = temp->next;
    }

    return outHead;
}

node* setDifference(node* headptr, node* headptrTwo)
{
    node* outHead = nullptr;
    node* temp = headptr;
    node* tempTwo = headptrTwo;

    while(temp != nullptr)
    {
        if(!find(temp->num, headptrTwo))
        {
            insert(temp->num, outHead);
        }
        temp = temp->next;
    }

    return outHead;
}

node* symmetricDifference(node* headptr, node* headptrTwo)
{
    node* outHead = nullptr;
    node* temp = headptr;
    node* tempTwo = headptrTwo;

    while(temp != nullptr)
    {
        if(!find(temp->num, headptrTwo))
        {
            insert(temp->num, outHead);
        }
        temp = temp->next;
    }

    while(tempTwo != nullptr)
    {
        if(!find(tempTwo->num, headptr))
        {
            insert(tempTwo->num, outHead);
        }
        tempTwo = tempTwo->next;
    }

    return outHead;
}