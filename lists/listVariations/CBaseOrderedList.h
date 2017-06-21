
#pragma once

#include "CListInterface.h"

namespace DS
{

    template<class T>
    class CBaseOrderedList : public CListInterface<T>
    {

        public :

        bool insert( T x );
        bool erase( T x );
    };


}

template<class T>
bool DS::CBaseOrderedList<T>::insert( T x )
{
    DS::CNode<T>** pToLink;
    if ( this->find( x, pToLink ) )
    {
        return false;
    }

    DS::CNode<T>* pToNode = new CNode<T>( x );
    pToNode->next = ( *pToLink );
    *pToLink = pToNode;

    return true;
}


template<class T>
bool DS::CBaseOrderedList<T>::erase( T x )
{
    CNode<T>** pToLink;
    if ( !this->find( x, pToLink ) )
    {
        return false;
    }

    CNode<T>* pToNode = *pToLink;
    *pToLink = ( *pToLink )->next;
    delete pToNode;

    return true;
}