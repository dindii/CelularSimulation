#include "Application.h"
#include <Window/Window.h>

#include <iostream>
namespace SC
{
	Application::Application(std::string&& appName) noexcept : m_Running(true)
	{
		if (!m_Instance)
			m_Instance = this;

		m_AppWindow = std::make_unique<Window>(std::move(appName));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			OnUpdate();
		}
	}

	void Application::OnUpdate()
	{
		m_AppWindow->OnUpdate();
	}
}