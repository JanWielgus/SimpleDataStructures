/**
 * @file IRandomAccessQueue.h
 * @author Jan Wielgus
 * @brief Queue interface that extends IQueue interface. Enables access to all elements in queue.
 * >> Random access queue is basically an automated array with ability to remove elements. 
 * @date 2020-08-31
 * 
 */

// FOR NOW, THIS INTERFACE IS DEPRECATED AND NOT USED !!!

#ifndef IRANDOMACCESSQUEUE_H
#define IRANDOMACCESSQUEUE_H

#include "IQueue.h"


template <class T>
class IRandomAccessQueue : public IQueue<T>
{
public:
    virtual ~IQueue() {}

    /**
     * @brief Removes and returns specific item from the queue.
     * 
     * @param index Index of an item to dequeue.
     * @return Reference to dequeued item from the queue.
     */
    virtual T& dequeue(size_t index) = 0;

    /**
     * @brief Returns reference to the specific element in the queue
     * without removing it.
     * 
     * @param index Number of the element to peek (0 is the first element)
     * @return Reference to the element on the index position.
     */
    virtual T& peek(size_t index) = 0;

    /**
     * @brief Returns const reference to the specific element in the queue
     * without removing it.
     * 
     * @param index Number of the element to peek (0 is the first element)
     * @return Reference const to the element on the index position.
     */
    virtual const T& peek(size_t index) const = 0;
};


#endif
