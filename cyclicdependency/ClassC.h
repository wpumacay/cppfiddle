
#pragma once
#include <iostream>

#include "CClassTrait.h"

using namespace std;

template<class cTypes>
class C
{
	public :

	typedef typename cTypes::cA A;
	typedef typename cTypes::cB B;

	B* p_B;
	A* p_A;

	void fun_C()
	{
		cout << "fun from C" << endl;
	}
};