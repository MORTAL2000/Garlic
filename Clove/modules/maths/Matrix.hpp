#pragma once

#include <cinttypes>
#include <array>
#include <type_traits>

//TODO: Wrap in namespace
//TODO: inl

template<std::uint32_t R, std::uint32_t C, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
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
constexpr Matrix<R, C, T> operator*(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs){
	Matrix<R, C, T> result;

	for(std::size_t row = 0; row < R; ++row){
		for(std::size_t col = 0; col < C; ++col){
			for(std::size_t i = 0, std::size_t j = 0; i < C && j < R; ++i, ++j){
				result[row][col] += lhs[row][i] * rhs[j][col];
			}
		}
	}

	return result;
}