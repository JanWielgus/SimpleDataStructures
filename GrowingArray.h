/**
 * @file GrowingArray.h
 * @author Jan Wielgus
 * @brief Array without fixed size.
 * Size is increased (by one) every time when full
 * and new element is added and size is not sufficient.
 * @date 2020-08-03
 * 
 */

#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H

#include "IArray.h"
#include "ArrayIterator.h"


namespace SimpleDataStructures
{
    /**
     * @brief Array without fixed size.
     * Size is increased (by one) every time when full
     * and new element is added and size is not sufficient.
     * Size can also be increased manually at any time.
     * @tparam T Array type.
     */
    template <class T>
    class GrowingArray : public IArray<T>
    {
        T* array = nullptr;
        size_t AllocatedSize = 0;
        size_t arraySize = 0; // amt of elements in the array

        T null_item; // returned when provided index is out of bounds


    public:
        /**
         * @brief Construct a new empty GrowingArray object.
         */
        GrowingArray()
        {
            array = nullptr;
            AllocatedSize = 0;
            arraySize = 0;
        }


        /**
         * @brief Construct a new GrowingArray object and allocate
         * internal array of specified size.
         * @param initialSize Size of the allocated internal array.
         */
        explicit GrowingArray(size_t initialSize)
        {
            ensureCapacity(initialSize, false);
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
            ensureCapacity(other.arraySize, false);

            for (size_t i = 0; i < other.arraySize; i++)
                array[i] = other.array[i];

            arraySize = other.arraySize;
        }


        /**
         * @brief Move constructor.
         * @param toMove GrowingArray to move.
         */
        GrowingArray(GrowingArray&& toMove)
        {
            array = toMove.array;
            AllocatedSize = toMove.AllocatedSize;
            arraySize = toMove.arraySize;

            toMove.array = nullptr;
            toMove.AllocatedSize = 0;
            toMove.arraySize = 0;
        }


        ~GrowingArray()
        {
            delete[] array;
        }


        /**
         * @brief Overloaded assignment operator.
         * Size of the new array is only the amount of data inside the copied array.
         */
        GrowingArray& operator=(const GrowingArray& other)
        {
            if (this != &other)
            {
                ensureCapacity(other.arraySize, false);

                for (size_t i = 0; i < other.arraySize; i++)
                    array[i] = other.array[i];
                
                arraySize = other.arraySize;
            }

            return *this;
        }


        GrowingArray& operator=(GrowingArray&& toMove)
        {
            if (this != &toMove)
            {
                delete[] array;

                array = toMove.array;
                AllocatedSize = toMove.AllocatedSize;
                arraySize = toMove.arraySize;

                toMove.array = nullptr;
                toMove.AllocatedSize = 0;
                toMove.arraySize = 0;
            }

            return *this;
        }


        bool add(const T& item) override
        {
            ensureCapacity(arraySize + 1); // TODO: should be always by one??

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
            return index < arraySize ? array[index] : null_item;
        }


        const T& operator[](size_t index) const override
        {
            return index < arraySize ? array[index] : null_item;
        }


        T* toArray() override
        {
            return array;
        }


        bool replace(const T& newItem, size_t index) override
        {
            if (index >= arraySize)
                return false;
            
            array[index] = newItem;
            return true;
        }


        size_t find(const T& itemToFind, size_t startIndex = 0) const override
        {
            for (size_t i = startIndex; i < arraySize; i++)
                if (array[i] == itemToFind)
                    return i;
            
            return npos;
        }


        bool contains(const T& itemToFind) const override
        {
            return find(itemToFind) != npos;
        }


        size_t size() const override
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
            delete [] array;
            array = nullptr;
            AllocatedSize = 0;
            arraySize = 0;
        }




        /**
         * @brief Check size of the allocated array inside.
         * @return Size of the allocated array.
         */
        size_t capacity() const
        {
            return AllocatedSize;
        }


        /**
         * @brief Increase size of allocated array if needed, that
         * adding elements within that size will be in O(1) time.
         * Data will remain unchanged.
         * @param minimumSize Minimum size that array should have.
         */
        void ensureCapacity(size_t minimumSize)
        {
            ensureCapacity(minimumSize, true);
        }


    private:
        /**
         * @brief Make array to have at least provided size.
         * If need to allocate new bigger array, keepData flag
         * decide if should copy old data to the new array or not.
         * This method don't shrink the allocated space.
         * @param minimumSize Minimum size that array should have.
         * @param keepData Flag. If true: after reallocation all
         * previous data will be copied. If false: in such situation
         * prev data won't be copied. 
         */
        void ensureCapacity(size_t minimumSize, bool keepData)
        {
            if (minimumSize <= AllocatedSize)
                return;
            
            if (array == nullptr)
                array = new T[minimumSize];
            else
            {
                T* biggerArray = new T[minimumSize];

                if (keepData)
                    for (size_t i = 0; i < arraySize; i++)
                        biggerArray[i] = array[i];
                
                delete[] array;
                array = biggerArray;
            }

            AllocatedSize = minimumSize;
        }
    };
}


#endif
