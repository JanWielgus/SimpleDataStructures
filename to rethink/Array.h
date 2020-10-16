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
class Array : public IArray<T>
{
protected:
    T* array = nullptr;
    size_t MaxSize;
    size_t arraySize = 0; // amt of elements in the array
    T null_item; // returned when provided index is out of bounds


    // protected constructor for classes that derive from this class
    Array()
    {
        array = nullptr;
        MaxSize = 0;
        arraySize = 0;
    }


public:
    Array(size_t arrayMaxSize)
        : MaxSize(arrayMaxSize)
    {
        if (MaxSize > 0)
            array = new T[MaxSize];
        arraySize = 0;
    }


    // copy constructor
    Array(const SimpleArray& other)
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


    virtual ~Array()
    {
        if (MaxSize > 0)
            delete [] array;
    }


    // overloaded assignment operator
    Array& operator=(const Array& other) = delete; // TODO: think if this should be deleted


    virtual bool add(const T& item) override
    {
        if (isFull())
            return false;
        
        array[arraySize] = item;
        arraySize++;
        return true;
    }


    virtual bool add(const T& item, size_t index) override
    {
        if (isFull())
            return false;
        
        // Make place for a new item
        for (size_t i = arraySize; i > index; i--)
            array[i] = array[i-1];
        
        array[index] = item;
        arraySize++;
        return true;
    }


    virtual bool remove(size_t index) override
    {
        return false; // TODO: implement remove method
    }


    T& get(size_t index) override
    {
        return index < arraySize ? array[index] : null_item;
    }


    const T& get(size_t index) const override
    {
        return index < arraySize ? array[index] : null_item;
    }


    T& operator[](size_t index) override
    {
        return get(index);
    }


    const T& operator[](size_t index) const override
    {
        return get(index);
    }


    T* toArray() override
    {
        return array;
    }


    virtual bool replace(size_t index, const T& newItem) override
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


    virtual bool isFull() const override
    {
        return arraySize >= MaxSize;
    }


    virtual bool isEmpty() const override
    {
        return arraySize == 0;
    }


    virtual void clear() override
    {
        arraySize = 0;
    }
};


#endif
