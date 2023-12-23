#include "Test.h"
#include <iostream>
#include <chrono>
#include <thread>

#define MaxDim 100

void main() {
	
	for (size_t dimention = 2; dimention < MaxDim; dimention++) {

		double dynamic_time, coord_time, flat_time;


/*-------------------------------------------------------------Dynamic Matrix Test-------------------------------------------------------------------*/

		TDynamicMatrix<int> dynamicMatrixA = RandomDynamicMatrix<int>(dimention);
		//std::this_thread::sleep_for(10ms);													//sleep for randomizing (and optimization ofk :) )
		TDynamicMatrix<int> dynamicMatrixB = RandomDynamicMatrix<int>(dimention);

		//std::cout << dynamicMatrixA << std::endl;
		//std::cout << dynamicMatrixB << std::endl;

		dynamic_time = DynamicMatrixMultiply<int>(dynamicMatrixA, dynamicMatrixB);
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/






/*---------------------------------------------------------------Coord Matrix Test---------------------------------------------------------------------*/
		TCoordMatrix<int> cooMatrixA(dynamicMatrixA);
		TCoordMatrix<int> cooMatrixB(dynamicMatrixB);

		coord_time = CoordMatrixMultiply<int>(cooMatrixA, cooMatrixB);
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------Flat Matrix Test---------------------------------------------------------------------*/
		TFlatMatrix<int> flatMatrixA(dimention);
		TFlatMatrix<int> flatMatrixB(dimention);

		for (size_t k = 0; k < dimention; k++) {
			for (size_t j = 0; j < dimention; j++) {
				flatMatrixA(k, j) = dynamicMatrixA[k][j];
				flatMatrixB(k, j) = dynamicMatrixB[k][j];
			}
		}

		flat_time = FlatMatrixMultiply<int>(flatMatrixA, flatMatrixB);
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/




		std::cout << "Matrix size: " << dimention << std::endl << std::endl << "DYNAMIC \t COORD \t\t FLAT" << std::endl << dynamic_time << "ms\t" << coord_time << "ms\t" << flat_time << "ms" << std::endl;
		std::cout << "-------------------------------------------" << std::endl;

	}
}