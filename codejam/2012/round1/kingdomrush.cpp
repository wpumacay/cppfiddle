
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct Pair
{
    int val;
    int indx;
};

bool compare( const &Pair &p1, const Pair &p2 )
{
    return p1.val < p2.val;
}

vector<string> split( const string &txt )
{
    int pos = txt.find( ' ' );
    int initpos = 0;
    vector<string> _res;

    while ( pos != std::string::npos )
    {
        _res.push_back( txt.substr( initpos, pos - initpos + 1 );
        initpos = pos + 1;

        pos = txt.find( ' ', initpos );
    }

    _res.push_back( txt.substr( initpos, std::min( pos, txt.size() ) - initpos + 1 ) );
    
    return _res;
}



int getMinGames( vector<int> stars_1, vector<int> stars_2  )
{
    int res;

    vector<Pair> elems_1;
    vector<Pair> elems_2;

    for ( int q = 0; q < stars_1.size(); q++ )
    {
        Pair _fun;
        _fun.val = stars_1[q];
        _fun.indx = q;

        Pair _foo;
        _foo.val = stars_2[q];
        _foo.indx = q;
    
        elems_1.push_back( _fun );
        elems_2.push_back( _foo );
    }    

    std::sort( elems_1.begin(), elems_1.end() );
    std::sort( elems_2.begin(), elems_2.end() );

    std::sort( stars_1.begin(), stars_1.end() );
    std::sort( stars_2.begin(), stars_2.end() );

    int nStars = 0;
    int p1 = 0;
    int p2 = 0;

    while ( p1 < stars_1.size() && p2 < stars_2.size() )
    {
        if ( p1 < stars_1.size() && nStars >= stars_1[p1] )
        {
            nStars += 1;
            p1++;
            res++;
        }
        else if ( p2 < stars_2.size() && nStars >= stars_2[p2] )
        {
            nStars += stars_2[p2]
            p2++;
            res++;
        }
        else
        {
            res = -1;
            break;
        }
        
    }


    return res;
}




int main()
{

    
    ifstream _f( "B-small-practice.txt" );

    if ( !_f.is_open() )
    {
        return -1;
    }

    string _line;

    getline( _f, _line );

    int N = std::stoi( _line );
    for ( int q = 0; q < N; q++ )
    {
        getline( _f, _line );
        int n = std::stoi( _line );
        vector<int> stars_1;
        vector<int> stars_2;
        for ( int p = 0; p < n; p++ )
        {
            string str_cases;
            getline( _f, str_cases );
            vector<string> _strs_stars = split( str_cases );
            int n_stars_1 = std::stoi( _strs[0] );
            int n_stars_2 = std::stoi( _strs[1] );

            stars_1.push_back( n_stars_1 );
            stars_2.push_back( n_stars_2 );

            int best = getMinGames( stars_1, stars_2 );
            cout << best << endl;
        }
    }

    _f.close();

    return 0;
}
