namespace clv::mth{
    template<size_type R, size_type C, typename T>
    mat<R, C, T>::mat(){
        std::for_each(data.begin(), data.end(), [](auto& innerArray){
			std::for_each(innerArray.begin(), innerArray.end(), [](T& value){
				value = 0;
			});
		});
    }

    template<size_type R, size_type C, typename T>
	T* mat<R, C, T>::ptr(){
		return &(data[0][0]);
	}

	template<size_type R, size_type C, typename T>
	constexpr mat<R, C, T> mat<R, C, T>::identity() noexcept{
		mat<R, C, T> matrix;
		for (size_type row = 0, col = 0; row < R && col < C; ++row, ++col){
			matrix[row][col] = 1;
		}
		return matrix;
	}

    template<size_type R, size_type C, typename T>
    constexpr auto& mat<R, C, T>::operator[](size_type index) noexcept{ 
		return data[index];
	}

    template<size_type R, size_type C, typename T>
	constexpr const auto& mat<R, C, T>::operator[](size_type index) const noexcept{
		return data[index];
	}

    template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, aC, T> operator+(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept{
		static_assert(aR == bR && aC == bC, "Matrices must be the same size");

		mat<aR, aC, T> result;

		for(std::size_t row = 0; row < aR; ++row){
			for(std::size_t col = 0; col < aC; ++col){
				result[row][col] = lhs[row][col] + rhs[row][col];
			}
		}

		return result;
	}

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, aC, T> operator-(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept{
		static_assert(aR == bR && aC == bC, "Matrices must be the same size");

		mat<aR, aC, T> result;

		for(std::size_t row = 0; row < aR; ++row){
			for(std::size_t col = 0; col < aC; ++col){
				result[row][col] = lhs[row][col] - rhs[row][col];
			}
		}

		return result;
	}

	template<size_type aR, size_type aC, size_type bR, size_type bC, typename T>
	constexpr mat<aR, bC, T> operator*(const mat<aR, aC, T>& lhs, const mat<bR, bC, T>& rhs) noexcept{
		static_assert(aC == bR, "Inner values must be the same");

		mat<aR, bC, T> result;

		for(std::size_t row = 0; row < aR; ++row){
			for(std::size_t col = 0; col < bC; ++col){
				for(std::size_t i = 0, j = 0; i < aC && j < bR; ++i, ++j){
					result[row][col] += lhs[row][i] * rhs[j][col];
				}
			}
		}

		return result;
	}
}