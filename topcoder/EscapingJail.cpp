
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

#define PSEUDO_INFINITY 1000000

class EscapingJail
{

    private :

    int *m_graphMat;
    int m_numVerts;

    int getCost( int fromIndx, int toIndx )
    {
        return *( m_graphMat + fromIndx * m_numVerts + toIndx );
    }

    void initializeGraphMatrix( const vector<string> &chain )
    {
        m_numVerts = chain.size();

        if ( m_graphMat != NULL )
        {
            delete[] m_graphMat;
        }
        m_graphMat = new int[m_numVerts * m_numVerts];

        int i,j;
        for ( i = 0; i < m_numVerts; i++ )
        {
            for ( j = 0; j < m_numVerts; j++ )
            {
                int _cost_i_j = 0;
                if ( i != j )
                {
                    char _chr_cost = chain[i][j];
                    if ( _chr_cost == ' ' )
                    {
                        _cost_i_j = PSEUDO_INFINITY;
                    }
                    else if ( _chr_cost <= '9' && _chr_cost >= '0' )
                    {
                        _cost_i_j = _chr_cost - '0' + 0;
                    }
                    else if ( _chr_cost <= 'z' && _chr_cost >= 'a' )
                    {
                        _cost_i_j = _chr_cost - 'a' + 10;
                    }
                    else
                    {
                        _cost_i_j = _chr_cost - 'A' + 36;
                    }
                }

                *( m_graphMat + i * m_numVerts + j ) = _cost_i_j;
            }
        }
    }

    int vectorIndexOf( const vector<int> &vect, int value )
    {
        int _indx = -1;
        for ( int q = 0; q < vect.size(); q++ )
        {
            if ( vect[q] == value )
            {
                _indx = q;
                break;
            }
        }

        return _indx;
    }

    public :

    EscapingJail()
    {
        m_graphMat = NULL;
        m_numVerts = 0;
    }

    ~EscapingJail()
    {
        if ( m_graphMat != NULL )
        {
            delete[] m_graphMat;
            m_graphMat = NULL;
        }
    }

    int getMaxLinkDistance( vector<int> conn_options, const int &pivot1, const int &pivot2, const int &pivots_dist )
    {
        int _result = PSEUDO_INFINITY;
        if ( conn_options.size() == 1 )
        {
            return getCost( pivot1, conn_options[0] ) + getCost( conn_options[0], pivot2 );
        }

        for ( int q = 0; q < conn_options.size(); q++ )
        {
            // two options, either connect to it, or recurse to less options
            int _result_1 = getCost( pivot1, conn_options[q] ) + 
                            getCost( conn_options[q], pivot2 );
            vector<int> _conn_options_reduced( conn_options );
            int _indx_to_remove = vectorIndexOf( _conn_options_reduced, conn_options[q] );
            if ( _indx_to_remove == -1 )
            {
                cout << "warning!!! there's is an error here" << endl;
                return _result;
            }
            _conn_options_reduced.erase( _conn_options_reduced.begin() + _indx_to_remove );
            int _result_2 = getCost( pivot1, conn_options[q] );
            if ( _result_2 <= pivots_dist )
            {
                _result_2 += getMaxLinkDistance( _conn_options_reduced, 
                                                 conn_options[q], 
                                                 pivot2, 
                                                 pivots_dist );
            }

            int _max_link_res = std::min( _result_1, _result_2 );
            _result = std::min( _result, std::min( pivots_dist, _max_link_res ) );
        }

        return _result;
    }

    int getMaxDistance( const vector<string> &chain )
    {
        int _result = 0;
        int p1, p2;
        initializeGraphMatrix( chain );
        for ( int x = 0; x < m_numVerts; x++ )
        {
            for ( int y = x + 1; y < m_numVerts; y++ )
            {
                int _max_dist = getCost( x, y );
                if ( x == 2 && y == 3 )
                {
                    cout << "? " << _max_dist << endl;
                }
                vector<int> _conn_options;
                for ( int q = 0; q < m_numVerts; q++ )
                {
                    if ( q == x || q == y )
                    {
                        continue;
                    }
                    _conn_options.push_back( q );
                }

                
                if ( _conn_options.size() > 0 )
                {
                    if ( x == 2 && y == 3 )
                    {
                        cout << "here" << endl;
                    }
                    int _max_link_dist = getMaxLinkDistance( _conn_options, x, y, getCost( x, y ) );
                    if ( x == 2 && y == 3 )
                    {
                        cout << "?? " << _max_link_dist << endl;
                    }
                    _max_dist = std::min( _max_dist, _max_link_dist );
                }
                if ( _result < _max_dist )
                {
                    p1 = x;
                    p2 = y;
                    _result = _max_dist;
                }
            }
        }
        if ( _result == PSEUDO_INFINITY )
        {
            _result = -1;
        }
        cout << "pair: " << p1 << " - " << p2 << endl;

        return _result;
    }

    void printCosts()
    {
        int i,j;
        cout << "costs: " << endl;
        for ( i = 0; i < m_numVerts; i++ )
        {
            for ( j = i + 1; j < m_numVerts; j++ )
            {
                if ( getCost( i, j ) == PSEUDO_INFINITY )
                {
                    cout << "c " << i << "-" << j << " : " << "Inf" << endl;
                }
                else
                {
                    cout << "c " << i << "-" << j << " : " << getCost( i, j ) << endl;
                }
            }
        }
        cout << endl;
    }

};





int main()
{
    // string _chain[] = {"0568", "5094", "6903", "8430"};
    // string _chain[] = {"0 ", " 0"};
    string _chain[] = {"0AxHH190", "A00f3AAA", "x00     ", "Hf 0 x  ", "H3 0    ", "1A 0    ", "9A x 0Z ", "0A Z0   "};
    // string _chain[] = {"00", "00"};
    vector<string> _test_chain( _chain, _chain + sizeof( _chain ) / sizeof( _chain[0] ) );

    EscapingJail _prob;
    int _result = _prob.getMaxDistance( _test_chain );

    cout << "result: " << _result << endl;

    _prob.printCosts();

    return 0;
}