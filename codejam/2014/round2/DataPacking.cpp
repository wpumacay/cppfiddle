

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

struct CFile
{
	int size;
	bool stored;
};

bool comparatorFiles( const CFile& f1, const CFile& f2 )
{
	return f1.size < f2.size;
}

int getMinimumDisks( int nFiles, int discsSize, vector<int> &filesSizes )
{
	int sol = 0;

	vector<CFile> _files;

	for ( int q = 0; q < filesSizes.size(); q++ )
	{
		CFile _file;
		_file.size = filesSizes[q];
		_file.stored = false;

		_files.push_back( _file );
	}

	// Sort the items
	sort( _files.begin(), _files.end(), comparatorFiles );

	// start from the end
	int _currFileIndx = _files.size() - 1;
	while ( true )
	{
		if ( !_files[_currFileIndx].stored )
		{

			for ( int c = _currFileIndx - 1; c >= 0; c-- )
			{
				if ( _files[c].stored )
				{
					continue;
				}

				if ( _files[_currFileIndx].size + _files[c].size <= discsSize )
				{
					// Pack it both into a same disk
					_files[_currFileIndx].stored = true;
					_files[c].stored = true;
					sol++;
					break;
				}
			}

			if ( _files[_currFileIndx].stored == false )
			{
				// Pack it into one disk lonely
				_files[_currFileIndx].stored = true;
				sol++;
			}
		}
		_currFileIndx--;

		bool remainingToPack = false;

		for ( int q = 0; q < _files.size(); q++ )
		{
			if ( !_files[q].stored )
			{
				remainingToPack = true;
			}
		}
		if ( !remainingToPack )
		{
			break;
		}
	}


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
		vector<string> _strs_data_1 = utils::split( _line );
		getline( _f, _line );
		vector<string> _strs_data_2 = utils::split( _line );

		int c_nFiles = std::stoi( _strs_data_1[0] );
		int c_discsSize = std::stoi( _strs_data_1[1] );

		vector<int> c_files_sizes;

		for ( int l = 0; l < _strs_data_2.size(); l++ )
		{
			c_files_sizes.push_back( std::stoi( _strs_data_2[l] ) );
		}

		int sol = getMinimumDisks( c_nFiles, c_discsSize, c_files_sizes );

		cout << "Case #" << ( q + 1 ) << ": " << sol << endl;
	}


	_f.close();
}


int main()
{
	
	solve( "A-small-practice.txt" );
	cout << endl << endl;
	solve( "A-large-practice.txt" );

	return 0;
}