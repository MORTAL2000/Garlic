namespace clv::mth{
	template<typename T>
	constexpr mat<4, 4, T> translate(const mat<4, 4, T>& matrix, const vec<3, T>& vector) noexcept{
		mat<4, 4, T> tranMat = mat<4, 4, T>::identity();

		tranMat[3][0] = vector.x;
		tranMat[3][1] = vector.y;
		tranMat[3][2] = vector.z;

		return matrix * tranMat;
	}

	template<typename T>
	constexpr mat<4, 4, T> rotate(const mat<4, 4, T>& matrix, T angle, const vec<3, T>& vector) noexcept{
		mat<4, 4, T> xRotMat = mat<4, 4, T>::identity();
		mat<4, 4, T> yRotMat = mat<4, 4, T>::identity();
		mat<4, 4, T> zRotMat = mat<4, 4, T>::identity();

		xRotMat[1][1] =  cos(angle) * vector.x;
		xRotMat[2][1] = -sin(angle) * vector.x;
		xRotMat[1][2] =  sin(angle) * vector.x;
		xRotMat[2][2] =  cos(angle) * vector.x;

		yRotMat[0][0] =  cos(angle) * vector.y;
		yRotMat[0][2] =  sin(angle) * vector.y;
		yRotMat[2][0] = -sin(angle) * vector.y;
		yRotMat[2][2] =  cos(angle) * vector.y;

		zRotMat[0][0] =  cos(angle) * vector.z;
		zRotMat[0][1] = -sin(angle) * vector.z;
		zRotMat[1][0] =  sin(angle) * vector.z;
		zRotMat[1][1] =  cos(angle) * vector.z;

		return matrix * (zRotMat * yRotMat * xRotMat);
	}

	template<typename T>
	constexpr mat<4, 4, T> scale(const mat<4, 4, T>& matrix, const vec<3, T>& vextor) noexcept{
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
	constexpr mat<4, 4, T> lookAt(const vec<3, T>& eye, const vec<3, T>& center, const vec<3, T>& up) noexcept{
		//TODO
	}
}
