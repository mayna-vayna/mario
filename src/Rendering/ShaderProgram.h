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

		//������ �� ����������� ��������� ��������� � ��������� ��������������
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
	private:
		//�������� �������
		bool ShaderCreate(const std::string& source,const GLenum ShaderType, GLuint& shaderID);

		//���������� ���������� ��������� �� ���������������� ��� ������������ �������
		bool m_CompiledShader=false;
		//�������������
		GLuint m_id=0;



	};



}