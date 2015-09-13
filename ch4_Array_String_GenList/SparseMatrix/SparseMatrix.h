#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

template <typename T>
struct Triple
{
	int row;
	int col;
	T value;

	Triple(int r = -1, int c = -1, T v = 0) : row(r), col(c), value(v) {}
};

template <typename T>
class SparseMatrix
{
	public:
		SparseMatrix(int row, int col, int max);
		SparseMatrix(SparseMatrix<T> &x);
		~SparseMatrix() { delete []smArray; }
		SparseMatrix<T> & operator = ( SparseMatrix<T> &M );

		SparseMatrix<T> Transpose();
		SparseMatrix<T> FastTranspose();
		SparseMatrix<T> Add(SparseMatrix<T> &b);
		SparseMatrix<T> Multiply(SparseMatrix<T> &b);

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
				in >> M.smArray[i].row >> M.smArray[i].col>> M.smArray[i].value;
			}
			return in;
		}

	private:
		Triple *smArray;
		int maxTerms;
		int Rows, Cols, Terms;
};

#endif