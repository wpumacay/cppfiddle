
#include <iostream>
#include <vector>
#include <cstdlib>
#include "CBTree.h"

using namespace std;

int main()
{
    cout << "-------------------------" << endl;
    DS::CBTree<int,DS::functors::GreaterThan<int>> myTree;

    /*
    myTree.insert( 63 );
    myTree.insert( 35 );
    myTree.insert( 72 );
    myTree.insert( 15 );
    myTree.insert( 48 );
    myTree.insert( 69 );
    myTree.insert( 83 );
    myTree.insert( 20 );
    myTree.insert( 40 );
    myTree.insert( 55 );
    myTree.insert( 17 );
    myTree.insert( 25 );
    */

    
    myTree.insert( 84 );
    myTree.insert( 87 );
    myTree.insert( 78 );
    myTree.insert( 16 );
    myTree.insert( 94 );
    myTree.insert( 36 );
    myTree.insert( 87 );
    myTree.insert( 93 );
    myTree.insert( 50 );
    myTree.insert( 22 );
    myTree.insert( 63 );
    myTree.insert( 28 );
    myTree.insert( 91 );
    myTree.insert( 60 );
    myTree.insert( 64 );
    myTree.insert( 27 );
    myTree.insert( 41 );
    myTree.insert( 27 );
    myTree.insert( 73 );
    myTree.insert( 37 );
    

    cout << "inorder-recursive" << endl;

    myTree.inOrderTraverse();

    cout << "inorder-iterators" << endl;
    
    DS::CBTree<int,DS::functors::GreaterThan<int>>::in_order_iterator it;
    
    for( it = myTree.in_begin(); it != myTree.in_end(); ++it )
    {
        cout << ( *it ).data << endl;
    }
    
    cout << "preorder-recursive" << endl;

    myTree.preOrderTraverse();

    cout << "preorder-iterators" << endl;

    DS::CBTree<int,DS::functors::GreaterThan<int>>::pre_order_iterator it2;

    for( it2 = myTree.pre_begin(); it2 != myTree.pre_end(); ++it2 )
    {
        cout << ( *it2 ).data << endl;
    }
    
    cout << "postorder-recursive" << endl;

    myTree.postOrderTraverse();

    cout << "postorder-iterators" << endl;    

    DS::CBTree<int,DS::functors::GreaterThan<int>>::post_order_iterator it3, itDummy;

    
    for( it3 = myTree.post_begin(); it3 != myTree.post_end(); ++it3 )
    {
        /// itDummy = it3;
        cout << ( *it3 ).data << endl;
        /// itDummy.consume();
        /// cin.get();
    }

    
    while( true )
    {
        DS::CBTree<int,DS::functors::GreaterThan<int>> _tree;
        int q;
        vector<int> _nums;
        for( q = 0; q < 20; q++ )
        {
            int _num = rand() % 100 + 1;
            _tree.insert( _num );
            _nums.push_back( _num );
        }
        cout << "testing: ";
        for( q = 0; q < _nums.size(); q++ )
        {
            cout << _nums[q] << " ";
        }
        cout << endl;
        // checking in-order traversal
        
        {
            vector<int> _order1;
            vector<int> _order2;
            cout << "in-order-recursive" << endl;
            _tree.inOrderTraverse( &_order1 );
            cout << "in-order-iterators" << endl;
            DS::CBTree<int,DS::functors::GreaterThan<int>>::in_order_iterator _it;
            for( _it = _tree.in_begin(); _it != _tree.in_end(); ++_it )
            {
                _order2.push_back( ( *_it ).data );
            }
            if ( _order2 != _order1 )
            {
                cout << "an error occurred here!" << endl;
                cout << "order1: " << endl;
                for( q = 0; q < _order1.size(); q++ )
                {
                    cout << _order1[q] << " ";
                }
                cout << endl;
                cout << "order2: " << endl;
                for( q = 0; q < _order2.size(); q++ )
                {
                    cout << _order2[q] << " ";
                }
                cout << endl;

                break;
            }

        }
        
        
        {
            vector<int> _order1;
            vector<int> _order2;
            cout << "pre-order-recursive" << endl;
            _tree.preOrderTraverse( &_order1 );
            cout << "pre-order-iterators" << endl;
            DS::CBTree<int,DS::functors::GreaterThan<int>>::pre_order_iterator _it;
            for( _it = _tree.pre_begin(); _it != _tree.pre_end(); ++_it )
            {
                _order2.push_back( ( *_it ).data );
            }
            if ( _order2 != _order1 )
            {
                cout << "an error occurred here!" << endl;
                cout << "order1: " << endl;
                for( q = 0; q < _order1.size(); q++ )
                {
                    cout << _order1[q] << " ";
                }
                cout << endl;
                cout << "order2: " << endl;
                for( q = 0; q < _order2.size(); q++ )
                {
                    cout << _order2[q] << " ";
                }
                cout << endl;

                break;
            }

        }
        
        {
            vector<int> _order1;
            vector<int> _order2;
            cout << "post-order-recursive" << endl;
            _tree.postOrderTraverse( &_order1 );
            cout << "post-order-iterators" << endl;
            DS::CBTree<int,DS::functors::GreaterThan<int>>::post_order_iterator _it;
            for( _it = _tree.post_begin(); _it != _tree.post_end(); ++_it )
            {
                _order2.push_back( ( *_it ).data );
            }
            if ( _order2 != _order1 )
            {
                cout << "an error occurred here!" << endl;
                cout << "order1: " << endl;
                for( q = 0; q < _order1.size(); q++ )
                {
                    cout << _order1[q] << " ";
                }
                cout << endl;
                cout << "order2: " << endl;
                for( q = 0; q < _order2.size(); q++ )
                {
                    cout << _order2[q] << " ";
                }
                cout << endl;

                break;
            }

        }
        
    }

    return 0;
}