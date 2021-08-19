/**
 * @file ListIterator.h
 * @author Jan Wielgus
 * @brief Iterator for all classes that implement IList interface.
 * @date 2021-06-13
 * 
 */

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "Iterator.h"
#include "IList.h"


namespace SimpleDataStructures
{
    /**
     * @brief Iterator for all classes that implement IList interface.
     * Can remove elements while iterating.
     */
    template <class T>
    class ListIterator : public RemovingIterator<T>
    {
        IList<T>* list = nullptr;
        size_t nextIndex;
        T nullElement;


    public:
        ListIterator(IList<T>& list)
        {
            this->list = &list;
            nextIndex = 0;
        }


        ListIterator(const ListIterator&) = delete;
        ListIterator& operator=(const ListIterator&) = delete;


        ListIterator(ListIterator&& toMove)
        {
            list = toMove.list;
            nextIndex = toMove.nextIndex;

            toMove.list = nullptr;
            toMove.nextIndex = 0;
        }


        ListIterator& operator=(ListIterator&& toMove)
        {
            if (this != &toMove)
            {
                list = toMove.list;
                nextIndex = toMove.nextIndex;

                toMove.list = nullptr;
                toMove.nextIndex = 0;
            }

            return *this;
        }


        bool hasNext() override
        {
            return list != nullptr && nextIndex < list->size();
        }


        T& next() override
        {
            if (!hasNext())
                return nullElement;

            nextIndex++;
            return list->get(nextIndex - 1);
        }


        bool remove() override
        {
            if (list == nullptr || nextIndex == 0)
                return false;
            
            --nextIndex;
            return list->remove(nextIndex);
        }


        /**
         * @brief Disables iterator (hasNext() will remove false).
         */
        void reset()
        {
            list = nullptr;
        }
        

        /**
         * @brief Sets iterator on the passed list.
         * @param list reference to list to iterate though.
         */
        void reset(IList<T>& list)
        {
            this->list = &list;
            nextIndex = 0;
        }
    };
}


#endif
