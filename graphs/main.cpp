
#include <iostream>

#include "CGraph.h"

using namespace std;






int main()
{
	DS::CGraph<int, int> _graph;

	cout << "started testing graph" << endl;

	_graph.insertNode( 0 );
	_graph.insertNode( 1 );
	_graph.insertNode( 2 );
	_graph.insertNode( 3 );

	_graph.insertEdge( _graph.nodes[0],
					   _graph.nodes[1],
					   1, true );
	
	_graph.insertEdge( _graph.nodes[0],
					   _graph.nodes[2],
					   2, true );
	_graph.insertEdge( _graph.nodes[0],
					   _graph.nodes[3],
					   3, true );
	_graph.insertEdge( _graph.nodes[1],
					   _graph.nodes[2],
					   4, true );
	_graph.insertEdge( _graph.nodes[1],
					   _graph.nodes[3],
					   5, true );
	_graph.insertEdge( _graph.nodes[2],
					   _graph.nodes[3],
					   6, true );
	
	_graph.print();

	_graph.removeEdge( _graph.nodes[0]->edges[0] );
	_graph.removeEdge( _graph.nodes[1]->edges[0] );

	_graph.removeNode( _graph.nodes[2] );

	_graph.print();

	cout << "finished testing graph" << endl;

	return 0;
}