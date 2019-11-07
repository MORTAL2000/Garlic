#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

namespace clv::mth{
	template<typename T>
	constexpr mat<4, 4, T> translate(const mat<4, 4, T>& matrix, const vec<3, T>& vector) noexcept;

	template<typename T>
	constexpr mat<4, 4, T> rotate(const mat<4, 4, T>& matrix, T angle, const vec<3, T>& vector) noexcept;

	template<typename T>
	constexpr mat<4, 4, T> scale(const mat<4, 4, T>& matrix, const vec<3, T>& vector) noexcept;

	template<size_type R, size_type C, typename T>
	constexpr mat<R, C, T> inverse(const mat<R, C, T>& matrix) noexcept;

	template<size_type R, size_type C, typename T>
	constexpr mat<R, C, T> transpose(const mat<R, C, T>& matrix) noexcept;

	template<typename T>
	constexpr mat<4, 4, T> lookAt(const vec<3, T>& eye, const vec<3, T>& center, const vec<3, T>& up) noexcept;
}

#include "MatrixMath.inl"