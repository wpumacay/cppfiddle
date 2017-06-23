
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class GreedyTravelingSalesman
{

	private :

	int *m_graphMat;
	int m_numVerts;
	vector<int> path;

	int getCost( int fromIndx, int toIndx )
	{
		return *( m_graphMat + fromIndx * m_numVerts + toIndx );
	}

	void initializeGraphMatrix( int numVerts,
								vector<string> thousands,
					   			vector<string> hundreds,
					   			vector<string> tens,
					   			vector<string> ones )
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
				int _cost_i_j = 0;
				if ( i != j )
				{
					_cost_i_j += ( (int)( ( thousands[i][j] - '0' ) ) ) * 1000;
					_cost_i_j += ( (int)( ( hundreds[i][j] - '0' ) ) ) * 100;
					_cost_i_j += ( (int)( ( tens[i][j] - '0' ) ) ) * 10;
					_cost_i_j += ( (int)( ( ones[i][j] - '0' ) ) ) * 1;
				}

				*( m_graphMat + i * m_numVerts + j ) = _cost_i_j;
			}
		}
	}

	int getDistance( int startIndx, bool canChange, vector<int> choices )
	{
		if ( choices.size() == 0 )
		{
			return 0;
		}

		int _result = 0;
		int _bestChoiceIndx = 0;
		int _bestDist = getMinDistance( startIndx, choices, _bestChoiceIndx );
		int _bestDecision = choices[_bestChoiceIndx];
		if ( !canChange )
		{
			choices.erase( choices.begin() + _bestChoiceIndx );
			_result = _bestDist + getDistance( _bestDecision, false, choices );
		}
		else
		{
			// If someone changes
			int _resultWhenChanges = 0;
			// Suppose we pop the best distance
			int _secondBestIndx = 0;
			int _secondBestDecision = 0;
			int _secondBestDist = 0;

			vector<int> _choicesReduced( choices );
			_choicesReduced.erase( choices.begin() + _bestChoiceIndx );
			_secondBestDist = getMinDistance( startIndx, _choicesReduced, _secondBestIndx );
			_secondBestDecision = _choicesReduced[_secondBestIndx];
			_choicesReduced.erase( choices.begin() + _secondBestIndx );
			_choicesReduced.push_back( _bestDecision );
			std::sort( _choicesReduced.begin(), _choicesReduced.end() );

			_resultWhenChanges = _secondBestDist + getDistance( _secondBestDecision, false, _choicesReduced );
			// If not
			int _resultWhenNotChanges = _bestDist + getDistance( _bestDecision, true, choices );

			_result = std::max( _resultWhenChanges, _resultWhenNotChanges );
		}
		
		return _result;
	}

	int getMinDistance( int indxFrom, vector<int> choices, int &choiceIndx )
	{
		unsigned int q;
		int _minDist = 1000000;
		for( q = 0; q < choices.size(); q++ )
		{
			int _cost_to_chq = getCost( indxFrom, choices[q] );
			if ( _cost_to_chq < _minDist )
			{
				choiceIndx = q;
				_minDist = _cost_to_chq;
			}
		}
		return _minDist;
	}

	public :

	GreedyTravelingSalesman()
	{
		m_graphMat = NULL;
		m_numVerts = 0;
	}

	~GreedyTravelingSalesman()
	{
		if ( m_graphMat != NULL )
		{
			delete[] m_graphMat;
			m_graphMat = NULL;
		}
	}


	int worstDistance( vector<string> thousands,
					   vector<string> hundreds,
					   vector<string> tens,
					   vector<string> ones )
	{
		int _result = 0;

		int n_verts = thousands.size();
		initializeGraphMatrix( n_verts, thousands, hundreds, tens, ones );

		vector<int> choices;
		int q;
		for ( q = 1; q < m_numVerts; q++ )
		{
			choices.push_back( q );
		}


		_result = getDistance( 0, true, choices );

		return _result;
	}

	int getCostForPath( vector<int> path )
	{
		int _result = 0;
		unsigned int q;
		for ( q = 1; q < path.size(); q++ )
		{
			_result += getCost( path[q-1], path[q] );
		}
		return _result;
	}


};




int main()
{
	GreedyTravelingSalesman _prob;

	string th[] = {"00888", "00999", "00099", "00009", "00000"};
	string hu[] = {"00000", "00999", "00099", "00009", "00000"};
	string te[] = {"00000", "10999", "11099", "11109", "11110"};
	string on[] = {"01000", "00999", "00099", "00009", "00000"};

	vector<string> thousands( th, th + sizeof( th ) / sizeof( string ) );
	vector<string> hundreds( hu, hu + sizeof( hu ) / sizeof( string ) );
	vector<string> tens( te, te + sizeof( te ) / sizeof( string ) );
	vector<string> ones( on, on + sizeof( on ) / sizeof( string ) );

	int _result = _prob.worstDistance( thousands,
									   hundreds,
									   tens,
									   ones );

	cout << "result: " << _result << endl;

	int _testArr[] = { 0,1,2,3,4 };
	vector<int> _testPath( _testArr, _testArr + sizeof( _testArr ) / sizeof( _testArr[0] ) );

	cout << "cost of test path: " << _prob.getCostForPath( _testPath ) << endl;

	return 0;
}
