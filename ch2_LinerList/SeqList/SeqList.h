#ifndef SEQLIST_H
#define SEQLIST_H

#include <iostream>
#include <cassert>
using namespace std;

const int defaultSize = 100;

#include "LinerList.h"

template <typename T>
class SeqList : public LinerList<T>
{
	protected:
		T *data; //数据指针
		int maxSize; //数组容量
		int n; //数据大小
		
		void reSize(int newSize);
		
	public:
		SeqList(int sz = defaultSize);
		SeqList(SeqList<T>& L);
		~SeqList();

		bool setData(int i, T& x);
		bool getData(int i, T& x) const;
		int Search(T& x) const;
		bool Insert(int i, T& x);
		bool Remove(int i, T& x);
		
		int Size() const;
		int Length() const;
		bool IsEmpty() const;
		bool IsFull() const;
		
		void Sort();
		void input();
		void output();
		SeqList<T> operator = (SeqList<T>& L);

	friend istream& operator >> (istream &in, SeqList<T> &R)
	{
		R.n = 0;//先清空
		while (!in.eof())
		{
			assert(in >> R.data[R.n]);
			R.n++;
		}
		return in;
	}

	friend ostream& operator << (ostream &out, SeqList<T> &R)
	{
		for (int i = 0; i < R.n; i++){
			cout << "#" << i+1 << ":\t" << R.data[i] << endl;
		}
		return out;
	}
};

template<typename T>
SeqList<T>::SeqList(int sz)
{
	if ( sz > 0 ) 
	{
		maxSize = sz;
		n = 0;
		data = new T[maxSize];

		if ( data == NULL )
		{
			cerr << "存储分配失败！" << endl;
			exit(1);
		}
	}
}

template <typename T>
SeqList<T>::SeqList(SeqList<T>& L)
{
	maxSize = L.Size();
	n = L.Length();
	data = new T[maxSize];

	if (data == NULL)
	{
		cerr << "存储分配失败！" << endl;
		eixt(0);
	}

	T x;
	for (int i = 0; i < n; i++ ) 
	{
		L.getData(i + 1, x);
		data[i] = x;
	}
}

template <typename T>
SeqList<T>::~SeqList()
{
	delete []data;
}

template <typename T>
int SeqList<T>::Search(T& x) const
{
	for (int i = 0; i < n; i++ )
	{
		if ( data[i] == x )
			return i + 1;
	}

	return 0; //搜索失败
}

template <typename T>
bool SeqList<T>::setData(int i, T& x)
{
	if ( i < 1 || i > n )
		return false;

	data[i - 1] = x;
	return true;
}

template <typename T>
bool SeqList<T>::getData(int i, T& x) const
{
	if ( i < 1 || i > n )
		return false;

	x = data[i - 1];
	return true;
}

template <typename T>
bool SeqList<T>::Insert(int i, T& x)
{
	if (n == maxSize || i < 1 || i > n + 1)
		return false;
	
	for (int j = n; j >= i; j--)
	{
		data[j] = data[j - 1];
	}
	
	data[j] = x;
	n++;
	return true;
}

template <typename T>
bool SeqList<T>::Remove(int i, T& x)
{
	if ( n == 0 || i < 1 || i > n )
		return false;

	for (int j = i; j < n; j++ )
	{
		data[j - 1] = data[j];
	}
	n--;
	return true;
}

template <typename T>
bool SeqList<T>::IsEmpty() const
{
	return (n == 0) ? true : false;
}

template <typename T>
bool SeqList<T>::IsFull() const
{
	return (n == maxSize) ? true : false;
}

template <typename T>
int SeqList<T>::Length() const
{
	return n;
}

template <typename T>
int SeqList<T>::Size() const
{
	return maxSize;
}

template <typename T>
SeqList<T> SeqList<T>::operator = (SeqList<T>& L)
{
	maxSize = L.Size();
	n = L.Length();

	delete []data;
	data = new T[maxSize];
	if ( data == NULL ) 
	{
		cerr << "存储分配失败！" << endl;
		exit(0);
	}

	T x;
	for ( int i = 0; i < n; i++ )
	{
		L.getData(i, x);
		data[i] = x;
	}
}

template <typename T>
void SeqList<T>::input()
{
	cout << "Input the size of the list which will be created:";
	while (1)	
	{
		assert(cin >> n);
		if (n < 1) {
			cout << "Input error, the size must be positive!\n";
			cout << "Input the size again:";
		}
		else if (n > maxSize-1) {
			cout << "Input error, the size must be less than maxSize!\n";
			cout << "Input the size again:";
		}
		else	break;
	}

	cout << "\nInput the data for each element to create the list:" << endl;
	for (int i = 0; i < n; i++){
		cout << "#" << i+1 << ":";
		assert(cin >> data[i]);
	}
}

template <typename T>
void SeqList<T>::output()
{
	cout << "\nThe size of the list is:" << n << endl;
	for (int i = 0; i < n; i++)	
	{
		cout << "#" << i+1 << ":\t" << data[i] << endl;
	}
}

template <typename T>
void SeqList<T>::Sort()
{

}

#endif