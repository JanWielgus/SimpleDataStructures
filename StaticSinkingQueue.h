/**
 * @file StaticSinkingQueue.h
 * @author Jan Wielgus
 * @brief Queue that when is full, remove the oldest element.
 * @date 2020-08-03
 * 
 */

#ifndef STATICSINKINGQUEUE_H
#define STATICSINKINGQUEUE_H

#include "StaticQueue.h"


namespace SimpleDataStructures
{
    template <class T>
    class StaticSinkingQueue : public StaticQueue<T>
    {
    protected:
        using StaticQueue<T>::QueueSize;
        using StaticQueue<T>::array;
        using StaticQueue<T>::null_item;
        using StaticQueue<T>::queueFrontIndex;
        using StaticQueue<T>::queueLength;


    public:
        StaticSinkingQueue(size_t queueSize)
            : SimpleQueue(queueSize)
        {
        }


        StaticSinkingQueue(const StaticSinkingQueue& other)
            : SimpleQueue(other)
        {
        }


        ~StaticSinkingQueue()
        {
        }


        // overloaded assignment operator
        StaticSinkingQueue& operator=(const StaticSinkingQueue& other) = delete;


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
}


#endif
