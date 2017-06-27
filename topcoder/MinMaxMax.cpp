

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define PSEUDO_INFINITY 100000000


struct MinPathNode
{
	int max_node;
	int max_edge;
	int difficulty;
};

class MinMaxMax
{

	private :

	int *m_graphMat;
	int m_numVerts;
	vector<int> m_nodesCost;
	vector<vector<int> > m_adjGraph;

	int getEdgeCost( int fromIndx, int toIndx )
	{
		return *( m_graphMat + fromIndx * m_numVerts + toIndx );
	}

	int getNodeCost( int indx )
	{
		return m_nodesCost[indx];
	}

	void initializeGraphMatrix( vector<int> a,
					   			vector<int> b,
					   			vector<int> w )
	{

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
				*( m_graphMat + i * m_numVerts + j ) = PSEUDO_INFINITY;
			}
		}

		int _indxFrom, _indxTo;
		for ( i = 0; i < a.size(); i++ )
		{
			_indxFrom = a[i];
			_indxTo = b[i];
			*( m_graphMat + _indxFrom * m_numVerts + _indxTo ) = w[i];
			*( m_graphMat + _indxTo * m_numVerts + _indxFrom ) = w[i];
		}
	}

	void initializeGraphAdj( vector<int> a,
					   		 vector<int> b,
					   		 vector<int> w )
	{
		int i;
		for( i = 0; i < m_numVerts; i++ )
		{
			m_adjGraph.push_back( vector<int>() );
		}

		int _indxFrom, _indxTo;
		for ( i = 0; i < a.size(); i++ )
		{
			_indxFrom = a[i];
			_indxTo = b[i];
			m_adjGraph[_indxFrom].push_back( _indxTo );
			m_adjGraph[_indxTo].push_back( _indxFrom );
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

	MinPathNode getMinPathDifficulty( vector<int> path_so_far, int from, int to, long long max_node_so_far, long long max_edge_so_far )
	{
		MinPathNode _result;
		_result.max_node = PSEUDO_INFINITY;
		_result.max_edge = PSEUDO_INFINITY;
		_result.difficulty = PSEUDO_INFINITY;

		vector<int> _to_explore;
		for ( int q = 0; q < ( m_adjGraph[from] ).size(); q++ )
		{
			int _conn_decision = m_adjGraph[from][q];
			if ( vectorIndexOf( path_so_far, _conn_decision ) != -1 )
			{
				// Is already there, so don't loop
				continue;
			}
			_to_explore.push_back( _conn_decision );
		}

		if ( _to_explore.size() == 0 )
		{
			return _result;
		}

		for ( int q = 0; q < _to_explore.size(); q++ )
		{
			int _conn_decision = _to_explore[q];
			long long _difficulty_so_far = 1;
			long long _local_max_node_so_far = max( max_node_so_far, (long long) getNodeCost( _conn_decision ) );
			long long _local_max_edge_so_far = max( max_edge_so_far, (long long) getEdgeCost( from, _conn_decision ) );
			if ( _conn_decision == to )
			{
				// We have closed a path
				_difficulty_so_far = _local_max_node_so_far * _local_max_edge_so_far;
			}
			else
			{
				// Keep recursing
				vector<int> _path( path_so_far );
				_path.push_back( _conn_decision );
				MinPathNode _r_result = getMinPathDifficulty( _path, _conn_decision, to, _local_max_node_so_far, _local_max_edge_so_far );
				_local_max_edge_so_far = max( (long long) _r_result.max_edge, _local_max_edge_so_far );
				_local_max_node_so_far = max( (long long) _r_result.max_node, _local_max_node_so_far );
				if ( _local_max_node_so_far == PSEUDO_INFINITY || 
					 _local_max_edge_so_far == PSEUDO_INFINITY )
				{
					_difficulty_so_far = PSEUDO_INFINITY;
					continue;
				}
				_difficulty_so_far = _local_max_node_so_far * _local_max_edge_so_far;
			}

			if ( _difficulty_so_far < 0 )
			{
				cout << "here" << endl;
			}

			if ( _result.difficulty > _difficulty_so_far )
			{
				_result.difficulty = _difficulty_so_far;
				_result.max_node = _local_max_node_so_far;
				_result.max_edge = _local_max_edge_so_far;
			}
		}

		return _result;
	}

	long long minDifficulty( int fromIndx, int toIndx )
	{
		vector<int> path_so_far;
		path_so_far.push_back( fromIndx );

		MinPathNode _result = getMinPathDifficulty( path_so_far, fromIndx, toIndx, getNodeCost( fromIndx ), 0 );

		return _result.difficulty;
	}

	public :

	long long findMin( vector<int> a, vector<int> b, vector<int> w, vector<int> v )
	{
		m_numVerts = v.size();
		m_nodesCost = v;

		initializeGraphMatrix( a, b, w );
		initializeGraphAdj( a, b, w );
		int p, q;
		long long _result = 0;
		for ( p = 0; p < m_numVerts; p++ )
		{
			for( q = p + 1; q < m_numVerts; q++ )
			{
				_result += minDifficulty( p, q );
				cout << "res: " << _result << endl;
			}
		}

		return _result;
	}

	MinMaxMax()
	{
		m_graphMat = NULL;
		m_numVerts = 0;
	}

	~MinMaxMax()
	{
		if ( m_graphMat != NULL )
		{
			delete[] m_graphMat;
			m_graphMat = NULL;
		}
	}


};






int main()
{

	MinMaxMax _prob;

	/// int a[] = {0,0,1};
	/// int b[] = {1,2,2};
	/// int w[] = {10,11,12};
	/// int v[] = {6,5,4};

	/// int a[] = {0};
	/// int b[] = {1};
	/// int w[] = {5};
	/// int v[] = {3,6};

	/// int a[] = {0,0,1};
	/// int b[] = {1,2,2};
	/// int w[] = {100,1,1};
	/// int v[] = {1,1,100};

	/// int a[] = {0,1,2,3,4,5,6,7,8,9};
	/// int b[] = {1,2,3,4,5,6,7,8,9,10};
	/// int w[] = {1000000,1,1000000,1,1000000,1,1000000,1,1000000,1};
	/// int v[] = {1000000,1,1000000,1,1000000,1,1000000,1,1000000,1,1000000};

	/// int a[] = {9,12,4,11,0,8,6,11,11,10,12,7,3,12,3,10,0,3,2,7, 0,10,8,1,11,9,2,0,3,6,4,2,3,5,9,0,6};
	/// int b[] = {0,5,6,5,10,2,1,2,3,4,6,9,9,10,5,5,6,4,12,5,12,7, 7,3,4,12,4,1,8,7,1,6,6,4,11,5,11};
	/// int w[] = {879651,656980,11,51564,206,420,917584,205,59290,3323, 644,1,13243,84162,154,561242,1,190,10,136901,420623, 353,573129,81,25,133670,72,528049,5,715560,82641,46, 1,527672,923948,1,13};
	/// int v[] = {5,1829,51302,3026,4,14,5189,3,25289,2,2967,15994,6};

	int a[] = {4,16,0,10,11,21,11,21,20,6,13,10,10,3,20,15,16,9,6,14,13,8, 17,9,2,21,3,4,10,13,5,7,13,1,12,1,3,13,5,21,12,0,19,15,6,0, 5,13,1,8};
	int b[] = {17,1,8,2,1,7,6,12,18,21,7,20,18,7,6,7,17,20,15,10,14,16,2,6, 19,3,19,3,6,18,10,11,10,4,17,13,15,9,15,17,11,16,13,1,19,17, 19,17,10,2};
	int w[] = {327583,4194,990205,481090,868602,722789,547481,738569,188373, 973550,462208,74066,639614,693164,86808,442101,811939,995334, 551737,335601,147231,93330,799032,130164,839277,757103,234057, 909252,415269,945015,715797,549525,581349,130104,493780,553519, 755216,626951,743631,231151,205857,917585,553454,352015,873807, 573520,569698,317228,754891,875856};
	int v[] = {220468,844712,599675,53333,825995,711279,289092,415428,805292, 985205,197039,193974,95433,244829,558762,555423,725065,498922, 519543,4803,305565,61949};

	long long _result = _prob.findMin( vector<int>( a, a + sizeof( a ) / sizeof( a[0] ) ),
				   					   vector<int>( b, b + sizeof( b ) / sizeof( b[0] ) ),
				   					   vector<int>( w, w + sizeof( w ) / sizeof( w[0] ) ),
				   					   vector<int>( v, v + sizeof( v ) / sizeof( v[0] ) ) );

	cout << "result: " << _result << endl;

	return 0;
}