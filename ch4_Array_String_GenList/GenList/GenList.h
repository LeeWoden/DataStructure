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

	GenListNode() : type( LIST ), sublist( NULL ), next( NULL ) {}

	GenListNode(GenListNode<T> &gl) : type( gl.type ), info( gl.info ), next( gl.next ) {}
};

template <typename T>
class GenList
{
	public:
		GenList();
		GenList(GenList<T> &gl);
		~GenList();

		void Traverse(ostream &out = cout) const;
		void Copy(const GenList<T> &gList);
		bool equal(GenList<T> &list) const;
		void delValue(const T &e);

		bool Head(GenListNode<T> &head) const;
		bool Tail(GenList<T> &list) const;
		int Length() const;
		int Depth() const;

	private:
		GenListNode<T> *head;

		void Traverse(GenListNode<T> *p, ostream &out) const; 
		GenListNode<T> *Copy(GenListNode<T> *p);
		void Free(GenListNode<T> *headList);
		void delValue(GenListNode<T> *p, const T &e);

		int Depth(GenListNode<T> *p) const;
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
bool GenList<T>::Head(GenListNode<T> &x)
{
	if ( head == NULL || head->sublist == NULL )
		return false;

	x.type = head->sublist->type;
	x.info = head->sublist->info;
	x.tlink = NULL;
	return true;
}

template <typename T>
bool GenList<T>::Tail(GenList<T> *list)
{

}

template <typename T>
int GenList<T>::Length() const
{
	int count = 0;
	for ( GenListNode<T> *p = head->sublist; p != NULL; p = p->next )
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
	if ( head == NULL || head->type == ATOM )
		return 0;

	int maxDepth = 0;
	for ( p = p->sublist; p != NULL; p = p->next )
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
			out << p->data << " ";
		else
		{
			out << "(";
			Traverse( p->sublist );
			out << ")";
		}
	}
}

template <typename T>
GenListNode<T> * GenList<T>::Copy(GenListNode<T> *p)
{
	if ( p == NULL )
		return ;
	//如果复制方式：考虑表头、子表
	GenListNode<T> *newNode = new GenListNode<T>( *p );
	GenListNode<T> *tail = newNode;
	for ( p = p->sublist; p != NULL; p = p->next )
	{
		if ( newNode == tail ) //首次复制子表
			newNode->sublist = tail = new GenListNode<T>(*p);	
		else
			newNode->next = tail = new GenListNode<T>(*p);

		if ( p->type == LIST )
				tail->sublist = Copy( p->sublist );
	}
	return newNode;
/*
	//如果复制方式：考虑兄弟、子表
	GenListNode<T> *tmpHead = NULL;
	GenListNode<T> *tmpTail = NULL;
	for ( ; p ; p = p->next )
	{
		GenListNode<T> *newNode = new GenListNode<T>(*p);
		if ( p->type == LIST )
			newNode->sublist = Copy(p->sublist);

		if ( tmpHead == NULL )
			tmpHead = tail = newNode;
		else
			tail->next = newNode;
			tail = newNode;
	}
	return tmpHead;
*/
}

template <typename T>
void GenList<T>::Free(GenListNode<T> *list)
{
	if ( list == NULL )
		return ;
	//考虑兄弟、子表，当作单链表
	while ( p )
	{
		GenListNode<T> *del = p;
		p = p->next;
		if ( del->type == LIST )
			Free( del->sublist );
		delete p;
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
void delValue(const T &e)
{
	delValue(e);
}

template <typename T>
void delValue(GenListNode<T> *p, const T &e)
{
	if ( p == NULL )
		return ;

	for (GenListNode<T> *q = p->first; q != NULL; )
	{
		if ( q->type == ATOM && q->data == e )
		{
			p->next = q->next;
			delete q;
		}
		else
			delValue(q, e);
	}

	if ( p->type == LIST && p->sublist )
	{
		
	}
}

#endif