/**
 * @file GrowingArray.h
 * @author Jan Wielgus
 * @brief Array without fixed size.
 * Size is increased by one every time when full and new element is added.
 * @date 2020-08-03
 * 
 */

#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H

#include <Array.h>


template <class T>
class GrowingArray : public Array<T>
{
private:
    using Array<T>::array;
    using Array<T>::MaxSize;
    using Array<T>::arraySize;
    using Array<T>::null_item;


public:
    GrowingArray()
    {
    }


    GrowingArray(size_t initialSize)
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
    GrowingArray(const GrowingArray& other)
    {
        ensureCapacity(other.arraySize);
        arraySize = other.arraySize;
        null_item = other.null_item;

        for (size_t i = 0; i < arraySize; i++)
            array[i] = other.array[i];
    }


    virtual ~GrowingArray() {}


    /**
     * @brief Overloaded assignment operator.
     * Size of the new array is only the amount of data inside the copied array.
     * 
     * @param other 
     * @return GrowingArray& 
     */
    GrowingArray& operator=(const GrowingArray& other)
    {
        if (this != &other)
        {
            if (MaxSize != other.arraySize)
            {
                delete [] array;
                array = new T[other.arraySize];
                MaxSize = other.arraySize;
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


    void isFull() const override
    {
        return false;
    }


    /**
     * @brief Remove all data and free the allocated memory.
     */
    void clear() override
    {
        if (MaxSize > 0)
            delete [] array;
        array = nullptr;
        MaxSize = 0;
        arraySize = 0;
    }


    /**
     * @brief Make array to have at least provided size.
     * 
     * @param minimumSize Minimum size of array to have
     */
    void ensureCapacity(size_t minimumSize)
    {
        if (minimumSize <= MaxSize)
            return;
        
        if (MaxSize == 0)
            array = new T[minimumSize];
        else
        {
            T* biggerArray = new T[minimumSize];

            for (size_t i = 0; i < arraySize; i++)
                biggerArray[i] = array[i];
            
            delete [] array;
            array = biggerArray;
        }

        MaxSize = minimumSize;
    }
};


#endif
