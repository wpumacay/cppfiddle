
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


string getLineup( int N, int R, int P, int S )
{
    string _res;

    int rx

    return _res;
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

        vector<string> c_strNums = utils::split( _line );
        vector<int> c_nums;


        for ( int l = 0; l < c_strNums.size(); l++ )
        {
            c_nums.push_back( std::stoi( c_strNums[l] ) );
        }

        int c_N = c_nums[0];
        int c_R = c_nums[1];
        int c_P = c_nums[2];
        int c_S = c_nums[3];

        string sol = getLineup( c_N, c_R, c_P, c_S );

        cout << "Case #" << ( q + 1 ) << ": " << sol << endl;
    }


    _f.close();

}

int main()
{
    
    solve( "A-small-practice.txt" );
    cout << endl << endl;

    return 0;
}