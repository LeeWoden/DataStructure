#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	int degree; //���ڵ�Ķ�
	TreeNode<T> *firstChild, *nextSibling; //�����ֵܷ���ʾ��

	TreeNode(T val, TreeNode<T> *child = NULL, TreeNode<T> *sibling = NULL )
		: data( val ), degree( 0 ), firstChild( child ), nextSibling( sibling ) {}
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

		void PreOrder(void (*visit)(TreeNode<T> *t)) { PreOrder(root, visit); } //����ǰ�� <=> ��������ǰ��
		void PostOrder(void (*visit)(TreeNode<T> *t)) { PostOrder(root, visit); } //���ĺ��� <=> ������������
//		void LevelOrder() const { LevelOrder(root, visit); }
		void IntendedText(ostream &out = cout){	//�����������ı���ʽ���	
			IntendedText(root, string(), out);//string()�ǹ��캯��
		}

		int Depth() const { return Depth(root); }
		int Size() const { return Size(root); }
		void Degree() const { return Degree(root); };
		int LeafSize() const { return LeafSize(root); };
		bool IsEmpty() const { return root == NULL; }
		vector<vector<T> > LeafPath()
		{
			vector<vector<T> > paths;
			vector<TreeNode<T> *> stack;
			LeafPath(root, stack, paths);
			return paths;
		}

		friend istream & operator >> (istream &in, Tree<T> &tree)
		{
			tree.CreateTree(tree.root, in);
			return in;
		}

		friend ostream & operator << (ostream &out, Tree<T> &tree)
		{
			tree.IntendedText(out);
			return out;
		}

	private:
		TreeNode<T> *root;
		T endTag;
		
		void CreateTree(TreeNode<T> *&r, istream &in = cin);
		void Destroy(TreeNode<T> *r);

		void PreOrder(TreeNode<T> *r, void (*visit)(TreeNode<T> *t));
		void PostOrder(TreeNode<T> *r, void (*visit)(TreeNode<T> *t));
		void LevelOrder(TreeNode<T> *r, void (*visit)(TreeNode<T> *t));
        void Output(TreeNode<T> *subTree, string str, ostream &out);
	    void IntendedText(TreeNode<T> *subTree, string str, ostream &out);

		int Depth(TreeNode<T> *r) const;
		int Size(TreeNode<T> *r) const;
		int LeafSize(TreeNode<T> *r) const;
		void Degree(TreeNode<T> *r) const;
		void LeafPath(TreeNode<T> *p, vector<TreeNode<T> *> &stack, vector<vector<T> > &paths);
		
};

template <typename T>
void Tree<T>::CreateTree(TreeNode<T> *&r, istream &in)
{
	T item;
	if ( in >> item )
	{
		if ( item != endTag )
		{
			r = new TreeNode<T>(item);
			assert(r);
			CreateTree(r->firstChild, in);
			CreateTree(r->nextSibling, in);
		}
	}
	else
		r = NULL;
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

template <typename T>
void Tree<T>::PreOrder(TreeNode<T> *r, void (*visit)(TreeNode<T> *t))
{
	if ( r == NULL )
		return ;

	visit( r );
	PreOrder( r->firstChild, visit );
	PreOrder( r->nextSibling, visit );
}

template <typename T>
void Tree<T>::PostOrder(TreeNode<T> *r, void (*visit)(TreeNode<T> *t))
{
	if ( r == NULL )
		return ;

	PostOrder( r->firstChild, visit );
	visit( r );
	PostOrder( r->nextSibling, visit );
}

template <typename T>
void Tree<T>::IntendedText(TreeNode<T> *subTree, string str, ostream &out)
{
	TreeNode<T> *p = subTree;
	while ( p )
	{   //�������
		out << str << p->data << endl;
		string temp = str + string("\t");//ע����ʽ���һ���������׼��
		if (p->firstChild){
			IntendedText(p->firstChild, temp, out);//��ȵݹ�
		}
		p = p->nextSibling;//���ѭ��
	}
}

template <typename T>
int Tree<T>::Size(TreeNode<T> *r) const
{
	if ( r == NULL )
		return 0;

	return 1 + Size(r->firstChild) + Size(r->nextSibling);
}

template <typename T>
int Tree<T>::LeafSize(TreeNode<T> *r) const
{
	//ɭ�ֵĽǶ�˼��
	//����Զ�������˼·����Ϊһ��Ҷ�ӽڵ㣬�ܷ���1�𣿵�Ȼ���ܣ���Ҫ�����������ֵܽڵ㣻��Ȼ��·��ͨ��
	if ( r == NULL )
		return 0;

	int count = 0;
	for ( TreeNode<T> *p = r->firstChild; p != NULL; p = p->nextSibling )
	{
		if ( p->firstChild == NULL )
			count++;
		else
			count += LeafSize( p );
	}
	return count;
}

template <typename T>
int Tree<T>::Depth(TreeNode<T> *r) const
{
	//ɭ��˼·
	if ( r == NULL )
		return 0;

	int maxDepth = 0, depth = 0;
	for ( TreeNode<T> *p = r->firstChild; p; p = p->nextSibling )
	{
		if ( p->firstChild == NULL )
			depth = 1;
		else
			depth = Depth( p );
		
		(maxDepth < depth) ? (maxDepth = depth) : (maxDepth = maxDepth);
	}
	return maxDepth + 1;
/*
    //������˼·
	if ( r == NULL )
		return 0;

	int firstChild = Depth( r->firstChild );
	int sibling = Depth( r->nextSibling );
	return ( firstChild + 1 > sibling ) ? ( firstChild + 1 ) : sibling;
*/
}

template <typename T>
void Tree<T>::Degree(TreeNode<T> *r) const
{
	if ( r == NULL )
		return ;

	r->degree = 0;
	for ( TreeNode<T> *p = r->firstChild; p != NULL; p = p->nextSibling )
	{
		r->degree++;
	}
	Degree( r->firstChild );
	Degree( r->nextSibling );
}

template <typename T>
void Tree<T>::LeafPath(TreeNode<T> *p, vector<TreeNode<T> *> &stack, vector<vector<T> > &paths)
{
	if ( p == NULL )
		return ;

	stack.push_back( p );
	//����Ҷ�ӽڵ㣬ֻҪ��ÿһ��ѡ��Ľڵ����·�����ɣ���Ȼ�Ǹ��ӶԵĸ��ڵ�
	if ( p->firstChild == NULL )
	{
		vector<T> path;
		for ( int i = 0; i < stack.size() - 1; i++ )
		{
			if ( stack[i]->firstChild == stack[i + 1] )
				path.push_back( stack[i]->data );
		}
		path.push_back( stack[i]->data );
		paths.push_back( path );
	}

	LeafPath(p->firstChild, stack, paths);
	LeafPath(p->nextSibling, stack, paths);
	stack.pop_back();
}

#endif