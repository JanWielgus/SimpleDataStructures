/**
 * @file IArray.h
 * @author Jan Wielgus
 * @brief Common interface for arrays
 * @date 2020-08-03
 * 
 */

#ifndef IARRAY_H
#define IARRAY_H

#include "IList.h"


namespace SimpleDataStructures
{
    template <class T>
    class IArray : public IList<T>
    {
    public:
        virtual ~IArray() {}

        /**
         * @brief Return pointer to the first element of the array or nullptr if array is empty.
         * This object take care about releasing the allocated memory.
         */
        virtual T* toArray() = 0;

        virtual const T* toArray() const = 0;

        /**
         * @brief Checks if array is full.
         * 
         * @return true if array is full
         */
        virtual bool isFull() const = 0;
    };
}


#endif
