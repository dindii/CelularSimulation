#include "LowLevelMesh.h"
#include <Math/vec2.h>

#include <glad/glad.h>

namespace CS
{
	LowLevelMesh::LowLevelMesh(std::string& vertexShader, std::string& fragmentShader, std::vector<float>&& vertices, std::vector<float>&& UVs) noexcept : m_VertexBuffer(0),
		m_VertexArrayBuffer(0), m_VertexCount(0), m_UVsCount(0)
	{
		m_VertexCount = vertices.size() / 3;
		m_UVsCount = UVs.size() / 2;

		glGenVertexArrays(1, &m_VertexArrayBuffer);
		glBindVertexArray(m_VertexArrayBuffer);

		glGenBuffers(1, &m_VertexBuffer);

		glBindVertexArray(m_VertexArrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		size_t bufferSize = sizeof(float) * vertices.size() +  sizeof(float) * UVs.size();

		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertices.size(), vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), sizeof(float) * UVs.size(), UVs.data());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * vertices.size()));


		m_Shader = std::make_unique<Shader>(vertexShader, fragmentShader);
	}
	void LowLevelMesh::Bind() const
	{
		glBindVertexArray(m_VertexArrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		m_Shader->Bind();
	}
}