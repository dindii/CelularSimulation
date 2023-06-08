#pragma once
#include "Defines.h"

#include <string>

namespace CS
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader();
	
		virtual void Bind();
		virtual void UnBind();
	
		void SetUint(const std::string& name, uint32_t data);
		
		Handle GetHandle() const { return m_RendererID; }
	private:
		virtual bool ParseShaderFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual bool CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		virtual unsigned int CompileShader(unsigned int type, const std::string& source);
	
	private:
		Handle m_RendererID;
		std::string m_VertexShaderFilepath, m_FragmentShaderFilepath;
	};
}