
#include <iostream>
#include "CBTree.h"

using namespace std;

int main()
{
    DS::CBTree<int,DS::functors::GreaterThan<int>> myTree;

    myTree.insert( 63 );
    myTree.insert( 35 );
    myTree.insert( 72 );
    myTree.insert( 15 );
    myTree.insert( 48 );
    myTree.insert( 69 );
    myTree.insert( 83 );

    myTree.inOrderTraverse();

    cout << "---- iterators" << endl;

    DS::CBTree<int,DS::functors::GreaterThan<int>>::in_order_iterator itFoo;
    
    for( itFoo = myTree.begin(); itFoo != myTree.end(); ++itFoo )
    {
        std::cout << ( *itFoo ).data << std::endl;
    }

    cout << "----" << endl;

    myTree.erase( 63 );

    myTree.inOrderTraverse();

    cout << "----" << endl;

    DS::CBTree<int,DS::functors::GreaterThan<int>> myTree2;

    myTree2.insert( 63 );
    myTree2.insert( 35 );
    myTree2.insert( 72 );
    myTree2.insert( 15 );
    myTree2.insert( 48 );
    myTree2.insert( 69 );
    myTree2.insert( 83 );
    myTree2.insert( 40 );
    myTree2.insert( 55 );

    myTree2.inOrderTraverse();

    cout << "---- iterators" << endl;

    DS::CBTree<int,DS::functors::GreaterThan<int>>::in_order_iterator it;
    
    for( it = myTree2.begin(); it != myTree2.end(); ++it )
    {
        std::cout << ( *it ).data << std::endl;
    }
    

    return 0;
}