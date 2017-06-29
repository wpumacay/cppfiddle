

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Node
{
	int vert;
	int cost;
	bool visited;

	Node( int vert, int cost )
	{
		this->vert = vert;
		this->cost = cost;
		this->visited = false;
	}
};


class TimeTravellingSalesman
{

	private :

	int m_numverts;
	vector<vector<Node> > m_adjGraph;

	void parse_roads( vector<string> roads )
	{
		for( int i = 0; i < m_numverts; i++ )
		{
			m_adjGraph.push_back( vector<Node>() );
		}

		string _roads_str = "";
		for ( int q = 0; q < roads.size(); q++ )
		{
			_roads_str += roads[q];
		}

		int k = 0;
		int _size = _roads_str.size();
		while ( k < _size )
		{
			string _a,_b,_cost;
			while( _roads_str[k] != ',' )
			{
				_a += _roads_str[k];
				k++;
			}
			k++;
			while( _roads_str[k] != ',' )
			{
				_b += _roads_str[k];
				k++;
			}
			k++;
			while( k < _size && _roads_str[k] != ' ' )
			{
				_cost += _roads_str[k];
				k++;
			}
			k++;

			int _vert_a,_vert_b,_cost_ab;
			_vert_a = std::stoi( _a );
			_vert_b = std::stoi( _b );
			_cost_ab = std::stoi( _cost );

			m_adjGraph[_vert_a].push_back( Node( _vert_b, _cost_ab ) );
			m_adjGraph[_vert_b].push_back( Node( _vert_a, _cost_ab ) );
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

	int determineCost( int verts, vector<string> roads )
	{
		long long _result = 0;

		m_numverts = verts;
		parse_roads( roads );

		vector<long long > _results;

		for ( int q = 0; q < m_numverts; q++ )
		{
			// reset the graph
			for ( int p = 0; p < m_numverts; p++ )
			{
				for ( int s = 0; s < m_adjGraph[p].size(); s++ )
				{
					m_adjGraph[p][s].visited = false;
				}
			}

			long long _sub_result = 0;
			queue<Node> _fringe;
			vector<int> _explored;
			vector<int> _touched;


			Node _n( q, 0 );
			_fringe.push( _n );
			_touched.push_back( _n.vert );

			// cout << "start: " << q << endl;

			while ( !_fringe.empty() )
			{
				Node _t = _fringe.front();
				_fringe.pop();
				if ( vectorIndexOf( _explored, _t.vert ) != -1 )
				{
					continue;
				}
				_explored.push_back( _t.vert );

				// cout << "  explored: " << _t.vert << endl;

				if ( _explored.size() == m_numverts )
				{
					break;
				}

				// cin.get();
				for ( int r = 0; r < m_adjGraph[_t.vert].size(); r++ )
				{
					Node _o = m_adjGraph[_t.vert][r];
					if ( vectorIndexOf( _explored, _o.vert ) == -1 && 
						 vectorIndexOf( _touched, _o.vert ) == -1 )
					{
						_fringe.push( _o );
						_touched.push_back( _o.vert );
						_sub_result += _o.cost;
					}
				}

			}
			cout << _explored.size() << endl;
			if ( _explored.size() != m_numverts )
			{
				_sub_result = -1;
			}

			_results.push_back( _sub_result );
		}

		cout << "[ ";
		for ( int r = 0; r < _results.size(); r++ )
		{
			cout << _results[r] << " ";
		}
		cout << " ]" << endl;

		sort( _results.begin(), _results.end() );

		_result = -1;
		int k = _results.size() - 1;
		while ( k > 0 && _results[k] >= 0 )
		{
			k--;
		}
		if ( k != _results.size() - 1 )
		{
			_result = _results[k];
		}

		return _result;
	}




	void print()
	{
		cout << "graph: " << endl;
		for ( int q = 0; q < m_numverts; q++ )
		{
			cout << "-> " << q << " : ";
			for ( int p = 0; p < m_adjGraph[q].size(); p++ )
			{
				cout << m_adjGraph[q][p].vert << " - " << m_adjGraph[q][p].cost << " , ";
			}
			cout << endl;
		}
	}

};






int main()
{
	vector<int> _cases_N;
	vector<string*> _cases_arr;
	vector<int> _cases_sizes;
	vector<long long > _cases_answers;

	int N1 = 3;
	string _arr1[] = {"0,1,1 0,2,1 1,2,2"};
	_cases_N.push_back( N1 );
	_cases_arr.push_back( _arr1 );
	_cases_sizes.push_back( sizeof( _arr1 ) / sizeof( _arr1[0] ) );
	_cases_answers.push_back( 2 );

	int N2 = 4;
	string _arr2[] = {"1,0",",10","0 2,1",",584 3,2",",754"};
	_cases_N.push_back( N2 );
	_cases_arr.push_back( _arr2 );
	_cases_sizes.push_back( sizeof( _arr2 ) / sizeof( _arr2[0] ) );
	_cases_answers.push_back( 1438 );

	int N3 = 3;
	string _arr3[] = {"0,2,2"};
	_cases_N.push_back( N3 );
	_cases_arr.push_back( _arr3 );
	_cases_sizes.push_back( sizeof( _arr3 ) / sizeof( _arr3[0] ) );
	_cases_answers.push_back( -1 );

	int N4 = 6;
	string _arr4[] = {"0,1,2 1,4,2 4,3,3 2,4,4 0,5,3"};
	_cases_N.push_back( N4 );
	_cases_arr.push_back( _arr4 );
	_cases_sizes.push_back( sizeof( _arr4 ) / sizeof( _arr4[0] ) );
	_cases_answers.push_back( 14 );

	for ( int q = 0; q < _cases_N.size(); q++ )
	{
		int N = _cases_N[q];
		vector<string> _roads( _cases_arr[q], _cases_arr[q] + _cases_sizes[q] );

		TimeTravellingSalesman _prob;

		long long _result = _prob.determineCost( N, _roads );

		cout << "result: " << _result << endl;

		if ( _result == _cases_answers[q] ) 
		{
			cout << "CORRECT ANSWER! :)" << endl;
		} 
		else
		{
			cout << "WRONG ANSWER :(" << endl;
		}
	}


	return 0;
}
