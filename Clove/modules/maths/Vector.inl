namespace clv::mth{
	template<typename T>
    T* Vector<2, T>::ptr(){
		return &(x);
	}

    template<typename T>
    constexpr T& Vector<2, T>::operator[](length_type index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<2, T>::operator[](length_type index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

	template<typename T>
    T* Vector<3, T>::ptr(){
		return &(x);
	}

    template<typename T>
    constexpr T& Vector<3, T>::operator[](length_type index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<3, T>::operator[](length_type index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

	template<typename T>
    T* Vector<4, T>::ptr(){
		return &(x);
	}

    template<typename T>
    constexpr T& Vector<4, T>::operator[](length_type index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<4, T>::operator[](length_type index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

    template<length_type L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, T scalar) noexcept{
		Vector<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] + scalar;
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, const Vector<L, T>& rhs) noexcept{
		Vector<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, T scalar) noexcept{
		Vector<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] - scalar;
		}
		return result;
	}
	
	template<length_type L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, const Vector<L, T>& rhs) noexcept{
		Vector<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}

	template<length_type L, typename T>
	constexpr Vector<L, T> operator*(const Vector<L, T>& lhs, T scalar) noexcept{
		Vector<L, T> result;
		for(length_type i = 0; i < L; ++i){
			result[i] = lhs[i] * scalar;
		}
		return result;
	}
}