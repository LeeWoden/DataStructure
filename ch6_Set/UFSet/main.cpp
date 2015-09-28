#include "UFSet.h"
#include <iostream>
using namespace std;

int main(){
	int i;
	UFSet<int> ufs1(10);
	cout << "1. Test Union(r1, r2): ";
	for (i = 8; i >=0; i--)	{
		ufs1.Union(i, i+1);
	}
	cout << ufs1 << endl;

	UFSet<int> ufs2(10);
	cout << "2. Test WeightUnion(r1, r2): ";
	for (i = 8; i >=0; i--)	{
		ufs2.WeightUnion(i, i+1);
	}
	cout << ufs2 << endl;
	cout << "Tips: 1 and 2 have the same Union order but different result!\n" << endl;

	UFSet<int> ufs3(10);
	ufs3.Union(1,2);
	ufs3.Union(1,4);
	ufs3.Union(9,3);
	ufs3.Union(9,5);
	ufs3.Union(7,9);
	ufs3.Union(7,1);
	ufs3.Union(0,6);
	ufs3.Union(0,7);
	ufs3.Union(0,8);
	cout << "A new UFSet<int> for test: " << ufs3 << endl;

	cout << "3. Test Find(i): \n";
	for (i = 0; i < 10; i++){
		cout << "The root of Node " << i << " is: " << ufs3.Find(i) << endl;
	}
	cout << "\nAfter Find(i): " << ufs3 << endl;
	cout << "Tips: The UFSet<int> is not changed!\n" << endl;

	cout << "4. Test CollapsingFind(i): \n";
	for (i = 0; i < 10; i++){
		cout << "The root of Node " << i << " is: " << ufs3.CollapsingFind(i) << endl;
	}
	cout << "\nAfter CollapsingFind(i): " << ufs3 << endl;
	cout << "Tips: The UFSet<int> is changed!" << endl;

	cout << "Press enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
