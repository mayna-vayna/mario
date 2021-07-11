#include "ShaderProgram.h"

#include <iostream>

namespace Rendering {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexShader_id;
		if (!ShaderCreate(vertexShader, GL_VERTEX_SHADER, vertexShader_id)) {
			std::cerr << "Vertex Shader: Compile time error" << std::endl;
			return;
		}

		GLuint fragmentShader_id;
		if (!ShaderCreate(fragmentShader, GL_FRAGMENT_SHADER, fragmentShader_id)) {
			std::cerr << "Fragment Shader: Compile time error" << std::endl;
			glDeleteShader(vertexShader_id);
			return;
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShader_id);
		glAttachShader(m_id, fragmentShader_id);
		glLinkProgram(m_id);

		GLint success;
		glGetShaderiv(m_id, GL_LINK_STATUS, &success);

		//проверка на линковку

		if (!success) {
			GLchar InfoLog[1024];
			glGetProgramInfoLog(m_id, 1024, nullptr, InfoLog);
			std::cerr << "ERROR::SHADER: Link time error!\n" << InfoLog << std::endl;
		}else {
			m_CompiledShader = true;
		}

		//удаляем все шейдеры 
		glDeleteShader(vertexShader_id);
		glDeleteShader(fragmentShader_id);
	}

	bool ShaderProgram::ShaderCreate(const std::string& source,const GLenum ShaderType, GLuint& shaderID) {
		shaderID = glCreateShader(ShaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		//проверка ошибок

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success) {
			GLchar InfoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, InfoLog);
			std::cerr << "ERROR::SHADER: Compile time error!\n"<<InfoLog<<std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram() {
		//удаляем шейдерную программу
		glDeleteProgram(m_id);
	}

	void ShaderProgram::Use() const {
		glUseProgram(m_id);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_id);
		m_id = shaderProgram.m_id;
		m_CompiledShader = shaderProgram.m_CompiledShader;

		shaderProgram.m_id = 0;
		shaderProgram.m_CompiledShader = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_id = shaderProgram.m_id;
		m_CompiledShader = shaderProgram.m_CompiledShader;

		shaderProgram.m_id = 0;
		shaderProgram.m_CompiledShader = false;
	}



}