#pragma	once

#include <array>
#include <cinttypes>
#include <type_traits>

namespace clv::mth{
	using length_type = std::uint8_t;

	template<length_type L, typename T>
	struct vec{ };

	template<typename T>
	struct vec<2, T>{
		//VARIABLES
	public:
		union{
			std::array<T, 2> data;

			struct{ T x; T y; };
			struct{ T r; T g; };
			struct{ T s; T t; };
		};

		//FUNCTIONS
	public:
		vec() : x(0), y(0){}
		vec(T a, T b) : x(a), y(b){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<typename T>
	struct vec<3, T>{
		//VARIABLES
	public:
		union{
			std::array<T, 3> data;

			struct{ T x; T y; T z; };
			struct{ T r; T g; T b; };
			struct{ T s; T t; T p; };
		};

		//FUNCTIONS
	public:
		vec() : x(0), y(0), z(0){}
		vec(T x, T y, T z) : x(x), y(y), z(z){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<typename T>
	struct vec<4, T>{
		//VARIABLES
	public:
		union{
			std::array<T, 4> data;
			
			struct{ T x; T y; T z; T w; };
			struct{ T r; T g; T b; T a; };
			struct{ T s; T t; T p; T q; };
		};

		//FUNCTIONS
	public:
		vec() : x(0), y(0), z(0), w(0){}
		vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<length_type L, typename T>
	constexpr vec<L, T> operator+(const vec<L, T>& lhs, T scalar) noexcept;
	template<length_type L, typename T>
	constexpr vec<L, T> operator+(const vec<L, T>& lhs, const vec<L, T>& rhs) noexcept;

	template<length_type L, typename T>
	constexpr vec<L, T> operator-(const vec<L, T>& lhs, T scalar) noexcept;
	template<length_type L, typename T>
	constexpr vec<L, T> operator-(const vec<L, T>& lhs, const vec<L, T>& rhs) noexcept;

	template<length_type L, typename T>
	constexpr vec<L, T> operator*(const vec<L, T>& lhs, T scalar) noexcept;

	using vec2i = vec<2, std::int32_t>;
	using vec3i = vec<3, std::int32_t>;
	using vec4i = vec<4, std::int32_t>;

	using vec2f = vec<2, float>;
	using vec3f = vec<3, float>;
	using vec4f = vec<4, float>;

	using vec2d = vec<2, double>;
	using vec3d = vec<3, double>;
	using vec4d = vec<4, double>;
}

#include "Vector.inl"