#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cassert>
#include <string>
#include <stack>
#include <queue>
using namespace std;

template <typename T>
struct BinTreeNode
{
	T data;
	BinTreeNode<T> *lchild, *rchild;

	BinTreeNode(BinTreeNode<T> &lptr = NULL, BinTreeNode<T> *rptr = NULL) 
		: lchild( lptr ), rchild( rptr ) 
	{}

	BinTreeNode(T &x, BinTreeNode<T> *lptr = NULL, BinTreeNode<T> *rptr = NULL)
		: data( x ), lchild( lptr ), rchild( rptr )
	{}
};

template <typename T>
class BinaryTree
{
	public:
		BinaryTree() : root(NULL) {}
		BinaryTree(T &end) : root(NULL), endTag(end) {}
		BinaryTree(BinaryTree<T> &t) 
		{
			if ( this != &t )
				root = Copy(t.root);
		}
		~BinaryTree() { Destroy(root); }


		//递归前、中、后序遍历
		void PreOrder_Recursion(void (*visit)(BinTreeNode<T> *t))
		{ PreOrder_Recursion(root, visit); cout << endl; }
		void InOrder_Recursion(void (*visit)(BinTreeNode<T> *t))
		{ InOrder_Recursion(root, visit); cout << endl; }
		void PostOrder_Recursion(void (*visit)(BinTreeNode<T> *t))
		{ PostOrder_Recursion(root, visit); cout << endl; }
		//非递归层次、前、中、后序遍历
		void LevelOrder(void (*visit)(BinTreeNode<T> *t));
		void PreOrder_NonRe(void (*visit)(BinTreeNode<T> *t));
		void InOrder_NonRe(void (*visit)(BinTreeNode<T> *t));
		void PostOrder_NonRe(void (*visit)(BinTreeNode<T> *t));

		BinTreeNode<T> *Parent(BinTreeNode<T> *t) const { return Parent(root, t); }
		bool Find(T &x) const { return Find(root, x); }
		bool Insert(T item) { return Insert(root, item); }
		void CreateCompBinTree(T *CBT, int num) //建立完全二叉树
		{ CreateCompBinTree(CBT, num, 0, root); }
		void PrintBinTree(ostream &out = cout) { PrintBinTree(root, out); }//按广义表打印
		void Output(ostream &out = cout) { Output(root, string("  "), out); }//按缩格文本输出

		int Depth() const { return Depth(root); }
		int Size() const { return Size(root); }
		bool IsEmpty() const { return root == NULL; }
		BinTreeNode<T> * LeftChild(BinTreeNode<T> *t)
		{
			return (t != NULL) ? t->leftChild : NULL;
		}
		BinTreeNode<T> * RightChild(BinTreeNode<T> *t)
		{
			return (t != NULL) ? t->rightChild : NULL;
		}
		BinTreeNode<T> * getRoot() const { return root; }

		friend istream& operator >> (istream &in, BinaryTree<T> &Tree)
		{
			Tree.CreateBinTree(in, Tree.root);
			return in;
		}
	
		friend ostream& operator << (ostream& out, BinaryTree<T>& Tree)
		{
			Tree.PrintBinTree(out);
			out << endl;
			return out;
		}
		
	private:
		BinTreeNode<T> *root;
		T endTag;

		void CreateBinTree(istream &in, BinTreeNode<T> *&parent);
		void CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *&parent);
		BinTreeNode<T> *Copy(BinTreeNode<T> *parent);
		void Destroy(BinTreeNode<T> *parent);

		void PreOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t));//前序遍历
		void InOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t));//中序遍历
		void PostOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t));//后序遍历

		int Depth(BinTreeNode<T> *parent) const;
		int Size(BinTreeNode<T> *parent) const;
		BinTreeNode<T> *Parent(BinTreeNode<T> *r, BinTreeNode<T> *t) const;
		bool Find(BinTreeNode<T> *r, T &x) const;
		bool Insert(BinTreeNode<T> *&r, T &item);
		void PrintBinTree(BinTreeNode<T> *r, ostream &out); //按广义表打印
		void Output(BinTreeNode<T> *r, string str, ostream &out); //按缩进文本打印
};

//引用：直接改变指针的地址
//返回地址也可以，创建节点并返回
template <typename T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&parent)
{
	T item;
	if ( in >> item )
	{
		if ( item == endTag )
			parent = NULL;
		else
		{
			parent = new BinTreeNode<T>(item);
			assert( parent );
			CreateBinTree(in, parent->lchild);
			CreateBinTree(in, parent->rchild);
		}
	}
}

template <typename T>
void BinaryTree<T>::CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *&parent)
{
	if ( rt >= num )
		parent = NULL;
	else
	{
		parent = new BinTreeNode<T>( CBT[rt] );
		assert( parent );
		CreateCompBinTree(CBT, num, 2*rt+1, parent->lchild );
		CreateCompBinTree(CBT, num, 2*rt+2, parent->rchild );
	}
}

template <typename T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *parent)
{
	if ( parent == NULL )
		return NULL;

	BinTreeNode<T> *newNode = new BinTreeNode<T>(parent->data);
	assert( newNode );
	newNode->lchild = Copy(parent->lchild);
	newNode->rchild = Copy(parent->rchild);
	return newNode;
}

template <typename T>
void BinaryTree<T>::Destroy(BinTreeNode<T> *parent)
{
	if ( parent == NULL )
		return ;

	Destroy(parent->lchild);
	Destroy(parent->rchild);
	delete parent;
	parent = NULL;
}

template <typename T>
int BinaryTree<T>::Depth(BinTreeNode<T> *parent) const
{
	if ( parent == NULL )
		return 0;

	int l = Depth( parent->lchild );
	int r = Depth( parent->rchild );
	return ( l > r ) ? ( l + 1 ) : ( r + 1 );
}

template <typename T>
int BinaryTree<T>::Size(BinTreeNode<T> *parent) const
{
	if ( parent == NULL )
		return 0;

	return Size( parent->lchild ) + Size( parent->rchild ) + 1;
}

template <typename T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T> *r, BinTreeNode<T> *t) const
{
	if ( r == NULL || r == t )
		return NULL;

	if ( r->lchild == t || r->rchild == t )
		return r;

	BinTreeNode<T> *p = Parent( r->lchild, t );
	if ( p != NULL )
		return p;

	return Parent( r->rchild, t );
}

template <typename T>
bool BinaryTree<T>::Find(BinTreeNode<T> *r, T &x) const
{
	if ( r == NULL )
		return false;

	if ( r->data == x )
		return true;

	if ( Find(r->lchild, x) )
		return true;
	else
		return Find(r->rchild, x);
}

template <typename T>
bool BinaryTree<T>::Insert(BinTreeNode<T> *&r, T &item)
{
	if ( r == NULL )
	{
		r = new BinTreeNode<T>(item);
		assert(r);
		return true;
	}

	return Insert(r->lchild, item) || Insert(r->rchild, item);
}

template <typename T>
void BinaryTree<T>::PrintBinTree(BinTreeNode<T> *r, ostream &out)
{
	if ( r != NULL )
	{
		out << r->data;
		if ( r->lchild || r->rchild )
		{
			out << '(';
			PrintBinTree(r->lchild, out);
			if (r->rchild){
				out << ",";
			}
			PrintBinTree(r->rchild, out);
			out << ')';
		}
	}
}
//1. 有左右孩子
//2. 只有左孩子
//3. 只有右孩子
template <typename T>
void BinaryTree<T>::Output(BinTreeNode<T> *r, string str, ostream &out)
{
	if ( r == NULL )
		return ;

	out << str << r->data;
	if ( r->lchild )
	{
		out << "─┐" << endl;
		if ( r->rchild )
			Output(r->lchild, str + "│　", out);
		else
			Output(r->lchild, str + "  　", out);
	}

	if ( r->rchild )
	{
		out << endl << str << "└─┐" << endl;
		Output(r->rchild, str+"　　", out);
	}
}

template <typename T>
void BinaryTree<T>::PreOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t))
{
	if ( r == NULL )
		return ;

	visit( r );
	PreOrder_Recursion( r->lchild, visit );
	PreOrder_Recursion( r->rchild, visit );
}

template <typename T>
void BinaryTree<T>::InOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t))
{
	if ( r == NULL )
		return ;

	InOrder_Recursion( r->lchild, visit );
	visit( r );
	InOrder_Recursion( r->rchild, visit );
}

template <typename T>
void BinaryTree<T>::PostOrder_Recursion(BinTreeNode<T> *r, void (*visit)(BinTreeNode<T> *t))
{
	if ( r == NULL )
		return ;

	PostOrder_Recursion( r->lchild, visit );
	PostOrder_Recursion( r->rchild, visit );
	visit( r );
}

template <typename T>
void BinaryTree<T>::LevelOrder(void (*visit)(BinTreeNode<T> *t))
{
	if ( root == NULL )
		return ;

	queue<BinTreeNode<T> *> Q;
	Q.push( root );
	while ( !Q.empty() )
	{
		BinTreeNode<T> *p = Q.front();
		Q.pop();
		visit( p );

		if ( p->lchild )
			Q.push( p->lchild );
		if ( p->rchild )
			Q.push( p->rchild );
	}
}

template <typename T>
void BinaryTree<T>::PreOrder_NonRe(void (*visit)(BinTreeNode<T> *t))
{
	if ( root == NULL )
		return ;

	stack<BinTreeNode<T> * > S;
	S.push( root );
	while ( !S.empty() )
	{
		BinTreeNode<T> *p = S.top();
		S.pop();
		visit( p );

		if ( p->rchild )
			S.push( p->rchild );
		if ( p->lchild )
			S.push( p->lchild );
	}
	cout << endl;
}

template <typename T>
void BinaryTree<T>::InOrder_NonRe(void (*visit)(BinTreeNode<T> *t))
{
	stack<BinTreeNode<T> * > S;
	BinTreeNode<T> *p = root;

	while ( p || !S.empty() )
	{
		while ( p )
		{
			S.push( p );
			p = p->lchild;
		}

		if ( !S.empty() )
		{
			p = S.top();
			S.pop();
			visit(p);
			p = p->rchild;
		}
	}
	cout << endl;
}

template <typename T>
struct stkNode
{
	BinTreeNode<T> *ptr;
	enum { START, LEFT, RIGHT } tag;

	stkNode(BinTreeNode<T> *p = NULL) : ptr( p ), tag( START ) {}
};

template <typename T>
void BinaryTree<T>::PostOrder_NonRe(void (*visit)(BinTreeNode<T> *t))
{
	if ( root == NULL )
		return ;

	stack<stkNode<T> > S;
	S.push( stkNode<T>( root ) );

	while ( !S.empty() )
	{
		stkNode<T> &top = S.top();
		switch ( top.tag )
		{
		case stkNode<T>::START:
			if ( top.ptr->lchild )
				S.push( stkNode<T>(top.ptr->lchild) );
			top.tag = stkNode<T>::LEFT;
			break ;
		case stkNode<T>::LEFT:
			if ( top.ptr->rchild )
				S.push( stkNode<T>(top.ptr->rchild) );
			top.tag = stkNode<T>::RIGHT;
			break ;
		case stkNode<T>::RIGHT:
			visit( top.ptr );
			S.pop();
			break;
		}
	}
	cout << endl;
}
#endif
