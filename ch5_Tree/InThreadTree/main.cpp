#include "InThreadTree.h"
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	int *array;
	int num = 0;
	ifstream fin("data.txt");
	fin >> num;
	assert(num > 0);
	array = new int[num];
	for ( int i = 0; i < num; i++ )
		fin >> array[i];
	fin.close();

    int end = 0;
	InThreadTree<int> tree(array, num, end);

	cout <<"+-------------------------------------------------+" << endl;
	cout << "#1 Test the InOrder funcion : " << endl;
	tree.InOrder();	

	cout <<"+-------------------------------------------------+" << endl;
	cout << "#2 Test the Search function : " << endl;
	cout<<"Please input a char to search : "<<endl;
	int ch;
	cin >> ch;
	ThrTreeNode<int> *p = tree.Find(ch);
	if( p == NULL )
		cout << '!' << endl;
	else
		cout << p << ':' << p->data << endl;

	cout << "search the prev node in inorder sequence according to the selected root" << endl;
	ThrTreeNode<int> *tmp = tree.GetPrev(p);
	if ( tmp )
		cout << tmp->data << endl;
	else
		cout << "NULL" << endl;

	cout << "search the next node in inorder sequence according to the selected root" << endl;
	tmp = tree.GetNext(p);
	if ( tmp )
		cout << tmp->data << endl;
	else
		cout << "NULL" << endl;

	cout << "search the next node in inorder sequence according to the selected root" << endl;
	tmp = tree.GetParent(p);
	if ( tmp )
		cout << tmp->data << endl;
	else
		cout << "NULL" << endl;
	return 0;
}
