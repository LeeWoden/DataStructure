#include "Tree.h"
#include <fstream>
#include <cassert>
#include <iomanip>
using namespace std;

void visit(TreeNode<int> * n){
	cout << setw(4) << n->data;
}

int main()
{
	Tree<int> tree(0);                   //ÊäÈë½áÊø·ûÎª0
	cout << "The Intended text of the tree is:\n";
	ifstream fin("data.txt");
	assert(fin);
	fin >> tree;
	fin.close();
	cout << tree;

	cout << "\nThe preorder of the tree is:\n";
	tree.PreOrder(visit);
	cout << "\nThe postorder of the tree is:\n";
	tree.PostOrder(visit);

	cout << "\npaths of the tree is:\n";
	vector<vector<int> > paths = tree.LeafPath();
	for ( int i = 0; i < paths.size(); i++ )
	{
		for ( int j = 0; j < paths[i].size(); j++ )
			cout << paths[i][j] << ends;
		cout << endl;
	}
	
	cout << "\nthe depth of the tree is:\n" << tree.Depth() << endl;

	cout << "\nthe size of the tree is:\n" << tree.Size() << endl;

	cout << "\nthe leaf's size is:\n" << tree.LeafSize() << endl;

	cout << "\n\nPress enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}