#pragma once

#include "Core/Graphics/Surface.hpp"

namespace clv::gfx::ogl{
	class GLSurface : public Surface{
		//FUNCTIONS
	public:
		virtual void makeCurrent() = 0;
	};
}