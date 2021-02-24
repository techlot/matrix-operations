#include "Matrix.h"

using namespace std;

// functions prototypes
void test_addition();
void test_substraction();
void test_multiplication();
void test_scalar_product();
void test_transpose();
void test_inverse();
void test_create_from_row();
void test_create_from_col();


int main()
{
	test_addition();
	test_substraction();
	test_multiplication();
	test_scalar_product();
	test_transpose();
	test_inverse();
	test_create_from_row();
	test_create_from_col();
}


void test_addition()
{
	cout << "_____________________________________.::ADDITION" << endl;
	cout << "\n     [ EXAMPLE 1 ]\n" << endl;

	int a1[6] = { 3, 5,  8,
				-2, 10, 9 };

	Matrix<int> m1(2, 3, a1);

	int a2[6] = { 7, 5,  2,
				 2, 10, 1 };

	Matrix<int> m2(2, 3, a2);

	cout << m1 << m2 << endl;
	cout << m1 + m2 << endl;

	cout << "\n     [ EXAMPLE 2 ]\n" << endl;
	ifstream load_matrix_1("matrix_samples/sample1-23.txt");
	ifstream load_matrix_2("matrix_samples/sample2-23.txt");

	Matrix<double> m3(4);
	load_matrix_1 >> m3;

	Matrix<double> m4(4);
	load_matrix_2 >> m4;

	cout << m3 << m4 << endl;
	cout << m3 + m4 << endl;

	load_matrix_1.close();
	load_matrix_2.close();
}

void test_substraction()
{
	cout << "_____________________________________.::SUBSTRACTION" << endl;
	cout << "\n     [ EXAMPLE 1 ]\n" << endl;

	int a1[8] = { 10, 15,
				 5,  3,
				 8,  11,
				 12, 8 };

	Matrix<int> m1(4, 2, a1);

	int a2[8] = { -5, 10,
				 15, -8,
				 0,  -9,
				 4,  8 };

	Matrix<int> m2(4, 2, a2);

	cout << m1 << m2 << endl;
	cout << m1 - m2 << endl;

	cout << "\n     [ EXAMPLE 2 ]\n" << endl;
	ifstream load_matrix_1("matrix_samples/sample1-23.txt");
	ifstream load_matrix_2("matrix_samples/sample2-23.txt");

	Matrix<double> m3(4);
	load_matrix_1 >> m3;

	Matrix<double> m4(4);
	load_matrix_2 >> m4;

	cout << m3 << m4 << endl;
	cout << m3 - m4 << endl;

	load_matrix_1.close();
	load_matrix_2.close();
}

void test_multiplication()
{
	cout << "_____________________________________.::MULTIPLICATION" << endl;
	cout << "\n     [ EXAMPLE 1 ]\n" << endl;
	cout << "By vector:\n" << endl;

	ifstream load_matrix("matrix_samples/sample3-23.txt");

	Matrix<int> m1(2, 3);
	load_matrix >> m1;

	int a1[3] = { -1, 3, 2 };
	Matrix<int> m2(3, 1, a1);

	cout << m1 << m2 << endl;
	cout << m1 * m2 << endl;

	load_matrix.close();

	cout << "\n     [ EXAMPLE 2 ]\n" << endl;
	cout << "By matrix:\n" << endl;

	ifstream load_matrix_1("matrix_samples/sample4-23.txt");
	ifstream load_matrix_2("matrix_samples/sample5-32.txt");
	Matrix<int> m3(2, 3);
	Matrix<int> m4(3, 2);

	load_matrix_1 >> m3;
	load_matrix_2 >> m4;

	cout << m3 << m4 << endl;
	cout << m3 * m4 << endl;

	load_matrix_1.close();
	load_matrix_2.close();

	cout << "\n     [ EXAMPLE 3 ]\n" << endl;
	cout << "By a number:\n" << endl;


	ifstream load_matrix_3("matrix_samples/sample_int.txt");
	Matrix<int> m5(3, 6);

	load_matrix_3 >> m5;

	cout << m5 << endl;
	cout << m5 * 5 << endl;

	load_matrix_3.close();
}

void test_scalar_product()
{
	cout << "_____________________________________.::SCALAR PRODUCT" << endl;
	cout << "\n     [ EXAMPLE 1 ]\n" << endl;

	int a1[3] = { 1, -1, 4 };
	int a2[3] = { 2, 2, 0 };

	Matrix<int> m1(3, 1, a1);
	Matrix<int> m2(3, 1, a2);

	cout << m1 << m2 << endl;
	m1.scalar_product(m2);
}

void test_transpose()
{
	cout << "_____________________________________.::TRANSPOSE" << endl;
	cout << "\n     [ EXAMPLE 1 ]\n" << endl;

	int a1[8] = { 1, -1,
				  5, 6,
				  7, 1,
				  0, 5 };

	Matrix<int> m1(4, 2, a1);

	cout << m1 << endl;
	cout << m1.transpose() << endl;

	cout << "\n     [ EXAMPLE 2 ]" << endl;
	ifstream load_matrix("matrix_samples/sample_float.txt");
	Matrix<float> m3(3, 6);

	load_matrix >> m3;

	cout << m3 << endl;
	cout << m3.transpose() << endl;

	load_matrix.close();
}

void test_inverse()
{
	cout << "_____________________________________.::INVERSE" << endl;
	cout << "\n     [ EXAMPLE 1 ]" << endl;

	double a1[4] = {4, 7,
					2, 6 };

	Matrix<double> m1(2, 2, a1);

	cout << m1 << endl;
	cout << m1.inverse() << endl;

	cout << "\n     [ EXAMPLE 2 ]" << endl;

	double a2[4] = { 3,   3.5,
					3.2, 3.6 };

	Matrix<double> m2(2, 2, a2);

	cout << m2 << endl;
	cout << m2.inverse() << endl;
}

void test_create_from_row()
{
	cout << "_____________________________________.::FROM ROW" << endl;
	cout << "\n     [ EXAMPLE 1 ]" << endl;

	double a[10] = { 0.2, 1,
					-1,  2,
					8,  10,
					5.75,1,
					-6,  0 };

	Matrix<double> m(5, 2, a);
	cout << m << endl;

	Matrix<double> m0 = m.from_row(4);

	cout << m0 << endl;

	cout << "     [ EXAMPLE 2 ]\n" << endl;
	ifstream load_matrix("matrix_samples/sample_int.txt");
	Matrix<int> m1(3, 6);

	load_matrix >> m1;

	cout << m1 << endl;

	Matrix<int> m2 = m1.from_row(2);
	cout << m2 << endl;

	Matrix<int> m3 = m1.from_row(3);
	cout << m3 << endl;

	load_matrix.close();
}

void test_create_from_col()
{
	cout << "_____________________________________.::FROM COLUMN" << endl;
	cout << "\n     [ EXAMPLE 1 ]" << endl;

	double a[10] = { 0.2, 1,
					-1,  2,
					8,  10,
					5.75,1,
					-6,  0 };

	Matrix<double> m(5, 2, a);
	cout << m << endl;

	Matrix<double> m0 = m.from_column(1);
	cout << m0 << endl;

	Matrix<double> m1 = m.from_column(2);
	cout << m1 << endl;

	cout << "\n     [ EXAMPLE 2 ]\n" << endl;
	ifstream load_matrix("matrix_samples/sample_int.txt");
	Matrix<int> m2(3, 6);

	load_matrix >> m2;

	cout << m2 << endl;

	Matrix<int> m3 = m2.from_column(2);
	cout << m3 << endl;

	Matrix<int> m4 = m2.from_column(4);
	cout << m4 << endl;

	Matrix<int> m5 = m2.from_column(6);
	cout << m5 << endl;

	load_matrix.close();
}

