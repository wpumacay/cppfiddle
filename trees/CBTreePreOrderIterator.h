
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
            
            if ( ( this->m_stack.top() ).state == StackNode<T>::STAY )
            {
                StackNode<T>& _top = this->m_stack.top();
                _top.state = StackNode<T>::VISIT_RIGHT;
                if ( _top.node->children[1] == nullptr )
                {
                    _top.state = StackNode<T>::BACK;
                    // In this state, just pop it
                    this->m_stack.pop();
                    // If the node on top is a type 2 node, we have already visited ...
                    // all its subtree
                    if ( ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                    {
                        while( this->m_stack.size() != 0 && ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                        {
                            ( this->m_stack.top() ).state = StackNode<T>::BACK;// Just to remember, should not do this
                            this->m_stack.pop();
                        }
                    }
                }
                else
                {
                    CBNode<T>* pToNode = _top.node->children[1];
                    this->m_stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    while ( pToNode->children[0] != nullptr )
                    {
                        pToNode = pToNode->children[0];
                        ( this->m_stack.top() ).state = StackNode<T>::STAY;
                        this->m_stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    }
                    ( this->m_stack.top() ).state = StackNode<T>::STAY;
                }
            }

            return *this;
        }

    };

}