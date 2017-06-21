

#include <iostream>
#include "listVariations/COrderedList_normal.h"
#include "listVariations/COrderedList_fpointers.h"
#include "listVariations/COrderedList_polymorphism.h"
#include "listVariations/COrderedList_functors.h"


int main()
{
    std::cout << "Normal comp ordered list ********************" << std::endl;
    DS::COrderedListNormal<int> myListNormal;

    myListNormal.insert( 3 );
    myListNormal.insert( 1 );
    myListNormal.insert( 4 );

    myListNormal.printList();

    DS::COrderedListNormal<int>::iterator it;
    for( it = myListNormal.begin(); it != myListNormal.end(); it++ )
    {
        std::cout << ( *it ).data << std::endl;
    }

    std::cout << "Fpointers comp ordered list *****************" << std::endl;
    DS::COrderedListFpointers<int> myListFPointers( DS::comparationFunctions::lessThan<int> );

    myListFPointers.insert( 3 );
    myListFPointers.insert( 1 );
    myListFPointers.insert( 4 );

    myListFPointers.printList();

    std::cout << "Polymorphic comp ordered list ***************" << std::endl;
    DS::polyComparators::Comparator<int>* _comp = new DS::polyComparators::LessComparator<int>();
    DS::COrderedListPolymorphic<int> myListFPolymorphic( _comp );

    myListFPolymorphic.insert( 3 );
    myListFPolymorphic.insert( 1 );
    myListFPolymorphic.insert( 4 );
    myListFPolymorphic.erase( 1 );

    myListFPolymorphic.printList();

    std::cout << "Functors comp ordered list ******************" << std::endl;
    DS::COrderedListFunctors<int, DS::functors::LessThan<int>> myListFunctors;

    myListFunctors.insert( 3 );
    myListFunctors.insert( 1 );
    myListFunctors.insert( 4 );

    myListFunctors.printList();

    return 0;
}