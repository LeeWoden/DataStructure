#ifndef SEQDEQUE_H
#define SEQDEQUE_H

#include "SeqQueue.h"

/*
*˫�˶���
*1. ����ͷ��������β��
*2. ����β��������ͷ��
*/
template <typename T>
class SeqDeque : public SeqQueue<T>
{
	public:
		SeqDeque(int sz = defaultSize) : SeqQueue<T>(sz) {};
		~SeqDeque() {}; //���û���������������

		bool getHead(T &x)const;
		bool getTail(T &x)const;

		bool EnQueueHead(const T &x);
		bool EnQueueTail(const T &x);
		bool DeQueueHead(T &x);
		bool DeQueueTail(T &x);
};

template <typename T>
bool SeqDeque<T>::getHead(T &x) const
{
	return SeqQueue<T>::getFront( x );
}

template <typename T>
bool SeqDeque<T>::getTail(T &x) const
{
	if ( SeqQueue<T>::IsEmpty() )
		return false;

	x = elems[(rear - 1 + maxSize) % maxSize];
	return true;
}

template <typename T>
bool SeqDeque<T>::EnQueueHead(const T &x)
{
	if ( SeqQueue<T>::IsFull() )
		return false;

	front = (front - 1 + maxSize) % maxSize;
	elems[front] = x;
	return true;
}

template <typename T>
bool SeqDeque<T>::EnQueueTail(const T &x)
{
	return SeqQueue<T>::EnQueue( x );
}

template <typename T>
bool SeqDeque<T>::DeQueueTail(T &x)
{
	if ( SeqQueue<T>::IsEmpty() )
		return false;

	rear = ( rear - 1 + maxSize ) % maxSize;
	x = elems[rear];
	return true;
}

template <typename T>
bool SeqDeque<T>::DeQueueHead(T &x)
{
	return SeqQueue<T>::DeQueue( x );
}

#endif