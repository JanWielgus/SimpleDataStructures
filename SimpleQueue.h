/**
 * @file SimpleQueue.h
 * @author Jan Wielgus
 * @brief Simple queue that implement IQueue interface.
 * @date 2020-08-31
 * 
 */

#ifndef SIMPLEQUEUE_H
#define SIMPLEQUEUE_H

#include "IQueue.h"


template <class T>
class SimpleQueue : public IQueue<T>
{
protected:
    const size_t QueueSize; // size of the array
    T* array = nullptr;
    T null_item; // element returned when queue is empty and dequeue() is called
    
    size_t queueFrontIndex = 0; // element to be dequeued in the first place
    size_t queueLength = 0; // amount of elements in the queue


public:
    SimpleQueue(size_t queueSize)
        : QueueSize(queueSize)
    {
        if (QueueSize > 0)
            array = new T[QueueSize];
        
        clear();
    }


    SimpleQueue(const SimpleQueue& other)
        : QueueSize(other.QueueSize)
    {
        queueFrontIndex = other.queueFrontIndex;
        queueLength = other.queueLength;

        if (QueueSize > 0)
        {
            array = new T[QueueSize];

            for (size_t i = 0; i < queueLength; i++)
            {
                size_t currentArrayIndex = (queueFrontIndex + i) % QueueSize;
                array[currentArrayIndex] = other.array[currentArrayIndex];
            }
        }
    }


    virtual ~SimpleQueue()
    {
        if (QueueSize > 0)
            delete[] array;
    }


    SimpleQueue& operator=(const SimpleQueue& other) = delete;


    void clear() override 
    {
        queueFrontIndex = 0;
        queueLength = 0;
    }


    virtual bool enqueue(const T& item) override
    {
        if (QueueSize == 0)
            return false;
        
        if (queueLength == QueueSize)
            return false;
        
        // queueEndIndex is index to put the new item
        size_t queueEndIndex = (queueFrontIndex + queueLength) % QueueSize;
        array[queueEndIndex] = item;
        queueLength++;
        return true;
    }


    virtual T& dequeue() override
    {
        if (isEmpty())
            return null_item;
        
        T& itemToReturn = array[queueFrontIndex];

        queueLength--;
        queueFrontIndex++; // move to the next item
        queueFrontIndex %= QueueSize;

        return itemToReturn;
    }


    T& peek() override
    {
        return isEmpty() ? null_item : array[queueFrontIndex];
    }


    const T& peek() const override
    {
        return isEmpty() ? null_item : array[queueFrontIndex];
    }


    bool isEmpty() const override
    {
        return queueLength == 0;
    }


    bool isFull() const override
    {
        return queueLength == QueueSize;
    }


    size_t getQueueLength() const override
    {
        return queueLength;
    }
};


#endif
