
#include "Texture2D.h"


namespace Rendering {

	Texture2D::Texture2D(const GLuint width, GLuint height,
		const unsigned char* data,
		const unsigned int channel,
		const GLenum filter,
		const GLenum wrapMode)
	    : m_width(width)
	    , m_height(height) {

		//  проверяем количество каналов цвета 

		switch (channel) {
		case 4:
			m_mode = GL_RGBA;
			break;

		case 3:
			m_mode = GL_RGB;
			break;

		default:
			m_mode = GL_RGBA;
			break;
		}

		// генерируем поинтер текстуры 

		glGenTextures(1, &m_id);

		// делаем текущей текстуру
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

		// Параметры фильтрации текстуры

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		// зануляем текстуру 
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	Texture2D& Texture2D::operator = (Texture2D&& Texture2d) {
		// удаляем текущую текстуру и заменяем новой
		glDeleteTextures(1, &m_id);

		m_id = Texture2d.m_id;
		Texture2d.m_id = 0;
		m_mode = Texture2d.m_mode;
		m_width = Texture2d.m_width;
		m_height = Texture2d.m_height;

		return *this;
	}


	Texture2D::Texture2D(Texture2D&& Texture2d) {
		m_id = Texture2d.m_id;
		Texture2d.m_id = 0;
		m_mode = Texture2d.m_mode;
		m_width = Texture2d.m_width;
		m_height = Texture2d.m_height;
	}

	Texture2D::~Texture2D() {
		// удаляем текстуру
		glDeleteTextures(1, &m_id);
	}


	void Texture2D::Bind() const {
		glBindTexture(GL_TEXTURE_2D, m_id);
	}




}