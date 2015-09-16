#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T> *firstChild, *nextSibling; //孩子兄弟法表示树

	TreeNode(T val, TreeNode<T> *child = NULL, TreeNode<T> *sibling = NULL )
		: data( val ), firstChild( child ), nextSibling( sibling ) {}
};

template <typename T>
class Tree
{
	public:
		Tree() 
			: root( NULL ) {}
		Tree(T end) 
			: root( NULL ), endTag( end ) {}
		~Tree() { Destroy(root); }

		void PreOrder() const { PreOrder(root); } //树的前序 <=> 二叉树的前序
		void PostOrder() const { InOrder(root); } //树的后序 <=> 二叉树的中序

		int Depth() const { return Depth(root); }
		int Size() const { return Size(root); }
		bool IsEmpty() const { return root == NULL; }
	private:
		TreeNode<T> *root;
		T endTag;
		
		void CreateTree(istream &in = cin, TreeNode<T> *&r);
		void Destroy(TreeNode<T> *r);
};

template <typename T>
void Tree<T>::CreateTree(istream &in, TreeNode<T> *&r)
{
	T item;
	if ( in >> item )
	{
		r = new TreeNode<T>(T);
		assert(r);
		CreateTree(in, r->firstChild);
		CreateTree(in, r->nextSibling);
	}
}


template <typename T>
void Tree<T>::Destroy(TreeNode<T> *r)
{
	if ( r == NULL )
		return ;

	Destroy(r->firstChild);
	Destroy(r->nextSibling);
	delete r;
	r = NULL;
}
#endif