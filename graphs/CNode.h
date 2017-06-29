
#pragma once

#include "CGraph.h"
#include <vector>

using namespace std;

namespace DS
{

	template<class G>
	class CNode
	{
		public :

		typedef typename G::NodeData N;
		typedef typename G::Edge Edge;
		
		N data;
		vector<Edge*> edges;

		CNode( N node_data )
		{
			data = node_data;
		}
	};
	
}