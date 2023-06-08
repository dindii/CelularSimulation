#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Shader.h"

namespace CS
{
	class LowLevelMesh
	{
	public:
		LowLevelMesh(std::string& vertexShader, std::string& fragmentShader, std::vector<float>&& vertices, std::vector<float>&& UVs) noexcept;
		
		void Bind() const;

		inline uint32_t GetVertexCount() const { return m_VertexCount; }
		std::unique_ptr<Shader>& GetShader() { return m_Shader; }

	private:
		std::unique_ptr<Shader> m_Shader;
		Handle m_VertexBuffer, m_VertexArrayBuffer;

		uint32_t m_VertexCount, m_UVsCount;
	};
}
