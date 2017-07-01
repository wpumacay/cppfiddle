A simple Tree implementation.


The basic functionality implemented:

CBTree: 
         * find
         * insert
         * erase
         * inOrderTraverse
         * preOrderTraverse
         * postOrderTraverse

         * iterators:
         	->Single class implementation
         		. CBTreeInOrderIterator
         		. CBTreePreOrderIterator
         		. CBTreePostOrderIterator

         	->Forced generalized implementation using 
         		template specialization
         		. CBTreeGeneralSpecializationIterator
         			( for the 3 iterators implemented above )

         	-> Generalized implementation
         		. CBTreeGeneralIterator


testingApp.cpp

		A simple quite unbalanced three is used as test 
		for the tree functionality

		There is a mode in which you can try random trees, is commented
		in line 141. Just change the value from false to true to test it