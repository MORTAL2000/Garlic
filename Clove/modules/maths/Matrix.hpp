#pragma once

#include <cinttypes>
#include <array>

//TODO: Wrap in namespace
//TODO: inl

template<std::uint32_t R, std::uint32_t C, typename T>
struct Matrix{
	//VARIABLES
private:
	std::array<std::array<T, C>, R> mat;

	//FUNCTIONS
public:
	

	auto& operator[](std::uint32_t index){
		return mat[index];
	}
};

template<std::uint32_t R, std::uint32_t C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs){
	//loop through lhs row and mult by rhs col
	
	Matrix<R, C, T> result;

	for(size_t row = 0; row < R; ++row){
		for(size_t col = 0; col < C; ++col){
			//result[0][0] = lhs[i][j] * rhs[j][i];

			//imagine 2 x 2 

			result[0][0] = lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1];
			result[1][0] = lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1];
			result[0][1] = lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1];
			result[1][1] = lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1];
		}
	}

	return result;
}

/*
 1  2     2  3
 3  4  x  4  5

 1 * 2 + 2 * 4  1 * 3 + 2 * 5
 3 * 2 + 4 * 4  3 * 3 + 4 * 5
 */