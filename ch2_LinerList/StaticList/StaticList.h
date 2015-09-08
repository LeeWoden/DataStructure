#ifndef STATICLIST_H
#define STATICLIST_H

#include <iostream>
#include <cassert>
using namespace std;

const int defaultSize = 100;

template <typename T>
struct SLinkNode
{
	T data;
	int link;
};

template <typename T>
class StaticList
{
	public:
		StaticList(int sz = defaultSize);
		~StaticList();

		bool IsEmpty() const;
		int Length() const;

		int Search( T x ) const;
		int Locate( int i ) const;
		bool getData( int i, T &x ) const;
		bool Append( T x );
		bool Insert( int i, T x );
		bool Remove( int i, T &x );
		//bool setData( int i, T &x );
		void output(int type = 0);

		friend istream& operator >> (istream& in, StaticList<T> &stl)
		{
			while ( !in.eof() )
			{//��ԭ�������ӣ����������Ա�ͬ
				T data;
				in >> data;
				stl.Append(data);
			}
			return in;
		}
		
		friend ostream & operator<<(ostream &out, StaticList <T> &stl)
		{
			int p = stl.elem[0].link;//elem[0]Ϊ����ͷ���
			while(p != -1)
			{
				out << stl.elem[p].data << ends;
				p = stl.elem[p].link;
			}
			cout << endl;
			return out;
		}

	private:
		SLinkNode<T> *elem;
		int maxSize;
		int avil; //���пռ�
};

template <typename T>
StaticList<T>::StaticList(int sz)
{
	maxSize = sz;
	//allocated
	elem = new SLinkNode<T>[ maxSize ];
	assert( elem );
	elem[0].link = -1;
	//available
	avil = 1;
	for ( int i = 1; i < maxSize - 1; i++ )
		elem[i].link = i + 1;
	
	elem[i].link = -1;
}

template <typename T>
StaticList<T>::~StaticList()
{
	delete []elem;
}

template <typename T>
int StaticList<T>::Length() const
{
	int p = 0;
	int count = 0;
	
	while ( elem[p].link != -1 )
	{
		count++;
		p = elem[p].link;
	}

	return count;
}

template <typename T>
bool StaticList<T>::IsEmpty() const
{
	return ( elem[0].link == -1 ) ? true : false;
}

template <typename T>
int StaticList<T>::Search(T x) const
{
	int p = elem[0].link;
	for ( ; p != -1 && elem[p].data != x; p = elem[p].link ) {}

	return p;
}

template <typename T>
int StaticList<T>::Locate(int i) const
{
	int count  = 0;
	int p = 0;

	for ( ; p != -1 && count < i; p = elem[p].link, count++ ) {}
	return p;
}

template <typename T>
bool StaticList<T>::getData( int i, T &x ) const
{
	if ( i <= 0 )
		return false;

	int p = Locate( i );
	if ( p == -1 )
		return false;
	else
	{
		x = elem[p].data;
		return true;
	}
}

template <typename T>
bool StaticList<T>::Append(T x)
{
	if ( avil == -1 )
		return false;

	//�����ڵ�
	int alloc = avil;
	avil = elem[avil].link;
	elem[alloc].data = x;
	elem[alloc].link = -1;
	//Ѱ�������β
	for ( int tail = 0; elem[tail].link != -1; tail = elem[tail].link ) {}
	//����
	elem[tail].link = alloc;
	return true;
}

template <typename T>
bool StaticList<T>::Insert(int i, T x)
{
	if ( avil == -1 )
		return false;

	int pre = Locate(i - 1);
	if ( pre == -1 )
		return false;
	
	int alloc = avil;
	avil =elem[avil].link;
	elem[alloc].data = x;
	elem[alloc].link = elem[pre].link;
	elem[pre].link = alloc;
	return true;
}

template <typename T>
bool StaticList<T>::Remove( int i, T &x )
{
	if ( i <= 0 || elem[0].link == -1 )
		return false;
	
	int pre = Locate( i - 1 );
	if ( pre == -1 || elem[pre].link == -1 )
		return false;

	//�ͷ�
	int del = elem[pre].link;
	elem[pre].link = elem[del].link;
	x = elem[del].data;
	//����
	elem[del].link = avil;
	avil = del;
	return true;
}

template <typename T>
void StaticList<T>::output(int type)
{
	if ( IsEmpty() )
	{
		cout << "The static list is empty!\n";
		return;
	}

	if (type == 0){//���������
		cout << "Index\tData" << endl;
		cout << "0\thead" << endl;
		int p = elem[0].link;
		while(p != -1)
		{
			cout << p << "\t" << elem[p].data << endl;
			p = elem[p].link;
		}
		cout << "Static List length: " << Length() << endl;
	}
	else {//��˳������
		cout << "Index\tData\tLink" << endl;
		cout << "0\thead\t" << elem[0].link << endl;
		int avl = avil;
		for (int i = 1, len = Length(); len > 0; i++){//�������������
			if (i == avl){
				cout << i << "\t\t" << elem[i].link << endl;//���ý�㲻���ֵ
				avl = elem[avl].link;
			}
			else{//�����еĽ��
				cout << i << "\t" << elem[i].data << "\t" << elem[i].link << endl;
				len--;
			}
		}
		cout << "First available position: " << avil << endl;
	}
	cout << endl;
}


#endif