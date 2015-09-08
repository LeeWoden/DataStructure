#include "StaticList.h"
#include <iostream>
using namespace std;

int main(){
	StaticList<int> list(10);
	list.Append(1);
	list.Append(2);
	list.Append(3);
	list.Append(4);
	list.Append(5);
	list.Insert(1, 0);
	list.Insert(7, 6);

	// Print the list
	list.output();
	list.output(1);

	cout << "search 0: " << list.Search(0) << endl;
	cout << "search 6: " << list.Search(6) << endl;
	cout << "search 5: " << list.Search(5) << endl;
	cout << "search 2: " << list.Search(2) << endl;
	cout << endl;

	int x;
	if (list.Remove(1, x) && list.Remove(6, x)){
		cout << "Remove the 1th and 6th data:\n" << list;
		list.output();
		list.output(1);
	}

	list.Append(11);
	cout << "After Insert 11 in the rear:\n" << list;
	list.output();
	list.output(1);
	return 0;
}