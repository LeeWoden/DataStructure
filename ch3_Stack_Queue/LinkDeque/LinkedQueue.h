#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;

	LinkNode( T &item, LinkNode<T> *ptr = NULL )
	{
		data = item;
		link = ptr;
	}

	LinkNode( LinkNode<T> *ptr = NULL )
	{
		link = ptr;
	}
};

/*
*队列 ：带头节点的循环链表
*/
template <typename T>
class LinkQueue
{
	public:
		LinkQueue();
		LinkQueue(T &x);
		~LinkQueue();

		bool EnQueue(T &x);
		bool DeQueue(T &x);
		void makeEmpty();
		bool getFront(T &x) const;

		int getSize() const;
		bool IsEmpty() const { return rear->link == rear; }
		bool IsFull() const { return false; }

	protected:
		LinkNode<T> *rear;

	friend ostream & operator << ( ostream &os, LinkQueue<T> &Q )
	{
		LinkNode<T> *head = Q.rear->link;
		LinkNode<T> *p = head->link;
		int count = 0;
		
		while ( p != head )
		{
			os << "#" << ++count << ": " << p->data << endl;
			p = p->link;
		}
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
};

template <typename T>
LinkQueue<T>::LinkQueue()
{
	LinkNode<T> *head = new LinkNode<T>;
	assert( head );
	head->link = rear = head;
}

template <typename T>
LinkQueue<T>::LinkQueue(T &x)
{
	LinkNode<T> *head = new LinNode<T>( x );
	assert( head );
	head->link = rear = head;
}

template <typename T>
LinkQueue<T>::~LinkQueue()
{
	makeEmpty(); //清空后头尾指针指向一个位置
	delete rear;
}

//将尾节点转化为头结点，其余节点删除
template <typename T>
void LinkQueue<T>::makeEmpty()
{
	while ( rear->link != rear )
	{
		LinkNode<T> *del = rear->link;
		rear->link = del->link;
		delete del;
		del = NULL;
	}
}

template <typename T>
bool LinkQueue<T>::EnQueue(T &x)
{
	rear->link = new LinkNode<T>(x, rear->link);
	assert( rear->link );
	rear = rear->link;
	return true;
}

template <typename T>
bool LinkQueue<T>::DeQueue(T &x)
{
	if ( IsEmpty() )
		return false;

	LinkNode<T> *head = rear->link;
	LinkNode<T> *del = head->link;

	head->link = del->link; //连接
	if ( del == rear )	//判断删除对尾指针的影响
		rear = head;
	
	delete del;
	return true;
}

template <typename T>
bool LinkQueue<T>::getFront(T &x) const
{
	if ( IsEmpty() )
		return false;

	x = rear->link->link->data;
	return true;
}

template <typename T>
int LinkQueue<T>::getSize() const
{
	LinkNode<T> *p = rear;
	int count = 0;

	while ( p->link != rear )
	{
		p = p->link;
		count++;
	}

	return count;
}

#endif