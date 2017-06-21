
#pragma once

#include "CBaseOrderedList.h"

namespace DS
{

    namespace polyComparators
    {
        template<class T>
        class Comparator
        {
            public :

            virtual bool comp( T a, T b ) = 0;
        };

        template<class T>
        class GreaterComparator : public Comparator<T>
        {
            bool comp( T a, T b )
            {
                return a > b;
            }
        };

        template<class T>
        class LessComparator : public Comparator<T>
        {
            bool comp( T a, T b )
            {
                return a < b;
            }
        };
    }

    template<class T>
    class COrderedListPolymorphic : public CBaseOrderedList<T>
    {

        private :

        polyComparators::Comparator<T>* m_polyComparator;

        public :

        COrderedListPolymorphic( polyComparators::Comparator<T>* polyComparator )
        {
            m_polyComparator = polyComparator;
        }

        bool find( T x, CNode<T>** &pToLink );
    };


}


template<class T>
bool DS::COrderedListPolymorphic<T>::find( T x, CNode<T>** &pToLink )
{
    pToLink = &( this->m_head );
    while ( ( *pToLink != NULL ) && ( m_polyComparator->comp( x, ( *pToLink )->data ) ) )
    {
        pToLink = &( ( *pToLink )->next );
    }

    return ( *pToLink != NULL ) && ( x == ( *pToLink )->data );
}