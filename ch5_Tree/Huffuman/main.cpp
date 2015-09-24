#include "Huffuman.h"
#include <iostream>
using namespace std;

int main()
{
	ifstream fin("data.txt");
	assert( fin );
	Huffuman<char> h;
	fin >> h;
	fin.close();

	for ( char tmp = 'a'; tmp < 'h'; tmp++ )
		h.Code( tmp );

	char data[] = "010101010100000011111110010101001";
	h.Decode(data, 33);

	return 0;
}