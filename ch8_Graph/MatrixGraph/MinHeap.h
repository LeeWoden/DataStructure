#ifndef MINHEAP_H
#define MINHEAP_H

#include <cassert>
#include <iostream>
using namespace std;

const int MAXSIZE = 5;
const int INCREASESIZE = 5;

template <typename T>
class MinHeap
{
	public:
		MinHeap(int sz = MAXSIZE);
		MinHeap(T *array, int n, int sz = MAXSIZE);
		~MinHeap();

		bool IsEmpty() { return length == 0; }
		bool Insert(T &x);
		bool RemoveMin(T &x);

		void output()
		{
			for ( int i = 0; i< length; i++ )
				cout << data[i] << " ";
			cout << endl;
		}

	private:
		T *data;
		int maxSize;
		int length;

		void OverFlowProcess(int increaseSize = INCREASESIZE);
		void ShiftDown(int i);
		void ShiftUp(int i);
};


template <typename T>
MinHeap<T>::MinHeap(int sz)
{
	maxSize = sz;
	length = 0;
	data = new T[maxSize];
	assert( data );
}

template <typename T>
MinHeap<T>::MinHeap(T *array, int n, int sz)
{
	while ( sz < n )
		sz += INCREASESIZE;

	maxSize = sz;
	length = n;
	data = new T[sz];
	for ( int i = 0; i < length; i++ )
		data[i] = array[i];

	for ( i = ( length - 2 ) / 2; i >= 0; i-- )
		ShiftDown( i );
}

template <typename T>
MinHeap<T>::~MinHeap()
{
	delete []data;
	data = NULL;
	maxSize = length = 0;
}

template <typename T>
void MinHeap<T>::OverFlowProcess(int increaseSize)
{
	T *tmp = new T[maxSize + increaseSize];
	assert( tmp );
	for ( int i = 0; i < length; i++ )
		tmp[i] = data[i];

	maxSize += increaseSize;
	delete []data;
	data = tmp;
}

template <typename T>
void MinHeap<T>::ShiftDown(int i)
{
	assert( i >= 0 && i <= length - 1 );

	T tmp = data[i];
	int pos = i;
	int child = 2 * i + 1;

	while ( child < length )
	{
		if ( child + 1 < length && data[child] > data[child + 1] )
			child += 1;

		if ( tmp > data[child] )
		{
			data[pos] = data[child];
			pos = child;
			child = 2 * pos + 1;
		}
		else
			break;
	}
	data[pos] = tmp;
}

template <typename T>
void MinHeap<T>::ShiftUp(int i)
{
	assert( length >= 1 && i >= 0 && i <= length - 1 );

	T tmp = data[i];
	int pos = i;
	int parent = (pos - 1) / 2;

	while ( pos > 0 )
	{
		if ( data[parent] > tmp )
			data[pos] = data[parent];
		else
			break;

		pos = parent;
		parent = (pos - 1) / 2;
	}
	data[pos] = tmp;
}

template <typename T>
bool MinHeap<T>::Insert(T &x)
{
	if ( length == maxSize )
		OverFlowProcess();

	data[length++] = x;
	ShiftUp(length - 1);
	return true;
}

template <typename T>
bool MinHeap<T>::RemoveMin(T &x)
{
	if ( length == 0 )
		return false;

	x = data[0];
	data[0] = data[length - 1];
	length -= 1;
	ShiftDown( 0 );
	return true;
}

#endif