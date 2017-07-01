
#pragma once

#include "CBTreeIterator.h"

namespace DS
{
    struct PreOrder;
    struct PostOrder;
    struct InOrder;

    template<class T,class TypeIterator>
    class CBTreeGeneralSpecializationIterator : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralSpecializationIterator(){}

        CBTreeGeneralSpecializationIterator( const CBTreeGeneralSpecializationIterator<T,TypeIterator>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralSpecializationIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralSpecializationIterator<T,TypeIterator>& operator++()
        {
            // Specialize this
            return *this;
        }

    };
    
    template<class T>
    class CBTreeGeneralSpecializationIterator<T,PreOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralSpecializationIterator(){}

        CBTreeGeneralSpecializationIterator( const CBTreeGeneralSpecializationIterator<T,PreOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralSpecializationIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralSpecializationIterator<T,PreOrder>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }
            
            StackNode<T> _top = this->m_stack.top();
            this->m_stack.pop();
            if ( _top.node->children[1] != NULL )
            {
                this->m_stack.push( StackNode<T>( StackState::STAY, _top.node->children[1] ) );
            }
            if ( _top.node->children[0] != NULL ) 
            {
                this->m_stack.push( StackNode<T>( StackState::STAY, _top.node->children[0] ) );
            }
            

            return *this;
        }

    };
    

    template<class T>
    class CBTreeGeneralSpecializationIterator<T,InOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralSpecializationIterator(){}

        CBTreeGeneralSpecializationIterator( const CBTreeGeneralSpecializationIterator<T,InOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralSpecializationIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralSpecializationIterator<T,InOrder>& operator++()
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

    template<class T>
    class CBTreeGeneralSpecializationIterator<T,PostOrder> : public CBTreeIterator<T>
    {

        public :

        CBTreeGeneralSpecializationIterator(){}

        CBTreeGeneralSpecializationIterator( const CBTreeGeneralSpecializationIterator<T,PostOrder>& other )
        {
            this->m_stack = other.m_stack;
        }

        CBTreeGeneralSpecializationIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralSpecializationIterator<T,PostOrder>& operator++()
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
