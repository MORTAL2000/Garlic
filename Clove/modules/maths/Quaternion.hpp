#pragma once

#include "Vector.hpp"

#include <cinttypes>

//TODO: inl

namespace clv::mth{
    template<typename T>
    struct quat{
        //VARIABLES
    public:
    	T x = 0;
    	T y = 0;
    	T z = 0;
    	T w = 0;

    	//FUNCTIONS
    public:
		quat(const vec<3, T>& axis, T angle){
			x = axis.x * sin(angle / 2);
			y = axis.y * sin(angle / 2);
			z = axis.z * sin(angle / 2);
			w = cos(angle / 2);
		}
    };

    using quati = quat<std::int32_t>;
    using quatf = quat<float>;
    using quatd = quat<double>;
}

#include "Quaternion.inl"