
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

        CBTreeGeneralIterator( std::stack<StackNode<T> > &pStack )
        {
            this->m_stack = pStack;
        }

        CBTreeGeneralIterator<T,TypeIterator>& operator++()
        {
            if ( this->m_stack.size() == 0 )
            {
                return *this;
            }

            do
            {
                StackNode<T>& _top = this->m_stack.top();
                switch ( _top.state )
                {
                    case TypeIterator::START :
                        _top.state = TypeIterator::STATE_VISIT_1;
                        visitNext( _top, TypeIterator::STATE_VISIT_1 );
                    break;

                    case TypeIterator::STATE_VISIT_1 :
                        visitNext( _top, TypeIterator::STATE_VISIT_2 );
                    break;

                    case TypeIterator::STATE_VISIT_2 :
                        visitNext( _top, TypeIterator::STATE_VISIT_3 );
                    break;

                    case TypeIterator::STATE_VISIT_3 :
                        visitNext( _top, TypeIterator::END );
                    break;

                    case TypeIterator::END :
                        // GO up one level
                        this->m_stack.pop();
                        if ( this->m_stack.size() > 0 )
                        {
                            if ( ( this->m_stack.top() ).state == TypeIterator::STATE_VISIT_1 )
                            {
                                ( this->m_stack.top() ).state = TypeIterator::STATE_VISIT_2;
                            }
                            else if ( ( this->m_stack.top() ).state == TypeIterator::STATE_VISIT_2 )
                            {
                                ( this->m_stack.top() ).state = TypeIterator::STATE_VISIT_3;
                            }
                            else if ( ( this->m_stack.top() ).state == TypeIterator::STATE_VISIT_3 )
                            {
                                ( this->m_stack.top() ).state = TypeIterator::END;
                            }
                        }
                    break;
                }


            } while ( ( this->m_stack.size() > 0 ) &&
                      ( ( this->m_stack.top() ).state != StackState::STAY ) );

            return *this;
        }

        void visitNext( StackNode<T> &top, StackState::_StackState nextState )
        {
            

            if ( top.state == StackState::VISIT_LEFT || nextState == StackState::VISIT_LEFT )
            {
                if ( top.node->children[0] != NULL )
                {
                    this->m_stack.push( StackNode<T>( StackState::START, top.node->children[0] ) );
                }
                else
                {
                    if ( nextState == TypeIterator::STATE_VISIT_1 )
                    {
                        top.state = TypeIterator::STATE_VISIT_2;
                    }
                    else if ( nextState == TypeIterator::STATE_VISIT_2 )
                    {
                        top.state = TypeIterator::STATE_VISIT_3;
                    }
                    else if ( nextState == TypeIterator::STATE_VISIT_3 )
                    {
                        if ( nextState != StackState::STAY )
                        {
                            top.state = TypeIterator::END;
                        }
                        else
                        {
                            top.state = nextState;
                        }
                    }
                    else if ( nextState == TypeIterator::END )
                    {
                        top.state = TypeIterator::END;
                    }
                    return;
                }
            }
            else if ( top.state == StackState::VISIT_RIGHT || nextState == StackState::VISIT_RIGHT )
            {
                if ( top.node->children[1] != NULL )
                {
                    this->m_stack.push( StackNode<T>( StackState::START, top.node->children[1] ) );
                    if ( nextState == StackState::STAY )
                    {
                        return;
                    }
                }
                else
                {
                    if ( nextState == TypeIterator::STATE_VISIT_1 )
                    {
                        top.state = TypeIterator::STATE_VISIT_2;
                    }
                    else if ( nextState == TypeIterator::STATE_VISIT_2 )
                    {
                        top.state = TypeIterator::STATE_VISIT_3;
                    }
                    else if ( nextState == TypeIterator::STATE_VISIT_3 )
                    {
                        if ( nextState != StackState::STAY )
                        {
                            top.state = TypeIterator::END;
                        }
                        else
                        {
                            top.state = nextState;
                        }
                    }
                    else if ( nextState == TypeIterator::END )
                    {
                        top.state = TypeIterator::END;
                    }
                    return;
                }
            }

            top.state = nextState;
        }

    };
    
}
