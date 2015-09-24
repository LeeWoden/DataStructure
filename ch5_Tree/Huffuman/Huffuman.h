#ifndef HUFFUMAN_H
#define HUFFUMAN_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

template <typename T>
struct HuffumanNode
{
	T data;
	double weight;
	int parent, lchild, rchild;

	HuffumanNode(T val, double w, int p = -1, int l = -1, int r = -1 )
		: data( val ), weight( w ), parent( p ), lchild( l ), rchild( r ) {}

	HuffumanNode() 
		: data(0), weight(0.0), parent(-1), lchild(-1), rchild(-1) {}
};

template <typename T>
class Huffuman
{
	public:
		Huffuman() : tree( NULL ), leafSize( 0 ) {}
		~Huffuman() { delete []tree; }
		void Code(T &x);
		void Decode(char codes[], int n);

		friend istream & operator >> (istream &in, Huffuman<T> &h)
		{
			h.CreateHuffuman( in );
			return in;
		}
		
	private:
		HuffumanNode<T> *tree;
		int leafSize; //叶子数量n，哈夫曼数的节点数量为2*n - 1
		vector<vector<int> > codes;

		void CreateHuffuman( istream &in = cin );
		void SelectSmall(int &least, int &leass);
};

template <typename T>
void Huffuman<T>::CreateHuffuman( istream &in = cin )
{
	in >> this->leafSize;
	tree = new HuffumanNode<T> [ this->leafSize * 2 - 1 ];
	assert( tree );
	//初始化
	for ( int i = 0; i < this->leafSize; i++ )
	{
		in >> tree[i].data;
		in >> tree[i].weight;
	}
	//构建哈夫曼树
	for ( i = leafSize; i < this->leafSize * 2 - 1; i++ )
	{
		int least = -1, less = -1;
		SelectSmall(least, less);
		tree[i].weight = tree[least].weight + tree[less].weight;
		tree[i].lchild = least;
		tree[i].rchild = less;
		
		tree[least].parent = tree[less].parent = i;
	}
}

template <typename T>
void Huffuman<T>::SelectSmall(int &least, int &less)
{
	int flag = 0; //0：表示初始化least, 1：表示初始化less
	for ( int i = 0; i < this->leafSize * 2 - 1; i++ )
	{   //该节点存在 且 未被选中
		if ( tree[i].weight != 0 && tree[i].parent == -1 )
		{
			if( flag == 0 )
			{
			    least =  i;
				flag = 1;
			}
			else
			{
				less = i;
				if ( tree[least].weight > tree[less].weight )
				{
					int tmp = least; least = less; less = tmp;
				}
				break ;
			}
		}
	}

	if (i == this->leafSize * 2 - 1)
	{
		cout << "不能选择两个最小节点!as" << endl;
		return;
	}

	//继续比较
	for (  i = i + 1; i < this->leafSize * 2 - 1; i++ )
	{   //存在且未被选中
		if ( tree[i].weight != 0 && tree[i].parent == -1 )
		{
			if ( tree[i].weight < tree[least].weight )
			{
				less = least;
				least = i;
			}
			else if ( tree[i].weight < tree[less].weight ) 
			{
				less = i;
			}
		}
	}
}

template <typename T>
void Huffuman<T>::Code( T &x )
{
	//定位
    for ( int index = 0; index < leafSize && tree[index].data != x; index++ ) {}
    if ( index == leafSize )
    {
		cout << x << " : 不是恰当的字符!"  << endl;
		return ;
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
void Huffuman<T>::Decode(char codes[], int n)
{
	int currentPos = 2 * this->leafSize - 2;
	for ( int i = 0; i < n; i++ )
	{
		if ( codes[i] == '0' )
			currentPos = tree[currentPos].lchild;
		else if ( codes[i] == '1' )
			currentPos = tree[currentPos].rchild;
		
		if ( tree[currentPos].lchild == -1 && tree[currentPos].rchild == -1 )
		{
			cout << tree[currentPos].data;
			currentPos = 2 * this->leafSize - 2;
		}
	}
	cout << endl;
}

#endif