#include "clvpch.hpp"
#include "Application.hpp"

#include "Clove/Platform/Window.hpp"
#include "Clove/Input/Input.hpp"
#include "Clove/LayerStack.hpp"
#include "Clove/Layer.hpp"
#include "Clove/Utils/DeltaTime.hpp"
#include "Clove/ECS/Manager.hpp"

#include "Clove/Graphics/Renderer.hpp"
#include "Clove/Graphics/Renderer2D.hpp"
#include "Clove/Graphics/RenderCommand.hpp"

namespace clv{
	Application* Application::instance = nullptr;

	Application::Application(){
		CLV_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->onWindowCloseDelegate.bind(&Application::onWindowClose, this);
		window->setVSync(true);

		gfx::RenderCommand::initialiseRenderAPI(window->getContext());
		gfx::RenderCommand::setClearColour({ 1.0f, 0.54f, 0.1f, 1.0f });

		gfx::Renderer::initialise();
		gfx::Renderer2D::initialise();

		ecsManager = std::make_unique<ecs::Manager>();
		layerStack = std::make_unique<LayerStack>();

		CLV_LOG_INFO("Successfully initialised Clove");

		prevFrameTime = std::chrono::system_clock::now();
	}

	Application::~Application() = default;

	void Application::run(){
		while(running){
			auto currFrameTime = std::chrono::system_clock::now();
			std::chrono::duration<float> deltaSeonds = currFrameTime - prevFrameTime;
			prevFrameTime = currFrameTime;

			window->beginFrame();

			//TODO:
			//Will need process the mouse and keyboard events here eventually

			for(auto layer : *layerStack){
				layer->onUpdate(deltaSeonds.count());
			}

			gfx::Renderer::clearRenderTargets();

			gfx::Renderer::beginScene();
			gfx::Renderer2D::beginScene();

			ecsManager->update(deltaSeonds.count());

			gfx::Renderer::endScene();
			gfx::Renderer2D::endScene();

			window->endFrame();
		}
	}

	void Application::stop(){
		running = false;
	}

	void Application::pushLayer(std::shared_ptr<Layer> layer){
		layerStack->pushLayer(layer);
	}

	void Application::pushOverlay(std::shared_ptr<Layer> overlay){
		layerStack->pushOverlay(overlay);
	}

	Application& Application::get(){
		return *instance;
	}

	Window& Application::getWindow(){
		return *window;
	}

	ecs::Manager& Application::getManager(){
		return *ecsManager;
	}

	void Application::onWindowClose(){
		running = false;
	}
}