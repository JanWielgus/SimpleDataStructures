/**
 * @file Iterator.h
 * @author Jan Wielgus
 * @brief Base class for all iterators.
 * @date 2020-10-14
 * 
 */

#ifndef ITERATOR_H
#define ITERATOR_H


template <class T>
class Iterator
{
public:
    virtual ~Iterator() {}

    /**
     * @return true if iterator is not at the end of data (you can use next() method).
     * Return false if there are no more data and next() cannot be used.
     */
    virtual bool hasNext() = 0;

    /**
     * @brief Can be used to access next data. Check if there are any data using hasNext() method first!
     * @return Pointer to the data.
     */
    virtual T& next() = 0;
};


#endif
