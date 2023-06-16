#include "Particle.h"
#include <Math/vec2.h>
#include <Math/vec4.h>
#include <vector>

namespace CS
{
	class Simulator
	{
	public:
		Simulator() = delete;

		static void Init();
		static void Update();

		static void SpawnParticle(EParticleType type, vec2<uint32_t> pos);

	private:
		//We will not use virtual functions or so, because this area is performance critic
		static void UpdateSand(int32_t x, int32_t y, int32_t currentCachedIdx);
		static void UpdateWater(int32_t x, int32_t y, int32_t currentCachedIdx);

		static void ClearUpdateStatus();

		static bool IsCellEmpty(uint32_t x, uint32_t y);
		static bool IsCellEmpty(uint32_t idx);

		static bool IsInBounds(uint32_t x, uint32_t y);
		static bool IsInBounds(uint32_t idx);
	private:
		static std::vector<Particle> m_Particles;
		static vec2<int32_t> m_CachedDims;

		static vec4<uint8_t> m_MaterialColors[(uint8_t)EParticleType::SIZE];

	};
}