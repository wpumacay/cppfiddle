
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

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

int moveNumToSide( vector<int> &nums, int fromIndx, int side )
{
	int count = 0;

	if ( side == 0 )
	{
		while ( fromIndx >= 1 )
		{
			if ( nums[fromIndx] < nums[fromIndx - 1] )
			{
				int _tmp = nums[fromIndx];
				nums[fromIndx] = nums[fromIndx - 1];
				nums[fromIndx - 1] = _tmp;
				count++;
				fromIndx--;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		while ( fromIndx <= nums.size() - 2 )
		{
			if ( nums[fromIndx] < nums[fromIndx + 1] )
			{
				int _tmp = nums[fromIndx];
				nums[fromIndx] = nums[fromIndx + 1];
				nums[fromIndx + 1] = _tmp;
				count++;
				fromIndx++;
			}
			else
			{
				break;
			}
		}
	}

	return count;
}

int getMinimumSwaps( vector<int> &nums )
{
	// utils::printvector( nums );

	vector<int> nums_sorted = nums;
	sort( nums_sorted.begin(), nums_sorted.end() );

	int side = 0;

	int sol = 0;

	for ( int q = 0; q < nums_sorted.size(); q++ )
	{
		int _indx = utils::indexof<int>( nums, nums_sorted[q] );
		vector<int> nums1 = nums;
		vector<int> nums2 = nums;
		int sol1 = moveNumToSide( nums1, _indx, 0 );
		int sol2 = moveNumToSide( nums2, _indx, 1 );
		if ( sol1 < sol2 )
		{
			nums = nums1;
			sol += sol1;
		}
		else
		{
			nums = nums2;
			sol += sol2;
		}
	}

	// utils::printvector( nums );

	return sol;
}

void solve( const char path[] )
{
	ifstream _f( path );

	if ( !_f.is_open() )
	{
		cout << "couldnot open file" << endl;
		return;
	}

	string _line;


	getline( _f, _line );

	int N = std::stoi( _line );

	for ( int q = 0; q < N; q++ )
	{
		getline( _f, _line );
		
		int c_nNums = std::stoi( _line );

		getline( _f, _line );
		
		vector<string> c_strNums = utils::split( _line );
		vector<int> c_nums;


		for ( int l = 0; l < c_strNums.size(); l++ )
		{
			c_nums.push_back( std::stoi( c_strNums[l] ) );
		}

		int sol = getMinimumSwaps( c_nums );

		cout << "Case #" << ( q + 1 ) << ": " << sol << endl;
	}


	_f.close();

}


int main()
{
	
	solve( "B-small-practice.txt" );
	cout << endl << endl;
	solve( "B-large-practice.txt" );

	return 0;
}