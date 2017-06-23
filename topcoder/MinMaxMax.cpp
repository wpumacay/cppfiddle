

#include <vector>

using namespace std;

class MinMaxMax
{

	private :

	int *m_graphMat;
	int m_numVerts;
	vector<int> m_nodesCost;
	vector<vector<int>> m_adjGraph;

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
		m_numVerts = numVerts;

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
				*( m_graphMat + i * m_numVerts + j ) = -1;
			}
		}

		int _indxFrom, _indxTo;
		for ( i = 0; i < a.size(); i++ )
		{
			_indxFrom = a[i];
			_indxTo = b[i];
			*( m_graphMat + _indxFrom * m_numVerts + _indxTo ) = w[i];
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
			_indxTo = b[j];
			m_adjGraph[_indxFrom] = _indxTo;
		}
	}

	long long minDifficulty( int fromIndx, int toIndx )
	{
		int q;
		vector<int> _neighbors = m_adjGraph[fromIndx];
		vector<int> frontier( _neighbors );
		while( frontier.size() != 0 )
		{
			
		}
	}

	public :

	long long findMin( vector<int> a, vector<int> b, vector<int> w, vector<int> v )
	{
		m_numVerts = v.size();
		m_nodesCost = v;

		initializeGraphMatrix( a, b, w );
		initializeGraphAdj( a, b, w );
		int p, q;
		long long _result;
		for ( p = 0; p < m_numVerts; p++ )
		{
			for( q = p + 1; q < m_numVerts; q++ )
			{
				_result += minDifficulty( p, q );
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




	return 0;
}