
#pragma once

#include "CBTreeIterator.h"

namespace DS
{
    struct PreOrder;
    struct PostOrder;
    struct InOrder;

    template<class T,class TypeIterator>
    class CBTreeGeneralIterator : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralIterator(){}

        CBTreeGeneralIterator( const CBTreeGeneralIterator<T,TypeIterator>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralIterator<T,TypeIterator>& operator++()
        {
            return *this;
        }

    };
    
    template<class T>
    class CBTreeGeneralIterator<T,PreOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralIterator(){}

        CBTreeGeneralIterator( const CBTreeGeneralIterator<T,PreOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralIterator<T,PreOrder>& operator++()
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
    

    template<class T>
    class CBTreeGeneralIterator<T,InOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralIterator(){}

        CBTreeGeneralIterator( const CBTreeGeneralIterator<T,InOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralIterator<T,InOrder>& operator++()
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
                    this->m_stack.pop();
                    // If the node on top is a type 2 node, we have already visited ...
                    // all its subtree
                    if ( ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                    {
                        while( this->m_stack.size() != 0 && ( this->m_stack.top() ).state == StackNode<T>::VISIT_RIGHT )
                        {
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

    template<class T>
    class CBTreeGeneralIterator<T,PostOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralIterator(){}

        CBTreeGeneralIterator( const CBTreeGeneralIterator<T,PostOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralIterator( std::stack<StackNode<T>> &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralIterator<T,PostOrder>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }
                
            if ( ( this->m_stack.top() ).state == StackNode<T>::STAY )
            {
                this->m_stack.pop();
                if ( this->m_stack.size() == 0 )
                {
                    return *this;
                }

                StackNode<T>& _top = this->m_stack.top();

                if ( _top.state == StackNode<T>::VISIT_LEFT )
                {
                    _top.state = StackNode<T>::VISIT_RIGHT;
                    if ( _top.node->children[1] != nullptr )
                    {
                        this->m_stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, _top.node->children[1] ) );
                        while ( ( this->m_stack.top() ).node->children[0] != nullptr || 
                                ( this->m_stack.top() ).node->children[1] != nullptr )
                        {
                            if ( ( this->m_stack.top() ).node->children[0] != nullptr )
                            {
                                ( this->m_stack.top() ).state = StackNode<T>::VISIT_LEFT;
                                this->m_stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, 
                                                                  ( this->m_stack.top() ).node->children[0] ) );
                            }
                             else
                            {
                                ( this->m_stack.top() ).state = StackNode<T>::VISIT_RIGHT;
                                this->m_stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, 
                                                                  ( this->m_stack.top() ).node->children[1] ) );
                            }
                        }
                        ( this->m_stack.top() ).state = StackNode<T>::STAY;
                    }
                    else
                    {
                        _top.state = StackNode<T>::STAY;
                    }
                }
                else if ( _top.state == StackNode<T>::VISIT_RIGHT )
                {
                    _top.state = StackNode<T>::STAY;
                }
            }

            return *this;
        }
    };

    
}