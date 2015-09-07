#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct CircleLinkNode
{
	T data;
	CircleLinkNode<T> *link;

	CircleLinkNode(T &item, CircleLinkNode<T> *ptr = NULL)
	{
		data = item;
		link = ptr;
	}

	CircleLinkNode(CircleLinkNode<T> *ptr = NULL)
	{
		link = ptr;
	}
};

//��ͷ�ڵ��ѭ������
template <typename T>
class CircleList
{
	public:
		CircleList()
		{
			head = rear = new CircleLinkNode<T>;
			head->link = head;
		}

		CircleList(T &x)
		{
			head = rear = new CircleLinkNode<T>;
			head->link = head;
		}
		
		//�������͡����������Ϊ��Ҫͬʱ��д
		CircleList( CircleList<T> &L ) {}
		CircleList<T> &operator = ( CircleList<T> &L ) {}
		~CircleList()
		{
			makeEmpty();
			delete head;
			head = rear = NULL;
		}
		
		CircleLinkNode<T> *Search(T &x) const;
		CircleLinkNode<T> *Locate(int i) const;
		bool Insert(int i, T &x);
		bool Remove(int i, T &x);
		bool setData(int i, T &x);
		bool getData(int i, T &x) const;
		
		void input(T endTag, int sel)
		{
			assert(sel == 0 || sel ==1 );
			(sel == 0) ? inputFront( endTag ) : inputRear( endTag );
		}

		CircleLinkNode<T> *getHead() 
		{
			return head;
		}

		void makeEmpty();
		void Reverse();
		
		bool IsEmpty()const
		{
			return ( head->link == head) ? true : false;
		}

		int Length() const;

	private:
		CircleLinkNode<T> *head;
		CircleLinkNode<T> *rear;

		void inputFront(T endTag);
		void inputRear(T endTag);

		friend ostream& operator << (ostream &out, CircleList<T> &L)
		{
			CircleLinkNode<T> *p = L.head->link;
			while (p != L.head){
				out << p->data <<'\t';
				p = p->link;
			}
			out<<endl;
			return out;
		}

		friend istream& operator >> (istream &in, CircleList<T> &L)
		{
			L.makeEmpty();
			while (!in.eof()){
				T val;
				in >> val;
				L.rear->link = new CircleLinkNode<T>(val);
				assert(L.rear->link);
				L.rear = L.rear->link;
			}
			L.rear->link = L.head;
			in.clear(0);//����ctrl_Z���������رգ��������´�
			return in;
		}
};

template <typename T>
void CircleList<T>::makeEmpty()
{
	CircleLinkNode<T> *p = head->link;
	while (p != head)
	{
		CircleLinkNode<T> *q = p;
		p = p->link;
		delete q;
	}
	
	head->link = head;
	rear = head;
}

template <typename T>
int CircleList<T>::Length() const
{
	CircLinkNode<T> *p = head->link;
	int count = 0;
	while (p != head )
	{
		count++;
		p = p->link;
	}
	return count;
}

template <typename T>
CircleLinkNode<T> *CircleList<T>::Search( T &x ) const
{
	CircleLinkNode<T> *p = head->link;
	while ( p != head && p->data != x )
	{
		p = p->link;
	}
	if( p == head ) 
		p = NULL;//δ�ҵ�����NULL�����ָ�����һ��
	return p;
}

template <typename T>
CircleLinkNode<T> *CircleList<T>::Locate( int i ) const
{
	if ( i < 0 )
		return NULL;
	if ( i == 0 )
		return head;

	CircleLinkNode<T> *p = head->link;
	int count = 1;
//	( p == head ) ? count = 0 : count = 1;

	while ( p != head && count < i){
		p = p->link;
		count++;
	}
	return ( p == head ) ? NULL : p;
}

template <typename T>
bool CircleList<T>::getData( int i,T &x ) const
{
	if (i <= 0)
	{
		return false;
	}

	CircleLinkNode<T> *p = Locate( i );
	if ( p == NULL ){
		return false;
	}
	else
	{
		x = p->data
		return true;
	}
}

template <typename T>
bool CircleList<T>::setData( int i, T &x )
{
	if (i <= 0)	
		return;

	CircleLinkNode<T> *p = Locate( i );
	if ( p == NULL ) 
		return false;
	else 
	{
		current->data = x;
		return true;
	}
}

template <typename T>
bool CircleList<T>::Insert( int i, T &x )
{
	if ( i <= 0 )
		return false;

	CircleLinkNode<T> *p = Locate( i - 1 );
	if ( p == NULL )
		return false;

	p->link = new CircleLinkNode<T>( x, p->link );
	assert( p->link );
	if ( p == rear ) //�ı�β�ڵ�
		rear = rear->link;

	return true;
}

template <typename T>
bool CircleList<T>::Remove(int i, T &x)
{
	if ( i <= 0 )
		return false;

	CircleLinkNode<T> *p = Locate( i - 1 );
	if ( p->link == head || p == NULL )
		return false;
	/*
	*����ɾ����ѭ������Ϊ�գ������ڵ㣩p == head
	*ɾ��ͷ��㣬Ӱ��β�ڵ㣨�����ڵ㣩p == head
	*ɾ��β�ڵ�p->link = rear
	*    => q = p->link; p->link = q->link; delete q; rear = p;
	*/
	CircleLinkNode<T> *q = p->link;
	p->link = q->link;
	x = q->data;
	delete q;

	if ( p->link == rear )
		rear = p;

	return true;
}

//ͷ�巢ʵ����ת
template <typename T>
void CircleList<T>::Reverse()
{
	CircleLinkNode<T> *p = head->link;
	head->link = rear = head;
	

	while ( p != head )
	{
		CircleLinkNode<T> *q = p;
		p = p->link;

		q->link = head->link;
		head->link = q;
		
		if ( head == rear )	//�״β��룬�ı�β�ڵ�
			rear = q;
	}
}

#endif