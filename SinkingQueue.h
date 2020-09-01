/**
 * @file SinkingQueue.h
 * @author Jan Wielgus
 * @brief Queue that when is full, remove the oldest element.
 * @date 2020-08-03
 * 
 */

#ifndef SINKINGQUEUE_H
#define SINKINGQUEUE_H

#include "SimpleQueue.h"


template <class T>
class SinkingQueue : public SimpleQueue<T>
{
protected:
    using SimpleQueue<T>::QueueSize;
    using SimpleQueue<T>::array;
    using SimpleQueue<T>::null_item;
    using SimpleQueue<T>::queueFrontIndex;
    using SimpleQueue<T>::queueLength;


public:
    SinkingQueue(size_t queueSize)
        : SimpleQueue(queueSize)
    {
    }


    SinkingQueue(const SinkingQueue& other)
        : SimpleQueue(queueSize)
    {
    }


    ~SinkingQueue()
    {
    }


    // overloaded assignment operator
    SinkingQueue& operator=(const SinkingQueue& other) = delete; // temporarily deleted //TODO: this


    bool enqueue(const T& item) override
    {
        if (QueueSize == 0)
            return false;

        // queueEndIndex is index to put the new item
        size_t queueEndIndex = (queueFrontIndex + queueLength) % QueueSize;
        array[queueEndIndex] = item;

        // queue is full, overwrite the oldest item
        if (queueLength == QueueSize)
        {
            // overwrite the oldest item
            queueFrontIndex++;
            queueFrontIndex %= QueueSize;
        }
        else // queue is not full
            queueLength++;
        
        return true;
    }







    /*

    // TODO: this method goes to class that implement IRandomAccessQueue interface
    T& peek(size_t index) override
    {
        if (index >= queueLength)
            return null_item;
        
        size_t returnIndex = (queueFrontIndex + index) % QueueSize;
        return array[returnIndex];
    }


    const T& peek(size_t index) const override
    {
        if (index >= queueLength)
            return null_item;
        
        size_t returnIndex = (queueFrontIndex + index) % QueueSize;
        return array[returnIndex];
    }

    */
};


#endif
