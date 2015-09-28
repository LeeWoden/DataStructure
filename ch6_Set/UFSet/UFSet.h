#ifndef UFSET_H
#define UFSET_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
using namespace std;

const int defaultSize = 20; 

template <typename T>
class UFSet
{
	public:
		UFSet(int sz = defaultSize);
		~UFSet();

		int Find(int i);
		void Union(int i, int j);
		void WeightUnion(int i, int j);
		int CollapsingFind(int i);

		friend ostream & operator << (ostream & out, UFSet & R)
		{
			int i;
			out << "\n" << string(70, '=');
			for ( int j = 0; j <= ( R.size - 1 ) / 10; j++ )
			{
				out << "\nNode:\t";
				for( i = 10 * j; i < 10 * ( j + 1 ) && i < R.size; i++)
				{
					out << setw(6) << i;
				}
				cout << "\nParent:\t";
				for(i = 10 * j; i < 10 * ( j + 1 ) && i < R.size; i++)
				{
					out << setw(6) << R.parent[i];
				}
				
				if (i < R.size)
				{
					out << "\n" << string(70, '-');
				}
			}
			out << "\n" << string(70, '=') << "\n";
			return out;
		}

	private:
		T *data;
		int *parent; //初始化，父节点均为-1；根节点中存储着节点数量的负数
		int size;
};

template <typename T>
UFSet<T>::UFSet(int sz)
{
	size =sz;
	data = new T[sz];
	assert( data );
	parent = new int[sz];
	assert( data );

	for ( int i = 0; i < size; i++ )
		parent[i] = -1;
}

template <typename T>
UFSet<T>::~UFSet()
{
	if ( data != NULL )
		delete data;
	if ( parent != NULL )
		delete parent;
}

template <typename T>
int UFSet<T>::Find(int i)
{
	while ( parent[i] >= 0 )
		i = parent[i];
	return i;
}

template <typename T>
void UFSet<T>::Union(int i, int j)
{
	int root1 = Find( i );
	int root2 = Find( j );

	if ( root1 != root2 )
	{
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}

template <typename T>
void UFSet<T>::WeightUnion(int i, int j)
{
	int root1 = Find( i );
	int root2 = Find( j );

	if ( root1 != root2 )
	{
		//根节点存储节点数量的负数
		if ( parent[root1] < parent[root2] )
		{
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
		else
		{
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
	}
}

template <typename T>
int UFSet<T>::CollapsingFind(int i)
{
	//根节点
	int root = i;
	while ( parent[root] >= 0 )
		root = parent[root];

	while ( i != root )
	{
		int tmp = parent[i];
		parent[i] = root;
		i = tmp;
	}

	return root;
}

#endif