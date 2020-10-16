/**
 * @file LinkedList.h
 * @author Jan Wielgus
 * @brief One-way, dynamically allocated linked list class.
 * @date 2020-09-01
 * 
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "IList.h"

// Issues:
// FIXME: Removing the last element is not effective. I don't know if there is anything that can be done in one-way linked list.



template <class T>
class LinkedList;



template <class T>
class Node
{
public:
    T data;
    Node<T>* next;

    Node() : next(nullptr)
    {}
};



template <class T>
class LinkedListIterator : public Iterator<T>
{
private:
    Node<T>* currentNode = nullptr;
    T nullElement;

public:
    virtual ~LinkedListIterator() {}

    /**
     * @return true if iterator is not at the end and next() method can be used.
     * If returned false, don't use next method().
     */
    bool hasNext() override
    {
        return currentNode != nullptr;
    }

    /**
     * @return pointer to next data or nullptr if there is no next data.
     * Check if there are any data using hasNext() method first!
     */
    T& next() override
    {
        if (currentNode != nullptr)
        {
            T& toReturn = currentNode->data;
            currentNode = currentNode->next;
            return toReturn;
        }
        return nullElement;
    }

    friend class LinkedList<T>;
};



template <class T>
class LinkedList : public IList<T>
{
private:
    Node<T>* root = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;
    LinkedListIterator<T> iteratorInstance;

    T nullElement; // element returned for example when used get on empty list


public:
    LinkedList()
    {
    }


    void clear() override
    {
        Node<T>* current = root;
        while (current != nullptr)
        {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        root = nullptr;
        tail = nullptr;
        size = 0;
        iteratorInstance.currentNode = nullptr;
    }


    bool add(const T& item) override
    {
        if (root == nullptr)
        {
            root = new Node<T>();
            root->data = item;
            tail = root;
        }
        else
        {
            tail->next = new Node<T>();
            tail = tail->next;
            tail->data = item;
        }
        
        size++;
        return true;
    }

    
    bool add(const T& item, size_t index) override
    {
        if (index > size)
            return false;
        
        bool returnFlag = true;

        if (root == nullptr || index == size)
            returnFlag = add(item);
        else // neither first nor last element
        {
            Node<T>* preceding = getNode(index - 1);
            Node<T>* newNode = new Node<T>();
            newNode->data = item;
            newNode->next = preceding->next;
            preceding->next = newNode;
            size++;
        }
        
        return returnFlag;
    }

    
    T& get(size_t index) override
    {
        Node<T>* toReturn = getNode(index);
        return toReturn == nullptr ? nullElement : toReturn->data;
    }

    
    const T& get(size_t index) const override
    {
        Node<T>* toReturn = getNode(index);
        return toReturn == nullptr ? nullElement : toReturn->data;
    }

    
    T& operator[](size_t index) override
    {
        Node<T>* toReturn = getNode(index);
        return toReturn == nullptr ? nullElement : toReturn->data;
    }

    
    const T& operator[](size_t index) const override
    {
        Node<T>* toReturn = getNode(index);
        return toReturn == nullptr ? nullElement : toReturn->data;
    }


    Iterator<T>* getIterator() override
    {
        iteratorInstance.currentNode = root;
        return &iteratorInstance;
    }

    
    bool replace(const T& newItem, size_t index) override
    {
        Node<T>* toReplace = getNode(index);
        
        if (toReplace == nullptr)
            return false;
        
        toReplace->data = newItem;
        return true;
    }

    
    size_t getSize() const override
    {
        return size;
    }

    
    bool isEmpty() const override
    {
        return root == nullptr;
    }


    /**
     * @brief Remove element at specified index.
     * The fastest is removing the first element, slowest is removing the last one.
     * 
     * @param index Index of element to be removed from the linked list.
     * @return true if element was removed. Return false if list is empty
     * or index is out of bounds.
     */
    bool remove(size_t index)
    {
        if (root == nullptr || index >= size)
            return false;
        
        if (index == 0)
        {
            Node<T>* toDelete = root;
            root = root->next;
            delete toDelete;
        }
        else
        {
            Node<T>* preceding = getNode(index - 1);
            Node<T>* toDelete = preceding->next;
            preceding->next = toDelete->next;

            if (toDelete->next == nullptr)
                tail = preceding;

            delete toDelete;
        }
        
        size--;
        return true;
    }


private:
    Node<T>* getNode(size_t index) const
    {
        if (index >= size)
            return nullptr;

        if (index == size - 1)
            return tail;

        Node<T>* lookedFor = root;
        for (size_t i = 0; i < index; i++)
            lookedFor = lookedFor->next;
        
        return lookedFor;
    }
};

#endif
