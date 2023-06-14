#include <stdint.h>
#include <Math/vec2.h>

namespace CS
{
	enum class EParticleType : uint8_t
	{
		NONE = 0,
		
		BEGIN = 1,
		
		SAND = BEGIN,
		
		END
	};

	struct Particle
	{
	public:
		Particle(EParticleType type = EParticleType::NONE, uint32_t initialLifetime = UINT32_MAX, vec2<uint32_t> initialVelocity = { 0, 1 }) 
			: m_Type(type), m_LifeTime(initialLifetime), m_Velocity(initialVelocity), m_IsUpdated(false) {};

		inline void SetType(const EParticleType type) { m_Type = type; }
		inline void SetLifeTime(const uint32_t lifetime) { m_LifeTime = lifetime; }
		inline void SetVelocity(const vec2<uint32_t> velocity) { m_Velocity = velocity; }
		inline void SetUpdated(bool updated) { m_IsUpdated = updated; }

		inline bool           GetUpdated()  const { return m_IsUpdated; }
		inline EParticleType  GetType()     const { return m_Type;}
		inline uint32_t       GetLifeTime() const { return m_LifeTime;}
		inline vec2<uint32_t> GetVelocity() const { return m_Velocity;}
	private:
		EParticleType m_Type;
		uint32_t m_LifeTime;
		vec2<uint32_t> m_Velocity;
		bool m_IsUpdated;
	};
}