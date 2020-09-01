/**
 * @file LinkedList.h
 * @author Jan Wielgus
 * @brief One-way linked list class.
 * @date 2020-09-01
 * 
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "IList.h"


template <class T>
class LinkedList : public IList<T>
{
    // TODO: implement LinkedList class.
private:
    // ...


public:
    // constructor/constructors


    void clear() override
    {

    }


    virtual bool add(const T& item) override
    {

    }

    
    virtual bool add(const T& item, size_t index) override
    {

    }

    
    virtual T& get(size_t index) override
    {

    }

    
    virtual const T& get(size_t index) const override
    {

    }

    
    virtual T& operator[](size_t index) override
    {

    }

    
    virtual const T& operator[](size_t index) const override
    {

    }

    
    virtual bool replace(size_t index, const T& newItem) override
    {

    }

    
    virtual size_t getSize() const override
    {

    }

    
    virtual bool isEmpty() const override
    {

    }
};

#endif
