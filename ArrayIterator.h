/**
 * @file ArrayIterator.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Concrete class for an array iterator.
 * @date 2021-04-18
 * 
 */

#ifndef ARRAYITERATOR_H
#define ARRAYITERATOR_H

#include "Iterator.h"
#include "IArray.h"


namespace SimpleDataStructures
{
    template <class T>
    class ArrayIterator : public Iterator<T>
    {
    private:
        T* nextElement = nullptr;
        size_t remainingElements = 0;
        T nullElement; // element returned when called next() when no elements were available

    public:
        explicit ArrayIterator(IArray<T>& array)
        {
            nextElement = array.toArray();
            remainingElements = array.size();
        }


        ArrayIterator(T* firstElement, size_t size)
        {
            nextElement = firstElement;
            remainingElements = size;
        }


        ArrayIterator(const ArrayIterator&) = delete;
        ArrayIterator& operator=(const ArrayIterator&) = delete;


        bool hasNext() override
        {
            return remainingElements != 0;
        }


        T& next() override
        {
            if (remainingElements == 0)
                return nullElement;

            T& elementToReturn = *nextElement;
            nextElement++;
            remainingElements--;
            return elementToReturn;
        }
    };
}


#endif
