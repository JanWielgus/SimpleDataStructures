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


namespace SimpleDataStructures
{
    template <class T>
    class Node
    {
    public:
        T data;
        Node<T>* next;

        Node()
            : next(nullptr)
        {
        }

        Node(const T& _data, Node<T>* _next = nullptr)
            : data(_data), next(_next)
        {
        }
    };




    template <class T>
    class LinkedListIterator : public Iterator<T>
    {
        Node<T>* nextNode = nullptr;
        T nullElement;

    public:
        LinkedListIterator() {}

        LinkedListIterator(const LinkedListIterator&) = delete;
        LinkedListIterator& operator=(const LinkedListIterator&) = delete;


        /**
         * @return trueif there is some data to be obtained
         * by calling next() method. If returned false,
         * don't use next() method.
         */
        bool hasNext() override
        {
            return nextNode != nullptr;
        }


        /**
         * @return reference to next data or default value
         * if next data is not available. Check if there is
         * any data using hasNext() method first!
         */
        T& next() override
        {
            if (nextNode == nullptr)
                return nullElement;

            T& toReturn = nextNode->data;
            nextNode = nextNode->next;
            return toReturn;
        }


        /**
         * @brief Iterator won't have next elements from now.
         */
        void reset()
        {
            nextNode = nullptr;
        }


        /**
         * @brief Initialize the iterator.
         * @param startNode Node from the iteration will begin.
         */
        void setup(Node<T>* startNode)
        {
            nextNode = startNode;
        }
    };




    template <class T>
    class LinkedList : public IList<T>
    {
        Node<T>* root = nullptr;
        Node<T>* tail = nullptr;
        size_t linkedListSize = 0;
        LinkedListIterator<T> iteratorInstance;

        T nullElement; // element returned for example when used get() on empty list


    public:
        LinkedList() {}


        LinkedList(const LinkedList& other)
        {
            setFrom(other);
        }


        LinkedList(LinkedList&& toMove)
        {
            root = toMove.root;
            tail = toMove.tail;
            linkedListSize = toMove.linkedListSize;

            toMove.root = nullptr;
            toMove.tail = nullptr;
            toMove.linkedListSize = 0;
            toMove.iteratorInstance.reset();
        }


        ~LinkedList()
        {
            clear();
        }
        

        LinkedList& operator=(const LinkedList& other)
        {
            if (this != &other)
                setFrom(other);

            return *this;
        }


        LinkedList& operator=(LinkedList&& toMove)
        {
            if (this != &toMove)
            {
                clear();

                root = toMove.root;
                tail = toMove.tail;
                linkedListSize = toMove.linkedListSize;

                toMove.root = nullptr;
                toMove.tail = nullptr;
                toMove.linkedListSize = 0;
                toMove.iteratorInstance.reset();
            }

            return *this;
        }


        bool add(const T& item) override
        {
            if (root == nullptr)
            {
                root = new Node<T>(item);
                tail = root;
            }
            else
            {
                tail->next = new Node<T>(item);
                tail = tail->next;
            }
            
            linkedListSize++;
            return true;
        }

        
        bool add(const T& item, size_t index) override
        {
            if (index > linkedListSize)
                return false;

            if (root == nullptr || index == linkedListSize)
                return add(item);

            Node<T>* newNode = new Node<T>(item);

            if (index == 0)
            {
                newNode->next = root;
                root = newNode;
            }
            else
            {
                Node<T>* preceding = getNode(index - 1);
                newNode->next = preceding->next;
                preceding->next = newNode;
            }

            linkedListSize++;
            
            return true;
        }


        /**
         * @brief Remove element at specified index.
         * The fastest is removing the first element, slowest is removing the last one.
         * 
         * @param index Index of element to be removed from the linked list.
         * @return true if element was removed. Return false if list is empty
         * or index is out of bounds.
         */
        bool remove(size_t index) override
        {
            if (root == nullptr || index >= linkedListSize)
                return false;
            
            Node<T>* toDelete;

            if (index == 0)
            {
                toDelete = root;
                root = root->next;

                if (root == nullptr)
                    tail = nullptr;
            }
            else
            {
                Node<T>* preceding = getNode(index - 1);
                toDelete = preceding->next;
                preceding->next = toDelete->next;

                if (toDelete->next == nullptr) // if this was a tail node
                    tail = preceding;
            }
            
            delete toDelete;
            linkedListSize--;
            iteratorInstance.reset();
            return true;
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


        Iterator<T>* iterator() override
        {
            iteratorInstance.setup(root);
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


        size_t find(const T& itemToFind, size_t startIndex = 0) const override
        {
            Node<T>* startNode = getNode(startIndex);

            if (startNode == nullptr)
                return npos;

            size_t elemIndex = startIndex;
            for (Node<T>* node = startNode; node != nullptr; node = node->next)
            {
                if (node->data == itemToFind)
                    return elemIndex;

                elemIndex++;
            }

            return npos;
        }


        bool contains(const T& itemToFind) const override
        {
            for (Node<T>* node = root; node != nullptr; node = node->next)
                if (node->data == itemToFind)
                    return true;
                
            return false;
        }

        
        size_t size() const override
        {
            return linkedListSize;
        }

        
        bool isEmpty() const override
        {
            return root == nullptr;
        }


        void clear() override
        {
            deleteFromNode(root);
            root = nullptr;
            tail = nullptr;
            linkedListSize = 0;
            iteratorInstance.reset();
        }



    private:
        Node<T>* getNode(size_t index) const
        {
            if (index >= linkedListSize)
                return nullptr;

            if (index == linkedListSize - 1)
                return tail;

            Node<T>* lookedFor = root;
            for (size_t i = 0; i < index; i++)
                lookedFor = lookedFor->next;
            
            return lookedFor;
        }


        /**
         * @brief Return node that is before the node passed in the parameter
         * (or nullptr if passed root or preceding node was not found).
         * @param node Node which predecessor we are looking for.
         */
        Node<T>* getPrecedingNode(const Node<T>* node)
        {
            if (node == root)
                return nullptr;

            Node<T>* precedingNode = root;
            while (precedingNode != nullptr && precedingNode->next != node)
                precedingNode = precedingNode->next;
            
            return precedingNode;
        }


        bool removeNode(const Node<T>* nodeToRemove)
        {
            if (root == nullptr || nodeToRemove == nullptr)
                return false;
            
            if (nodeToRemove == root)
            {
                root = root->next;
                
                if (root == nullptr)
                    tail = nullptr;
            }
            else
            {
                Node<T>* precedingNode = getPrecedingNode(nodeToRemove);
                if (precedingNode == nullptr) // node was not found
                    return false;
                
                precedingNode->next = nodeToRemove->next;

                if (nodeToRemove->next == nullptr) // if this was a tail node
                    tail = precedingNode;
            }
            
            delete nodeToRemove;
            linkedListSize--;
            iteratorInstance.reset();
            return true;
        }


        /**
         * @brief Delete passed node and all next nodes.
         * @param startNode Pointer to the first node to delete.
         */
        void deleteFromNode(Node<T>* startNode)
        {
            Node<T>* nodeToDel = startNode;
            while (nodeToDel != nullptr)
            {
                Node<T>* next = nodeToDel->next;
                delete nodeToDel;
                nodeToDel = next;
            }
        }


        /**
         * @brief Clear LinkedList and make a deep copy of data from other.
         * @param other LinkedList to make a deep copy.
         */
        void setFrom(const LinkedList& other)
        {
            if (other.linkedListSize == 0)
            {
                clear();
                return;
            }


            if (root == nullptr)
                root = new Node<T>();

            root->data = other.root->data;

            Node<T>* lastSrcNode = other.root;
            Node<T>* lastDestNode = root;

            // copy all data
            while (lastSrcNode->next != nullptr)
            {
                // if node doesn't exist, allocate memory for a new node
                if (lastDestNode->next == nullptr)
                    lastDestNode->next = new Node<T>();

                lastDestNode->next->data = lastSrcNode->next->data;

                // move to next nodes
                lastSrcNode = lastSrcNode->next;
                lastDestNode = lastDestNode->next;
            }

            // delete remaining nodes if this linked list was bigger than copied one
            deleteFromNode(lastDestNode->next);

            tail = lastDestNode;
            tail->next = nullptr;

            linkedListSize = other.linkedListSize;
        }
    };
}


#endif
