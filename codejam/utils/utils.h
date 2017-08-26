
#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace utils
{

	vector<string> split( const string &txt )
	{
	    vector<string> _res;
		
	    int pos = txt.find( ' ' );
	    if ( pos == std::string::npos )
	    {
	    	_res.push_back( txt );
	    	return _res;
	    }

	    int initpos = 0;

	    while ( pos != std::string::npos )
	    {
	        _res.push_back( txt.substr( initpos, pos - initpos + 1 ) );
	        initpos = pos + 1;

	        pos = txt.find( ' ', initpos );
	    }

	    _res.push_back( txt.substr( initpos, std::min( pos, (int) txt.size() ) - initpos + 1 ) );
	    
	    return _res;
	}

	template<class T>
	void printvector( const vector<T> &vec )
	{
		for ( int q = 0; q < vec.size(); q++ )
		{
			cout << vec[q] << " ";
		}

		cout << endl;
	}

	template<class T>
	int indexof( const vector<T> &vec, T val )
	{
		int indx = -1;
		for ( int  q = 0; q < vec.size(); q++ )
		{
			if ( val == vec[q] )
			{
				indx = q;
				break;
			}
		}

		return indx;
	}

}