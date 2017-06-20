
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
                _top.state = StackNode<T>::VISIT_LEFT;
                if ( _top.node->children[0] == nullptr && 
                     _top.node->children[1] == nullptr )
                {
                    // In this state, just pop the top
                    _top.state = StackNode<T>::BACK;
                    this->m_stack.pop();
                    // If have already visited the left, visit the right
                    if ( ( this->m_stack.top() ).state == StackNode<T>::VISIT_LEFT )
                    {
                        ( this->m_stack.top() ).state = StackNode<T>::VISIT_RIGHT;
                        CBNode<T>* pToNode = ( this->m_stack.top() ).node->children[1];
                        this->m_stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
                    }
                    // If have already visited the left and right ... well, just go back
                    else if ( ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                    {
                        // We have already visited all of this node, so just pop it until a non visit-right is found
                        while( this->m_stack.size() != 0 && ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                        {
                            ( this->m_stack.top() ).state = StackNode<T>::BACK;// Just to remember, should not do this
                            this->m_stack.pop();
                        }
                        if ( this->m_stack.size() != 0 )
                        {
                            if ( ( this->m_stack.top() ).state == StackNode<T>::VISIT_LEFT )
                            {
                                if ( ( this->m_stack.top() ).node->children[1] != nullptr )
                                {
                                    ( this->m_stack.top() ).state = StackNode<T>::VISIT_RIGHT;
                                    CBNode<T>* pToNode = ( this->m_stack.top() ).node->children[1];
                                    this->m_stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
                                }
                            }
                        }
                    }
                }
                else if ( _top.node->children[0] != nullptr )
                {
                    CBNode<T>* pToNode = _top.node->children[0];
                    this->m_stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
                }
                else
                {
                    _top.state = StackNode<T>::VISIT_RIGHT;
                    CBNode<T>* pToNode = _top.node->children[1];
                    this->m_stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
                }
            }

            return *this;
        }

    };

}