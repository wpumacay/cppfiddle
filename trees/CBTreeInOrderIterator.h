
#pragma once

#include "CBTreeIterator.h"

namespace DS
{


    template<class T>
    class CBTreeInOrderIterator : public CBTreeIterator<T>
    {

        public :

        CBTreeInOrderIterator()
        {
            
        }

        CBTreeInOrderIterator( const CBTreeInOrderIterator<T>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeInOrderIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeInOrderIterator<T>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }
            
            if ( ( this->m_stack.top() ).state == StackState::STAY )
            {
                StackNode<T>& _top = this->m_stack.top();
                _top.state = StackState::VISIT_RIGHT;
                if ( _top.node->children[1] == NULL )
                {
                    this->m_stack.pop();
                    // If the node on top is a type 2 node, we have already visited ...
                    // all its subtree
                    if ( ( this->m_stack.top() ).state == StackState::VISIT_RIGHT )
                    {
                        while( this->m_stack.size() != 0 && ( this->m_stack.top() ).state == StackState::VISIT_RIGHT )
                        {
                            this->m_stack.pop();
                        }
                    }
                }
                else
                {
                    CBNode<T>* pToNode = _top.node->children[1];
                    this->m_stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    while ( pToNode->children[0] != NULL )
                    {
                        pToNode = pToNode->children[0];
                        ( this->m_stack.top() ).state = StackState::STAY;
                        this->m_stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    }
                    ( this->m_stack.top() ).state = StackState::STAY;
                }
            }

            return *this;
        }
    };

}