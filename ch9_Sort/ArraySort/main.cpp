#include "ArraySort.h"
#include <fstream>
#include <cassert>
#include <string>
using namespace std;

template <typename T>
void testSort( void (* fun)(T *array, int n) )
{
	ifstream fin("data.txt");
	assert( fin );

	int size = 0;
	fin >> size;
	int *array = new int[size];
	assert( array );
	for ( int i = 0; i < size; i++ )
		fin >> array[i];
	
	fun(array, size);
	
	for ( i = 0; i < size; i++ )
		cout << array[i] << ends;
	cout << endl;

	fin.close();
	delete []array;
}

void FindNth(int pos)
{
	ifstream fin("data.txt");
	assert( fin );

	int size = 0;
	fin >> size;
	int *array = new int[size];
	assert( array );
	for ( int i = 0; i < size; i++ )
		fin >> array[i];
	
	FindNth<int>(array, size, pos);

	fin.close();
	delete []array;
}

int main()
{
	cout << "#1. Test InsertSort: ";
	testSort<int>( InsertSort<int> );
	cout << "#2. Test ShellSort: ";
	testSort<int>( ShellSort<int> );

	cout << "#3. Test BoubbleSort: ";
	testSort<int>( BoubbleSort<int> );
	cout << "#3.1. Test BidBoubbleSort: ";
	testSort<int>( BidBoubbleSort<int> );
	cout << "#4. Test QuickSort: ";
	testSort<int>( QuickSort<int> );
	FindNth( 5 );
	FindNth( 10 );

	cout << "#5. Test SelectSort: ";
	testSort<int>( SelectSort<int> );

	cout << "#6. Test HeapSort: ";
	testSort<int>( HeapSort<int> );

	cout << "#7. Test MergeSort: ";
	testSort<int>( MergeSort<int> );
	cout << "#8. Test RadixSort: ";
	testSort<int>( RadixSort<int> );
	cout << "#9. Test CountSort: ";
	testSort<int>( CountSort<int> );
	return 0;
}
