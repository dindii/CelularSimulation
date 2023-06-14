#include "Particle.h"
#include <Math/vec2.h>
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
	private:
		static std::vector<Particle> m_Particles;
		static vec2<int32_t> m_CachedDims;
	};
}