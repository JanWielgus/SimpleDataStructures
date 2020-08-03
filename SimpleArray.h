/**
 * @file SimpleArray.h
 * @author Jan Wielgus
 * @brief Implementation of simple C++ library for IArray interface.
 * @date 2020-08-03
 * 
 */

#ifndef SIMPLEARRAY_H
#define SIMPLEARRAY_H

#include <IArray.h>


template <class T>
class SimpleArray : public IArray<T>
{
private:
    T* array = nullptr;
    const size_t MaxSize;
    size_t arraySize = 0; // amt of elements in the array
    T null_item; // returned when provided index is out of bounds


public:
    SimpleArray(size_t arrayMaxSize)
        : MaxSize(arrayMaxSize)
    {
        if (MaxSize > 0)
            array = new T[MaxSize];
        arraySize = 0;
    }


    // copy constructor
    SimpleArray(const SimpleArray& other)
        : MaxSize(other.MaxSize)
    {
        arraySize = other.arraySize;
        null_item = other.null_item;

        if (MaxSize > 0)
        {
            array = new T[MaxSize];
            
            for (size_t i = 0; i < arraySize; i++)
                array[i] = other.array[i];
        }
    }


    ~SimpleArray()
    {
        if (MaxSize > 0)
            delete [] array;
    }


    // overloaded assignment operator
    SimpleArray& operator=(const SimpleArray& other) = delete; // temporary deleted //TODO: this


    bool add(const T& item) override
    {
        if (isFull())
            return false;
        
        array[arraySize] = item;
        return true;
    }


    bool add(const T& item, size_t index) override
    {
        if (isFull())
            return false;
        
        // Make place for a new item
        for (size_t i = arraySize; i > index; i--)
            array[i] = array[i-1];
        
        array[index] = item;
        return true;
    }


    T& get(size_t index) override
    {
        if (index < arraySize)
            return array[index];
        return null_item;
    }


    const T& get(size_t index) const override
    {
        if (index < arraySize)
            return array[index];
        return null_item;
    }


    T& operator[](size_t index) override
    {
        return get(index);
    }


    const T& operator[](size_t index) const override
    {
        return get(index);
    }


    bool replace(size_t index, const T& newItem) override
    {
        if (index >= arraySize)
            return false;
        
        array[index] = newItem;
        return true;
    }


    size_t getSize() const override
    {
        return arraySize;
    }


    bool isFull() override
    {
        if (arraySize >= MaxSize)
            return true;
        return false;
    }


    bool isEmpty() override
    {
        if (arraySize == 0)
            return true;
        return false;
    }


    void clear() override
    {
        arraySize = 0;
    }
};


#endif
