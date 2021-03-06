#pragma once

#include "Clove/Platform/Core/Platform.hpp"

namespace clv::plt{
	class LinuxPlatform : public Platform{
		//FUNCTIONS
	public:
		LinuxPlatform();

		LinuxPlatform(const LinuxPlatform& other) = delete;
		LinuxPlatform(LinuxPlatform&& other) noexcept;

		LinuxPlatform& operator=(const LinuxPlatform& other) = delete;
		LinuxPlatform& operator=(LinuxPlatform&& other) noexcept;

		virtual ~LinuxPlatform();

		virtual std::shared_ptr<Window> createWindow(const WindowDescriptor& props) override;
        virtual std::shared_ptr<Window> createChildWindow(const Window& parentWindow, const mth::vec2i& position, const mth::vec2i& size, const gfx::API api) override;
	};
}
