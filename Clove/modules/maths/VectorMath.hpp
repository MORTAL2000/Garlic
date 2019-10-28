#include "Vector.hpp"

namespace clv::mth{
    template<length_type L, typename T>
	Vector<L, T> normalise(const Vector<L, T>& vector);

	template<typename T>
	Vector<3, T> cross(const Vector<3, T>& vector1, const Vector<3, T>& vector2);

	template<length_type L, typename T>
	T dot(const Vector<L, T>& vector1, const Vector<L, T>& vector2);

	template<length_type L, typename T>
	T distance(const Vector<L, T>& vector1, const Vector<L, T>& vector2);

	template<length_type L, typename T>
	T length(const Vector<L, T>& vector);
}

#include "VectorMath.inl"