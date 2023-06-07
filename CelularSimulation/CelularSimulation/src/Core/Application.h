#pragma once

#include <string>
#include <memory>
#include <Window/Window.h>


namespace SC
{

	class Application
	{
	public:
		Application(std::string&& appName) noexcept;
	
		void Run();
		void OnUpdate();

		inline void Terminate() { m_Running = false; }

		static Application& GetInstance() { return *m_Instance; }

	private:
		static inline Application* m_Instance = nullptr;
		std::unique_ptr<Window> m_AppWindow;
	
		bool m_Running;
	};

}