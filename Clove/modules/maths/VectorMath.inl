namespace clv::mth{
	template<length_type L, typename T>
	constexpr Vector<L, T> normalise(const Vector<L, T>& vector) noexcept{
		Vector<L, T> result = {};
		const T vectorLength = length(vector);
		for(length_type i = 0; i < L; ++i){
			result[i] = vector[i] / vectorLength;
		}
		return result;
	}

	template<typename T>
	constexpr Vector<3, T> cross(const Vector<3, T>& vector1, const Vector<3, T>& vector2) noexcept{
		//TODO
	}

	template<length_type L, typename T>
	constexpr T dot(const Vector<L, T>& vector1, const Vector<L, T>& vector2) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			result += vector1[i] * vector2[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr T distance(const Vector<L, T>& vector1, const Vector<L, T>& vector2) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			const T diff = vector1[i] - vector2[i];
			result += diff * diff;
		}
		return sqrt(result);
	}

	template<length_type L, typename T>
	constexpr T length(const Vector<L, T>& vector) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			result += vector[i] * vector[i];
		}
		return sqrt(result);
	}
}