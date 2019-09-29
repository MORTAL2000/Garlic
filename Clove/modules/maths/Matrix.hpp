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
	Matrix(){
		for(auto&& outer : mat){
			for(auto&& inner : outer){
				inner = 0;
			}
		}
	}

	auto& operator[](std::uint32_t index){
		return mat[index];
	}
	const auto& operator[](std::uint32_t index) const{
		return mat[index];
	}
};

template<std::uint32_t a, std::uint32_t b>
struct sameValue{
	static constexpr bool value = a == b;
};

template<std::uint32_t aR, std::uint32_t aC, std::uint32_t bR, std::uint32_t bC, typename T,
	std::enable_if_t<sameValue<aC, bR>::value, int> = 0, std::enable_if_t<sameValue<aR, bC>::value, int> = 0>
constexpr auto operator*(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs){
	constexpr auto minLen = std::min(aR, aC);
	Matrix<minLen, minLen, T> result;

	for(std::size_t row = 0; row < minLen; ++row){
		for(std::size_t col = 0; col < minLen; ++col){
			for(std::size_t i = 0, j = 0; i < aC && j < bR; ++i, ++j){
				result[row][col] += lhs[row][i] * rhs[j][col];
			}
		}
	}
	return result;
}