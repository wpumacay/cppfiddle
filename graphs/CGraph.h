
#pragma once

#include <iostream>
#include <vector>
#include <list>

#include "CNode.h"
#include "CEdge.h"

using namespace std;

namespace DS
{
	template<class N, class E>
	class CGraph
	{

		public :

		typedef CGraph<N,E> self;
		typedef CNode<self> Node;
		typedef CEdge<self> Edge;

		typedef N NodeData;
		typedef E EdgeData;

		vector<Node*> nodes;

		void insertNode( N node_data );
		void insertEdge( Node* from, Node* to, E edge_data, bool dir );
		void removeEdge( Edge* edge );
		// void removeNode( Node* node );


		void print();
	};

	template<class N, class E>
	void CGraph<N,E>::insertNode( N node_data )
	{
		nodes.push_back( new CNode<CGraph<N,E>>( node_data ) );
	}

	template<class N, class E>
	void CGraph<N,E>::insertEdge( CNode<CGraph<N,E>>* from, 
								  CNode<CGraph<N,E>>* to,
								  E edge_data, bool bidir )
	{
		CEdge<CGraph<N,E>>* _edge_from = new CEdge<CGraph<N,E>>( edge_data, bidir );

		_edge_from->nodes[0] = from;
		_edge_from->nodes[1] = to;
		from->edges.push_back( _edge_from );

		if ( bidir )
		{
			CEdge<CGraph<N,E>>* _edge_to = new CEdge<CGraph<N,E>>( edge_data, bidir );

			_edge_to->nodes[0] = to;
			_edge_to->nodes[1] = from;
			to->edges.push_back( _edge_to );
		}

	}

	template<class N, class E>
	void CGraph<N,E>::removeEdge( CEdge<CGraph<N,E>>* edge )
	{
		// Remove from the "from" node's edges
		CNode<CGraph<N,E>>* _node_from = edge->nodes[0];

		if ( edge->bidir )
		{
			// Remove from the "to" node's edges
			CNode<CGraph<N,E>>* _node_to = edge->nodes[1];
		}

		delete edge;
	}


	template<class N, class E>
	void CGraph<N,E>::print()
	{
		cout << "graph: " << endl;
		for ( int q = 0; q < nodes.size(); q++ )
		{
			cout << " node ( " << nodes[q]->data << " ): ";
			vector<CEdge<CGraph<N,E>>*> _vect_for_node = nodes[q]->edges;
			
			for ( int p = 0; p < _vect_for_node.size(); p++ )
			{
				cout << ( _vect_for_node[p]->nodes[1] )->data << "(" << _vect_for_node[p]->data << ") ";
			}
			cout << endl;
		}
		cout << "********" << endl;
	}
}