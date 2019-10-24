namespace clv::mth{
    template<typename T>
    constexpr T& Vector<2, T>::operator[](std::uint8_t index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<2, T>::operator[](std::uint8_t index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

    template<typename T>
    constexpr T& Vector<3, T>::operator[](std::uint8_t index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<3, T>::operator[](std::uint8_t index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

    template<typename T>
    constexpr T& Vector<4, T>::operator[](std::uint8_t index) noexcept{
		return *reinterpret_cast<T*>(&x + index);
	}

    template<typename T>
	constexpr const T& Vector<4, T>::operator[](std::uint8_t index) const noexcept{
		return *reinterpret_cast<const T*>(&x + index);
	}

    template<std::uint8_t L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, T scalar){
		Vector<L, T> result;
		for(std::uint8_t i = 0; i < L; ++i){
			result[i] = lhs[i] + scalar;
		}
		return result;
	}
	template<std::uint8_t L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, const Vector<L, T>& rhs){
		Vector<L, T> result;
		for(std::uint8_t i = 0; i < L; ++i){
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}

	template<std::uint8_t L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, T scalar){
		Vector<L, T> result;
		for(std::uint8_t i = 0; i < L; ++i){
			result[i] = lhs[i] - scalar;
		}
		return result;
	}
	template<std::uint8_t L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, const Vector<L, T>& rhs){
		Vector<L, T> result;
		for(std::uint8_t i = 0; i < L; ++i){
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}

	template<std::uint8_t L, typename T>
	constexpr Vector<L, T> operator*(const Vector<L, T>& lhs, T scalar){
		Vector<L, T> result;
		for(std::uint8_t i = 0; i < L; ++i){
			result[i] = lhs[i] * scalar;
		}
		return result;
	}
}