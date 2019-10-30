#pragma once

#include "Vector.hpp"

namespace clv::mth{
    template<length_type L, typename T>
	constexpr vec<L, T> normalise(const vec<L, T>& vector) noexcept;

	template<typename T>
	constexpr vec<3, T> cross(const vec<3, T>& vector1, const vec<3, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T dot(const vec<L, T>& vector1, const vec<L, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T distance(const vec<L, T>& vector1, const vec<L, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T length(const vec<L, T>& vector) noexcept;
}

#include "VectorMath.inl"