#include "Application.h"
#include <Window/Window.h>
#include <Rendering/Renderer.h>

#include <iostream>

namespace CS
{
	Application::Application(std::string&& appName) noexcept : m_Running(true)
	{
		if (!m_Instance)
			m_Instance = this;

		m_AppWindow = std::make_unique<Window>(std::move(appName));

		Renderer::Init();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			OnUpdate();

			Renderer::Draw();
		}
	}

	void Application::OnUpdate()
	{
		m_AppWindow->OnUpdate();
	}
}