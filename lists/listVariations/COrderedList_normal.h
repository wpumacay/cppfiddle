
#pragma once

#include "CBaseOrderedList.h"

namespace DS
{

    template<class T>
    class COrderedListNormal : public CBaseOrderedList<T>
    {

        public :

        bool find( T x, CNode<T>** &pToLink );
    };


}


template<class T>
bool DS::COrderedListNormal<T>::find( T x, CNode<T>** &pToLink )
{
    pToLink = &( this->m_head );
    while ( ( *pToLink != NULL ) && ( x > ( *pToLink )->data ) )
    {
        pToLink = &( ( *pToLink )->next );
    }

    return ( *pToLink != NULL ) && ( x == ( *pToLink )->data );
}