/**
 * @file IQueue.h
 * @author Jan Wielgus
 * @brief Common interface for queues
 * @date 2020-08-03
 * 
 */

#ifndef IQUEUE_H
#define IQUEUE_H


template <class T>
class IQueue
{
public:
    virtual ~IQueue() {}

    /**
     * @brief Removes all objects from the queue.
     */
    virtual void clear() = 0;

    /**
     * @brief Adds new item to the end of the queue.
     * 
     * @param item Item to add to the end of the queue
     * @return false if queue is full or element was not
     * added because of any reason
     */
    virtual bool enqueue(const T& item) = 0;

    /**
     * @brief Removes and returns item from the queue beginning.
     * 
     * @return Reference to the first element in the queue
     */
    virtual T& dequeue() = 0;

    /**
     * @brief Returns item from the queue beginning without removing it.
     * 
     * @return Referenve to the first element in the queue.
     */
    virtual T& peek() = 0;

    /**
     * @brief Returns item from the queue beginning without removing it.
     * 
     * @return Const referenve to the first element in the queue.
     */
    virtual const T& peek() const = 0;

    /**
     * @brief Checks if queue is empty.
     * 
     * @return true if queue is empty
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief Checks if queue is full.
     * 
     * @return true if queue is full
     */
    virtual bool isFull() const = 0;

    /**
     * @return Amount of elements currently in the queue
     */
    virtual size_t getQueueLength() const = 0;
};


#endif
