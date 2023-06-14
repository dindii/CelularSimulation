#include "Application.h"
#include <Window/Window.h>
#include <Rendering/Renderer.h>
#include <Physics/Simulator.h>

#include <iostream>

namespace CS
{
	Application::Application(std::string&& appName) noexcept : m_Running(true)
	{
		if (!m_Instance)
			m_Instance = this;

		m_AppWindow = std::make_unique<Window>(std::move(appName));

		Renderer::Init();
		Simulator::Init();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			OnUpdate();

			Simulator::Update();
			Renderer::Draw();
		}
	}

	void Application::OnUpdate()
	{
		m_AppWindow->OnUpdate();
	}

	void Application::OnMouseClicked(const KeyCodes mouseButton, vec2<uint32_t> clickedPosition)
	{
		//TEST

		const int radius = 25;

		for (int32_t x = clickedPosition.x - radius; x < clickedPosition.x + radius; ++x)
			for (int32_t y = clickedPosition.y - radius; y < clickedPosition.y + radius; ++y)
			{
				int dx = x - clickedPosition.x;
				int dy = y - clickedPosition.y;
		
				float distance = sqrt(dx * dx + dy * dy);
		
				if (distance < radius)
				{
					Simulator::SpawnParticle(EParticleType::SAND, {(uint32_t)x, (uint32_t)y});
				}
			}
		//Simulator::SpawnParticle(EParticleType::SAND, clickedPosition);


	}
}