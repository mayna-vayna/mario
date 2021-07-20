#pragma once 

#include<glad/glad.h>
#include<string>

namespace Rendering {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool CompiledShader() const { return m_CompiledShader; }
		void Use() const;

		// Метод для задавания uniform  в шейдере
		void setInt(const std::string& name, const GLint value);

		//Запрет на копирование шейдерной программы и некоторых констркукторов
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	private:
		//создание шейдера
		bool ShaderCreate(const std::string& source,const GLenum ShaderType, GLuint& shaderID);

		//переменная показывает нормально ли скомпилировались или слинковались Шейдеры
		bool m_CompiledShader=false;
		//идентификатор
		GLuint m_id=0;



	};



}