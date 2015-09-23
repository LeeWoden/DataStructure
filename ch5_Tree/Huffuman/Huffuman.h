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

	HuffumanNode() 
		: data(0), weight(0.0), parent(-1), lchild(-1), rchild(-1) {}
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
		void SelectSmall(T &least, T &leass);
};

template <typename T>
void Huffuman<T>::CreateHuffuman( instream &in = cin )
{
	cin >> this->leafSize;
	tree = new HuffumanNode<T> [ this->leafSize * 2 - 1 ];
	assert( tree );
	//初始化
	for ( int i = 0; i < this->leafSize; i++ )
	{
		cin >> tree[i].date;
		cin >> tree[i].weight;
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
bool Huffuman<T>::SelectSmall(T &least, T &less)
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
					int tmp = least; least = less; less = least;
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
	for (  ; i < this->leafSize * 2 - 1; i++ )
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

#endif