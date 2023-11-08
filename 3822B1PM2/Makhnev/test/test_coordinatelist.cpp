#include <iostream>
#include "gtest.h"
#include "tcoordinatelist.h"
#include "tmatrix.h"


TEST(TCoordinateList, can_init_by_TDynamicMatrix)
{
	TDynamicMatrix<int> matrix(10);
	matrix[0][0] = 10;
	ASSERT_NO_THROW(TCoordinateList<int> matrix2(matrix));
}
TEST(TCoordinateList, can_set_elment)
{
	TCoordinateList<int> matrix(10);
	ASSERT_NO_THROW(matrix.set(1, 0, 0));
}
TEST(TCoordinateList, is_established_elments_correct)
{
	TCoordinateList<int> matrix(10);
	matrix.set(1, 3, 2);
	matrix.set(2, 0, 0);
	matrix.set(3, 2, 5);
	matrix.set(10, 0, 0);
	ASSERT_EQ(matrix.get(3, 2), 1);
	ASSERT_EQ(matrix.get(0, 0), 10);
	ASSERT_EQ(matrix.get(2, 5), 3);
}
TEST(TCoordinateList, can_multiple_vector_with_matrix)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) % 2;
		}
	}
	TCoordinateList<int> coord(matrix);
	ASSERT_NO_THROW(TCoordinateList<int>(matrix) * vector);
}
TEST(TCoordinateList, is_multiplication_vector_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) ;
		}
	}
	ASSERT_EQ(matrix * vector, TCoordinateList<int>(matrix) * vector);
}
TEST(TCoordinateList, is_multiplication_matrix_with_scalar_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) % 2;
		}
	}
	TCoordinateList<int> result = matrix * 8;
	TCoordinateList<int> list_result(matrix);
	list_result = list_result * 8;
	ASSERT_EQ(list_result, result);
}
TEST(TCoordinateList, can_sum_matrix_with_matrix)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	TCoordinateList<int> list (matrix);
	ASSERT_NO_THROW(list + list);
}
TEST(TCoordinateList, is_sum_matrix_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) * i%2;
		}
	}
	TCoordinateList<int> list(matrix);
	list = list + list;
	matrix = matrix + matrix;
	TCoordinateList<int> result(matrix);

	ASSERT_EQ(list, result);
}
TEST(TCoordinateList, is_multiple_matrix_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	TCoordinateList<int> list(matrix);
	list = list * list;
	matrix = matrix * matrix;
	TCoordinateList<int> result(matrix);
	ASSERT_EQ(list, result);
}
TEST(TCoordinateList, is_multiple_matrix_with_matrix_correct_contr)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 0;
	m1[0][1] = 7;
	m1[1][0] = 6;
	m1[1][1] = 2;
	TDynamicMatrix<int> m2(2);
	m2[0][0] = 5;
	m2[0][1] = 0;
	m2[1][0] = 9;
	m2[1][1] = 2;
	TCoordinateList<int> TCL1(m1);
	TCoordinateList<int> TCL2(m2);
	TCoordinateList<int> TCL3 = TCL1 * TCL2;
	TDynamicMatrix<int> result(TCL3);
	TDynamicMatrix<int> m3 = m1 * m2;
	ASSERT_EQ(m3, result);
}
TEST(TCoordinateList, can_transpose)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	TCoordinateList<int> list(matrix);
	list = list.transpose();

	ASSERT_NO_THROW(list.transpose());
}
TEST(TCoordinateList, can_sum_contr)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 9;
	m1[0][1] = 4;
	m1[1][0] = 9;
	m1[1][1] = 8;
	TDynamicMatrix<int> m2(2);
	m2[0][0] = 8;
	m2[0][1] = 1;
	m2[1][0] = 8;
	m2[1][1] = 6;
	TCoordinateList<int> TCL1(m1);
	TCoordinateList<int> TCL2(m2);
	TCoordinateList<int> TCL3 = TCL1 - TCL2;
	TDynamicMatrix<int> result(TCL3);
	TDynamicMatrix<int> m3 = m1 - m2;
	ASSERT_EQ(m3, result);
}
TEST(TCoordinateList, can_mul_contr2)
{
	TDynamicMatrix<int> m1(3);
	m1[1][1] = 9;
	TDynamicMatrix<int> m2(3);
	m2[1][1] = 8;
	TCoordinateList<int> TCL1(m1);
	TCoordinateList<int> TCL2(m2);
	TCoordinateList<int> TCL3 = TCL1 * TCL2;
	TDynamicMatrix<int> result(TCL3);
	TDynamicMatrix<int> m3 = m1 * m2;
	ASSERT_EQ(m3, result);
}
TEST(TCoordinateList, can_sum_contr2)
{
	TDynamicMatrix<int> m1(5);
	m1[0][0] = 9;
	TDynamicMatrix<int> m2(5);
	m2[2][4] = 56;
	TCoordinateList<int> TCL1(m1);
	TCoordinateList<int> TCL2(m2);
	TCoordinateList<int> TCL3 = TCL1 + TCL2;
	TDynamicMatrix<int> result(TCL3);
	TDynamicMatrix<int> m3 = m1 + m2;
	ASSERT_EQ(m3, result);
}