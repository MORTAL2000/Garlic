#pragma once

namespace clv::gfx{
	enum class API{
		None,
		OpenGL4,
	#if CLV_PLATFORM_WINDOWS
		DirectX11
	#endif
	};

	enum class ShaderType{
		Vertex,
		Pixel,
		Geometry
	};

	enum class ShaderStyle{ //TODO: Rename to material style
		Lit,
		Unlit,
		_2D,
		RT,
		Font,
		CubeShadowMap
	};

	enum class TextureStyle{
		Default,
		Cubemap
	};

	enum class TextureUsage{
		Default,
		RenderTarget_Colour,
		RenderTarget_Depth,
		Font
	};

	enum class VertexElementType{
		position2D,
		position3D,
		texture2D,
		normal,
	};

	struct TextureDescriptor{
		TextureStyle style = TextureStyle::Default;
		TextureUsage usage = TextureUsage::Default;
		math::Vector<2, uint32, math::qualifier::defaultp> dimensions = { 0, 0 };
		uint8 arraySize = 1;
	};
}