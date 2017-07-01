
#pragma once

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstddef>

// Base class for the iterators
#include "CBTreeIterator.h"
// Single classes for non-general implementations of ...
// the iterators
#include "CBTreePreOrderIterator.h"
#include "CBTreeInOrderIterator.h"
#include "CBTreePostOrderIterator.h"
// General iterators ( second version, by ...
// generalizing the code )
#include "CBTreeGeneralIterator.h"
// Gemerañ iterators ( first version, forced ...
// to one by template specialization )
#include "CBTreeGeneralSpecializationIterator.h"

using namespace std;

namespace DS
{

    namespace functors
    {
        template<class T>
        struct GreaterThan
        {
            __attribute__ ((always_inline)) inline bool operator()( T a, T b )
            {
                return a > b;
            }
        };

        template<class T>
        struct LessThan 
        {
            __attribute__ ((always_inline)) inline bool operator()( T a, T b )
            {
                return a < b;
            }
        };
    }

    template<class T>
    class CBTreeIterator;

    template<class T>
    class CBTreeInOrderIterator;

    template<class T>
    class CBTreePreOrderIterator;

    template<class T>
    class CBTreePostOrderIterator;

    template<class T,class IteratorType>
    class CBTreeGeneralIterator;

    template<class T,class IteratorType>
    class CBTreeGeneralSpecializationIterator;

    template<class T>
    struct StackNode;

    struct InOrder
    {
        static const StackState::_StackState START          = StackState::START;
        static const StackState::_StackState STATE_VISIT_1  = StackState::VISIT_LEFT;
        static const StackState::_StackState STATE_VISIT_2  = StackState::STAY;//visit root
        static const StackState::_StackState STATE_VISIT_3  = StackState::VISIT_RIGHT;//visit right
        static const StackState::_StackState END            = StackState::BACK;// back
    };

    struct PreOrder
    {
        static const StackState::_StackState START          = StackState::START;
        static const StackState::_StackState STATE_VISIT_1  = StackState::STAY;//visit root
        static const StackState::_StackState STATE_VISIT_2  = StackState::VISIT_LEFT;//visit left
        static const StackState::_StackState STATE_VISIT_3  = StackState::VISIT_RIGHT;//visit right
        static const StackState::_StackState END            = StackState::BACK;// back
    };

    struct PostOrder
    {
        static const StackState::_StackState START          = StackState::START;
        static const StackState::_StackState STATE_VISIT_1  = StackState::VISIT_LEFT;//visit left
        static const StackState::_StackState STATE_VISIT_2  = StackState::VISIT_RIGHT;//visit right
        static const StackState::_StackState STATE_VISIT_3  = StackState::STAY;//visit root
        static const StackState::_StackState END            = StackState::BACK;// back
    };

    template<class T>
    struct CBNode
    {
        T data;
        CBNode<T>* children[2];

        CBNode( T x )
        {
            this->data = x;
            this->children[0] = NULL;
            this->children[1] = NULL;
        }
    };

    template<class T, class FunctorType>
    class CBTree
    {

        private :

        CBNode<T>* m_root;
        FunctorType m_comp;
        void findReplace( CBNode<T>** &p, CBNode<T>** &q );
        void inOrder( const CBNode<T>* pNode, vector<int>* pBuff = NULL );
        void preOrder( const CBNode<T>* pNode, vector<int>* pBuff = NULL );
        void postOrder( const CBNode<T>* pNode, vector<int>* pBuff = NULL );

        public :

        typedef CBTreeInOrderIterator<T> in_order_iterator;
        typedef CBTreePreOrderIterator<T> pre_order_iterator;
        typedef CBTreePostOrderIterator<T> post_order_iterator;

        typedef CBTreeGeneralIterator<T,InOrder> g_in_order_iterator;
        typedef CBTreeGeneralIterator<T,PreOrder> g_pre_order_iterator;
        typedef CBTreeGeneralIterator<T,PostOrder> g_post_order_iterator;

        typedef CBTreeGeneralSpecializationIterator<T,InOrder> g_sp_in_order_iterator;
        typedef CBTreeGeneralSpecializationIterator<T,PreOrder> g_sp_pre_order_iterator;
        typedef CBTreeGeneralSpecializationIterator<T,PostOrder> g_sp_post_order_iterator;

        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        // GENERAL ITERATORS BY USING GENERALIZED TRAVERSAL IMPLEMENTATION ********************************************

        g_in_order_iterator g_in_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::START, pToNode ) );
            }
            CBTreeGeneralIterator<T,InOrder> it = CBTreeGeneralIterator<T,InOrder>( _stack );
            ++it;
            return it;
        }

        g_in_order_iterator g_in_end()
        {
            return CBTreeGeneralIterator<T,InOrder>();
        }

        g_pre_order_iterator g_pre_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::START, pToNode ) );
            }
            CBTreeGeneralIterator<T,PreOrder> it = CBTreeGeneralIterator<T,PreOrder>( _stack );
            ++it;
            return it;
        }

        g_pre_order_iterator g_pre_end()
        {
            return CBTreeGeneralIterator<T,PreOrder>();
        }

        g_post_order_iterator g_post_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::START, pToNode ) );
            }
            CBTreeGeneralIterator<T,PostOrder> it = CBTreeGeneralIterator<T,PostOrder>( _stack );
            ++it;
            return it;
        }

        g_post_order_iterator g_post_end()
        {
            return CBTreeGeneralIterator<T,PostOrder>();
        }
        // ********************************************************************************************

        // GENERAL ITERATORS USING TEMPLATE SPECIALIZATION ********************************************

        g_sp_in_order_iterator g_sp_in_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != NULL )
                {
                    pToNode = pToNode->children[0];
                    ( _stack.top() ).state = StackState::STAY;
                    _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                }
                ( _stack.top() ).state = StackState::STAY;
            }
            return CBTreeGeneralSpecializationIterator<T,InOrder>( _stack );
        }

        g_sp_in_order_iterator g_sp_in_end()
        {
            return CBTreeGeneralSpecializationIterator<T,InOrder>();
        }

        g_sp_pre_order_iterator g_sp_pre_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::STAY, pToNode ) );
            }
            return CBTreeGeneralSpecializationIterator<T,PreOrder>( _stack );
        }

        g_sp_pre_order_iterator g_sp_pre_end()
        {
            return CBTreeGeneralSpecializationIterator<T,PreOrder>();
        }

        g_sp_post_order_iterator g_sp_post_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != NULL || pToNode->children[1] != NULL )
                {
                    if ( pToNode->children[0] != NULL )
                    {
                        pToNode = pToNode->children[0];
                        ( _stack.top() ).state = StackState::VISIT_LEFT;
                        _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    }
                    else
                    {
                        pToNode = pToNode->children[1];
                        ( _stack.top() ).state = StackState::VISIT_RIGHT;
                        _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    }
                }
                ( _stack.top() ).state = StackState::STAY;
            }
            return CBTreeGeneralSpecializationIterator<T,PostOrder>( _stack );
        }

        g_sp_post_order_iterator g_sp_post_end()
        {
            return CBTreeGeneralSpecializationIterator<T,PostOrder>();
        }

        // ***************************************************************************************************

        // SIMPLE ITERATORS BY USING AN IMPLEMENTATION FOR EACH ONE ******************************************
        in_order_iterator in_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != NULL )
                {
                    pToNode = pToNode->children[0];
                    ( _stack.top() ).state = StackState::STAY;
                    _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                }
                ( _stack.top() ).state = StackState::STAY;
            }
            return CBTreeInOrderIterator<T>( _stack );
        }

        in_order_iterator in_end()
        {
            return CBTreeInOrderIterator<T>();
        }

        pre_order_iterator pre_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::STAY, pToNode ) );
            }
            return CBTreePreOrderIterator<T>( _stack );
        }

        pre_order_iterator pre_end()
        {
            return CBTreePreOrderIterator<T>();
        }

        post_order_iterator post_begin()
        {
            std::stack<StackNode<T> > _stack;
            if ( m_root != NULL )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != NULL || pToNode->children[1] != NULL )
                {
                    if ( pToNode->children[0] != NULL )
                    {
                        pToNode = pToNode->children[0];
                        ( _stack.top() ).state = StackState::VISIT_LEFT;
                        _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    }
                    else
                    {
                        pToNode = pToNode->children[1];
                        ( _stack.top() ).state = StackState::VISIT_RIGHT;
                        _stack.push( StackNode<T>( StackState::VISIT_LEFT, pToNode ) );
                    }
                }
                ( _stack.top() ).state = StackState::STAY;
            }
            return CBTreePostOrderIterator<T>( _stack );
        }

        post_order_iterator post_end()
        {
            return CBTreePostOrderIterator<T>();
        }

        // ***************************************************************************************************

        CBTree()
        {
            m_root = NULL;
        }

        bool find( T x, CBNode<T>** &p );
        bool insert( T x );
        bool erase( T x );
        void inOrderTraverse( vector<int>* pBuff = NULL );
        void preOrderTraverse( vector<int>* pBuff = NULL );
        void postOrderTraverse( vector<int>* pBuff = NULL );
    };

}

template<class T, class FunctorType>
bool DS::CBTree<T,FunctorType>::find( T x, CBNode<T>** &p )
{
    p = &m_root;

    while( ( *p != NULL ) && ( *p )->data != x )
    {
        p = &( ( *p )->children[m_comp( (*p)->data, x ) ? 0 : 1] );
    }

    return ( *p ) != NULL;
}

template<class T, class FunctorType>
bool DS::CBTree<T,FunctorType>::insert( T x )
{
    CBNode<T>** p;
    if ( find( x, p ) )
    {
        return false;
    }

    ( *p ) = new CBNode<T>( x );

    return true;
}

template<class T, class FunctorType>
bool DS::CBTree<T,FunctorType>::erase( T x )
{
    CBNode<T>** p;
    if ( !find( x, p ) )
    {
        return false;
    }

    // Check if case (2)
    if ( (*p)->children[0] != NULL &&
         (*p)->children[1] != NULL )
    {
        CBNode<T>** q;
        std::cout << "finding replace" << std::endl;
        findReplace( p, q );
        std::cout << "found replace" << std::endl;
        (*p)->data = (*q)->data;
        std::cout << "copying" << std::endl;
        p = q;
    }
    std::cout << "trying to delete" << std::endl;
    // Handle both (1) and (0) cases
    CBNode<T>* t = *p;
    *p = (*p)->children[ (*p)->children[0] == NULL ? 1 : 0];
    delete t;

    std::cout << "deleted successfully" << std::endl;

    return true;
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::findReplace( CBNode<T>** &p, CBNode<T>** &q )
{
    int indxChoice = 0;//rand() % 2;
    q = &( (*p)->children[indxChoice] );
    while ( (*q) != NULL && (*q)->children[1 - indxChoice] != NULL ) 
    {
        q = &( (*q)->children[1 - indxChoice] );
    }
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::inOrderTraverse( vector<int>* pBuff )
{
    if ( m_root == NULL )
    {
        return;
    }

    inOrder( m_root->children[0], pBuff );
    if ( pBuff != NULL )
    {
        pBuff->push_back( m_root->data );
    }
    else
    {
        std::cout << m_root->data << std::endl;
    }
    inOrder( m_root->children[1], pBuff );
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::inOrder( const CBNode<T>* pNode, vector<int>* pBuff )
{
    if ( pNode == NULL )
    {
        return;
    }

    inOrder( pNode->children[0], pBuff );
    if ( pBuff != NULL )
    {
        pBuff->push_back( pNode->data );
    }
    else
    {
        std::cout << pNode->data << std::endl;
    }
    inOrder( pNode->children[1], pBuff );
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::preOrderTraverse( vector<int>* pBuff )
{
    if ( m_root == NULL )
    {
        return;
    }

    if ( pBuff != NULL )
    {
        pBuff->push_back( m_root->data );
    }
    else
    {
        std::cout << m_root->data << std::endl;
    }
    preOrder( m_root->children[0], pBuff );
    preOrder( m_root->children[1], pBuff );
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::preOrder( const CBNode<T>* pNode, vector<int>* pBuff )
{
    if ( pNode == NULL )
    {
        return;
    }

    if ( pBuff != NULL )
    {
        pBuff->push_back( pNode->data );
    }
    else
    {
        std::cout << pNode->data << std::endl;
    }
    preOrder( pNode->children[0], pBuff );
    preOrder( pNode->children[1], pBuff );
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::postOrderTraverse( vector<int>* pBuff )
{
    if ( m_root == NULL )
    {
        return;
    }

    postOrder( m_root->children[0], pBuff );
    postOrder( m_root->children[1], pBuff );
    if ( pBuff != NULL )
    {
        pBuff->push_back( m_root->data );
    }
    else
    {
        std::cout << m_root->data << std::endl;
    }
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::postOrder( const CBNode<T>* pNode, vector<int>* pBuff )
{
    if ( pNode == NULL )
    {
        return;
    }

    postOrder( pNode->children[0], pBuff );
    postOrder( pNode->children[1], pBuff );
    if ( pBuff != NULL )
    {
        pBuff->push_back( pNode->data );
    }
    else
    {
        std::cout << pNode->data << std::endl;
    }
}