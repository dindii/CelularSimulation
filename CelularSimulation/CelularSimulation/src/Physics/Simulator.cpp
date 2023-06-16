#include "Simulator.h"

#include <Core/Application.h>
#include <Rendering/Renderer.h>
#include <Utils/Utils.h>

namespace CS
{
	std::vector<Particle> Simulator::m_Particles;
	vec2<int32_t> Simulator::m_CachedDims = { 0, 0 };
	vec4<uint8_t> Simulator::m_MaterialColors[(uint8_t)EParticleType::SIZE];

	void Simulator::Init()
	{
		Application& app = Application::GetInstance();

		vec2<int32_t> dims = app.GetWindow()->GetDims();

		m_Particles.resize(dims.x * dims.y);

		m_CachedDims = dims;

		const vec4<float>& defaultColor = Renderer::GetClearColor();

		vec4<uint8_t> defaultByteColor = ColorFloatToByte(defaultColor);

		m_MaterialColors[(uint8_t)EParticleType::NONE]  = defaultByteColor;
		m_MaterialColors[(uint8_t)EParticleType::SAND]  = vec4<uint8_t>(255, 255, 0, 255);
		m_MaterialColors[(uint8_t)EParticleType::WATER] = vec4<uint8_t>(0, 0, 255, 255);
	}

	void Simulator::Update()
	{
		static uint64_t updateCounter = 0;
		bool evenFrame = (updateCounter % 2) == 0;

		for (int32_t y = m_CachedDims.y - 1; y > 0; --y)
		{		
			for (int32_t x = evenFrame ? 0 : m_CachedDims.x - 1; evenFrame ? x < m_CachedDims.x : x > 0; evenFrame ? ++x : --x)
			{
				uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
				Particle& particle = m_Particles[idx];

				EParticleType particleType = particle.GetType();

				Renderer::SetPixel(vec2<uint32_t>(x, y), m_MaterialColors[(uint8_t)particleType]);

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

					case EParticleType::WATER:
						UpdateWater(x, y, idx);
						break;
				}

				m_Particles[idx].SetUpdated(true);
			}
		}

		updateCounter++;

		ClearUpdateStatus();
	}

	void Simulator::ClearUpdateStatus()
	{
		for (int32_t y = m_CachedDims.y - 1; y > 0; --y)
		{
			for (int32_t x = 0; x < m_CachedDims.x; x++)
			{
				uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
				Particle& particle = m_Particles[idx];

				particle.SetUpdated(false);
			}
		}
	}

	bool Simulator::IsCellEmpty(uint32_t x, uint32_t y)
	{
		uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
		return IsCellEmpty(idx);
	}

	bool Simulator::IsCellEmpty(uint32_t idx)
	{
		return (m_Particles[idx].GetType() == EParticleType::NONE);
	}

	bool Simulator::IsInBounds(uint32_t x, uint32_t y)
	{
		uint32_t idx = Get1DIndexFrom2DArray(x, y, m_CachedDims.x);
		return IsInBounds(idx);
	}

	bool Simulator::IsInBounds(uint32_t idx)
	{
		return (idx >= 0 && idx < m_Particles.size());
	}

	void Simulator::SpawnParticle(EParticleType type, vec2<uint32_t> pos)
	{
		uint32_t idx = Get1DIndexFrom2DArray(pos.x, pos.y, m_CachedDims.x);
		
		if(!IsInBounds(idx))
			return;
		
		m_Particles[idx] = type;
	}

	void Simulator::UpdateSand(int32_t x, int32_t y, int32_t currentCachedIdx)
	{
		uint32_t belowIdx      = Get1DIndexFrom2DArray(x, y + 1, m_CachedDims.x);
		uint32_t belowLeftIdx  = Get1DIndexFrom2DArray(x - 1, y + 1, m_CachedDims.x);
		uint32_t belowRightIdx = Get1DIndexFrom2DArray(x + 1, y + 1, m_CachedDims.x);

		if (!(IsInBounds(belowIdx) && IsInBounds(belowLeftIdx) && IsInBounds(belowRightIdx)))
			return;

		if (IsCellEmpty(belowIdx))
		{
			m_Particles[belowIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowIdx].SetType(EParticleType::SAND);
		}
		else if (IsCellEmpty(belowLeftIdx))
		{
			m_Particles[belowLeftIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowLeftIdx].SetType(EParticleType::SAND);
		}
		else if (IsCellEmpty(belowRightIdx))
		{
			m_Particles[belowRightIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowRightIdx].SetType(EParticleType::SAND);
		}
	}
	
	void Simulator::UpdateWater(int32_t x, int32_t y, int32_t currentCachedIdx)
	{
		uint32_t belowIdx      = Get1DIndexFrom2DArray(x, y + 1, m_CachedDims.x);
		uint32_t belowLeftIdx  = Get1DIndexFrom2DArray(x - 1, y + 1, m_CachedDims.x);
		uint32_t belowRightIdx = Get1DIndexFrom2DArray(x + 1, y + 1, m_CachedDims.x);

		if (!(IsInBounds(belowIdx) && IsInBounds(belowLeftIdx) && IsInBounds(belowRightIdx)))
			return;

		if (IsCellEmpty(belowIdx))
		{
			m_Particles[belowIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowIdx].SetType(EParticleType::WATER);
		}
		else if (IsCellEmpty(belowLeftIdx))
		{
			m_Particles[belowLeftIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowLeftIdx].SetType(EParticleType::WATER);
		}
		else if (IsCellEmpty(belowRightIdx))
		{
			m_Particles[belowRightIdx].SetUpdated(true);

			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[belowRightIdx].SetType(EParticleType::WATER);
		}
		else if (IsCellEmpty(currentCachedIdx - 1))
		{
			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[currentCachedIdx - 1].SetType(EParticleType::WATER);
		}
		else if (IsCellEmpty(currentCachedIdx + 1))
		{
			m_Particles[currentCachedIdx].SetType(EParticleType::NONE);
			m_Particles[currentCachedIdx + 1].SetType(EParticleType::WATER);
		}
	}
}