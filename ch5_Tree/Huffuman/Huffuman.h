#ifndef HUFFUMAN_H
#define HUFFUMAN_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct HuffumanNode
{
	T data;
	double weight;
	int parent, lchild, rchild;

	HuffumanNode(T val, double w, int p = -1, int l = -1, int r = -1 )
		: data( val ), weight( w ), parent( p ), lchild( l ), rchild( r ) {}
};

template <typename T>
class Huffuman
{
	public:
		Huffuman() : tree( NULL ), leafSize( 0 ) {}
		~Huffuman() { delete []tree; }

	private:
		HuffumanNode<T> *tree;
		int leafSize; //叶子数量n，哈夫曼数的节点数量为2*n - 1
		vector<vector<int> > codes;

		void CreateHuffuman( instream &in = cin );
};

template <typename T>
void Huffuman<T>::CreateHuffuman( instream &in = cin )
{
	
}

#endif