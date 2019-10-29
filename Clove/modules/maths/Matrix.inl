namespace clv::mth{
    template<std::uint32_t R, std::uint32_t C, typename T>
    Matrix<R, C, T>::Matrix(){
        std::for_each(mat.begin(), mat.end(), [](auto& innerArray){
			std::for_each(innerArray.begin(), innerArray.end(), [](T& value){
				value = 0;
			});
		});
    }

    template<std::uint32_t R, std::uint32_t C, typename T>
	T* Matrix<R, C, T>::ptr(){
		return &(mat[0][0]);
	}

    template<std::uint32_t R, std::uint32_t C, typename T>
    constexpr auto& Matrix<R, C, T>::operator[](std::uint32_t index) noexcept{ 
		return mat[index];
	}

    template<std::uint32_t R, std::uint32_t C, typename T>
	constexpr const auto& Matrix<R, C, T>::operator[](std::uint32_t index) const noexcept{
		return mat[index];
	}

    template<std::uint32_t aR, std::uint32_t aC, std::uint32_t bR, std::uint32_t bC, typename T>
	constexpr Matrix<aR, aC, T> operator+(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept{
		static_assert(aR == bR && aC == bC, "Matrices must be the same size");

		Matrix<aR, aC, T> result;

		for(std::size_t row = 0; row < aR; ++row){
			for(std::size_t col = 0; col < aC; ++col){
				result[row][col] = lhs[row][col] + rhs[row][col];
			}
		}

		return result;
	}

	template<std::uint32_t aR, std::uint32_t aC, std::uint32_t bR, std::uint32_t bC, typename T>
	constexpr Matrix<aR, aC, T> operator-(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept{
		static_assert(aR == bR && aC == bC, "Matrices must be the same size");

		Matrix<aR, aC, T> result;

		for(std::size_t row = 0; row < aR; ++row){
			for(std::size_t col = 0; col < aC; ++col){
				result[row][col] = lhs[row][col] - rhs[row][col];
			}
		}

		return result;
	}

	template<std::uint32_t aR, std::uint32_t aC, std::uint32_t bR, std::uint32_t bC, typename T>
	constexpr Matrix<aR, bC, T> operator*(const Matrix<aR, aC, T>& lhs, const Matrix<bR, bC, T>& rhs) noexcept{
		static_assert(aC == bR, "Inner values must be the same");

		Matrix<aR, bC, T> result;

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