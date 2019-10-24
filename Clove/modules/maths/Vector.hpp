#pragma	once

#include <cinttypes>
#include <array>
#include <type_traits>

//TODO: inl

namespace clv::mth{
	template<std::uint8_t L, typename T>
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

		constexpr T& operator[](std::uint8_t index) noexcept{
			return *reinterpret_cast<T*>(&x + index);
		}
		constexpr const T& operator[](std::uint8_t index) const noexcept{
			return *reinterpret_cast<const T*>(&x + index);
		}
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

		constexpr T& operator[](std::uint8_t index) noexcept{
			return *reinterpret_cast<T*>(&x + index);
		}
		constexpr const T& operator[](std::uint8_t index) const noexcept{
			return *reinterpret_cast<const T*>(&x + index);
		}
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

		constexpr T& operator[](std::uint8_t index) noexcept{
			return *reinterpret_cast<T*>(&x + index);
		}
		constexpr const T& operator[](std::uint8_t index) const noexcept{
			return *reinterpret_cast<const T*>(&x + index);
		}
	};

	using Vector2i = Vector<2, std::int32_t>;
	using Vector3i = Vector<3, std::int32_t>;
	using Vector4i = Vector<4, std::int32_t>;

	using Vector2f = Vector<2, float>;
	using Vector3f = Vector<3, float>;
	using Vector4f = Vector<4, float>;

	using Vector2d = Vector<2, double>;
	using Vector3d = Vector<3, double>;
	using Vector4d = Vector<4, double>;

	//TODO: operator isn't picked up
	template<std::uint32_t L, typename T, typename U, typename V>
	constexpr Vector<L, V> operator+(const Vector<L, T>& lhs, const Vector<L, U>& rhs){
		Vector<L, V> result;
		for(std::uint32_t i = 0; i < L; ++i){
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}
}