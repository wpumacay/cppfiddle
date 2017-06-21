
#pragma once

#include "CBaseOrderedList.h"

namespace DS
{
    namespace functors
    {
        template<class T>
        struct GreaterThan
        {
            __attribute__ ((always_inline)) inline bool operator()( T a, T b )
            {
                return a > b;
            }
        };

        template<class T>
        struct LessThan 
        {
            __attribute__ ((always_inline)) inline bool operator()( T a, T b )
            {
                return a < b;
            }
        };
    }

    template<class T, class FunctorType>
    class COrderedListFunctors : public CBaseOrderedList<T>
    {

        private :

        FunctorType m_functor;

        public :

        bool find( T x, CNode<T>** &pToLink );
    };


}


template<class T, class FunctorType>
bool DS::COrderedListFunctors<T, FunctorType>::find( T x, CNode<T>** &pToLink )
{
    pToLink = &( this->m_head );
    while ( ( *pToLink != NULL ) && ( m_functor( x, ( *pToLink )->data ) ) )
    {
        pToLink = &( ( *pToLink )->next );
    }

    return ( *pToLink != NULL ) && ( x == ( *pToLink )->data );
}