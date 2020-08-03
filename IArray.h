/**
 * @file IArray.h
 * @author Jan Wielgus
 * @brief Common interface for arrays
 * @version 0.1
 * @date 2020-08-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef IARRAY_H
#define IARRAY_H


template <class T>
class IArray
{
    virtual ~IArray() {}

    /**
     * @brief Adds new item to the array.
     * 
     * @param item Reference to item to be added to the array
     * @return false if item was not added (for example because array is full)
     */
    virtual bool add(const T& item) = 0;

    /**
     * @brief Adds new item to the array at the specified index.
     * Do not remove any items from the array.
     * 
     * @param item Reference to item to be added to the array
     * @param index Index where to add new item
     * (following items will be moved one place forward)
     * @return false if item was not added (for example because array is full)
     */
    virtual bool add(const T& item, size_t index) = 0;

    /**
     * @brief Returns item at the specified index.
     * 
     * @param index Index of the item to be returned
     */
    virtual T& get(size_t index) = 0;

    /**
     * @brief Returns item at the specified index.
     * 
     * @param index Index of the item to be returned
     */
    virtual const T& get(size_t index) const = 0;

    /**
     * @brief Overloaded array subscript operator.
     */
    virtual T& operator[](size_t index) = 0;

    /**
     * @brief Overloaded array subscript operator.
     */
    virtual const T& operator[](size_t index) const = 0;

    /**
     * @brief Replace item at the specified index with another item.
     * Old item is just deleted from the array.
     * 
     * @param index Index of the item to be replaced
     * @param newItem New item that will be put in the index
     * @return false if index is out of bounds or just something bad happened
     */
    virtual bool replace(size_t index, const T& newItem) = 0;

    /**
     * @brief Returns amount of item in the array.
     */
    virtual size_t getSize() const = 0;

    /**
     * @brief Checks if array is full.
     * 
     * @return true if array is full
     */
    virtual bool isFull() const = 0;

    /**
     * @brief Checks if array is empty.
     * 
     * @return true if array is empty
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief Removes all objects from the array.
     * 
     */
    virtual void clear() = 0;
};


#endif
