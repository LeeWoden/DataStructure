#ifndef GRAPH_H
#define GRAPH_H

#include "UFSet.h"
#include "MinHeap.h"

#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

const int INF = 10000; //���Ȩ��

//���ࣺ����ͼ
//T:������ͣ�E:Ȩ�ص�����
template <typename T, typename E>
class Graph
{
	public:
		Graph( int sz )
			: maxVertexs(sz), numVertexs(0), numEdges(0) {}
		virtual ~Graph() {}

		int NumberOfVertexs() { return numVertexs; }
		int NumberOfEdges() { return numEdges; }

		virtual int GetFirstNeighbor( int v ) = 0; //��õ�һ���ڽӵ�
		virtual int GetNextNeighbor( int v, int u ) = 0; //�����һ���ڽӵ�
		virtual T GetValue(int v) = 0; //��õ��ֵ
		virtual E GetWeight(int u, int v) = 0;

		virtual bool insertVertex(const T &vertex) = 0;			//��ͼ�в���һ������vertex
//		virtual bool removeVertex(int v) = 0;					//��ͼ��ɾ��һ������v
		virtual bool insertEdge(int v1, int v2, E weight) = 0;	//����ȨֵΪweight�ı�(v1,v2)
//		virtual bool removeEdge(int v1, int v2) = 0;			//ɾ����(v1,v2)
		virtual int  getVertexPos(const T &vertex) = 0;			//��������vertex��ͼ�е�λ��

	    void DFS();
		void BFS();
		void Kruskal();
		void Prim();

//	    bool GraphEmpty() const { return (numEdges == 0); }
//		virtual bool GraphFull() const {} //��������ͼ������ͼ

		friend istream& operator >> (istream &in, Graph<T,E> &G)
		{
			int i, j, k, n, m;
			T e1, e2;
			E weight;
			in >> n >> m;				//���붥���������
			for (i = 0; i < n; i++)
			{	//�������붥��ֵ
				in >> e1;
				G.insertVertex(e1);
			}
			i = 0;
			while (i < m)
			{
				assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
				j = G.getVertexPos(e1);				//ȡ��Ӧ�����±�
				k = G.getVertexPos(e2);
				if (j == -1 || k == -1){			//ȡ��Ӧ���㲻����
					cout << "Input error!\n";
				}
				else{
					G.insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
					i++;
				}
			}
			return in;
		}

		friend ostream& operator << (ostream &out, Graph<T,E> &G)
		{
			int i, j, n, m;
			T e1, e2;
			E weight;
			n = G.NumberOfVertexs();		//�����������
			m = G.NumberOfEdges();
			out << "Number of Vertices: " << n << endl;
			out << "Number of Edges: " << m << endl;
			out << "The edges in the graph are:\n";
			for (i = 0; i < n; i++){
				for (j = i + 1; j < n; j++){
					weight = G.GetWeight(i, j);
					if (weight > 0 && weight < INF){
						e1 = G.GetValue(i);	//���±�ȡ�ö���ֵ
						e2 = G.GetValue(j);
						out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
					}
				}
			}
			return out;
		}

	public:
		int numVertexs; //��ǰ������Ŀ
		int maxVertexs; //��󶨵���Ŀ
		int numEdges;   //�ߵ�����

		void DFS(int v, bool *visit);
		int GetMinEdge(E *dist, int n);
};

template <typename T, typename E>
void Graph<T, E>::DFS()
{
	bool *visit = new bool[numVertexs];
	assert( visit );
	for ( int i = 0; i < numVertexs; i++ )
		visit[i] = false;

	for ( i = 0; i < numVertexs; i++ )
		if ( !visit[i] )
			DFS(i, visit);
}

template <typename T, typename E>
void Graph<T, E>::DFS( int v, bool *visit )
{
	cout << GetValue( v ) << ends;
	visit[v] = true;

	for ( int i = GetFirstNeighbor(v); i >= 0; i = GetNextNeighbor(v, i) )
		if ( !visit[i] )
			DFS( i, visit );
}

template <typename T, typename E>
void Graph<T, E>::BFS()
{
	bool *visit = new bool[numVertexs];
	assert( visit );
	memset(visit, 0, numVertexs);
	queue<int> Q;
	Q.push( 0 );
	visit[0] = true;

	while ( !Q.empty() )
	{
		int v = Q.front();
		Q.pop();
		cout << GetValue(v) << ends;

		for ( int u = GetFirstNeighbor(v); u >= 0; u = GetNextNeighbor(v, u) )
			if ( !visit[u] )
			{
				Q.push( u );
				visit[u] = true;
			}
	}
}

template <typename T, typename E>
struct MSTEdge
{
	int head;
	int tail;
	E weight;

	MSTEdge() : head(-1), tail(-1) {}
	MSTEdge(int h, int t, E w) : head(h), tail(t), weight(w) {}

	bool operator > ( MSTEdge<T, E> edge ) { return this->weight > edge.weight; }
};

//����MST���ʣ�ÿ����ѡ��С�ߣ������ò��鼯������Ƿ񹹳ɻ�
template <typename T, typename E>
void Graph<T, E>::Kruskal()
{
	UFSet<T> set( numVertexs );
	MinHeap<MSTEdge<T, E> > heap;
	for ( int i = 0; i < numVertexs; i++ )
		for ( int j = GetFirstNeighbor(i); j >= 0; j = GetNextNeighbor(i, j) )
			heap.Insert( MSTEdge<T, E>(i, j, GetWeight(i, j) ) );

	for ( int count = 0; count < numVertexs && !heap.IsEmpty(); )
	{
		MSTEdge<T, E> edge;
		heap.RemoveMin( edge );
		if ( set.Find(edge.head) != set.Find(edge.tail) )
		{
			count = set.Union(edge.head, edge.tail);
			cout << GetValue(edge.head) << "->" << GetValue(edge.tail) << ends;
		}
	}
}

template <typename T, typename E>
int Graph<T, E>::GetMinEdge(E *dist, int n)
{
	int min = -1;
	//dist==0����ѡ��dist=INF��������
	for ( int i = 0; i < n; i++ )
	{
		if ( dist[i] > 0 && dist[i] < INF )
			if ( min == -1 ) //��ʼ����Сֵ
				min = i;
			else if ( dist[min] > dist[i] ) //�Ƚ�
				min = i;
	}

	return min;
}

//����MST���ʣ�ֻ��Ҫά��V����ѡ�㼯�ϣ���U=S-V��δѡ�㼯�ϣ�
template <typename T, typename E>
void Graph<T, E>::Prim()
{
	E *dist = new E[numVertexs];
	int *parent = new int[numVertexs];
	assert( dist && parent );
	for ( int i = 0; i < numVertexs; i++ )
	{
		dist[i] = GetWeight(0, i);  //��ʼ����ѡ���һ����
		if ( dist[i] == 0 || dist[i] == INF )
			parent[i] = -1;
		else
			parent[i] = 0;
	}

	//����numVertexs - 1��ѡ����С��
	for ( i = 1; i < numVertexs; i++ )
	{
		int v = GetMinEdge(dist, numVertexs);
		dist[v] = 0;
		
		for ( int j = 0; j < numVertexs; j++ )
			if ( dist[j] > 0 && dist[j] > GetWeight(v, j) )
			{
				dist[j] = GetWeight(v, j);
				parent[j] = v;
			}
	}

	//���MST
	for ( i = 0; i < numVertexs; i++ )
		if ( parent[i] != -1 )
			cout << GetValue( i ) << "->" << GetValue( parent[i] ) << ends;
}

//������Ȩ��
template <typename T, typename E>
void Dijkstra(Graph<T, E> &graph, int vertex)
{
	E *dist = new E[graph.numVertexs];
	int *path = new int[graph.numVertexs];
	assert( dist && path );
	for ( int i = 0; i < graph.numVertexs; i++ )
	{
		dist[i] = graph.GetWeight(vertex, i);
		if ( dist[i] == 0 || dist[i] == INF )
			path[i] = -1;
		else
			path[i] = vertex;
	}

	//����n-1��ѡ����̱� dist(j) = min{ dist(i) + weight(i, j) }
	for ( i = 1; i < graph.numVertexs; i++ )
	{
		int v = graph.GetMinEdge(dist, graph.numVertexs);
		dist[v] = -dist[v];
		
		for ( int j = 0; j < graph.numVertexs; j++ )
			if ( dist[j] > 0 && dist[j] > -dist[v] + graph.GetWeight(v, j) )
			{
				dist[j] = (-dist[v]) + graph.GetWeight(v, j);
				path[j] = v;
			}
	}

	for ( i = 0; i < graph.numVertexs; i++ )
	{
		cout << graph.GetValue(i);
		for ( int j = path[i]; j >= 0; j = path[j] )
			cout << "<-" << graph.GetValue(j);
		cout << ": " << -dist[i] << endl;
	}
}

//������Ȩ��
template <typename T, typename E>
void Floyed(Graph<T, E> &graph)
{
	E **dist = new E *[ graph.numVertexs ];
	int **path = new int *[ graph.numVertexs ];
	for ( int i = 0; i < graph.numVertexs; i++ )
	{
		dist[i] = new E[graph.numVertexs];
		path[i] = new int[graph.numVertexs];
	}
	//��ʼ��
	for ( i = 0; i < graph.numVertexs; i++ )
	{
		for ( int j = 0; j < graph.numVertexs; j++ )
		{
			dist[i][j] = graph.GetWeight(i, j);
			if ( dist[i][j] == 0 || dist[i][j] == INF )
				path[i][j] = -1;
			else
				path[i][j] = i;
		}
	}

    //dist(i, j) = min{ dist(i, k) + dist(k, j) }
	for ( int k = 0; k < graph.numVertexs; k++ )
		for ( int i = 0; i < graph.numVertexs; i++ )
			for ( int j = 0; j < graph.numVertexs; j++ )
				if ( dist[i][j] > dist[i][k] + dist[k][j] )
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}

	//output
	for ( i = 0; i < graph.numVertexs; i++ )
		for ( int j = 0; j < graph.numVertexs; j++ )
		{
			cout << graph.GetValue(j);
			for ( int k = path[i][j]; k >= 0 && k != i; k = path[i][k] )
				cout << "<-" << graph.GetValue(k);
			cout << "<-" << graph.GetValue(i) << ": " << dist[i][j] << endl;
		}
}
#endif