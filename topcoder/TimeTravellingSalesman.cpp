

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Node
{
	int vert;
	int cost;
	Node( int vert, int cost )
	{
		this->vert = vert;
		this->cost = cost;
	}
};

struct TimeTravelExploration
{
	long long cost;
	vector<int> explored;
	vector<int> fringe;
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

	TimeTravelExploration time_travel_visit( TimeTravelExploration current_exp, int previous_indx )
	{
		TimeTravelExploration _exp;
		_exp.fringe = current_exp.fringe;
		_exp.explored = current_exp.explored;
		_exp.cost = current_exp.cost;

		if ( _exp.fringe.size() == 0 )
		{
			return _exp;
		}

		for ( int q = 0; q < _exp.fringe.size(); q++ )
		{
			int _to_explore = _exp.fringe[q];

			if ( vectorIndexOf( _exp.explored, _to_explore ) != -1 )
			{
				continue;
			}
			// For all nodes in the fringe, branch
			TimeTravelExploration _exp_q;
			_exp_q.cost = _exp.cost;
			if ( previous_indx != -1 )
			{
				_exp_q.cost += m_adjGraph[previous_indx][_to_explore].cost;
			}

			_exp_q.fringe = _exp.fringe;
			_exp_q.explored = _exp.explored;
			_exp_q.explored.push_back( _exp_q.fringe[q] );
			_exp_q.fringe.erase( _exp_q.fringe.begin() + q );
			for ( int p = 0; p < m_adjGraph[_to_explore].size(); p++ )
			{
				_exp_q.fringe.push_back( m_adjGraph[_to_explore][p].vert );
			}

			TimeTravelExploration _sub_exploration = time_travel_visit( _exp_q, _to_explore );

			// merge the branch explorations
			for ( int r = 0; r < _sub_exploration.explored.size(); r++ )
			{
				_exp.explored.push_back( _sub_exploration.explored[r] );
			}
			_exp.cost += _sub_exploration.cost;
		}


		return _exp;
	}

	int determineCost( int verts, vector<string> roads )
	{
		long long _result = 0;

		m_numverts = verts;
		parse_roads( roads );

		vector<long long> _results;

		for ( int q = 0; q < m_numverts; q++ )
		{
			TimeTravelExploration _exploration;
			_exploration.cost = 0;
			_exploration.fringe.push_back( q );
			_exploration = time_travel_visit( _exploration, -1 );
			_results.push_back( _exploration.cost );
		}

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
	//int N = 3;
	//string _arr[] = {"0,1,1 0,2,1 1,2,2"};
	//int N = 4;
	//string _arr[] = {"1,0",",10","0 2,1",",584 3,2",",754"};
	int N = 6;
	string _arr[] = {"0,1,2 1,4,2 4,3,3 2,4,4 0,5,3"};
	vector<string> _roads( _arr, _arr + sizeof( _arr ) / sizeof( _arr[0] ) );

	TimeTravellingSalesman _prob;

	long long _result = _prob.determineCost( N, _roads );

	_prob.print();

	cout << "result: " << _result << endl;

	return 0;
}
