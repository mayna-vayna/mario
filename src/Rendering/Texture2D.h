#pragma once 

#include <glad/glad.h>
#include <string>


namespace Rendering {

	class Texture2D {

	public:

		Texture2D(const GLuint width, GLuint height,
			      const unsigned char* data,
			      const unsigned int channel = 4,
			      const GLenum filter = GL_LINEAR, 
			      const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator = (Texture2D&& Texture2d);
		Texture2D(Texture2D&& Texture2d);

		~Texture2D();


		// Метод для подключения текстуры

		void Bind() const;



	private:

		// id  текстуры для хранения в карте памяти

		GLuint m_id;

		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;
	};


}