

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

    std::cout << "printing using iterators: " << std::endl;

    DS::COrderedListNormal<int>::iterator it;
    for( it = myListNormal.begin(); it != myListNormal.end(); it++ )
    {
        std::cout << ( *it ).data << std::endl;
    }

    return 0;
}