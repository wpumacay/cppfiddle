
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

		void removeEdge( Edge* edge )
		{
			int _indx = -1;
			for ( int q = 0; q < edges.size(); q++ )
			{
				if ( edges[q] == edge )
				{
					_indx = q;
					break;
				}
			}
		}
	};
	
}