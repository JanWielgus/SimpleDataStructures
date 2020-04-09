// FC_SinkingQueue.h
/*
	Created:	08/04/2020
	Author:     Jan Wielgus

	If queue size is full, overrides the oldest element
*/


#ifndef _FC_SINKINGQUEUE_h
#define _FC_SINKINGQUEUE_h

#include "arduino.h"


template <class T>
class FC_SinkingQueue
{
private:
	T* array;
	uint16_t size;

	uint16_t queueFrontIndex = 0; // id of element to be dequeued in the first place
	uint16_t queueLength = 0; // amount of elements indside the queue (at most size)

	T nullElement; // element returned if queue is empty and asked for element

public:
	FC_SinkingQueue(uint16_t queueSize)
	{
		size = queueSize;

		if (size > 0)
			array = new T[size];

		queueFrontIndex = 0;
		queueLength = 0;
	}


	~FC_SinkingQueue()
	{
		if (size > 0)
			delete[] array;
	}


	// copy constructor
	FC_SinkingQueue(const FC_SinkingQueue& other)
	{
		size = other.size;

		// copy data
		if (size > 0)
		{
			array = new T[size];

			for (int i = 0; i < size; i++)
				array[i] = other.array[i];
		}
	}


	// overloaded assignment operator
	FC_SinkingQueue& operator=(const FC_SinkingQueue& other)
	{
		if (this != &other)                   // self-assignment check expected
		{
			if (other.size != size)           // storage cannot be reused
			{
				delete[] array;               // destroy storage in this
				array = new T[other.size];    // create storage in this
				size = other.size;
			}

			for (int i = 0; i < size; i++)
				array[i] = other.array[i];
		}

		return *this;
	}


	void clear()
	{
		queueFrontIndex = 0;
		queueLength = 0;
	}


	uint16_t getSize() const
	{
		return size;
	}


	uint16_t getQueueLength() const
	{
		return queueLength;
	}


	bool isEmpty() const
	{
		return queueLength == 0;
	}


	void enqueue(const T& item)
	{
		// calculate index of the end index
		uint16_t queueEndIndex = queueFrontIndex + queueLength;
		queueEndIndex %= size;

		if (queueLength == size) // queue is full and overwrites the oldest item
		{
			// move front index forward
			// because the oldest item will be overwritten
			queueFrontIndex++;
			queueFrontIndex %= size;
		}
		else // queue length is smaller than size
			queueLength++;

		// Put new item on its place
		array[queueEndIndex] = item;
	}


	T& dequeue()
	{
		if (getQueueLength() == 0)
			return nullElement;

		T& toReturn = array[queueFrontIndex];

		// Decrease the queue size
		queueLength--;

		// Move front index to the next element
		queueFrontIndex++;
		queueFrontIndex %= size;

		return toReturn;
	}


	T& peek()
	{
		if (getQueueLength() > 0)
			return array[queueFrontIndex];
		return nullElement;
	}


	const T& peek() const
	{
		if (getQueueLength() > 0)
			return array[queueFrontIndex];
		return nullElement;
	}
};


#endif

