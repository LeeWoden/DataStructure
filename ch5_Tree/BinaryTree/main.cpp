#include "BinaryTree.h"
#include <fstream>
#include <iomanip>
using namespace std;

void visit(BinTreeNode<int> *t)
{
	cout<<t->data<<"   ";
}

int main()
{
	ifstream fin("data.txt");
	assert(fin);
	int num = 0;
	BinaryTree<int> binTree(num);
	assert(fin >> binTree);
	fin.close();
	cout << "The binary tree is: \n" << binTree << endl;
	binTree.Output();
	ofstream fout("output.txt");
	assert(fout);
	binTree.Output(fout);
	fout.close();
	BinaryTree<int> binTree1(binTree);
	cout << "\nThe copy binary tree is: \n" << binTree1 << endl;
	binTree1.Output();

	cout << "\nThe preorder of the binary tree is(Recursion & Non):\n";
	binTree.PreOrder_Recursion(visit);
	binTree.PreOrder_NonRe(visit);
	cout << "\n\nThe inorder of the binary tree is(Recursion & Non):\n";
	binTree.InOrder_Recursion(visit);
	binTree.InOrder_NonRe(visit);
	cout << "\n\nThe postorder of the binary tree is(Recursion & Non):\n";
	binTree.PostOrder_Recursion(visit);
	binTree.PostOrder_NonRe(visit);
	cout << "\n\nThe levelOrder of the binary tree is:\n";
	binTree.LevelOrder(visit);
	cout << "\n\nThe height of the binary tree is:\n";
	cout<<binTree.Depth();
	cout << "\n\nThe Size of the binary tree is:\n";
	cout<<binTree.Size();
	cout << endl << endl;

	cout << "Create a complete Binary tree from an array:\n";
	cout << "Input the nodes num in the binary tree: ";
	assert(cin >> num);
	int *CBT = new int[num];
	cout << "\nThe data in the array is:\n";
	for (int i = 0; i < num; i++)
	{
		CBT[i] = i+1;
		cout << setw(4) << i+1;
	}
	cout << endl;
	BinaryTree<int> binTree2;
	binTree2.CreateCompBinTree(CBT, num);
	cout << "The binary tree is: \n" << binTree2 << endl;
	binTree2.Output();
	ofstream fout2("output2.txt");
	assert(fout2);
	binTree2.Output(fout2);
	fout2.close();
	cout << "\nThe preorder of the binary tree is:\n";
	binTree2.PreOrder_Recursion(visit);
	binTree2.PreOrder_NonRe(visit);
	cout << "\n\nThe inorder of the binary tree is:\n";
	binTree2.InOrder_Recursion(visit);
	binTree2.InOrder_NonRe(visit);
	cout << "\n\nThe postorder of the binary tree is:\n";
	binTree2.PostOrder_Recursion(visit);
	binTree2.PostOrder_NonRe(visit);
	cout << "\n\nThe levelOrder of the binary tree is:\n";
	binTree2.LevelOrder(visit);
	cout << endl << endl;
	delete []CBT;

	cout << "Press enter to exit!\n";
	cin.ignore(100,'\n');
	char ch;
	cin.get(ch);
	return 0;
}
