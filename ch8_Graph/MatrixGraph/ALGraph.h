#ifndef ALGRAPH_H
#define ALGRAPH_H

#include "Graph.h"

extern const int INF;

const int DefaultVertexs = 30;

template <typename T, typename E>
struct Edge
{
	int adjVertex;
	E weight;
	Edge<T, E> *nextArc;

	Edge(int adj = -1, E w = INF, Edge<T, E> *link = NULL)
		: adjVertex(adj), weight(w), nextArc(link) {}
};

template <typename T, typename E>
struct Vertex
{
	T data;
	Edge<T, E> *firstArc;

	Vertex() { firstArc = NULL; }
		//: firstArc<T, E>(NULL) {}
};

template <typename T, typename E>
class ALGraph : public Graph<T, E>
{
	public:
		ALGraph(int sz = DefaultVertexs);
		~ALGraph();

		int GetFirstNeighbor( int v );
		int GetNextNeighbor( int v, int u );
		T GetValue(int v); 
		E GetWeight(int v, int u);

		bool insertVertex(const T& vertex);
		bool insertEdge(int v1, int v2, E weight);
		int getVertexPos(const T &vertex)
		{					
			for (int i = 0; i < numVertexs; i++)
				if (vertexs[i].data == vertex)
					return i;
			return -1; 
		}

	private:
		Vertex<T, E> *vertexs;
};

template <typename T, typename E>
ALGraph<T,E>::ALGraph(int sz) : Graph<T,E>(sz)
{
	vertexs = new Vertex<T,E>[maxVertexs];		//创建顶点表数组
	assert(vertexs);
}

template <typename T, typename E>
ALGraph<T, E>::~ALGraph()
{
	for ( int i = 0; i < maxVertexs; i++ )
		for ( Edge<T, E> *e = vertexs[i].firstArc; e != NULL;  )
		{
			Edge<T, E> *del = e;
			e = e->nextArc;
			delete del;
		}
	
	delete []vertexs;
	vertexs = NULL;
}

template <typename T, typename E>
int ALGraph<T, E>::GetFirstNeighbor( int v )
{
	if ( vertexs[v].firstArc == NULL )
		return -1;
	else
		return (vertexs[v].firstArc)->adjVertex;
}

template <typename T, typename E>
int ALGraph<T, E>::GetNextNeighbor( int v, int u )
{
	Edge<T, E> *e = vertexs[v].firstArc;
	while ( e != NULL && e->adjVertex != u )
		e = e->nextArc;

	if ( e == NULL )
		return -1;
	else
		return (e->nextArc == NULL) ? -1 : (e->nextArc)->adjVertex;
}

template <typename T, typename E>
T ALGraph<T, E>::GetValue(int v)
{
	return vertexs[v].data;
}

template <typename T, typename E>
E ALGraph<T, E>::GetWeight(int v, int u)
{
	if ( v == u )
		return 0;

	Edge<T, E> *e = vertexs[v].firstArc;
	while ( e != NULL && e->adjVertex != u )
		e = e->nextArc;

	if (e == NULL)
		return INF;
	return e->weight;
}

template <typename T, typename E>
bool ALGraph<T, E>::insertVertex(const T& vertex)
{
	if (numVertexs == maxVertexs)
	{
		return false;
	}
	vertexs[numVertexs].data = vertex;
	numVertexs++;
	return true;
}

template <typename T, typename E> //此处按照无向图插入边
bool ALGraph<T, E>::insertEdge(int v1, int v2, E w)
{
	if (v1 >= 0 && v1 < numVertexs && v2 >= 0 && v2 < numVertexs)
	{
		Edge<T,E> *q, *p = vertexs[v1].firstArc;	
		while (p != NULL && p->adjVertex != v2)	
			p = p->nextArc;
		if (p != NULL)	
			return false;

		p = new Edge<T,E>(v2, w, vertexs[v1].firstArc);			
		q = new Edge<T,E>(v1, w, vertexs[v2].firstArc);
		vertexs[v1].firstArc = p;
		vertexs[v2].firstArc = q;
		
		numEdges += 2;
		return true;
	}
	return false;
}
#endif