#ifndef GENLIST_H
#define GENLIST_H

#include <iostream>
#include <cassert>
using namespace std;

typedef enum { ATOM, LIST } GListNodeType;

//区分表头节点、原子节点
template <typename T>
struct GenListNode
{
	int type;
	union
	{
		T data; //原子节点的数据部分
		GenListNode<T> *sublist;	//表头节点的头指针
	}info;
	GenListNode<T> *next; //尾结点指针

	GenListNode() : type( LIST ), next( NULL ) { info.sublist = NULL; }

	GenListNode(T &x) : type( ATOM ), next( NULL ) { info.data = x; }

	GenListNode(GenListNode<T> &gl) : type( gl.type ), next( gl.next ) 
	{ 
		if ( type == ATOM )
			this->info.data = gl.info.data;
		else
			this->info.sublist = gl.info.sublist;
	}
};

template <typename T>
class GenList
{
	public:
		GenList();
		GenList(GenList<T> &gl);
		~GenList();

		void Traverse(ostream &out = cout) const;
		void Copy(const GenList<T> &gl);
		bool equal(GenList<T> &list) const;
		void delValue(const T &e);

		bool Head(GenListNode<T> &head) const;
		bool Tail(GenList<T> *list) const;
		int Length() const;
		int Depth() const;

	private:
		GenListNode<T> *head;

		void Traverse(GenListNode<T> *p, ostream &out) const; 
		GenListNode<T> *Copy(GenListNode<T> *p);
		void Free(GenListNode<T> *headList);
		void delValue(GenListNode<T> *p, const T &e);
		GenListNode<T> *Create(T str[], int &index);
		T NextElem(T str[], int &index);

		int Depth(GenListNode<T> *p) const;

		friend istream & operator >> ( istream &in, GenList<T> &list )
		{
			char str[128] = "\0";
			int index = 0;
			in >> str;
			list.head = list.Create( str, index );
			return in;
		}

		friend ostream & operator << ( ostream &out, GenList<T> &list )
		{
			list.Traverse(out);
			return out;
		}
};

template <typename T>
GenList<T>::GenList()
{
	head = new GenListNode<T>;
	assert( head );
}

template <typename T>
GenList<T>::GenList(GenList<T> &gl)
{
	head = Copy( gl.head );
}

template <typename T>
GenList<T>::~GenList()
{
	Free( head );
}

template <typename T>
bool GenList<T>::Head(GenListNode<T> &x) const
{
	if ( head == NULL || head->info.sublist == NULL )
		return false;

	x.type = head->info.sublist->type;
	x.info = head->info.sublist->info;
	x.next = NULL;
	return true;
}

template <typename T>
bool GenList<T>::Tail(GenList<T> *list) const
{
	list = new GenListNode<T>;
	if ( head->info.sublist == NULL )
		return false;

	list->info.sublist = Copy( head->info.sublist->next );
	return true;
}

template <typename T>
int GenList<T>::Length() const
{
	int count = 0;
	for ( GenListNode<T> *p = head->info.sublist; p != NULL; p = p->next )
		count++;
	return count;
}

template <typename T>
int GenList<T>::Depth() const
{
	
	return Depth( head );
}

template <typename T>
int GenList<T>::Depth(GenListNode<T> *p) const
{
	if ( p == NULL || p->type == ATOM )
		return 0;

	int maxDepth = 0;
	for ( p = p->info.sublist; p != NULL; p = p->next )
	{
		int depth = Depth( p );
		maxDepth = ( depth > maxDepth ) ? depth : maxDepth;
	}
	return maxDepth + 1;
}

template <typename T>
void GenList<T>::Traverse( ostream &out = cout ) const
{
	Traverse( head, out );
}

template <typename T>
void GenList<T>::Traverse(GenListNode<T> *p, ostream &out) const
{
	if ( p == NULL )
		return ;

	for ( ; p != NULL; p = p->next )
	{
		if ( p->type == ATOM )
			out << p->info.data;
		else
		{
			out << "(";
			Traverse( p->info.sublist, out );
			out << ")";
		}

		if ( p->next != NULL )
			cout << ';';
	}
}

template <typename T>
void GenList<T>::Copy(const GenList<T> &gl)
{
	this->head = Copy( gl.head );
}

template <typename T>
GenListNode<T> * GenList<T>::Copy(GenListNode<T> *p)
{
	if ( p == NULL )
		return NULL;

	//如果复制方式：考虑兄弟、子表
	GenListNode<T> *tmpHead = NULL;
	GenListNode<T> *tmpTail = NULL;
	for ( ; p ; p = p->next )
	{
		GenListNode<T> *newNode = new GenListNode<T>(*p);
		if ( p->type == LIST )
			newNode->info.sublist = Copy(p->info.sublist);

		if ( tmpHead == NULL )
			tmpHead = tmpTail = newNode;
		else
			tmpTail->next = newNode;
			tmpTail = newNode;
	}
	return tmpHead;
}

template <typename T>
void GenList<T>::Free(GenListNode<T> *p)
{
	if ( p == NULL )
		return ;
	//考虑兄弟、子表，当作单链表
	while ( p )
	{
		GenListNode<T> *del = p;
		p = p->next;
		if ( del->type == LIST )
			Free( del->info.sublist );
		delete del;
	}
/*
	//考虑表头、子表，当作广义表
	for ( GenListNode<T> *q = p->sublist, q != NULL; q=q->next )
	{
		if ( q->type == LIST )
			Free( q->sublist );

		delete q;
	}
	delete p;
*/
}

template <typename T>
void GenList<T>::delValue(const T &e)
{
	delValue(head, e);
}

template <typename T>
void GenList<T>::delValue(GenListNode<T> *p, const T &e)
{
	if ( p == NULL )
		return ;

	if ( p->next != NULL )
	{
		GenListNode<T> *q = p->next;
		if ( q->type == ATOM && q->info.data == e )
		{
			p->next = q->next;
			delete q;
			delValue(p, e);
		}
		else
			delValue(q, e);
	}

	if ( p->type == LIST && p->info.sublist != NULL )
	{
		GenListNode<T> *q = p->info.sublist;
		if ( q->type == ATOM && q->info.data == e )
		{
			p->info.sublist = q->next;
			delete q;
			delValue(p, e);
		}
		else
			delValue(q, e);
	}
}

template <typename T>
GenListNode<T> * GenList<T>::Create( T str[], int &index )
{
	T elem = nextElem(str, index);
	if ( elem == '(' )
	{
		GenListNode<T> *newNode = new GenListNode<T>;
		newNode->info.sublist = Create(str, index);
		newNode->next = Create(str, index);
		return newNode;
	}

	if ( elem == ')' || elem == '\0' )
		return NULL;

	GenListNode<T> *newNode = new GenListNode<T>( elem );
	newNode->next = Create(str, index);
	return newNode;
}

template <typename T>
T nextElem( T str[], int &index )
{
	while ( str[index] == ',' ) //此处结束标记简单的记作空格
		index++;

	return str[index++];
}

#endif