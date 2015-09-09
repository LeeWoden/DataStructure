#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H
#include "LinkedQueue.h"

template <typename T>
class LinkDeque : public LinkQueue<T>
{
	public:
		LinkDeque() {} //调用基类
		~LinkDeque() {}//调用基类

		bool getHead( T &x ) const;
		bool getTail( T &x ) const;

		bool EnQueueHead(T &x );
		bool EnQueueTail(T &x );
		bool DeQueueHead( T &x );
		bool DeQueueTail( T &x );
		bool EnQueue( T &x ) { return EnQueueTail( x ); }
		bool DeQueue( T &x ) { return DeQueueHead( x ); }
};

template <typename T>
bool LinkDeque<T>::getHead(T &x) const
{
	return LinkQueue<T>::getFront( x );
}

template <typename T>
bool LinkDeque<T>::getTail(T &x) const
{
	if ( IsEmpty() )
		return false;

	return rear;
}

template <typename T>
bool LinkDeque<T>::EnQueueHead(T &x)
{
	LinkNode<T> *head = rear->link;
	head->link = new LinkNode<T>(x, head->link);
	assert( head->link );
	if ( head == rear )
		rear = head->link;
	return true;
}

template <typename T>
bool LinkDeque<T>::EnQueueTail(T &x)
{
	return LinkQueue<T>::EnQueue( x );
}

template <typename T>
bool LinkDeque<T>::DeQueueHead(T &x)
{
	return LinkQueue<T>::DeQueue( x );
}

template <typename T>
bool LinkDeque<T>::DeQueueTail(T &x)
{
	if ( IsEmpty() )
		return false;

	LinkNode<T> *pre = rear->link;
	while ( pre->link != rear )
		pre = pre->link;

	LinkNode<T> *del = rear;
	rear = pre;
	pre->link = del->link;
	delete del;
	return true;
}

#endif