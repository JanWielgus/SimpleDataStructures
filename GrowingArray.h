/**
 * @file GrowingArray.h
 * @author Jan Wielgus
 * @brief Array without fixed size.
 * Size is increased (by one) every time when full and new element is added and size is not sufficient.
 * @date 2020-08-03
 * 
 */

#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H

#include "IArray.h"


template <class T>
class GrowingArray;


template <class T>
class GrowingArrayIterator : public Iterator<T>
{
private:
    T* currentElement = nullptr;
    size_t remainingElements = 0;
    T nullElement; // element returned when called next() when any elements were available

public:
    GrowingArrayIterator() {}
    GrowingArrayIterator(const GrowingArrayIterator& other) = delete;

    bool hasNext() override
    {
        if (remainingElements == 0)
            return false;
        return true;
    }


    T& next() override
    {
        if (remainingElements == 0)
            return nullElement;
        else
        {
            T& elementToReturn = *currentElement;
            currentElement++;
            remainingElements--;
            return elementToReturn;
        }
    }

    friend class GrowingArray<T>;
};



template <class T>
class GrowingArray : public IArray<T>
{
private:
    T* array = nullptr;
    size_t MaxSize;
    size_t arraySize = 0; // amt of elements in the array
    T null_item; // returned when provided index is out of bounds
    GrowingArrayIterator<T> iteratorInstance;


public:
    GrowingArray()
    {
        array = nullptr;
        MaxSize = 0;
        arraySize = 0;
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


    ~GrowingArray()
    {
        if (MaxSize > 0)
            delete [] array;
    }


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

        resetIterator();

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
        // prevent from making unassigned gap
        if (index > arraySize)
            return false;

        ensureCapacity(arraySize + 1);

        // Make place for a new item
        for (size_t i = arraySize; i > index; i--)
            array[i] = array[i-1];

        array[index] = item;
        arraySize++;
        return true;
    }


    bool remove(size_t index) override
    {
        if (index >= arraySize)
            return false;
        
        for (size_t i = index + 1; i < arraySize; i++)
            array[i - 1] = array[i];
        
        arraySize--;
        resetIterator(); // probably could be replaced with just decreasing remainingElements in iterator instance
        return true;
        // TODO: add decreasing size of the allocated space
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


    Iterator<T>* getIterator() override
    {
        iteratorInstance.currentElement = array;
        iteratorInstance.remainingElements = arraySize;
        return &iteratorInstance;
    }


    bool replace(const T& newItem, size_t index) override
    {
        if (index >= arraySize)
            return false;
        
        array[index] = newItem;
        return true;
    }


    bool contain(const T& itemToFind) const override
    {
        for (int i=0; i < arraySize; i++)
            if (array[i] == itemToFind)
                return true;
        
        return false;
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
        if (MaxSize > 0)
            delete [] array;
        array = nullptr;
        MaxSize = 0;
        arraySize = 0;
        resetIterator();
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

        resetIterator();
    }



private:
    /**
     * @brief Makes that next call of hasNext() method of iterator will return false.
     * This method is used after any modifications to outdate the iterator.
     */
    void resetIterator()
    {
        iteratorInstance.remainingElements = 0;
    }
};


#endif
