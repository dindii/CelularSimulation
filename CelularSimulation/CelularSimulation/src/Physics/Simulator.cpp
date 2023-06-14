#include "Simulator.h"

#include <Core/Application.h>
#include <Rendering/Renderer.h>
#include <Utils/Utils.h>

namespace CS
{
	std::vector<Particle> Simulator::m_Particles;
	vec2<int32_t> Simulator::m_CachedDims = { 0, 0 };

	void Simulator::Init()
	{
		Application& app = Application::GetInstance();

		vec2<int32_t> dims = app.GetWindow()->GetDims();

		m_Particles.resize(dims.x * dims.y);

		m_CachedDims = dims;
	}

	void Simulator::Update()
	{

		for (int32_t y = m_CachedDims.y - 1; y > 0; --y)
		{
			for (int32_t x = 0; x < m_CachedDims.x; ++x)
			{
				uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
				Particle& particle = m_Particles[idx];

				EParticleType particleType = particle.GetType();

				if (particle.GetUpdated())
					continue;

				switch (particleType)
				{
				case EParticleType::NONE:
					continue;
					break;

				case EParticleType::SAND:
					UpdateSand(x, y, idx);
					break;

				}
			}
		}



		for (int32_t y = m_CachedDims.y - 1; y > 0; --y)
		{
			for (int32_t x = 0; x < m_CachedDims.x; x++)
			{
				uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
				Particle& particle = m_Particles[idx];

				if(particle.GetUpdated())
					particle.SetUpdated(false);
			}
		}
	}

	void Simulator::SpawnParticle(EParticleType type, vec2<uint32_t> pos)
	{
		uint32_t idx = Get1DIndexFrom2DArray(pos.x, pos.y, m_CachedDims.x);

		m_Particles[idx] = type;
	}

	void Simulator::UpdateSand(int32_t x, int32_t y, int32_t currentCachedIdx)
	{
		uint32_t belowIdx = Get1DIndexFrom2DArray(x, y + 1, m_CachedDims.x);
		uint32_t belowLeftIdx = Get1DIndexFrom2DArray(x - 1, y + 1, m_CachedDims.x);
		uint32_t belowRightIdx = Get1DIndexFrom2DArray(x + 1, y + 1, m_CachedDims.x);

		if (belowIdx >= m_Particles.size())
			return;

		if (m_Particles[belowIdx].GetType() == EParticleType::NONE)
		{
			m_Particles[currentCachedIdx].SetUpdated(true);
			m_Particles[belowIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowIdx].SetType(EParticleType::SAND);

			//#TODO: Move this color to a index array.
			Renderer::SetPixel(vec2<uint32_t>(x, y + 1), { 255, 255, 0, 255 });
			Renderer::SetPixel(vec2<uint32_t>(x, y), { 0, 0, 0, 255 });
		}
		else if (m_Particles[belowLeftIdx].GetType() == EParticleType::NONE)
		{
			m_Particles[currentCachedIdx].SetUpdated(true);
			m_Particles[belowLeftIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowLeftIdx].SetType(EParticleType::SAND);

			//#TODO: Move this color to a index array.
			Renderer::SetPixel(vec2<uint32_t>(x - 1, y + 1), { 255, 255, 0, 255 });
			Renderer::SetPixel(vec2<uint32_t>(x, y), { 0, 0, 0, 255 });
		}
		else if (m_Particles[belowRightIdx].GetType() == EParticleType::NONE)
		{
			m_Particles[currentCachedIdx].SetUpdated(true);
			m_Particles[belowRightIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowRightIdx].SetType(EParticleType::SAND);

			//#TODO: Move this color to a index array.
			Renderer::SetPixel(vec2<uint32_t>(x + 1, y + 1), { 255, 255, 0, 255 });
			Renderer::SetPixel(vec2<uint32_t>(x, y), { 0, 0, 0, 255 });
		}

	}
}