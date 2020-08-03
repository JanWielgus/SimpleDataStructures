/**
 * @file SinkingQueue.h
 * @author Jan Wielgus
 * @brief Queue class. When is full, remove the oldest element.
 * @date 2020-08-03
 * 
 */

#ifndef SINKINGQUEUE_H
#define SINKINGQUEUE_H

#include <IQueue.h>


template <class T>
class SinkingQueue : public IQueue<T>
{
private:
    const size_t QueueSize;
    T* array = nullptr;
    T null_item; // element returned when queue is empty and dequeue() is called

    size_t queueFrontIndex = 0; // element to be dequeued in the first place
    size_t queueLength = 0;


public:
    SinkingQueue(size_t queueSize)
        : QueueSize(queueSize)
    {
        if (QueueSize > 0)
            array = new T[QueueSize];
        
        queueFrontIndex = 0;
        queueLength = 0;
    }


    SinkingQueue(const SinkingQueue& other)
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


    ~SinkingQueue()
    {
        if (QueueSize > 0)
            delete [] array;
    }


    // overloaded assignment operator
    SinkingQueue& operator=(const SinkingQueue& other) = delete; // temporarily deleted //TODO: this


    void clear() override
    {
        queueFrontIndex = 0;
        queueLength = 0;
    }


    bool enqueue(const T& item) override
    {
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
    }


    T& dequeue() override
    {
        if (isEmpty())
            return null_item;
        
        T& toReturn = array[queueFrontIndex];

        queueLength--;
        queueFrontIndex++; // move to the next item
        queueFrontIndex %= QueueSize;

        return toReturn;
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
