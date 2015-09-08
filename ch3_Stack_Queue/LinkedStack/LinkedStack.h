#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct StackNode
{
	T data;
	StackNode<T> *link;

	StackNode( const T &item, StackNode<T> *ptr = NULL ) : data( item ), link( ptr ) {}
};

template <typename T>
class LinkedStack
{
	public:
		LinkedStack() : top( NULL ) {}
		~LinkedStack() { makeEmpty(); }

		void Push(const T &x);
		bool Pop(T &x);
		void makeEmpty();

		int getSize() const;
		bool getTop(T &x) const;
		bool IsEmpty() const { return top == NULL; }
		bool IsFull() const { return false; }
			
	private:
		StackNode<T> *top;

	friend ostream & operator << ( ostream &out, LinkedStack<T> &lst )
	{
		out << "Stack Size: " << lst.getSize() << endl;

		int count = 0;
		for ( StackNode<T> *p = lst.top; p != NULL; p = p->link )
			out << ++count << ": " << p->data << endl;
		
		return out;
	}
};

template <typename T>
bool LinkedStack<T>::getTop(T &x) const
{
	if ( IsEmpty() )
		return false;
	
	x = top->data;
	return true;
}

template <typename T>
void LinkedStack<T>::makeEmpty()
{
	while ( top != NULL )
	{
		StackNode<T> *del = top;
		top = top->link;
		delete del;
	}
}

template <typename T>
void LinkedStack<T>::Push(const T &x)
{
	top = new StackNode<T>(x, top);
	assert( top );
}

template <typename T>
bool LinkedStack<T>::Pop(T &x)
{
	if ( IsEmpty() )
		return false;

	StackNode<T> *del = top;
	top = top->link;
	x = del->data;
	delete del;
	return true;
}

template <typename T>
int LinkedStack<T>::getSize() const
{
	StackNode<T> *p = top;
	int count = 0;

	while ( p != NULL )
	{
		p = p->link;
		count++;
	}

	return count;
}

#endif