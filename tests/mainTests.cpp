#include <iostream>
#include <cstdlib>
#include "../LinkedList.h"
#include "../GrowingArray.h"
#include "../ListIterator.h"

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
    ListIterator<T> iter(list);
    int counter = 0;
    while (iter.hasNext())
        cout << counter++ << ". " << iter.next() << endl;
}


template <class T>
void performTests(string header);

// Testing functions:
template <class T>
void clearMethodTest();
template <class T>
void firstListTest();
template <class T>
void copyingTests();
template <class T>
void elementFindTests();



int main()
{
    cout << "Negative exit code indicate failure of any test" << endl;
    cout << "Absolute value of that code is number of assertion in a test" << endl;

    performTests<LinkedList<int>>("Linked list tests");
    performTests<GrowingArray<int>>("Growing array tests");

    cout << endl << ">> SUCCESS, end of testing" << endl;

    return 0;
}




template <class Test>
void performSingleTest(Test test, string testName)
{
    cout << "Performing: " << testName << " ... ";
    resetAssertionCounter();
    test();
    cout << "passed" << endl;
}

template <class T>
void performTests(string header)
{
    cout << endl << ">> " << header << ":" << endl;

    performSingleTest(clearMethodTest<T>, "clearMethodTest");
    performSingleTest(firstListTest<T>, "firstListTest");
    performSingleTest(copyingTests<T>, "copyingTests");
    performSingleTest(elementFindTests<T>, "elementFindTests");
    // other tests...
}





template <class T>
void clearMethodTest()
{
    T testList;

    assertEquals(true, testList.isEmpty());
    assertEquals<size_t>(0, testList.size());

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);

    testList.clear();

    assertEquals(true, testList.isEmpty());
    assertEquals<size_t>(0, testList.size());
}


template <class T>
void firstListTest()
{
    T testList;

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

    testList.remove(0);
    testList.remove(0);
    testList.remove(0);

    assertEquals(true, testList.isEmpty());

    for (int i = 0; i < 100; i++)
        testList.add(i, 0);

    assertEquals<size_t>(100, testList.size());
    assertEquals(0, testList[99]);
    assertEquals(99, testList.get(0));
}



template <class T>
void copyingTests()
{
    T testList;

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);

    T copiedList(testList);

    assertEquals(testList.size(), copiedList.size());
    for (int i=0; i < testList.size(); i++)
        assertEquals(testList.get(i), copiedList.get(i));
    ListIterator testListIter(testList);
    ListIterator copiedListIter(copiedList);
    while (testListIter.hasNext())
        assertEquals(testListIter.next(), copiedListIter.next());


    // -- assignment tests --
    
    testList.clear();
    copiedList.clear();

    testList.add(5);
    testList.add(6);
    testList.add(7);
    testList.add(8);
    testList.add(9);

    copiedList = testList;

    assertEquals(testList.size(), copiedList.size());
    for (int i=0; i < testList.size(); i++)
        assertEquals(testList.get(i), copiedList.get(i));
    testListIter.reset(testList);
    copiedListIter.reset(copiedList);
    while (testListIter.hasNext())
        assertEquals(testListIter.next(), copiedListIter.next());
}



template <class T>
void elementFindTests()
{
    T testList;

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
}

