#pragma once

#include <stdint.h>
#include <string>
#include <string_view>

#include <Math/vec2.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace SC
{
	class Window
	{
	public:
		Window(std::string&& name, vec2<int32_t> dims = { 800, 600 }) noexcept;
		Window() = delete;
		~Window();


		void OnUpdate();

		vec2<int32_t> GetDims() const { return m_Dims; }
		std::string_view GetWindowName() const { return m_WindowName; }

	private:
		bool LoadGraphicsContext();
		void PollEvents();
		void SwapBuffers();

	private:
		vec2<int32_t> m_Dims;
		std::string m_WindowName;

		HWND m_NativeWindow;
		HDC m_WindowContext;
	};
}