
#pragma once

#include "CBaseOrderedList.h"

namespace DS
{

    template<class T>
    using Cmp_fp = bool(*)( T, T );

    namespace comparationFunctions
    {
        template<class T>
        bool greaterThan( T a, T b )
        {
            return a > b;
        }

        template<class T>
        bool lessThan( T a, T b )
        {
            return a < b;
        }        
    }

    template<class T>
    class COrderedListFpointers : public CBaseOrderedList<T>
    {

        private :

        Cmp_fp<T> m_fpComparator;

        public :

        COrderedListFpointers()
        {
            m_fpComparator = comparationFunctions::greaterThan;
        }

        COrderedListFpointers( Cmp_fp<T> fpComparator )
        {
            m_fpComparator = fpComparator;
        }

        bool find( T x, CNode<T>** &pToLink );
    };


}


template<class T>
bool DS::COrderedListFpointers<T>::find( T x, CNode<T>** &pToLink )
{
    pToLink = &( this->m_head );
    while ( ( *pToLink != NULL ) && ( m_fpComparator( x, ( *pToLink )->data ) ) )
    {
        pToLink = &( ( *pToLink )->next );
    }

    return ( *pToLink != NULL ) && ( x == ( *pToLink )->data );
}