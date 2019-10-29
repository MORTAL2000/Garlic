#pragma	once

#include <cinttypes>
#include <type_traits>

namespace clv::mth{
	using length_type = std::uint8_t;

	template<length_type L, typename T>
	struct Vector{ };

	template<typename T>
	struct Vector<2, T>{
		//VARIABLES
	public:
		union{ T x; T r; T u; };
		union{ T y; T g; T v; };

		//FUNCTIONS
	public:
		Vector() : x(0), y(0){}
		Vector(T a, T b) : x(a), y(b){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<typename T>
	struct Vector<3, T>{
		//VARIABLES
	public:
		union{ T x; T r; };
		union{ T y; T g; };
		union{ T z; T b; };

		//FUNCTIONS
	public:
		Vector() : x(0), y(0), z(0){}
		Vector(T x, T y, T z) : x(x), y(y), z(z){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<typename T>
	struct Vector<4, T>{
		//VARIABLES
	public:
		union{ T x; T r; };
		union{ T y; T g; };
		union{ T z; T b; };
		union{ T w; T a; };

		//FUNCTIONS
	public:
		Vector() : x(0), y(0), z(0), w(0){}
		Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w){}

		T* ptr();

		constexpr T& operator[](length_type index) noexcept;
		constexpr const T& operator[](length_type index) const noexcept;
	};

	template<length_type L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, T scalar) noexcept;
	template<length_type L, typename T>
	constexpr Vector<L, T> operator+(const Vector<L, T>& lhs, const Vector<L, T>& rhs) noexcept;

	template<length_type L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, T scalar) noexcept;
	template<length_type L, typename T>
	constexpr Vector<L, T> operator-(const Vector<L, T>& lhs, const Vector<L, T>& rhs) noexcept;

	template<length_type L, typename T>
	constexpr Vector<L, T> operator*(const Vector<L, T>& lhs, T scalar) noexcept;

	using Vector2i = Vector<2, std::int32_t>;
	using Vector3i = Vector<3, std::int32_t>;
	using Vector4i = Vector<4, std::int32_t>;

	using Vector2f = Vector<2, float>;
	using Vector3f = Vector<3, float>;
	using Vector4f = Vector<4, float>;

	using Vector2d = Vector<2, double>;
	using Vector3d = Vector<3, double>;
	using Vector4d = Vector<4, double>;
}

#include "Vector.inl"