project(Maths)

add_library(
	Maths 
	STATIC
		Matrix.hpp
		Matrix.inl
		Vector.hpp
		Vector.inl
		VectorMath.hpp
		VectorMath.inl

		Temp.cpp #Required because of no cpp files and need to generate the .lib
)

target_include_directories(
	Maths
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

#Temp executable before a proper test auit is set up
add_executable(
	Test
	Test.cpp
)

target_link_libraries(
	Test
	PRIVATE
	Maths
)