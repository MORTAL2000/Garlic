#pragma	once

#include <cinttypes>
#include <array>
#include <type_traits>

//TODO: inl

namespace clv::mth{
	template<std::uint32_t L, typename T>
	struct Vector{ };

	template<typename T>
	struct Vector<2, T>{
		//VARIABLES
	public:
		union{ T x; T r; T u; };
		union{ T y; T g; T v; };

		//FUNCTIONS
	public:
		Vector(){
			x = 0;
			y = 0;
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
		Vector(){
			x = 0;
			y = 0;
			z = 0;
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
		Vector(){
			x = 0;
			y = 0;
			z = 0;
			w = 0;
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
}