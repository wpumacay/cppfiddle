

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class FloatingMedian
{

public :

    long long sumOfMedians( long int seed, long int mul, long int add, long int N, long int K )
    {

        long int _tk = seed;
        vector<long int> _temps;
        _temps.push_back( _tk );

        for ( long int q = 0; q < N; q++ )
        {
            _tk = ( _tk * mul + add ) % 65536;
            _temps.push_back( _tk );
        }

        long long _sum = 0;

        vector<long int> _slice;

        for ( long int q = 0; q < N - K + 1; q++ )
        {
            if ( q == 0 )
            {
                for ( long int i = 0; i < K; i++ )
                {
                    _slice.push_back( _temps[i] );
                }
                sort( _slice.begin(), _slice.end() );
            }
            else
            {
                long int _left = _temps[q - 1];
                long int _right = _temps[q + K - 1];
                // cout << vectorIndexOf( _slice, _left ) << endl;
                _slice.erase( _slice.begin() + vectorIndexOf( _slice, _left ) );
                _slice.push_back( _right );
                long int _end = K - 1;
                long int _l = 0;
                long int _r = K - 2;
                long int _mid = ( _l + _r ) / 2;
                if ( _slice[_end] < _slice[_l] )
                {
                    _slice.insert( _slice.begin(), _slice[_end] );
                    _slice.pop_back();
                }
                else if ( _slice[_end] <= _slice[_r] )
                {
                    while ( true )
                    {
                        if ( _slice[_end] > _slice[_mid] )
                        {
                            _l = _mid;
                        }
                        else
                        {
                            _r = _mid;
                        }
                        _mid = ( _l + _r ) / 2;
                        if ( _l >= _mid )
                        {
                            break;
                        }
                    }
                    _slice.insert( _slice.begin() + _r, _slice[_end] );
                    _slice.pop_back();
                }
            }
            long int _median = _slice[ ( K - 1 ) / 2 ];
            // printVector( _slice );
            _sum += _median;
            // cout << "med: " << _median << endl;
        }

        return _sum;
    } 

    long int vectorIndexOf( const vector<long int>& vect, long int val )
    {
        long int _indx = -1;

        for ( long int q = 0; q < vect.size(); q++ )
        {
            if ( vect[q] == val )
            {
                _indx = q;
                break;
            }
        }

        return _indx;
    }

    void printVector( const vector<long int>& vect )
    {
        cout << "[ ";
        for ( long int q = 0; q < vect.size(); q++ )
        {
            cout << vect[q] << " ";
        }
        cout << "]" << endl;
    }

};






int main()
{

    FloatingMedian _prob;

    cout << "-> " << _prob.sumOfMedians( 3, 1, 1, 10, 3 ) << endl;
    cout << "-> " << _prob.sumOfMedians( 10, 0, 13, 5, 2 ) << endl;
    cout << "-> " << _prob.sumOfMedians( 4123, 2341, 1231, 7, 3 ) << endl;
    cout << "-> " << _prob.sumOfMedians( 47, 5621, 1, 125000, 1700 ) << endl;
    cout << "-> " << _prob.sumOfMedians( 32321, 46543, 32552, 17, 17 ) << endl;


}
