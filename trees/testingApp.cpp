
#include <iostream>
#include "CBTree.h"

using namespace std;

int main()
{
    cout << "-------------------------" << endl;
    DS::CBTree<int,DS::functors::GreaterThan<int>> myTree;

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

    DS::CBTree<int,DS::functors::GreaterThan<int>>::post_order_iterator it3;

    it3 = myTree.post_begin();
    it3.consume();

    //for( it3 = myTree.post_begin(); it2 != myTree.post_end(); ++it3 )
    //{
    //    cout << ( *it3 ).data << endl;
    //}

    return 0;
}