#pragma once
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Matrix
{
private:
	int rows;
	int columns;
	T* matrix;

public:
	Matrix(int op_rows, int op_cols);					// constructor by rows and columns
	Matrix(int op_size);								// constructor for square matrix
	Matrix(const Matrix& op_matrix);					// copy constructor
	Matrix(int op_rows, int op_cols, T arr[]);			// constructor from array
	~Matrix();
	Matrix operator+(const Matrix& op_matrix);			// matrix addition
	Matrix operator-(const Matrix& op_matrix);			// matrix substraction
	Matrix operator*(const Matrix& op_matrix);			// matrix by matrix multiplication (vector included)
	Matrix operator*(double number);					// matrix by a number multiplication
	T scalar_product(const Matrix &op_matrix);			// scalar product
	Matrix transpose();									// matrix transpose
	Matrix minor_matrix(int op_rows, int op_cols);		// minor matrix
	T minor(int op_rows, int op_cols);					// matrix minor
	T det_helper(int op_rows, int op_cols);
	T determinant();									// determinant
	void operator/=(const T& value);					// matrix division by a number
	Matrix inverse();									// matrix inverse
	Matrix from_row(int op_row);						// vector from row
	Matrix from_column(int op_col);						// vector from colmun

	friend istream& operator>> <> (istream& stream, Matrix& op_matrix);				// overloaded input operator (input to matrix)
	friend ostream& operator<< <> (ostream& stream, const Matrix& op_matrix);		// overloaded output operator (print matrix to the output)

	friend ifstream& operator>> <> (ifstream& f_stream, Matrix& op_matrix);			// overloaded input operator from file (load matrix from file)
	friend ofstream& operator<< <> (ofstream& f_stream, const Matrix& op_matrix);	// overloaded output operator to file (load matrix to file)
};

// constructor by rows and columns
template <typename T>
Matrix<T>::Matrix(int op_rows, int op_cols)
{
	rows = op_rows;
	columns = op_cols;

	matrix = new T[rows * columns];
	//cout << "Matrix [" << rows << "][" << columns << "] created." << endl;
}

// constructor for square matrix
template <typename T>
Matrix<T>::Matrix(int op_size)
{
	rows = op_size;
	columns = op_size;

	matrix = new T[rows * columns];
	//cout << "Matrix [" << rows << "][" << columns << "] created." << endl;
}

// copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& op_matrix)
{
	rows = op_matrix.rows;
	columns = op_matrix.columns;

	matrix = new T[rows * columns];

	for (int i = 0; i < rows * columns; ++i)
	{
		matrix[i] = op_matrix.matrix[i];
	}
	//cout << "Matrix [" << rows << "][" << columns << "] created." << endl;
}

// constructor from an array
template <typename T>
Matrix<T>::Matrix(int op_rows, int op_cols, T arr[])
{
	rows = op_rows;
	columns = op_cols;

	matrix = new T[rows * columns];

	for (int i = 0; i < rows * columns; ++i)
	{
		matrix[i] = arr[i];
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	delete[] matrix;
	//cout << "Matrix destroyed." << endl;
};

// matrix addition
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& op_matrix)
{
	if (rows == op_matrix.rows && columns == op_matrix.columns)
	{
		Matrix result_add(rows, columns);
		for (int i = 0; i < rows * columns; ++i)
		{
			result_add.matrix[i] = matrix[i] + op_matrix.matrix[i];
		}
		cout << "Add operation succeeded." << endl;

		return result_add;
	}
	else
	{
		cout << "Error: add operation failed. Matrices have different sizes." << endl;
		return -1;
	}
}

// matrix substraction
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& op_matrix)
{
	if (rows == op_matrix.rows && columns == op_matrix.columns)
	{
		Matrix result_sub(rows, columns);
		for (int i = 0; i < rows * columns; ++i)
		{
			result_sub.matrix[i] = matrix[i] - op_matrix.matrix[i];
		}
		cout << "Substract operation succeeded." << endl;
		return result_sub;
	}
	else
	{
		cout << "Error: substract operation failed. Matrices have different sizes." << endl;
		return -1;
	}
}

// matrix by matrix multiplication (vector included)
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &op_matrix)
{
	if (columns == op_matrix.rows)
	{
		Matrix result_mul(rows, op_matrix.columns);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < op_matrix.columns; ++j)
			{
				result_mul.matrix[i * result_mul.columns + j] = 0;
				for (int k = 0; k < columns; ++k)
				{
					result_mul.matrix[i * result_mul.columns + j] += matrix[i * columns + k] * op_matrix.matrix[k * op_matrix.columns + j];
				}
			}
		}
		cout << "Multiply operation succeeded." << endl;
		return result_mul;
	}
	else
	{
		cout << "Error: multiply operation failed. Matrices have incorrect sizes.";
		return -1;
	}
}

// matrix multiplication by a number 
template <typename T>
Matrix<T> Matrix<T>::operator*(double number)
{
	Matrix result_mul_bn(rows, columns);
	for (int i = 0; i < rows * columns; ++i)
	{
		result_mul_bn.matrix[i] = matrix[i] * number;
	}
	cout << "Multiplication by a number " << number << " succeeded." << endl;
	return result_mul_bn;
}

// scalar product
template <typename T>
T Matrix<T>::scalar_product(const Matrix &op_matrix)
{
	T product = 0;
	for (int i = 0; i < rows; ++i)
	{
		product = product + matrix[i] * op_matrix.matrix[i];
	}
	cout << "Scalar product: " << product << endl;
	return product;
}

// matrix transpose
template <typename T>
Matrix<T> Matrix<T>::transpose()
{
	Matrix result_tr(columns, rows);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result_tr.matrix[j * rows + i] = matrix[i * columns + j];
		}
	}
	cout << "Transpose operation succeeded." << endl;
	return result_tr;
}

template <typename T>
Matrix<T> Matrix<T>::minor_matrix(int op_rows, int op_cols)
{
	if (op_rows <= rows && op_cols <= columns)
	{
		Matrix result_mm(rows - 1, columns - 1);

		int ii = 0;
		int jj = 0;

		for (int i = 0; i < rows; ++i)
		{
			if (i == op_rows - 1)
			{
				ii--;
			}

			for (int j = 0; j < columns; ++j)
			{
				if (j == op_cols - 1)
				{
					jj--;
				}

				if (i != op_rows - 1 && j != op_cols - 1)
				{
					result_mm.matrix[ii * (columns - 1) + jj] = matrix[i * columns + j];
				}

				jj++;
			}

			jj = 0;
			ii++;
		}
		return result_mm;
	}
	cout << "Error: cannot compute minor matrix. Incorrect matrix size.";
}

template <typename T>
T Matrix<T>::minor(int op_rows, int op_cols)
{
	if (rows == columns && op_rows <= rows && op_cols <= columns)
	{
		return this->minor_matrix(op_rows, op_cols).determinant();
	}
	cout << "Error: cannot compute minor. Incorrect matrix size.";
}

template <typename T>
T Matrix<T>::det_helper(int op_rows, int op_cols)
{
	if (rows == columns && op_rows <= rows && op_cols <= columns)
	{
		return (((op_rows + op_cols) % 2 == 0) ? 1 : -1) * this->minor(op_rows, op_cols);
	}
}

template <typename T>
T Matrix<T>::determinant()
{
	if (rows == columns)
	{
		if (rows == 1)
		{
			// cout << "Determinant: ";
			return matrix[0];
		}

		else if (rows == 2)
		{
			// cout << "Determinant: ";
			return matrix[0] * matrix[3] - matrix[1] * matrix[2];
		}

		else
		{
			T determinant = matrix[0] * det_helper(1, 1);

			for (int i = 2; i <= rows; ++i)
			{
				determinant += matrix[(i - 1) * columns] * det_helper(i, 1);
			}

			// cout << "Determinant: ";
			return determinant;
		}
	}
	cout << "Error: cannot compute determinant. Incorrect matrix size.";
}

template <typename T>
void Matrix<T>::operator/=(const T& value)
{
	for (int i = 0; i < rows * columns; ++i)
	{
		matrix[i] /= value;
	}
}

template <typename T>
Matrix<T> Matrix<T>::inverse()
{
	if (rows == columns)
	{
		T determinant = this->determinant();

		if (determinant != 0)
		{
			Matrix result_inv(rows);

			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					result_inv.matrix[i * columns + j] = this->det_helper(j + 1, i + 1);
				}
			}

			result_inv /= determinant;
			cout << "Inverse operation succeeded." << endl;
			return result_inv;
		}
	}
	else
	{
		cout << "Error: inverse operation failed. Incorrect matrix size.";
	}
}

// matrix from specified row
template <typename T>
Matrix<T> Matrix<T>::from_row(int op_row)
{
	if (op_row <= rows)
	{
		Matrix result_row(1, columns);
		int cI = 0;

		for (int i = 0; i < columns; ++i)
		{
			result_row.matrix[cI] = matrix[columns * (op_row - 1) + i];
			++cI;
		}
		cout << "Vector from row [" << op_row << "] created." << endl;
		return result_row;
	}
	else
	{
		cout << "Error: no such row. Incorrect row index.";
	}
}

// matrix from cpecified column
template <typename T>
Matrix<T> Matrix<T>::from_column(int op_col)
{
	if (op_col <= columns)
	{
		Matrix result_col(1, rows);
		int cI = 0;

		for (int i = 0; i < rows; ++i)
		{
			result_col.matrix[cI] = matrix[columns * i + (op_col - 1)];
			++cI;
		}
		cout << "Vector from column [" << op_col << "] created." << endl;
		return result_col;
	}
	else
	{
		cout << "Error: no such column. Incorrect column index.";
	}
}

template <typename T>
istream& operator>> (istream& stream, Matrix<T>& op_matrix)
{
	cout << "Enter [" << op_matrix.rows << "][" << op_matrix.columns << "] matrix:" << endl;
	for (int i = 0; i < op_matrix.rows * op_matrix.columns; ++i)
	{
		stream >> op_matrix.matrix[i];
	}
	return stream;
}

template <typename T>
ostream& operator<< <> (ostream& stream, const Matrix<T>& op_matrix)
{
	cout << "\nDisplaying [" << op_matrix.rows << "][" << op_matrix.columns << "] matrix:" << endl;
	for (int i = 0; i < op_matrix.rows; ++i)
	{
		stream << "|";
		for (int j = 0; j < op_matrix.columns; ++j)
		{
			stream << op_matrix.matrix[i * op_matrix.columns + j] << "\t";
		}
		stream << "|" << endl;
	}
	return stream;
}

template <typename T>
ifstream& operator>> (ifstream& f_stream, Matrix<T>& op_matrix)
{
	cout << "Reading matrix from file..." << endl;
	for (int i = 0; i < op_matrix.rows * op_matrix.columns; ++i)
	{
		f_stream >> op_matrix.matrix[i];
	}
	return f_stream;
}

template <typename T>
ofstream& operator<< <> (ofstream& f_stream, const Matrix<T>& op_matrix)
{
	cout << "Writing matrix to file..." << endl;
	for (int i = 0; i < op_matrix.rows; ++i)
	{
		for (int j = 0; j < op_matrix.columns; ++j)
		{
			f_stream << op_matrix.matrix[i * op_matrix.columns + j] << " ";
		}
		f_stream << endl;
	}
	return f_stream;
}



