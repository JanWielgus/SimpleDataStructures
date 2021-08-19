/**
 * @file ArrayIterator.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Iterator for any array (expecially for IArray types).
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


        ArrayIterator(ArrayIterator&& toMove)
        {
            nextElement = toMove.nextElement;
            remainingElements = toMove.remainingElements;

            toMove.nextElement = nullptr;
            toMove.remainingElements = 0;
        }


        ArrayIterator& operator=(ArrayIterator&& toMove)
        {
            if (this != &toMove)
            {
                nextElement = toMove.nextElement;
                remainingElements = toMove.remainingElements;

                toMove.nextElement = nullptr;
                toMove.remainingElements = 0;
            }

            return *this;
        }


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


        void reset()
        {
            remainingElements = 0;
        }


        void reset(IArray<T>& array)
        {
            nextElement = array.toArray();
            remainingElements = array.size();
        }


        void reset(T* firstElement, size_t size)
        {
            nextElement = firstElement;
            remainingElements = size;
        }
    };
}


#endif
