
#pragma once

#include <cstdlib>
#include <iostream>
#include <cstddef>

#include "CBTreeIterator.h"

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

    template<class T,class FunctorType>
    class CBTreeIterator;

    template<class T,class FunctorType>
    class CBTreeInOrderIterator;

    template<class T,class FunctorType>
    class CBTreePreOrderIterator;

    template<class T,class FunctorType>
    class CBTreePostOrderIterator;


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
        void inOrder( const CBNode<T>* pNode );

        public :

        typedef CBTreeInOrderIterator<T,FunctorType> in_order_iterator;
        typedef CBTreePreOrderIterator<T,FunctorType> pre_order_iterator;
        typedef CBTreePostOrderIterator<T,FunctorType> post_order_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        in_order_iterator begin()
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
            return CBTreeInOrderIterator<T,FunctorType>( _stack );
        }

        in_order_iterator end()
        {
            return CBTreeInOrderIterator<T,FunctorType>();
        }

        pre_order_iterator begin()
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
            return CBTreePreOrderIterator<T,FunctorType>( _stack );
        }

        pre_order_iterator end()
        {
            return CBTreePreOrderIterator<T,FunctorType>();
        }

        post_order_iterator begin()
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
            return CBTreePostOrderIterator<T,FunctorType>( _stack );
        }

        post_order_iterator end()
        {
            return CBTreePostOrderIterator<T,FunctorType>();
        }

        CBTree()
        {
            m_root = nullptr;
        }

        bool find( T x, CBNode<T>** &p );
        bool insert( T x );
        bool erase( T x );
        void inOrderTraverse();
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
void DS::CBTree<T,FunctorType>::inOrderTraverse()
{
    if ( m_root == nullptr )
    {
        return;
    }

    inOrder( m_root->children[0] );
    std::cout << m_root->data << std::endl;
    inOrder( m_root->children[1] );
}

template<class T, class FunctorType>
void DS::CBTree<T,FunctorType>::inOrder( const CBNode<T>* pNode )
{
    if ( pNode == nullptr )
    {
        return;
    }

    inOrder( pNode->children[0] );
    std::cout << pNode->data << std::endl;
    inOrder( pNode->children[1] );
}

