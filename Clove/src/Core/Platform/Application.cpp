#include "Clove/Core/Platform/Application.hpp"

#include "Clove/Core/Platform/Window.hpp"
#include "Clove/Core/Input/Input.hpp"
#include "Clove/Core/LayerStack.hpp"
#include "Clove/Core/Layer.hpp"
#include "Clove/Core/Utils/DeltaTime.hpp"
#include "Clove/Core/ECS/Manager.hpp"

#include "Clove/Core/Graphics/GraphicsGlobal.hpp"

#if CLV_PLATFORM_WINDOWS
	#include "Clove/Platform/Windows/WindowsApplication.hpp"
#elif CLV_PLATFORM_LINUX
	#include "Clove/Platform/Linux/LinuxApplication.hpp"
#elif CLV_PLATFORM_MACOS
	#include "Clove/Platform/Mac/MacApplication.hpp"
#endif

namespace clv::plt{
	Application* Application::instance = nullptr;

	Application::Application(){
		CLV_PROFILE_BEGIN_SESSION("Application cycle", "Profile-Cycle.json");

		CLV_ASSERT(!instance, "Application already exists!");
		instance = this;

		Log::init();

		CLV_LOG_INFO("Successfully initialised Clove");

		prevFrameTime = std::chrono::system_clock::now();
	}

	Application::~Application(){
		CLV_PROFILE_END_SESSION();
	}

	void Application::initialise(){
		//TODO: Added a 'start' function to handle not calling a virtual from the ctor
		//Would like as minimal api as possible when starting the application

		gfx::global::initialise(getPlatformPreferedAPI());

		window = createWindow();
		window->onWindowCloseDelegate.bind(&Application::onWindowClose, this);
		window->setVSync(true);

		gfx::global::graphicsDevice->setClearColour({ 1.0f, 0.54f, 0.1f, 1.0f });

		ecsManager = std::make_unique<ecs::Manager>();
		layerStack = std::make_unique<LayerStack>();
	}

	void Application::initialise(const Window& parentWindow, const mth::vec2i& position, const mth::vec2i& size){
		gfx::RenderCommand::initialise(getPlatformPreferedAPI());

		window = createChildWindow(parentWindow, position, size);
		//window->onWindowCloseDelegate.bind(&Application::onWindowClose, this);
		//window->setVSync(true);

		gfx::RenderCommand::setClearColour({ 1.0f, 0.54f, 0.1f, 1.0f });

		ecsManager = std::make_unique<ecs::Manager>();
		layerStack = std::make_unique<LayerStack>();
	}

	void Application::update(){
		CLV_PROFILE_FUNCTION();

		auto currFrameTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaSeonds = currFrameTime - prevFrameTime;
		prevFrameTime = currFrameTime;

		window->beginFrame();

		//TODO:
		//Will need process the mouse and keyboard events here eventually

		for(const auto& layer : *layerStack){
			layer->onUpdate(deltaSeonds.count());
		}

		ecsManager->update(deltaSeonds.count());

		{
			CLV_PROFILE_SCOPE("Window::endFrame");
			window->endFrame();
		}
	}

	void Application::stop(){
		currentState = ApplicationState::stopped;
	}

	ApplicationState Application::getState() const{
		return currentState;
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

	std::unique_ptr<Application> Application::createApplication(){
	#if CLV_PLATFORM_WINDOWS
		return std::make_unique<WindowsApplication>();
	#elif CLV_PLATFORM_LINUX
		return std::make_unique<LinuxApplication>();
	#elif CLV_PLATFORM_MACOS
		return std::make_unique<MacApplication>();
	#endif
	}

	void Application::onWindowClose(){
		stop();
	}
}