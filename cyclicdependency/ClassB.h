
#pragma once
#include <iostream>

#include "CClassTrait.h"

using namespace std;

template<class cTypes>
class B
{
	public :

	typedef typename cTypes::cA A;
	typedef typename cTypes::cC C;

	A* p_A;
	C* p_C;

	void fun_B()
	{
		cout << "fun from B" << endl;
	}
};