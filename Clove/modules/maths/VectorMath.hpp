#include "Vector.hpp"

namespace clv::mth{
    template<length_type L, typename T>
	constexpr Vector<L, T> normalise(const Vector<L, T>& vector) noexcept;

	template<typename T>
	constexpr Vector<3, T> cross(const Vector<3, T>& vector1, const Vector<3, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T dot(const Vector<L, T>& vector1, const Vector<L, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T distance(const Vector<L, T>& vector1, const Vector<L, T>& vector2) noexcept;

	template<length_type L, typename T>
	constexpr T length(const Vector<L, T>& vector) noexcept;
}

#include "VectorMath.inl"