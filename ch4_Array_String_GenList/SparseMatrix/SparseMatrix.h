#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <cassert>
using namespace std;

const int ROW = 6, COL = 7, MAX = 9;

template <typename T>
struct Triple
{
	int row;
	int col;
	T value;

	Triple(int r = -1, int c = -1, T v = 0) : row(r), col(c), value(v) {}
	
	Triple<T> & operator = ( Triple<T> &t)
	{
		row = t.row;
		col = t.col;
		value = t.value;

		return *this;
	}
};

template <typename T>
class SparseMatrix
{
	public:
		SparseMatrix(int row = ROW, int col = COL, int max = MAX);
		SparseMatrix(SparseMatrix<T> &x);
		~SparseMatrix() { delete []smArray; }
		SparseMatrix<T> & operator = ( SparseMatrix<T> &M );

		SparseMatrix<T> Transpose();
		SparseMatrix<T> FastTranspose();
		SparseMatrix<T> Add(SparseMatrix<T> &x);
		SparseMatrix<T> Multiply(SparseMatrix<T> &x);

		int getRows() { return Rows; }
		int getCols() { return Cols; }

		friend ostream & operator << (ostream &out, SparseMatrix<T> &M)
		{
			out << "rows = " << M.Rows << endl;
			out << "cols = " << M.Cols << endl;
			out << "Nonzero terms = " << M.Terms << endl;
			for (int i = 0; i < M.Terms; i++)		
			{
				out << "M[" << M.smArray[i].row << "][" << M.smArray[i].col
					<< "]=" << M.smArray[i].value << endl;
			}
			return out;
		}

		friend istream & operator >> (istream &in, SparseMatrix<T> &M)
		{
			cout<<"please input the number of nonzero nodes :";
			cin>>M.Terms;
			cout<<endl;
			for (int i = 0; i < M.Terms; i++)
			{
				cout << "Enter row, column, and value of term:" << i+1 << endl;
				in >> M.smArray[i].row >> M.smArray[i].col >> M.smArray[i].value;
			}
			return in;
		}

	private:
		Triple<T> *smArray;
		int maxTerms;
		int Rows, Cols, Terms;
};

template <typename T>
SparseMatrix<T>::SparseMatrix(int row, int col, int max)
{
	Rows = row, Cols = col, maxTerms = max, Terms = 0;
	smArray = new Triple<T>[ maxTerms ];
	assert( smArray );
}

template <typename T>
SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& x)
{
	Rows = x.Rows, Cols = x.Cols, maxTerms = x.maxTerms, Terms = x.Terms;
	smArray = new Triple<T>[ maxTerms ];
	assert( smArray );
	for ( int i = 0; i < Terms; i++ )
		smArray[i] = x.smArray[i];
}

template <typename T>
SparseMatrix<T> & SparseMatrix<T>::operator = ( SparseMatrix<T> &x)
{
	this->maxTerms = x.maxTerms;
	this->Terms = x.Terms;
	this->Rows = x.Rows;
	this->Cols = x.Cols;

	delete []smArray;
	smArray = new Triple<T>[maxTerms];
	assert( smArray );

	for ( int i = 0; i < Terms; i++ )
		smArray[i] = x.smArray[i];

	return *this;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::Transpose()
{
	SparseMatrix<T> trans(this->Cols, this->Rows, this->maxTerms );
	for ( int col = 0; col < Cols; col++ )
	{
		for ( int term = 0; term < Terms; term++ )
		{
			if ( smArray[term].col == col )
			{
				trans.smArray[trans.Terms].row = col;
				trans.smArray[trans.Terms].col = smArray[term].row;
				trans.smArray[trans.Terms++].value = smArray[term].value;
			}
		}
	}

	return trans;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::FastTranspose()
{
	int *colSize = new int[Cols]; //转置前；列的大小
	int *rowStart = new int[Cols]; //转职后；行的起始

	for ( int i = 0; i < Cols; i++ ) //初始化
		colSize[i] = 0;

	for ( i = 0; i < Terms; i++ ) //统计
		colSize[smArray[i].col]++;

	rowStart[0] = 0;
	for ( i = 1; i < Terms; i++ ) //开始
		rowStart[i] = rowStart[i - 1] + colSize[i - 1];

	SparseMatrix<T> result(Cols, Rows, maxTerms);
	for ( i = 0; i < Terms; i++ )
	{
		int &pos = rowStart[ smArray[i].col ];
		result.smArray[pos].row =  smArray[i].col;
		result.smArray[pos].col =  smArray[i].row;
		result.smArray[pos].value =  smArray[i].value;
		pos++;
	}
	result.Terms = Terms;

	return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T> &x)
{
	assert( Rows == x.Rows || Cols == x.Cols );
	SparseMatrix<T> result(Rows, Cols, Terms + x.Terms);
	
	int i = 0, j = 0;
	while ( i < this->Terms && j < x.Terms )
	{
		int index_A = Cols * smArray[i].row  + smArray[i].col;
		int index_B = Cols * x.smArray[j].row + x.smArray[j].col;
		
		if ( index_A < index_B )
			result.smArray[result.Terms++] = smArray[i++];
		else if ( index_A > index_B )
			result.smArray[result.Terms++] = x.smArray[j++];
		else
		{
			result.smArray[result.Terms] = smArray[i];
			result.smArray[result.Terms++].value 
				= smArray[i++].value + x.smArray[j++].value;
		}
	}

	for ( ; i < Terms; i++ )
		result.smArray[result.Terms++] = smArray[i];

	for ( ; j < x.Terms; j++ )
		result.smArray[result.Terms++] = x.smArray[j];

	return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::Multiply(SparseMatrix<T> &x)
{
	assert( this->Cols == x.Rows );

	int *rowSize = new int[x.Rows]; //右操作数的行大小
	int *rowStart = new int[x.Rows + 1];//右操作数的行开始；增加一行避免数组越界
	T *temp = new T[x.Cols];

	for ( int i = 0; i < x.Rows; i++ )
		rowSize[i] = 0;

	for ( i = 0; i < x.Terms; i++ )
		rowSize[ x.smArray[i].row ]++;

	rowStart[0] = 0;
	for ( i = 1; i < x.Rows + 1; i++ )
		rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

	
	int current = 0;
	SparseMatrix<T> result(Rows, x.Cols, Rows * x.Cols/2);
	while ( current < Terms )
	{
		for ( int i = 0; i < x.Cols; i++ )
			temp[i] = 0;
		
		int leftRow = smArray[current].row;
		while ( current < Terms && smArray[current].row == leftRow )
		{
			int leftCol = smArray[current].col;
			for ( i = rowStart[leftCol]; i < rowStart[leftCol + 1]; i++ )
			{
				int rightCol = x.smArray[i].col;
				temp[rightCol] += x.smArray[i].value * smArray[current].value;
			}
			current++;
		}

		for ( i = 0; i < x.Cols; i++ )
		{
			if ( temp[i] == 0 )
				break; 
			
			result.smArray[result.Terms].row = leftRow;
			result.smArray[result.Terms].col = i;
			result.smArray[result.Terms++].value = temp[i];
		}
	}

	return result;
} 

#endif