
#pragma once

#include "CBTreeIterator.h"

namespace DS
{

    template<class T, class FunctorType>
    class CBTreePreOrderIterator : public CBTreeIterator<T,FunctorType>
    {

        public :

        CBTreePreOrderIterator(){}

        CBTreePreOrderIterator( const CBTreePreOrderIterator<T,FunctorType>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreePreOrderIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreePreOrderIterator<T,FunctorType>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }

            StackNode<T> _top = this->m_stack.top();
            this->m_stack.pop();
            if ( _top.node->children[1] != nullptr )
            {
                this->m_stack.push( StackNode<T>( StackNode<T>::STAY, _top.node->children[1] ) );
            }
            if ( _top.node->children[0] != nullptr ) 
            {
                this->m_stack.push( StackNode<T>( StackNode<T>::STAY, _top.node->children[0] ) );
            }
            
            return *this;
        }

    };

}