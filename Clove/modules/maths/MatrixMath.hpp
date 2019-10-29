#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

namespace clv::mth{
	template<typename T>
	constexpr Matrix<4, 4, T> translate(const Matrix<4, 4, T>& matrix, const Vector<3, T>& vector) noexcept;

	template<typename T>
	constexpr Matrix<4, 4, T> rotate(const Matrix<4, 4, T>& matrix, T angle, const Vector<3, T>& vector) noexcept;

	template<typename T>
	constexpr Matrix<4, 4, T> scale(const Matrix<4, 4, T>& matrix, const Vector<3, T>& vextor) noexcept;

	template<size_type R, size_type C, typename T>
	constexpr Matrix<R, C, T> inverse(const Matrix<R, C, T>& matrix) noexcept;

	template<size_type R, size_type C, typename T>
	constexpr Matrix<R, C, T> transpose(const Matrix<R, C, T>& matrix) noexcept;

	template<typename T>
	constexpr Matrix<4, 4, T> lookAt(const Vector<3, T>& eye, const Vector<3, T>& center, const Vector<3, T>& up) noexcept;
}

#include "MatrixMath.inl"