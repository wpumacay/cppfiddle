
#pragma once

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstddef>

#include "CBTreeIterator.h"
#include "CBTreePreOrderIterator.h"
#include "CBTreeInOrderIterator.h"
#include "CBTreePostOrderIterator.h"
#include "CBTreeGeneralIterator.h"

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

    struct InOrder
    {

    };

    struct PreOrder
    {

    };

    struct PostOrder
    {

    };

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

    template<class T>
    struct StackNode;

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
        void inOrder( const CBNode<T>* pNode, vector<int>* pBuff = nullptr );
        void preOrder( const CBNode<T>* pNode, vector<int>* pBuff = nullptr );
        void postOrder( const CBNode<T>* pNode, vector<int>* pBuff = nullptr );

        public :

        typedef CBTreeInOrderIterator<T> in_order_iterator;
        typedef CBTreePreOrderIterator<T> pre_order_iterator;
        typedef CBTreePostOrderIterator<T> post_order_iterator;

        typedef CBTreeGeneralIterator<T,InOrder> g_in_order_iterator;
        typedef CBTreeGeneralIterator<T,PreOrder> g_pre_order_iterator;
        typedef CBTreeGeneralIterator<T,PostOrder> g_post_order_iterator;

        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        g_in_order_iterator g_in_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != nullptr )
                {
                    pToNode = pToNode->children[0];
                    ( _stack.top() ).state = StackNode<T>::STAY;
                    _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                }
                ( _stack.top() ).state = StackNode<T>::STAY;
            }
            return CBTreeGeneralIterator<T,InOrder>( _stack );
        }

        g_in_order_iterator g_in_end()
        {
            return CBTreeGeneralIterator<T,InOrder>();
        }

        g_pre_order_iterator g_pre_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
            }
            return CBTreeGeneralIterator<T,PreOrder>( _stack );
        }

        g_pre_order_iterator g_pre_end()
        {
            return CBTreeGeneralIterator<T,PreOrder>();
        }

        g_post_order_iterator g_post_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != nullptr || pToNode->children[1] != nullptr )
                {
                    if ( pToNode->children[0] != nullptr )
                    {
                        pToNode = pToNode->children[0];
                        ( _stack.top() ).state = StackNode<T>::VISIT_LEFT;
                        _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    }
                    else
                    {
                        pToNode = pToNode->children[1];
                        ( _stack.top() ).state = StackNode<T>::VISIT_RIGHT;
                        _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    }
                }
                ( _stack.top() ).state = StackNode<T>::STAY;
            }
            return CBTreeGeneralIterator<T,PostOrder>( _stack );
        }

        g_post_order_iterator g_post_end()
        {
            return CBTreeGeneralIterator<T,PostOrder>();
        }




        in_order_iterator in_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != nullptr )
                {
                    pToNode = pToNode->children[0];
                    ( _stack.top() ).state = StackNode<T>::STAY;
                    _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                }
                ( _stack.top() ).state = StackNode<T>::STAY;
            }
            return CBTreeInOrderIterator<T>( _stack );
        }

        in_order_iterator in_end()
        {
            return CBTreeInOrderIterator<T>();
        }

        pre_order_iterator pre_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::STAY, pToNode ) );
            }
            return CBTreePreOrderIterator<T>( _stack );
        }

        pre_order_iterator pre_end()
        {
            return CBTreePreOrderIterator<T>();
        }

        post_order_iterator post_begin()
        {
            std::stack<StackNode<T>> _stack;
            if ( m_root != nullptr )
            {
                CBNode<T>* pToNode = m_root;
                _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );

                while ( pToNode->children[0] != nullptr || pToNode->children[1] != nullptr )
                {
                    if ( pToNode->children[0] != nullptr )
                    {
                        pToNode = pToNode->children[0];
                        ( _stack.top() ).state = StackNode<T>::VISIT_LEFT;
                        _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    }
                    else
                    {
                        pToNode = pToNode->children[1];
                        ( _stack.top() ).state = StackNode<T>::VISIT_RIGHT;
                        _stack.push( StackNode<T>( StackNode<T>::VISIT_LEFT, pToNode ) );
                    }
                }
                ( _stack.top() ).state = StackNode<T>::STAY;
            }
            return CBTreePostOrderIterator<T>( _stack );
        }

        post_order_iterator post_end()
        {
            return CBTreePostOrderIterator<T>();
        }

        CBTree()
        {
            m_root = nullptr;
        }

        bool find( T x, CBNode<T>** &p );
        bool insert( T x );
        bool erase( T x );
        void inOrderTraverse( vector<int>* pBuff = nullptr );
        void preOrderTraverse( vector<int>* pBuff = nullptr );
        void postOrderTraverse( vector<int>* pBuff = nullptr );
    };

}

template<class T, class FunctorType>
bool DS::CBTree<T,FunctorType>::find( T x, CBNode<T>** &p )
{
    p = &m_root;

    while( ( *p != nullptr ) && ( *p )->data != x )
    {
        p = &( ( *p )->children[m_comp( (*p)->data, x ) ? 0 : 1] );
    }

    return ( *p ) != nullptr;
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
    if ( (*p)->children[0] != nullptr &&
         (*p)->children[1] != nullptr )
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
    *p = (*p)->children[ (*p)->children[0] == nullptr ? 1 : 0];
    delete t;

    std::cout << "deleted successfully" << std::endl;

    return true;
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::findReplace( CBNode<T>** &p, CBNode<T>** &q )
{
    int indxChoice = 0;//rand() % 2;
    q = &( (*p)->children[indxChoice] );
    while ( (*q) != nullptr && (*q)->children[1 - indxChoice] != nullptr ) 
    {
        q = &( (*q)->children[1 - indxChoice] );
    }
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::inOrderTraverse( vector<int>* pBuff )
{
    if ( m_root == nullptr )
    {
        return;
    }

    inOrder( m_root->children[0], pBuff );
    if ( pBuff != nullptr )
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
    if ( pNode == nullptr )
    {
        return;
    }

    inOrder( pNode->children[0], pBuff );
    if ( pBuff != nullptr )
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
    if ( m_root == nullptr )
    {
        return;
    }

    if ( pBuff != nullptr )
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
    if ( pNode == nullptr )
    {
        return;
    }

    if ( pBuff != nullptr )
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
    if ( m_root == nullptr )
    {
        return;
    }

    postOrder( m_root->children[0], pBuff );
    postOrder( m_root->children[1], pBuff );
    if ( pBuff != nullptr )
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
    if ( pNode == nullptr )
    {
        return;
    }

    postOrder( pNode->children[0], pBuff );
    postOrder( pNode->children[1], pBuff );
    if ( pBuff != nullptr )
    {
        pBuff->push_back( pNode->data );
    }
    else
    {
        std::cout << pNode->data << std::endl;
    }
}