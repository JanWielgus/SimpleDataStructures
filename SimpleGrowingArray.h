/**
 * @file SimpleGrowingArray.h
 * @author Jan Wielgus
 * @brief Array without fixed size.
 * Size is increased by one every time when full and new element is added.
 * @date 2020-08-03
 * 
 */

#ifndef SIMPLEGROWINGARRAY_H
#define SIMPLEGROWINGARRAY_H

#include <IArray.h>

// FIXME: This class can be inherited from SimpleArray. Now some code is duplicated !!!


template <class T>
class SimpleGrowingArray : public IArray<T>
{
private:
    T* array = nullptr;
    size_t maxSize = 0; // size of allocated data
    size_t arraySize = 0; // amt of items in the array
    T null_item; // returned when provided index is out of bounds


public:
    SimpleGrowingArray()
    {
        array = nullptr;
        maxSize = 0;
        arraySize = 0;
    }


    SimpleGrowingArray(size_t initialSize)
    {
        ensureCapacity(initialSize);
        arraySize = 0;
    }


    /**
     * @brief Copy constructor. Create new object and copy there data
     * from the other object.
     * Size of the new object array is only the amount of data in other object array
     * (regardless of allocated data by other object).
     */
    SimpleGrowingArray(const SimpleGrowingArray& other)
    {
        ensureCapacity(other.arraySize);
        arraySize = other.arraySize;
        null_item = other.null_item;

        for (size_t i = 0; i < arraySize; i++)
            array[i] = other.array[i];
    }


    ~SimpleGrowingArray()
    {
        if (maxSize > 0)
            delete [] array;
    }


    /**
     * @brief Overloaded assignment operator.
     * Size of the new array is only the amount of data inside the copied array.
     * 
     * @param other 
     * @return SimpleGrowingArray& 
     */
    SimpleGrowingArray& operator=(const SimpleGrowingArray& other)
    {
        if (this != &other)
        {
            if (maxSize != other.arraySize)
            {
                delete [] array;
                array = new T[other.arraySize];
                maxSize = other.arraySize;
                arraySize = other.arraySize;
            }

            for (size_t i = 0; i < arraySize; i++)
                array[i] = other.array[i];
        }

        return *this;
    }


    bool add(const T& item) override
    {
        ensureCapacity(arraySize + 1);

        array[arraySize] = item;
        arraySize++;

        return true;
    }


    bool add(const T& item, size_t index) override
    {
        ensureCapacity(arraySize + 1);

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


    bool isFull() const override
    {
        return false;
    }


    bool isEmpty() const override
    {
        return arraySize == 0;
    }


    /**
     * @brief Remove all data and free the allocated memory.
     */
    void clear() override
    {
        if (maxSize > 0)
            delete [] array;
        array = nullptr;
        maxSize = 0;
        arraySize = 0;
    }


    /**
     * @brief Make array to have at least provided size.
     * 
     * @param minimumSize Minimum size of array to have
     */
    void ensureCapacity(size_t minimumSize)
    {
        if (minimumSize <= maxSize)
            return;
        
        if (maxSize == 0)
            array = new T[minimumSize];
        else
        {
            T* biggerArray = new T[minimumSize];

            for (size_t i = 0; i < arraySize; i++)
                biggerArray[i] = array[i];
            
            delete [] array;
            array = biggerArray;
        }

        maxSize = minimumSize;
    }
};


#endif
