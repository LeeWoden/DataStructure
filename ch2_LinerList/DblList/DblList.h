#ifndef DBLLIST_H
#define DBLLIST_H

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

template <typename T>
struct DblNode
{
	T data;
	DblNode<T> *lLink;
	DblNode<T> *rLink;

	DblNode( DblNode<T> *l = NULL, DblNode<T> *r = NULL )
	{
		lLink = l;
		rLink = r;
	}

	DblNode(T value, DblNode<T> *l = NULL, DblNode<T> *r = NULL)
	{
		data = value;
		lLink = l;
		rLink = r;
	}
};

//带头节点的双向循环链表
template <typename T>
class DblList
{
	public:
		DblList();
		DblList( T &value );
		~DblList();

		//dirction=0表示查找前驱；direction=1表示查找后继
		DblNode<T> *Locate(int i, int direction = 1) const;
		DblNode<T> *Search(const T &x, int direction = 1) const;
		bool Insert( int i, const T &x, int direction = 1 );
		bool Remove( int i, T &x, int direction = 1 );
		void makeEmpty();
		DblNode<T> *getHead() const { return head; }

		bool IsEmpty() const { return (head->rLink == head ) ? true : false; }
		bool IsFull() const { return false; }

		friend ostream & operator << ( ostream &out, DblList<T> &dbl)
		{
			for( DblNode<T> *p = dbl.head->rLink; p != dbl.head; p = p->rLink )
			{
				out << p->data << ends;
			}
			out << endl;
			return out;
		}

		friend istream & operator >> ( istream &in, DblList<T> &dbl )
		{
			for ( int i = 1; !in.eof(); i++ )
			{
				T data;
				in >> data;
				dbl.Insert(i, data, 1);
			}
			return in;
		}

	private:
		DblNode<T> *head;
};

template <typename T>
DblList<T>::DblList()
{
	head = new DblNode<T>;
	assert( head );
	head->lLink = head->rLink = head;
}

template <typename T>
DblList<T>::DblList(T &value)
{
	head = new DblNode<T>( value );
	assert( head );
	head->lLink = head->rLink = head;
}

template <typename T>
DblList<T>::~DblList()
{
	makeEmpty();
	delete head;
}

template <typename T>
void DblList<T>::makeEmpty()
{
	while ( head->rLink != head )
	{
		DblNode<T> *q = head->rLink;
		head->rLink = q->rLink;
		delete q;
	}
	head->lLink = head; //处理左指针
}

template <typename T>
DblNode<T> *DblList<T>::Locate( int i, int direction ) const
{
	assert(direction == 0 || direction == 1 || i < 0);

	if ( i == 0 )
		return head;

	DblNode<T> *p = ( (direction == 0) ? head->lLink : head->rLink );
	int count = (p != head) ? 1 : 0;
	//cout << "***" << p->data << "**" << count << endl;////////////////////////////////

	while ( p != head && count < i )
	{
		p = ( (direction == 0) ? p->lLink : p->rLink );
		count++;
		//cout << "***" << p->data << "**" << count << endl;////////////////////////////////
	}

	return ( p == head ) ? NULL : p;
}

template <typename T>
DblNode<T> *DblList<T>::Search( const T &x, int direction ) const
{
	DblNode<T> *p = ( direction == 0 ) ? head->lLink : head->rLink;
	while ( p != head && p->data != x)	
	{
		p = ( direction == 0 ) ? p->lLink : p->rLink;
	}
	return ( p == head ) ? NULL : p;
}

template <typename T>
bool DblList<T>::Insert( int i, const T &x, int direction )
{
	assert( i <=0 || direction == 0 || direction == 1 );

	DblNode<T> *pre = Locate( i - 1, direction );
	if ( pre == NULL )
		return false;
	
	DblNode<T> *newNode = new DblNode<T>( x );
	if ( direction == 1 )
	{
		newNode->rLink = pre->rLink;
		newNode->lLink = pre;

		pre->rLink->lLink = newNode;
		pre->rLink = newNode;
	}
	else
	{
		//cout << "**" << pre->data << endl;////////////////////////////////s

		newNode->rLink = pre;
		newNode->lLink = pre->lLink;

		pre->lLink->rLink = newNode;
		pre->lLink = newNode;
	}
	return true;
}

template <typename T>
bool DblList<T>::Remove( int i, T &x, int direction )
{
	assert( i <= 0 || direction == 0 || direction == 1 );

	DblNode<T> *del = Locate( i, direction );
	if ( del == NULL )
		return false;

	del->rLink->lLink = del->lLink;
	del->lLink->rLink = del->rLink;
	x = del->data;
	delete del;
	return true;
}

#endif