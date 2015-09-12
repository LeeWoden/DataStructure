#include "GenList.h"
#include <fstream>
#include <string>
using namespace std;

int main(){
	ifstream fin1("data.txt");
	assert(fin1);
	char str[128];
	fin1 >> str;
	cout << "The genlist in the file is: \n" << str << endl;

	GenList<char> gl1;
	fin1.close();
	ifstream fin("data.txt");
	assert(fin);
	fin >> gl1;
	cout << "\nSome information about Genlist gl1:\n";
	cout << "\nThe data of GenList is:" << endl;
	cout << gl1 << endl;
	
	cout << "\nThe depth of the GenList is: " << gl1.Depth() << endl;
	cout << "The length of the GenList is: " << gl1.Length() << endl;


	//	GenList<char> gl2(gl1);//¸´ÖÆ
	GenList<char> gl2;
	gl2.Copy(gl1);
	cout << "\ngl2 is a copy of gl1:\n";
	cout << "The data of gl2 is: " << endl;
	cout << gl2 << endl;

	char rem;
	cout << "\nInput the data that you want to Remove: " << endl;
	cin >> rem;
	gl2.delValue(rem);
	cout << "The current GenList gl2 is: " << endl;
	cout << gl2<< endl;
	
	cout << "\nInput the data that you want to Remove: " << endl;
	cin >> rem;
	gl2.delValue(rem);
	cout << "The current GenList gl1 is: " << endl;
	cout << gl2<< endl;
	return 0;
}