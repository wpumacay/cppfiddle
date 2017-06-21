
#pragma once

#include <iostream>
#include <cstddef>

#include "CListIterator.h"


namespace DS
{

    template<class T>
    struct CNode
    {
        T data;
        CNode<T>* next;

        CNode( T x )
        {
            this->data = x;
        }
    };

    template<class T>
    class CListInterface
    {

        protected :

        CNode<T>* m_head;
        CNode<T>* m_tail;

        public :

        typedef CListIterator<T> iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        iterator begin()
        {
            return CListIterator<T>( m_head );
        }

        iterator end()
        {
            return CListIterator<T>( NULL );
        }

        CListInterface()
        {
            m_head = NULL;
        }

        ~CListInterface()
        {
            CNode<T>** pToLink = &m_head;
            while( ( *pToLink != NULL ) )
            {
                CNode<T>* pToNode = *pToLink;
                pToLink = &( ( *pToLink )->next );
                delete pToNode;
            }
        }

        virtual bool find( T x, CNode<T>** &pToLink ) = 0;
        virtual bool insert( T x ) = 0;
        virtual bool erase( T x ) = 0;

        void printList()
        {
            CNode<T>** pToLink = &m_head;
            while( ( *pToLink != NULL ) )
            {
                std::cout << ( *pToLink )->data << std::endl;
                pToLink = &( ( *pToLink )->next );
            }
        }
    };

    
}
