#pragma once

#include <cinttypes>

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

    };

    using quati = quat<std::int32_t>;
    using quatf = quat<float>;
    using quatd = quat<double>;
}

#include "Quaternion.inl"