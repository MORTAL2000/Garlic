#include "Clove/Platform/Core/Window.hpp"

#include "Clove/Graphics/Core/Surface.hpp"

namespace clv::plt{
	Window::Window() = default;

	Window::~Window() = default;

	void Window::beginFrame(){
		processInput();
	}

	void Window::endFrame(){
		surface->present();
	}

	void Window::setVSync(bool enabled){
		surface->setVSync(enabled);
	}

	bool Window::isVSync() const{
		return surface->isVsync();
	}

	Keyboard& Window::getKeyboard(){
		return keyboard;
	}

	Mouse& Window::getMouse(){
		return mouse;
	}

	gfx::Surface& Window::getSurface(){
		return *surface.get();
	}
}