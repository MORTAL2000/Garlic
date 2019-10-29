#pragma once

#include <cinttypes>
#include <array>
#include <type_traits>

namespace clv::mth{
	using size_type = std::uint32_t;

	template<size_type R, size_type C, typename T>
	struct Matrix{
		static_assert(std::is_arithmetic_v<T>, "Type is not arithmetic!");

		//VARIABLES
	private:
		std::array<std::array<T, C>, R> mat;

		//FUNCTIONS
	public:
		Matrix();

		T* ptr();

		constexpr auto& operator[](size_type index) noexcept;
		constexpr const auto& operator[](size_type index) const noexcept;
	};

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr Matrix<aR, aC, T> operator+(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept;

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr Matrix<aR, aC, T> operator-(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept;

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr Matrix<aR, bC, T> operator*(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept;

	using Matrix2i = Matrix<2, 2, std::int32_t>;
	using Matrix3i = Matrix<3, 3, std::int32_t>;
	using Matrix4i = Matrix<4, 4, std::int32_t>;

	using Matrix2f = Matrix<2, 2, float>;
	using Matrix3f = Matrix<3, 3, float>;
	using Matrix4f = Matrix<4, 4, float>;

	using Matrix2d = Matrix<2, 2, double>;
	using Matrix3d = Matrix<3, 3, double>;
	using Matrix4d = Matrix<4, 4, double>;
}

#include "Matrix.inl"