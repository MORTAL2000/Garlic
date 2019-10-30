#pragma once

#include <cinttypes>
#include <array>
#include <type_traits>

namespace clv::mth{
	using size_type = std::uint32_t;

	template<size_type R, size_type C, typename T>
	struct mat{
		static_assert(std::is_arithmetic_v<T>, "Type is not arithmetic!");

		//VARIABLES
	private:
		std::array<std::array<T, C>, R> data;

		//FUNCTIONS
	public:
		mat();

		T* ptr();

		constexpr auto& operator[](size_type index) noexcept;
		constexpr const auto& operator[](size_type index) const noexcept;
	};

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, aC, T> operator+(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept;

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, aC, T> operator-(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept;

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, bC, T> operator*(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept;

	using mat2i = mat<2, 2, std::int32_t>;
	using mat3i = mat<3, 3, std::int32_t>;
	using mat4i = mat<4, 4, std::int32_t>;

	using mat2f = mat<2, 2, float>;
	using mat3f = mat<3, 3, float>;
	using mat4f = mat<4, 4, float>;

	using mat2d = mat<2, 2, double>;
	using mat3d = mat<3, 3, double>;
	using mat4d = mat<4, 4, double>;
}

#include "Matrix.inl"