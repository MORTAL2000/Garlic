#include "Tunic/Application.hpp"

#include "Clove/Platform/Core/Platform.hpp"
#include "Clove/Platform/Core/Window.hpp"
#include "Tunic/Input.hpp"
#include "Clove/Core/LayerStack.hpp"
#include "Clove/Core/Layer.hpp"
#include "Clove/Core/Utils/DeltaTime.hpp"
#include "Tunic/ECS/Core/Manager.hpp"

using namespace clv;

namespace tnc{
	Application* Application::instance = nullptr;

	Application::Application(gfx::API api){
		CLV_PROFILE_BEGIN_SESSION("Application cycle", "Profile-Cycle.json");

		Log::init();

		CLV_ASSERT(!instance, "Application already exists!");
		instance = this;

		platformInstance = clv::plt::createPlatformInstance();

		mainWindow = platformInstance->createWindow({"Tunic Application", 1280, 720});
		mainWindow->onWindowCloseDelegate.bind(&tnc::Application::stop, this);
		mainWindow->setVSync(true);

		//gfx::global::graphicsDevice->setClearColour({ 1.0f, 0.54f, 0.1f, 1.0f });

		ecsManager = std::make_unique<ecs::Manager>();
		layerStack = std::make_unique<LayerStack>();

		CLV_LOG_INFO("Successfully initialised Clove");

		prevFrameTime = std::chrono::system_clock::now();
	}

	Application::Application(clv::gfx::API api, const clv::plt::Window& parentWindow, const clv::mth::vec2i& windowPosition, const clv::mth::vec2i& windowSize){
		CLV_PROFILE_BEGIN_SESSION("Application cycle", "Profile-Cycle.json");
		
		Log::init();

		CLV_ASSERT(!instance, "Application already exists!");
		instance = this;

		platformInstance = clv::plt::createPlatformInstance();

		mainWindow = platformInstance->createChildWindow(parentWindow, windowPosition, windowSize, api);
		mainWindow->onWindowCloseDelegate.bind(&tnc::Application::stop, this);
		mainWindow->setVSync(true);

		//gfx::global::graphicsDevice->setClearColour({ 1.0f, 0.54f, 0.1f, 1.0f });

		ecsManager = std::make_unique<ecs::Manager>();
		layerStack = std::make_unique<LayerStack>();

		CLV_LOG_INFO("Successfully initialised Clove");

		prevFrameTime = std::chrono::system_clock::now();
	}

	Application::~Application(){
		CLV_PROFILE_END_SESSION();
	}

	void Application::update(){
		CLV_PROFILE_FUNCTION();

		auto currFrameTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaSeonds = currFrameTime - prevFrameTime;
		prevFrameTime = currFrameTime;

		mainWindow->beginFrame();

		//TODO:
		//Will need process the mouse and keyboard events here eventually

		for(const auto& layer : *layerStack){
			layer->onUpdate(deltaSeonds.count());
		}

		ecsManager->update(deltaSeonds.count());

		{
			CLV_PROFILE_SCOPE("Window::endFrame");
			mainWindow->endFrame();
		}
	}

	void Application::stop(){
		currentState = ApplicationState::stopped;
	}

	ApplicationState Application::getState() const{
		return currentState;
	}

	void Application::pushLayer(std::shared_ptr<Layer> layer){
		layerStack->pushLayer(std::move(layer));
	}

	void Application::pushOverlay(std::shared_ptr<Layer> overlay){
		layerStack->pushOverlay(std::move(overlay));
	}

	Application& Application::get(){
		return *instance;
	}

	ecs::Manager& Application::getManager(){
		return *ecsManager;
	}

	plt::Window& Application::getMainWindow() const{
		return *mainWindow;
	}

	void Application::setMainWindow(const std::shared_ptr<plt::Window>& window){
		mainWindow = window;
	}

	clv::gfx::GraphicsFactory& Application::getGraphicsFactory(){
		return mainWindow->getGraphicsFactory();
	}
}