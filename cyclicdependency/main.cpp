
#include <iostream>

#include "CClassTrait.h"


int main()
{
	A<CTrait> a;
	B<CTrait> b;
	C<CTrait> c;

	a.fun_A();
	b.fun_B();
	c.fun_C();

	return 0;
}