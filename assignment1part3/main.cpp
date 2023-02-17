#include <iostream>
#include "part3.h"

int main()
{
    set<int> head;
    set<int> headTwo;
    set<int> temp;
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

    //comment out declarations above and uncomment
    //this to check that template works :)

    /*set<char> head;
    set<char> headTwo;
    set<char> temp;

    char numCheck = 'a';

    int sizeOne;
    int sizeTwo;

    head.insert('a');
    head.insert('y');
    head.insert('b');
    headTwo.insert('z');
    headTwo.insert('g');
    headTwo.insert('p');*/

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

