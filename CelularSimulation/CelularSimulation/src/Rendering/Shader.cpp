#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

namespace CS
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_VertexShaderFilepath(vertexSource), m_FragmentShaderFilepath(fragmentSource)
	{
		ParseShaderFiles(vertexSource, fragmentSource);
	}

	bool Shader::ParseShaderFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::ifstream vertexShader, fragmentShader;

		vertexShader.open(vertexShaderPath);
		fragmentShader.open(fragmentShaderPath);

		if (vertexShader && fragmentShader)
		{
			std::stringstream vertexShaderStream, fragmentShaderStream;

			vertexShaderStream << vertexShader.rdbuf();
			fragmentShaderStream << fragmentShader.rdbuf();

			vertexShader.close();
			fragmentShader.close();

			CreateShader(vertexShaderStream.str(), fragmentShaderStream.str());
		}
		else
		{
			std::cout << ("ERROR READING SHADER FILES!\n") << std::endl;
			return false;
		}

		return true;

	}

	bool Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{

		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		if (!vs || !fs)
		{
			glDeleteShader(vs);
			glDeleteShader(fs);
			glDeleteProgram(program);
			return false;
		}

		std::cout << "\nVertex Shader successfuly compiled! Shader: " << m_VertexShaderFilepath;
		std::cout << "\nFragment Shader successfuly compiled! Shader: " << m_FragmentShaderFilepath;

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		//@TODO: DETTACH
		m_RendererID = program;

		glDeleteShader(vs);
		glDeleteShader(fs);

		return true;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int shaderId = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(shaderId, 1, &src, nullptr);
		glCompileShader(shaderId);

		int compileResult;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);

		if (!compileResult)
		{
			int length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

			char* message = new char[length];
			glGetShaderInfoLog(shaderId, length, &length, message);

			if (type == GL_FRAGMENT_SHADER)
				std::cout << "\nFailed to compile Fragment Shader: " << message;

			else if (type == GL_VERTEX_SHADER)
				std::cout << "\nFailed to compile Vertex Shader: " << message;

			else if (type == GL_GEOMETRY_SHADER)
				std::cout << "\nFailed to compile Geometry Shader: " << message;

			glDeleteShader(shaderId);
			delete[] message;
			return 0;
		}

		return shaderId;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}


	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}
	void Shader::SetUint(const std::string& name, uint32_t data)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform1i(location, data);
	}
}