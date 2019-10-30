namespace clv::mth{
	template<typename T>
	constexpr mat<4, 4, T> translate(const mat<4, 4, T>& matrix, const Vector<3, T>& vector) noexcept{
		//TODO
	}

	template<typename T>
	constexpr mat<4, 4, T> rotate(const mat<4, 4, T>& matrix, T angle, const Vector<3, T>& vector) noexcept{
		//TODO
	}

	template<typename T>
	constexpr mat<4, 4, T> scale(const mat<4, 4, T>& matrix, const Vector<3, T>& vextor) noexcept{
		//TODO
	}

	template<size_type R, size_type C, typename T>
	constexpr mat<R, C, T> inverse(const mat<R, C, T>& matrix) noexcept{
		//TODO
	}

	template<size_type R, size_type C, typename T>
	constexpr mat<R, C, T> transpose(const mat<R, C, T>& matrix) noexcept{
		//TODO
	}

	template<typename T>
	constexpr mat<4, 4, T> lookAt(const Vector<3, T>& eye, const Vector<3, T>& center, const Vector<3, T>& up) noexcept{
		//TODO
	}
}
