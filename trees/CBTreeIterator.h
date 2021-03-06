
#pragma once

#include <stack>
#include <iostream>
#include "CBTree.h"

namespace DS
{
    template<class T>
    struct CBNode;

    namespace StackState
    {
        enum _StackState
        {
            START,
            VISIT_LEFT,
            STAY,
            VISIT_RIGHT,
            BACK
        };
    }

    template<class T>
    struct StackNode
    {

        StackState::_StackState state;
        CBNode<T>* node;

        StackNode( StackState::_StackState pState, CBNode<T>* pNode )
        {
            this->state = pState;
            this->node = pNode;
        }

    };

    template<class T>
    bool operator==( const StackNode<T>& p1, const StackNode<T>& p2 )
    {
        return ( p1.node == p2.node ) && ( p1.state == p2.state );
    }

    template<class T>
    class CBTreeIterator
    {

        protected :

        std::stack<StackNode<T> > m_stack;

        public :

        CBTreeIterator()
        {
            
        }

        CBTreeIterator( std::stack<StackNode<T> > &pStack )
        {
            m_stack = pStack;
        }

        CBTreeIterator( const CBTreeIterator<T>& other )
        {
            m_stack = other.m_stack;
        }

        CBTreeIterator<T>& operator=( const CBTreeIterator<T>& other )
        {
            m_stack = other.m_stack;
        }

        CBNode<T>& operator*()
        {
            return *( ( m_stack.top() ).node );
        }

        virtual CBTreeIterator<T>& operator++() = 0;

        bool operator!=( const CBTreeIterator<T>& other )
        {
            return m_stack != other.m_stack;
        }

        void consume()
        {
            while( m_stack.size() != 0 )
            {
                std::cout << ( ( m_stack.top() ).node )->data << " - " << ( m_stack.top() ).state << std::endl;
                m_stack.pop();
            }
        }
    };

}