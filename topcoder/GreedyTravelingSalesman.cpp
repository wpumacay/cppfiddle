
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

	int getWorstDistance( int startIndx, bool canChange, vector<int> choices )
	{
		if ( choices.size() == 0 )
		{
			return 0;
		}

		if ( !canChange )
		{
			int _result = 0;
			int _bestChoiceIndx = 0;
			int _bestDist = getMinDistance( startIndx, choices, _bestChoiceIndx );
			int _bestDecision = choices[_bestChoiceIndx];
			choices.erase( choices.begin() + _bestChoiceIndx );
			_result = _bestDist + getWorstDistance( _bestDecision, false, choices );

			cout << "res: " << _result << " " << choices.size() + 1 << endl;
			cout << "f: " << _bestDist << endl;

			return _result;
		}

		if ( choices.size() > 1 )
		{
			int _result = 0;
			int _firstMinIndx = 0;
			int _firstMinDist = getMinDistance( startIndx, choices, _firstMinIndx );
			int _firstDecision = choices[_firstMinIndx];
			int _secondMinIndx = 0;
			int _secondMinDist = getSecondMinDistance( startIndx, choices, _secondMinIndx );
			int _secondDecision = choices[_secondMinIndx];

			int _res1, _res2, _res3, _res4;
			vector<int> _ch1( choices ),_ch2( choices ),_ch3( choices ),_ch4( choices );
			_ch1.erase( _ch1.begin() + _firstMinIndx );
			_ch2.erase( _ch2.begin() + _firstMinIndx );
			_ch3.erase( _ch3.begin() + _firstMinIndx );
			_ch4.erase( _ch4.begin() + _secondMinIndx );

			_res1 = _firstMinDist + getWorstDistance( _firstDecision, true, _ch1 );
			_res2 = ( _secondMinDist - 1 ) + getWorstDistance( _firstDecision, false, _ch2 );
			_res2 = _firstMinDist != _secondMinDist ? _res2 : 0;
			_res3 = _secondMinDist + getWorstDistance( _firstDecision, false, _ch3 );
			_res4 = _secondMinDist + getWorstDistance( _secondDecision, false, _ch4 );
			_res3 = _secondDecision > _firstDecision ? _res3 : 0;
			cout << "res: " << _res1 << " " << _res2 << " " << _res3 << " " << _res4 << endl;
			cout << "f: " << _firstMinDist << " " << _secondMinDist - 1 << " " << _secondMinDist << " " << _secondMinDist << endl;
			_result = std::max( _res1, std::max( _res2, std::max( _res3, _res4 ) ) );

			return _result;
		}
		
		cout << 9999 << endl;
		return 9999;
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

	int getSecondMinDistance( int indxFrom, vector<int> choices, int &choiceIndx )
	{
		int _firstMinIndx = 0;
		int _firstMinDist = getMinDistance( indxFrom, choices, _firstMinIndx );

		int _secondMinDist = 1000000;
		unsigned int q;
		for( q = 0; q < choices.size(); q++ )
		{
			int _cost_to_chq = getCost( indxFrom, choices[q] );
			if ( _cost_to_chq < _secondMinDist && q != _firstMinIndx )
			{
				choiceIndx = q;
				_secondMinDist = _cost_to_chq;
			}
		}

		return _secondMinDist;
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


		_result = getWorstDistance( 0, true, choices );

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

	void printCosts()
	{
		int i,j;
		cout << "costs: ";
		for ( i = 0; i < m_numVerts; i++ )
		{
			for ( j = i + 1; j < m_numVerts; j++ )
			{
				cout << getCost( i, j ) << " ";
			}
		}
		cout << endl;
	}

};




int main()
{
	GreedyTravelingSalesman _prob;

/*
	string th[] = {"00888", "00999", "00099", "00009", "00000"};
	string hu[] = {"00000", "00999", "00099", "00009", "00000"};
	string te[] = {"00000", "10999", "11099", "11109", "11110"};
	string on[] = {"01000", "00999", "00099", "00009", "00000"};
*/
	/*
	string th[] = {"055", "505", "550"};
	string hu[] = {"000", "000", "000"};
	string te[] = {"000", "000", "000"};
	string on[] = {"000", "000", "000"};
	*/
	/*
	string th[] = {"018", "101", "990"};
	string hu[] = {"000", "000", "990"};
	string te[] = {"000", "000", "990"};
	string on[] = {"000", "000", "990"};
	*/
	/*
	string th[] = {"000000", "000000", "990999", "999099", "999909", "999990"};
	string hu[] = {"000000", "000000", "990999", "999099", "999909", "999990"};
	string te[] = {"000000", "000000", "990999", "999099", "999909", "999990"};
	string on[] = {"011111", "101111", "990998", "999099", "999809", "999980"};
	*/

	string th[] = {"098444156277392825243100607342", "200097656837707947798866622385",
				                     "290231695687128834848596019656", "407026565077650435591867333275",
				                     "843401002617957470339040852874", "349970591997218853400632158696",
				                     "419933000593511123878416328483", "696294503254214847884399055978",
				                     "641473980706392541888675375279", "936720077098054565078142449625",
				                     "203476089500970673371115103717", "511071853860312304204656816567",
				                     "347105714685052402147763392257", "125122220860203856679947732062",
				                     "121462979669220132944063071653", "928254504048223043681383050365",
				                     "502607124708785202536036594373", "793596587517012870906900400361",
				                     "712360060935346182084840996318", "761671392040312345002273366240",
				                     "812935320276738878200716148806", "228506917464479046839069740872",
				                     "755395721473881083093906155745", "192597782177910118061710039501",
				                     "721382839206745793530453013267", "076061794267810491768114700256",
				                     "857528357758085424372388710251", "173322450800442594145600093043",
				                     "761667192345925280210514410800", "521229810525064090301842864060"};
	string hu[] = {"098270581534726237580246464451", "108829763716747148395013332067",
				                    "830061279541380758964430491222", "431005058477371114834129826284",
				                    "601807314489142917339949914290", "330640126699733151822328009407",
				                    "851821069798846354566780680271", "648888407535627630663351884365",
				                    "051398660825518466890170447894", "631934884097214069747147155777",
				                    "768071219404930950472885304916", "924954163330715847561718395488",
				                    "189910033179029204426829479070", "960645776060701332402794474433",
				                    "244875842263950931884758650019", "528470075229660077692189442311",
				                    "752198673046476808978058423064", "899325998610605600525587569431",
				                    "965750123741820904031880230236", "121658852172052167706008445728",
				                    "556199378085507717770434101126", "864838242791403197110088834005",
				                    "593435343245223500439707230479", "622529771475840345624500421425",
				                    "503486612623475041392122088159", "518334626169655694269507400008",
				                    "967091631529233593414345370288", "300474162107271438029222620086",
				                    "010527691044447729596127150108", "742822904991333205419603623270"};
	string te[] = {"029421809872798033258029765788", "705135039569772524273274786652",
				                "170567418260893393020344098265", "401043354947659563658581268242",
				                "746709065616595245635350557925", "739570024549618413776557843034",
				                "184597012262496958610853505745", "689811400727818703807051112784", 
				                "894453010121164288965541305235", "323145029073008946088869964941", 
				                "834269564400729646453274750586", "538976762970745472202055589093", 
				                "765511399939087047106252621388", "906733295711605356366138410423", 
				                "107653940551700559321642810836", "428402693021051075533830345295", 
				                "386782660475155103347385287948", "936626025836194580089064628716", 
				                "718522629491464055045890912121", "370656945845300237607868352243", 
				                "951908186614186444840337711498", "535178875249889835014025850038", 
				                "505970047705717604298603983975", "484398304612602344941130624527", 
				                "048342694079170795987835013947", "860331019262176299872846206272", 
				                "549663926438975145562538360932", "329735455392841851511474791078", 
				                "711755200061373546828858448100", "778808866574640894148527759780"};
	string on[] = {"050738147930236727719964251439", "804492562859282318664226330103", 
				                "610197568193830684654773608216", "279000416545607314567843085541", 
				                "782201171759873927350740022455", "043370803444176631019883186675", 
				                "566092086050401228622782761449", "469598907881602996036692882305", 
				                "116923500417992303845370254124", "796876115092839169954790509461", 
				                "783836410405270687557924090071", "095144151150833738671751747749", 
				                "354474585664039135189964700948", "328968176148004939648962631420", 
				                "829651915384290848347221555092", "170980383407813034573738951375", 
				                "728655435703349509419725538350", "121896684176286430427852435647", 
				                "315710894574884960021671476788", "592177839598531202003634382961", 
				                "876587919610157913350259498196", "505517243779897451333006271744", 
				                "618607877753891664471800511372", "826358757330233811836040764274", 
				                "206641252044293046424432092833", "704519364781672964993499009545", 
				                "624793571592392775564426440338", "571938479010503551295729304078", 
				                "077967252884369103891335711508", "870185204806328841827105139840"};

	/*
	string th[] = {"00", "00"};
	string hu[] = {"00", "00"};
	string te[] = {"00", "00"};
	string on[] = {"01", "10"};
	*/
	/*
	string th[] = {"0930", "1064", "0104", "1070"};
	string hu[] = {"0523", "1062", "6305", "0810"};
	string te[] = {"0913", "0087", "3109", "1500"};
	string on[] = {"0988", "2030", "6103", "5530"};
	*/
	/*
	string th[] = {"0329", "2036", "2502", "8970"};
	string hu[] = {"0860", "5007", "0404", "2770"};
	string te[] = {"0111", "2087", "2009", "2670"};
	string on[] = {"0644", "1094", "7703", "7550"};
	*/
	vector<string> thousands( th, th + sizeof( th ) / sizeof( string ) );
	vector<string> hundreds( hu, hu + sizeof( hu ) / sizeof( string ) );
	vector<string> tens( te, te + sizeof( te ) / sizeof( string ) );
	vector<string> ones( on, on + sizeof( on ) / sizeof( string ) );

	int _result = _prob.worstDistance( thousands,
									   hundreds,
									   tens,
									   ones );

	cout << "result: " << _result << endl;
	//_prob.printCosts();

	return 0;
}
