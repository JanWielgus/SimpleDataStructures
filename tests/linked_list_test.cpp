// XXX: IMPORTANT THING: virtual methods are slower, but not when I have virtual in interface class and non-virtual methods in concrete classes. So don't use virtual in concrete classes, in abstract is OK.

#include <iostream>
#include <cstdlib>
#include "LinkedList.h"
#include "GrowingArray.h"

using namespace std;
using namespace SimpleDataStructures;


static int assertionNumber = 1;

template <class T>
void assertEquals(T expected, T actual)
{
    if (expected != actual)
    {
        cout << "TEST NUMBER " << assertionNumber << " FAILED" << endl;
        cout << "Expected: " << expected << endl;
        cout << "Actual: " << actual << endl;
        exit(-assertionNumber);
    }
    assertionNumber++;
}

void resetAssertionCounter()
{
    assertionNumber = 1;
}

template <class T>
void showListUsingIterator(IList<T>& list)
{
    Iterator<T>* iter = list.iterator();
    int counter = 0;
    while (iter->hasNext())
        cout << counter++ << ". " << iter->next() << endl;;
}


void firstListTest(IList<int>& testList);
void removingUsingIteratorTest(LinkedList<int>& testList);
void copyingTests(LinkedList<int>& testList);
void elementFindTests(IList<int>& testList);



int main()
{
    cout << "Testing linked list" << endl;
    cout << "Negative exit code indicate failure of any test" << endl;
    cout << "Absolute value of that code is index of performed test" << endl;
    cout << endl;


    LinkedList<int> testList;


    testList.clear();
    firstListTest(testList);

    testList.clear();
    removingUsingIteratorTest(testList);

    testList.clear();
    copyingTests(testList);

    testList.clear();
    elementFindTests(testList);


    cout << "SUCCESS, end of testing" << endl;


    return 0;
}




void firstListTest(IList<int>& testList)
{
    cout << "First list test" << endl;
    resetAssertionCounter();

    assertEquals(true, testList.isEmpty());
    assertEquals<size_t>(0, testList.size());
    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);
    assertEquals<size_t>(5, testList.size());
    assertEquals(8, testList.get(3));
    testList.remove(3);
    assertEquals(9, testList.get(3));
    testList.add(66, 2);
    assertEquals(6, testList.get(1));
    assertEquals(66, testList.get(2));
    assertEquals(7, testList.get(3));
    assertEquals(9, testList.get(4));
    assertEquals<size_t>(5, testList.size());

    //cout << endl;
    //showListUsingIterator(testList);

    //cout << endl;
    //for (int i = 0; i < testList.size(); i++)
        //cout << "elem: " << testList.get(i) << endl;


    assertEquals(false, testList.isEmpty());
    testList.remove(4);
    assertEquals(7, testList.get(3));
    assertEquals<size_t>(4, testList.size());
    testList.remove(0);
    assertEquals(6, testList.get(0));
    assertEquals(66, testList.get(1));
    assertEquals(7, testList.get(2));
    testList.clear();
    assertEquals<size_t>(0, testList.size());
    testList.add(123, 0);
    assertEquals(true, testList.add(124, 1));
    assertEquals(true, testList.add(125, 2));
    assertEquals(false, testList.add(126, 4));
    assertEquals(false, testList.remove(3));

    //cout << endl;
    //showListUsingIterator(testList);

    testList.remove(1);

    //cout << endl;
    //showListUsingIterator(testList);

    cout << "passed" << endl;
}



void removingUsingIteratorTest(LinkedList<int>& testList)
{
    cout << "Removing using iterator test" << endl;
    resetAssertionCounter();

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);

    RemovingIterator<int>* removIter = testList.removingIterator();

    assertEquals(5, removIter->next());
    assertEquals(6, removIter->next());
    assertEquals(true, removIter->remove());
    assertEquals(false, removIter->remove());
    assertEquals(7, removIter->next());
    assertEquals(true, removIter->remove());
    assertEquals(8, removIter->next());
    assertEquals(9, removIter->next());
    assertEquals(false, removIter->hasNext());


    assertEquals(5, testList.get(0));
    assertEquals(8, testList.get(1));
    assertEquals(9, testList.get(2));

    assertEquals(3, (int)testList.size());


    Iterator<int>* iter = testList.iterator();
    assertEquals(5, iter->next());
    assertEquals(8, iter->next());
    assertEquals(9, iter->next());


    removIter = testList.removingIterator();
    assertEquals(5, removIter->next());
    assertEquals(8, removIter->next());
    assertEquals(9, removIter->next());
    
    cout << "passed" << endl;
}



void copyingTests(LinkedList<int>& testList)
{
    cout << "Copying tests" << endl;
    resetAssertionCounter();

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);


    LinkedList<int> copiedList(testList);

    assertEquals(testList.size(), copiedList.size());
    for (int i=0; i < testList.size(); i++)
        assertEquals(testList.get(i), copiedList.get(i));
    auto testListIter = testList.iterator();
    auto copiedListIter = copiedList.iterator();
    while (testListIter->hasNext())
        assertEquals(testListIter->next(), copiedListIter->next());


    cout << "passed" << endl;
}



void elementFindTests(IList<int>& testList)
{
    cout << "Element find tests" << endl;
    resetAssertionCounter();

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);


    assertEquals(true, testList.find(0) == npos);
    assertEquals(true, testList.find(9) == 4);
    assertEquals(true, testList.find(9, 4) == 4);
    assertEquals(true, testList.find(5, 1) == npos);

    assertEquals(true, testList.contains(8));
    assertEquals(false, testList.contains(4));


    cout << "passed" << endl;
}

