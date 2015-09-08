#ifndef SEQSTACK_H
#define SEQSTACK_H

#include <iostream>
#include <cassert>
using namespace std;

const int defaultSize = 50;
const int stackIncrease = 20;

template <typename T>
class SeqStack
{
	public:
		SeqStack(int sz = defaultSize);
		~SeqStack() { delete []elems; }
	
		void Push(const T &x );
		bool Pop(T &x);
		void makeEmpty() { top = 0; }
		
		bool IsFull() const { return top == maxSize; }
		bool IsEmpty() const { return top == 0; }
		int getSize() const { return top; }
		bool getTop(T &x)
		{
			if ( IsEmpty() )
				return false;
			else {
				x = elems[top - 1];
				return true;
			}
		}
		
	
	private:
		T *elems;
		int maxSize;
		int top; //top指向下一个空闲位置
		void overflowProcess();
		
	friend ostream& operator << ( ostream &out, SeqStack<T> &s )
	{
		out << "Index of top is: " << s.top << endl;
		for ( int i = 0; i < s.top; i++ )
			out << i << ": " << s.elems[i] << endl;
		return out;
	}
};

template <typename T>
SeqStack<T>::SeqStack(int sz)
{
	maxSize = sz;
	top = 0;
	
	elems = new T[maxSize];
	assert( elems );
}

template <typename T>
void SeqStack<T>::overflowProcess()
{
	maxSize = maxSize + stackIncrease;
	T *newElems = new T[maxSize];
	assert( newElems );
	
	for ( int i = 0; i < top; i++ )
		newElems[i] = elems[i];
	
	delete []elems;
	elems = newElems;
}

template <typename T>
void SeqStack<T>::Push(const T &x)
{
	if ( IsFull() )
		overflowProcess();
	
	elems[top++] = x;	
}

template <typename T>
bool SeqStack<T>::Pop(T &x)
{
	if (IsEmpty()){
		return false;
	}
	x = elems[--top];
	return true; 
}

#endif