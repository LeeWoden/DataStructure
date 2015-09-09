#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include <cassert>
using namespace std;

const int defaultSize = 50;

template <typename T>
class PQueue
{
	public:
		PQueue( int sz = defaultSize );
		~PQueue() { delete []elems; }

		bool EnQueue(const T &x);
		bool DeQueue( T &x);
		void makeEmpty();

		bool getFront(T &x) const;
		int getSize() const { return count; }
		bool IsFull() const { return count == maxSize; }
		bool IsEmpty() const { return count == 0; }

		friend ostream& operator << ( ostream &os, PQueue<T> &Q )
		{
			for (int i = 0; i < Q.count; i++)
				os << "#" << i <<": " << Q.elems[i] << endl;
			os << "Queue Size: " << Q.getSize() << endl;
			return os;
		}

	private:
		T *elems;
		int count;
		int maxSize;

		void adjust();
};

template <typename T>
PQueue<T>::PQueue( int sz ) : maxSize( sz ), count( 0 )
{
	elems = new T[ maxSize ];
	assert( elems );
}

template <typename T>
bool PQueue<T>::EnQueue(const T &x)
{
	if ( IsFull() )
		return false;

	elems[count++] = x;
	adjust();
	return true;
}

template <typename T>
bool PQueue<T>::DeQueue(T &x)
{
	if ( IsEmpty() )
		return false;

	x = elems[0];
	for ( int i = 1; i < count; i++ )
		elems[i - 1] = elems[i];
	count--;
	return true;
}

//ÀàËÆÓÚ²åÈëÅÅÐò
template <typename T>
void PQueue<T>::adjust()
{
	T item = elems[count - 1];
	for ( int j = count - 2; j >= 0; j-- )
	{
		if ( elems[j] > item )
			elems[j + 1] = elems[j];
		else
			break;
	}
	elems[j + 1] = item;
}

template <typename T>
bool PQueue<T>::getFront(T &x) const
{
	if ( IsEmpty() )
		return false;

	x = elems[0];
	return true;
}
#endif