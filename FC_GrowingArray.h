// FC_GrowingArray.h
/*
    Created:	08/04/2020
    Author:     Jan Wielgus
*/


#ifndef _FC_GROWINGARRAY_h
#define _FC_GROWINGARRAY_h

#include "arduino.h"


template <class T>
class FC_GrowingArrayClass
{
private:
    T* array;
    uint16_t size;
    T nullItem; // returns that item for example if index is out of bounds

public:
    FC_GrowingArrayClass()
    {
        size = 0;
    }


    ~FC_GrowingArrayClass()
    {
        if (size > 0)
            delete[] array;
    }


    // copy constructor
    FC_GrowingArrayClass(const FC_GrowingArrayClass& other)
    {
        size = other.size;

        // copy data
        if (size > 0)
        {
            array = new T[size];

            for (int i = 0; i < size; i++)
                array[i] = other.array[i];
        }
    }


    // overloaded assignment operator
    FC_GrowingArrayClass& operator=(const FC_GrowingArrayClass& other)
    {
        if (this != &other)// self-assignment check expected
        {
            if (other.size != size)           // storage cannot be reused
            {
                delete[] array;               // destroy storage in this
                array = new T[other.size];    // create storage in this
                size = other.size;
            }

            for (int i = 0; i < size; i++)
                array[i] = other.array[i];
        }

        return *this;
    }


    void add(T item)
    {
        // create bigger array
        T* newArray = new T[size + 1];

        // copy data
        for (int i = 0; i < size; i++)
            newArray[i] = array[i];

        // put new item on the end of new array
        newArray[size] = item;
        size++;

        // delete old array and change to the new pointer
        delete[] array;
        array = newArray;
    }


    T& get(uint16_t index)
    {
        if (index < size)
            return array[index];
        return nullItem;
    }
	
	
	const T& get(uint16_t index) const
    {
        if (index < size)
            return array[index];
        return nullItem;
    }


    T& operator[](uint16_t index)
    {
        return get(index);
    }
	
	
	const T& operator[](uint16_t index) const
    {
        return get(index);
    }


    T* getArray()
    {
        return array;
    }
	
	
	const T* getArray() const
	{
		return array;
	}


    uint16_t getSize() const
    {
        return size;
    }
};


#endif

