#ifndef INTHREADTREE_H
#define INTHREADTREE_H

#include <iostream>
using namespace std;

enum Tag { THREAD, LINK };

template <typename T>
struct ThrTreeNode
{
	T data;
	Tag ltag, rtag;
	ThrTreeNode<T> *lchild, *rchild;

	ThrTreeNode( T &val ) 
		: data( val ), ltag( LINK ), rtag( LINK ), lchild( NULL ), rchild( NULL )
	{}
};

template <typename T>
class InThreadTree
{
	public:
		InThreadTree(T &end) : root( NULL ), endTag( end ) {}
		InThreadTree( T *array, int n, T &end );
		~InThreadTree() { MakeEmpty( root ); }

		ThrTreeNode<T> * GetNext( ThrTreeNode<T> *p );
		ThrTreeNode<T> * GetPrev( ThrTreeNode<T> *p );
		ThrTreeNode<T> * GetParent( ThrTreeNode<T> *p );
		ThrTreeNode<T> * Find( const T &x );
		void InOrder();

		void PrePost( ThrTreeNode<T> *p )
		{
			if ( p == NULL ) return;
			cout << p->data << ends;
			if ( p->ltag == LINK ) PrePost( p->lchild );
			if ( p->rtag == LINK ) PrePost( p->rchild );
		}
		
	private:
		ThrTreeNode<T> *root;
		T endTag;

		ThrTreeNode<T> *CreateByPre( T *array, int &pos );
		void MakeInThread( ThrTreeNode<T> *&pre, ThrTreeNode<T> *p);
		void MakeEmpty( ThrTreeNode<T> *p );
};

template <typename T>
InThreadTree<T>::InThreadTree(T *array, int n, T &end)
{
	endTag = end;
	int pos = 0;
	root = CreateByPre(array, pos);

    ThrTreeNode<T> *pre = NULL;
	MakeInThread( pre, root );
	pre->rtag = THREAD;
	pre->rchild = NULL; //毋忘，添加最后一个节点的后继指针
}

template <typename T>
ThrTreeNode<T> * InThreadTree<T>::CreateByPre( T *array, int &pos )
{
	if ( array[pos] == endTag )
	{
		pos++;
		return NULL;
	}

	ThrTreeNode<T> *tmp = new ThrTreeNode<T>( array[pos++] );
	tmp->lchild = CreateByPre(array, pos);
	tmp->rchild = CreateByPre(array, pos);
	return tmp;
}

template <typename T>
void InThreadTree<T>::MakeInThread( ThrTreeNode<T> *&pre, ThrTreeNode<T> *p)
{
	if ( p == NULL )
		return ;

	MakeInThread(pre, p->lchild);

	if ( pre != NULL && pre->rchild == NULL )
	{
		pre->rtag = THREAD;
		pre->rchild = p;
	}
	if ( p->lchild == NULL )
	{
		p->ltag = THREAD;
		p->lchild = pre;
	}
	pre = p;
	MakeInThread(pre, p->rchild);
}

template <typename T>
void InThreadTree<T>::MakeEmpty( ThrTreeNode<T> *p )
{
	if ( p == NULL )
		return ;

	if ( p->ltag == LINK )
		MakeEmpty( p->lchild );
	if ( p->rtag == LINK )
		MakeEmpty( p->rchild );
	delete p;
}

template <typename T>
ThrTreeNode<T> * InThreadTree<T>::GetNext( ThrTreeNode<T> *p )
{
	if ( p == NULL )
		return NULL;

	if ( p->rtag == THREAD )
		return p->rchild;

	for ( p = p->rchild; p && p->ltag == LINK; )
		p = p->lchild;
	
	return p;
}

template <typename T>
ThrTreeNode<T> * InThreadTree<T>::GetPrev( ThrTreeNode<T> *p )
{
	if ( p == NULL )
		return NULL;

	if ( p->ltag == THREAD )
		return p->lchild;
 
	for ( p = p->lchild; p && p->rtag == LINK; )
		p = p->rchild;

	return p;
}

template <typename T>
ThrTreeNode<T> * InThreadTree<T>::GetParent( ThrTreeNode<T> *p )
{
	if ( p == NULL || p == root )
		return NULL;

	//以该节点为根的子树subTree；subTree root NULL
	for ( ThrTreeNode<T> *parent = p; parent->rtag == LINK; )
		parent = parent->rchild;
	parent = parent->rchild;
	if ( parent && parent->lchild == p )
		return parent;
	//以该节点为根的子树subTree；NULL root subTree
	for ( parent = p; parent->ltag == LINK; )
		parent = parent->lchild;
	parent = parent->lchild;
	if ( parent && parent->rchild == p )
		return parent;

	return NULL;
}

template <typename T>
void InThreadTree<T>::InOrder()
{
	ThrTreeNode<T> *p = root;
	while ( p && p->ltag == LINK )
		p = p->lchild;

	while ( p )
	{
		cout << p->data << ends;
		p = GetNext( p );
	}
	cout << endl;
}

template <typename T>
ThrTreeNode<T> * InThreadTree<T>::Find(const T &x)
{
	ThrTreeNode<T> *p = root;
	while ( p && p->ltag == LINK )
		p = p->lchild;

	while ( p )
	{
		if ( p->data == x )
			return p;
		else
			p = GetNext( p );
	}

	return p;
}
#endif