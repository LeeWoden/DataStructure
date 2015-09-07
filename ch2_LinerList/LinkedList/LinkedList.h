#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cassert>
using namespace std;

/*
*链表节点
*/
template <typename T>
struct LinkedNode
{
	T data;
	LinkedNode<T> *link;

	LinkedNode(LinkedNode<T> *ptr = NULL)
	{
		link = ptr;
	}

	LinkedNode(const T &item, LinkedNode<T> *ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};

/*
* 带头节点的单向链表
*/
template <typename T>
class LinkedList
{
	public:
	    LinkedList()
		{
			head = new LinkedNode<T>;
		}

		LinkedList(const T& x)
		{
			head = new LinkedeNode<T>( x );
		}

		~LinkedList()
		{
			makeEmpty();
			delete head;
		}

		bool Insert(int i, T &x);
		bool Remove(int i, T &x);
		bool setData(int i, T &x);
		bool getData(int i, T &x) const;
		LinkedNode<T> *Locate(int i) const;
		LinkedNode<T> *Search(const T &x) const;

		int Length() const;
		LinkedNode<T> *getHead() const 
		{ 
			return head; 
		}
		bool IsEmpty() const
		{ 
			return (head->link == NULL) ? true : false; 
		}
		
		void input(T endTag, int sel); //0 表示头插，1表示尾插
		void makeEmpty();
		void Reverse1();
		void Reverse2();

	private:
		LinkedNode<T> *head;
		void inputFront(T endTag); //头插发
		void inputRear(T endTag); //尾插发

		friend ostream &operator << (ostream &out, LinkedList<T> &list) 
		{
			LinkedNode<T> *p = list.head->link;

			while ( p )
			{
				out << p->data <<'\t';
				p = p->link;
			}
			out<<endl;
			return out;
		}

		friend istream &operator >> (istream &in, LinkedList<T> &list) 
		{
			LinkedNode<T> *newNode, *last;
			T val;
			list.makeEmpty();
			last = list.head;
			while ( !in.eof() )
			{
				in >> val;
				newNode = new LinkedNode<T>(val);
				assert(newNode);
				last->link = newNode;
				last = newNode;
			}
			last->link = NULL;
			return in;
		}
};

template <typename T>
void LinkedList<T>::makeEmpty()
{
	LinkedNode<T> *p = head->link;

	while ( p != NULL )
	{
		LinkedNode<T> *q = p;
		p = p->link;
		delete q;
	}
}

template <typename T>
int LinkedList<T>::Length() const
{
	int count = 0;

	LinkedNode<T> *p = head->link;
	while ( p != null )
	{
		count++;
		p = p->link;
	}

	return count;
}

template <typename T>
LinkedNode<T> *LinkedList<T>::Search( const T &x ) const
{
	LinkedNode<T> *p = head->link;
	
	while ( p != NULL && p->data != x )
	{
		p = p->link;
	}

	return p;
}

template <typename T>
LinkedNode<T> *LinkedList<T>::Locate( int i ) const
{
	if ( i < 0 )//i = 0: 获得头节点
		return NULL;

	LinkedNode<T> *p = head;
	int count = 0;

	while ( p != NULL && count < i )
	{
		p = p->link;
		count++;
	}

	return p;
}

template <typename T>
bool LinkedList<T>::getData( int i, T &x ) const
{
	if ( i <= 0 )
		return false;

	LinkedNode<T> *p = Locate( i );
	if ( p == NULL )
		return false;
	else
	{
		x = p->data;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::setData( int i, T &x )
{
	if ( i <= 0 )
		return false;

	LinkedNode<T> *p = Locate( i );
	if ( p == NULL )
		return false;
	else
	{
		p->data = x;
		return true;
	}
}
//通过头结点统一空表、头部、尾部的插入
template <typename T>
bool LinkedList<T>::Insert( int i, T &x )
{
	if ( i <= 0 )
		return false;

	LinkedNode<T> *p = Locate( i - 1 );
	if ( p == NULL )
		return false;
	else
	{
		LinkedNode<T> *tmp = new LinkedNode<T>( x );
		tmp->link = p->link;
		p->link = tmp;
		return true;
	}
}
//通过头结点统一空表、头部、尾部的删除
template <typename T>
bool LinkedList<T>::Remove( int i, T &x )
{
	if ( i <= 0 )
		return false;

	LinkedNode<T> *p = Locate( i - 1 );
	if ( p == NULL || p->link == NULL ) //注意此处有两种状况
		return false;
	else
	{
		LinkedNode<T> *q = p->link;
		p->link = q->link;
		x = q->data;
		delete q;
		return true;
	}
}

//方法1：使用头插法
template <typename T>
void LinkedList<T>::Reverse1()
{
	LinkedNode<T> *q = head->link;
	LinkedNode<T> *p = head;
	p->link = NULL;

	while ( q != NULL )
	{
		LinkedNode<T> *tmp = q;
		q = q->link;
		
		tmp->link = p->link;
		p->link = tmp;
	}
}
//方法2：使用遍历法
template <typename T>
void LinkedList<T>::Reverse2()
{	//空链表或者只有一个节点，无需翻转
	if ( head->link == NULL || head->link->link == NULL )
		return ; 

	LinkedNode<T> *pre, *p;
	pre = head->link;
	p = pre->link;
	pre->link = NULL;

	while ( p != NULL )
	{
		LinkedNode<T> *tmpPre = pre;
		LinkedNode<T> *tmpP = p;

		pre = p;
		p = p->link;

		tmpP->link = tmpPre;
	}

	head->link = pre;
}

template <typename T>
void LinkedList<T>::inputFront(T endTag)
{
	LinkedNode<T> *newNode = NULL;
	T val;
	cin >> val;

	while ( val != endTag )
	{
		newNode = new LinkedNode<T>( val );
		if ( newNode == NULL )
		{
			cerr << "存储分配失败！" << endl;
			exit(0);
		}
		newNode->link = head->link;
		head->link = newNode;
		cin >> val;
	}
}

template <typename T>
void LinkedList<T>::inputRear(T endTag)
{
	LinkNode<T> *tail = head;
	LinkNode<T> *newNode = NULL;
	while ( tail->link != NULL)
		tail = tail->link;

	T val;
	cin >> val;

	while ( val != endTag )
	{
		newNode = new LinkedNode<T>(val);
		if ( newNode == NULL )
		{
			cerr << "存储分配失败！" << endl;
			exit(0);
		}
		tail->link = newNode;
		tail = newNode;
		cin >> val;
	}
	tail->link = NULL;
}

template <typename T>
void LinkedList<T>::input(T endTag, int sel)
{
	assert(sel == 0 || sel == 1);

	if ( sel == 0 )
		inputFront( endTag );
	else if ( sel == 1 )
		inputRear( endTag );
}

#endif