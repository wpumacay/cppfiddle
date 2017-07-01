
#pragma once

#include "CBTreeIterator.h"

namespace DS
{
    template<class T>
    class CBTreePostOrderIterator : public CBTreeIterator<T>
    {

        public :

        CBTreePostOrderIterator(){}

        CBTreePostOrderIterator( const CBTreePostOrderIterator<T>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreePostOrderIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreePostOrderIterator<T>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }
            
            if ( ( this->m_stack.top() ).state == StackState::STAY )
            {
                this->m_stack.pop();
                if ( this->m_stack.size() == 0 )
                {
                    return *this;
                }

                StackNode<T>& _top = this->m_stack.top();

                if ( _top.state == StackState::VISIT_LEFT )
                {
                    _top.state = StackState::VISIT_RIGHT;
                    if ( _top.node->children[1] != NULL )
                    {
                        this->m_stack.push( StackNode<T>( StackState::VISIT_LEFT, _top.node->children[1] ) );
                        while ( ( this->m_stack.top() ).node->children[0] != NULL || 
                                ( this->m_stack.top() ).node->children[1] != NULL )
                        {
                            if ( ( this->m_stack.top() ).node->children[0] != NULL )
                            {
                                ( this->m_stack.top() ).state = StackState::VISIT_LEFT;
                                this->m_stack.push( StackNode<T>( StackState::VISIT_LEFT, 
                                                                  ( this->m_stack.top() ).node->children[0] ) );
                            }
                             else
                            {
                                ( this->m_stack.top() ).state = StackState::VISIT_RIGHT;
                                this->m_stack.push( StackNode<T>( StackState::VISIT_LEFT, 
                                                                  ( this->m_stack.top() ).node->children[1] ) );
                            }
                        }
                        ( this->m_stack.top() ).state = StackState::STAY;
                    }
                    else
                    {
                        _top.state = StackState::STAY;
                    }
                }
                else if ( _top.state == StackState::VISIT_RIGHT )
                {
                    _top.state = StackState::STAY;
                }
            }

            return *this;
        }

    };

}
