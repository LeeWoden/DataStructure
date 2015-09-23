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
		void Code(T &x);
		void Decode(int codes[], int n);
		
	private:
		HuffumanNode<T> *tree;
		int leafSize; //叶子数量n，哈夫曼数的节点数量为2*n - 1
		vector<vector<int> > codes;

		void CreateHuffuman( instream &in = cin );
};

template <typename T>
void Huffuman<T>::Code( T &x )
{
	//定位
    for ( int index = 0; index < leafSize && tree[index].data != x; index++ ) {}
    if ( index == leafSize )
    {
		cout << "请输入恰当的字符!" << endl;
		exit( 0 );
    }
	//编码
	vector<int> codes;
	for ( ; tree[index].parent != -1; index = tree[index].parent)
	{
		int parent = tree[index].parent;
		if ( tree[parent].lchild == index )
			codes.push_back( 0 );
		else
			codes.push_back( 1 );
	}
	
	//输出
	cout << x << " : ";
	for ( int i = codes.size() - 1; i >= 0; i-- )
		cout << codes[i];
	cout << endl;
}

template <typename T>
void Huffuman<T>::Decode(int codes[], int n)
{
	int currentPos = 2 * this->leafSize - 2;
	for ( int i = 0; i < n; i++ )
	{
		if ( codes[n] == 0 )
			currentPos = tree[i].lchild;
		else if ( codes[n] == 1 )
			currentPos = tree[i].rchild;
		
		if ( tree[i].lchild == -1 && tree[i].rchild == -1 )
			cout << tree[i].data;	
	}
	cout << endl;
}

#endif
