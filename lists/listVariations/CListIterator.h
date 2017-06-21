
#pragma once

#include "CListInterface.h"

namespace DS
{
    template<class T>
    struct CNode;

    template<class T>
    class CListIterator
    {

        protected :

        CNode<T>* m_nodeRef;

        public :

        CListIterator()
        {
            m_nodeRef = NULL;
        }

        CListIterator( CNode<T>* pNodeRef )
        {
            m_nodeRef = pNodeRef;
        }

        CListIterator( const CListIterator<T>& other )
        {
            m_nodeRef = other.m_nodeRef;
        }

        CListIterator<T>& operator=( const CListIterator<T>& other )
        {
            m_nodeRef = other.m_nodeRef;
        }

        ~CListIterator()
        {
            m_nodeRef = NULL;
        }

        CNode<T>& operator*()
        {
            return *( m_nodeRef );
        }

        CListIterator<T>& operator++()
        {
            if ( m_nodeRef )
            {
                m_nodeRef = m_nodeRef->next;
            }
            return *this;
        }

        CListIterator<T>& operator++( int dummy )
        {
            CListIterator<T> clone( *this );
            if ( m_nodeRef )
            {
                m_nodeRef = m_nodeRef->next;
            }
            return clone;
        }

        bool operator!=( const CListIterator<T>& other )
        {
            return m_nodeRef != other.m_nodeRef;
        }
    };

}