#include <gtest.h>
#include "telementsvector.h"

TEST(TElementsVector, can_init_by_TDynamicMatrix)
{
	TDynamicMatrix<int> matrix(10);
	matrix[0][0] = 10;
	ASSERT_NO_THROW(TElementsVector<int> matrix2(matrix));
}
TEST(TElementsVector, can_set_elment)
{
	TElementsVector<int> matrix(10);
	ASSERT_NO_THROW(matrix.at(0, 0) = 0);
}
TEST(TElementsVector, is_established_elments_correct)
{
	TElementsVector<int> matrix(10);
	matrix.at(3, 2) = 1;
	matrix.at(0, 0) = 2;
	matrix.at(2, 5) = 3;
	matrix.at(0, 0) = 10;
	ASSERT_EQ(matrix.at(3, 2), 1);
	ASSERT_EQ(matrix.at(0, 0), 10);
	ASSERT_EQ(matrix.at(2, 5), 3);
}
TEST(TElementsVector, can_multiple_vector_with_matrix)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) % 2;
		}
	}
	TElementsVector<int> coord(matrix);
	//std::cout << std::endl << matrix << std::endl;
	//std::cout << std::endl << coord << std::endl;
	//std::cout << std::endl << vector << std::endl;
	//std::cout << coord * vector << std::endl;
	ASSERT_NO_THROW(TElementsVector<int>(matrix) * vector);
}
TEST(TElementsVector, is_multiplication_vector_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	/*std::cout << std::endl << matrix << std::endl;
	std::cout << matrix * vector << std::endl;*/
	ASSERT_EQ(matrix * vector, TElementsVector<int>(matrix) * vector);
}
TEST(TElementsVector, is_multiplication_matrix_with_scalar_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) % 2;
		}
	}
	/*std::cout << std::endl << matrix << std::endl;
	std::cout << matrix * vector << std::endl;*/
	TElementsVector<int> result = matrix * 8;
	TElementsVector<int> list_result(matrix);
	list_result = list_result * 8;
	//std::cout << (list_result == result);
	ASSERT_EQ(list_result, result);
}
TEST(TElementsVector, can_sum_matrix_with_matrix)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	TElementsVector<int> list(matrix);
	/*std::cout << std::endl << matrix << std::endl;
	std::cout << matrix * vector << std::endl;*/
	ASSERT_NO_THROW(list + list);
}
TEST(TElementsVector, is_sum_matrix_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j) * i % 2;
		}
	}
	TElementsVector<int> list(matrix);
	list = list + list;
	matrix = matrix + matrix;
	TElementsVector<int> result(matrix);
	//std::cout << std::endl << matrix << std::endl << std::endl;
	//std::cout << TDynamicMatrix<int>(list) << std::endl << std::endl;
	ASSERT_EQ(list, result);
}
TEST(TElementsVector, is_multiple_matrix_with_matrix_correct)
{
	TDynamicVector<int> vector(3);
	for (size_t i = 0; i < 3; i++)
	{
		vector[i] = i;
	}
	//std::cout << vector << std::endl;
	TDynamicMatrix<int> matrix(3);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			matrix[i][j] = (3 * i + j);
		}
	}
	TElementsVector<int> list(matrix);
	list = list * list;
	matrix = matrix * matrix;
	TElementsVector<int> result(matrix);
	//std::cout << std::endl << "result" << std::endl << matrix << std::endl << std::endl;
	//std::cout << TDynamicMatrix<int>(list) << std::endl << std::endl;
	ASSERT_EQ(list, result);
}