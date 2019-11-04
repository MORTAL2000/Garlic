namespace clv::mth{
	template<typename T>
    T* vec<2, T>::ptr(){
		return data.data();
	}

    template<typename T>
    constexpr T& vec<2, T>::operator[](length_type index) noexcept{
		return data[index];
	}

    template<typename T>
	constexpr const T& vec<2, T>::operator[](length_type index) const noexcept{
		return data[index];
	}

	template<typename T>
    T* vec<3, T>::ptr(){
		return data.data();
	}

    template<typename T>
    constexpr T& vec<3, T>::operator[](length_type index) noexcept{
		return data[index];
	}

    template<typename T>
	constexpr const T& vec<3, T>::operator[](length_type index) const noexcept{
		return data[index];
	}

	template<typename T>
    T* vec<4, T>::ptr(){
		return data.data();
	}

    template<typename T>
    constexpr T& vec<4, T>::operator[](length_type index) noexcept{
		return data[index];
	}

    template<typename T>
	constexpr const T& vec<4, T>::operator[](length_type index) const noexcept{
		return data[index];
	}

    template<length_type L, typename T>
	constexpr vec<L, T> operator+(const vec<L, T>& lhs, T scalar) noexcept{
		vec<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] + scalar;
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr vec<L, T> operator+(const vec<L, T>& lhs, const vec<L, T>& rhs) noexcept{
		vec<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr vec<L, T> operator-(const vec<L, T>& lhs, T scalar) noexcept{
		vec<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] - scalar;
		}
		return result;
	}
	
	template<length_type L, typename T>
	constexpr vec<L, T> operator-(const vec<L, T>& lhs, const vec<L, T>& rhs) noexcept{
		vec<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr vec<L, T> operator*(const vec<L, T>& lhs, T scalar) noexcept{
		vec<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] * scalar;
		}
		return result;
	}
}