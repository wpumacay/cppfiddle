
#pragma once

#include <stack>
#include <iostream>
#include "CBTree.h"

namespace DS
{
    template<class T>
    struct CBNode;

    template<class T>
    struct StackNode
    {
        enum _State
        {
            VISIT_LEFT,
            STAY,
            VISIT_RIGHT,
            BACK
        };

        _State state;
        CBNode<T>* node;

        StackNode( _State pState, CBNode<T>* pNode )
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

    template<class T, class FunctorType>
    class CBTreeIterator
    {

        protected :

        std::stack<StackNode<T>> m_stack;

        public :

        CBTreeIterator()
        {
            
        }

        CBTreeIterator( std::stack<StackNode<T>> &pStack )
        {
            m_stack = pStack;
        }

        CBTreeIterator( const CBTreeIterator<T,FunctorType>& other )
        {
            m_stack = other.m_stack;
        }

        CBTreeIterator<T,FunctorType>& operator=( const CBTreeIterator<T,FunctorType>& other )
        {
            m_stack = other.m_stack;
        }

        CBNode<T>& operator*()
        {
            return *( ( m_stack.top() ).node );
        }

        virtual CBTreeIterator<T,FunctorType>& operator++() = 0;

        bool operator!=( const CBTreeIterator<T,FunctorType>& other )
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

    template<class T, class FunctorType>
    class CBTreeInOrderIterator : public CBTreeIterator<T,FunctorType>
    {

        public :

        CBTreeInOrderIterator()
        {
            
        }

        CBTreeInOrderIterator( const CBTreeInOrderIterator<T,FunctorType>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeInOrderIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeInOrderIterator<T,FunctorType>& operator++()
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

    template<class T, class FunctorType>
    class CBTreePostOrderIterator : public CBTreeIterator<T,FunctorType>
    {

        public :

        CBTreePostOrderIterator(){}

        CBTreePostOrderIterator( const CBTreePostOrderIterator<T,FunctorType>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreePostOrderIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreePostOrderIterator<T,FunctorType>& operator++()
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