#pragma once

#include <string>
#include <memory>
#include <Window/Window.h>
#include <Input/KeyCodes.h>

namespace CS
{

	class Application
	{
	public:
		Application(std::string&& appName) noexcept;
	
		void Run();
		void OnUpdate();

		inline void Terminate() { m_Running = false; }

		static Application& GetInstance() { return *m_Instance; }
		std::unique_ptr<Window>& GetWindow() { return m_AppWindow; }

		void OnMouseClicked(const KeyCodes mouseButton, vec2<uint32_t> clickedPosition);

	private:
		static inline Application* m_Instance = nullptr;
		std::unique_ptr<Window> m_AppWindow;
	
		bool m_Running;
	};

}