namespace clv::mth{
	template<length_type L, typename T>
	constexpr vec<L, T> normalise(const vec<L, T>& vector) noexcept{
		vec<L, T> result = {};
		const T vectorLength = length(vector);
		for(length_type i = 0; i < L; ++i){
			result[i] = vector[i] / vectorLength;
		}
		return result;
	}

	template<typename T>
	constexpr vec<3, T> cross(const vec<3, T>& vector1, const vec<3, T>& vector2) noexcept{
		return {
			(vector1.y * vector2.z) - (vector1.z * vector2.y),
			(vector1.z * vector2.x) - (vector1.x * vector2.z),
			(vector1.x * vector2.y) - (vector1.y * vector2.x)
		};
	}

	template<length_type L, typename T>
	constexpr T dot(const vec<L, T>& vector1, const vec<L, T>& vector2) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			result += vector1[i] * vector2[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr T distance(const vec<L, T>& vector1, const vec<L, T>& vector2) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			const T diff = vector1[i] - vector2[i];
			result += diff * diff;
		}
		return sqrt(result);
	}

	template<length_type L, typename T>
	constexpr T length(const vec<L, T>& vector) noexcept{
		T result = 0;
		for(length_type i = 0; i < L; ++i){
			result += vector[i] * vector[i];
		}
		return sqrt(result);
	}
}