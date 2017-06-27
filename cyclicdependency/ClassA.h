
#pragma once
#include <iostream>

#include "CClassTrait.h"

using namespace std;

template<class cTypes>
class A
{
	public :

	typedef typename cTypes::cB B;
	typedef typename cTypes::cC C;

	B* p_B;
	C* p_C;

	void fun_A()
	{
		cout << "fun from A" << endl;
	}
};