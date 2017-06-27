
#pragma once

#include "ClassA.h"
#include "ClassB.h"
#include "ClassC.h"



class CTrait
{

	public :
	
	typedef CTrait self;
	typedef A<self> cA;
	typedef B<self> cB;
	typedef C<self> cC;
};