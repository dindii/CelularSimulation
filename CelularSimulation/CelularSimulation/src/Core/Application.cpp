#include "Application.h"
#include <Window/Window.h>
#include <Rendering/Renderer.h>
#include <Physics/Simulator.h>

#include <iostream>

#include <chrono>

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
		const int radius = 300;
		
		vec2<int32_t> signedClickedPos((int32_t)clickedPosition.x, (int32_t)clickedPosition.y);

		for (int32_t x = signedClickedPos.x - radius; x < signedClickedPos.x + radius; ++x)
			for (int32_t y = signedClickedPos.y - radius; y < signedClickedPos.y + radius; ++y)
			{
				int32_t dx = x - clickedPosition.x;
				int32_t dy = y - clickedPosition.y;
		
				float distance = (dx * dx + dy * dy);
		
				if (distance < radius)
				{
					if(mouseButton == KeyCodes::CS_MOUSE_LBUTTON)
						Simulator::SpawnParticle(EParticleType::SAND, {(uint32_t)x, (uint32_t)y});
					else
						Simulator::SpawnParticle(EParticleType::WATER, {(uint32_t)x, (uint32_t)y});

				}
			}
	}
}