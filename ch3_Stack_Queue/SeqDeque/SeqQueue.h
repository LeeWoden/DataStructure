#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <cassert>
#include <iostream>
using namespace std;

const int defaultSize = 50;

//循环队列
template <typename T>
class SeqQueue
{
	public:
		SeqQueue(int sz = defaultSize);
		~SeqQueue() { delete []elems; }

		bool EnQueue(const T &x);
		bool DeQueue(T &x);
		bool getFront(T &x) const;
		void makeEmpty();

		bool IsEmpty() const { return front == rear; }
		bool IsFull() const { return ( rear + 1 ) % maxSize == front; }
		int getSize() const { return ( rear - front + maxSize ) % maxSize; }

	protected:
		T *elems;
		int maxSize;
		int front, rear; //font:指向队头，rear:指向队尾下面一个位置

	friend ostream & operator << ( ostream & os, SeqQueue<T> &Q )
	{
		os << "front = " << Q.front << ", rear = " << Q.rear << endl;
		for (int i = Q.front; i != Q.rear; i = (i+1) % Q.maxSize){
			os << "#" << i <<": " << Q.elems[i] << endl;
		}			
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
};

template <typename T>
SeqQueue<T>::SeqQueue(int sz)
{
	maxSize = sz;
	front = rear = 0;

	elems = new T[maxSize];
	assert( elems );
}

template <typename T>
bool SeqQueue<T>::EnQueue(const T &x)
{
	if ( IsFull() )
		return false;

	elems[rear] = x;
	rear = ( rear + 1 ) % maxSize;
	return true;
}

template <typename T>
bool SeqQueue<T>::DeQueue(T &x)
{
	if ( IsEmpty() )
		return false;

	x = elems[front];
	front = ( front + 1 ) % maxSize;
	return true;
}

template <typename T>
bool SeqQueue<T>::getFront(T &x) const
{
	if ( IsEmpty() )
		return false;

	x = elems[front];
	return true;
}

#endif