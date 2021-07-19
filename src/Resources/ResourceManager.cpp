
#include "ResourceManager.h"
#include "../Rendering/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

// �����������  stb image ��� �������� �������
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include "stb_image.h"






ResourceManager::ResourceManager(const std::string& executablePath)
{
    // ���������� ���� �� / ��� "\"
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
    std::ifstream f;

    // ��������� ���� 

    f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

    // �������� �� �������� ������ �������
    if (!f.is_open())
    {
        std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Rendering::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    //  �������� ����� �� ������ �������

    std::string vertexString = getFileString(vertexPath);  // vertexShader
    if (vertexString.empty())
    {
        std::cerr << "No vertex shader!" << std::endl;
        return nullptr;
    }

    std::string fragmentxString = getFileString(fragmentPath);  // fragmentShader
    if (fragmentxString.empty())
    {
        std::cerr << "No fragment shader!" << std::endl;
        return nullptr;
    }

    // ��� �������� ��������� ��������� � MAP

    std::shared_ptr<Rendering::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Rendering::ShaderProgram>(vertexString, fragmentxString)).first->second;
    if (newShader->CompiledShader())
    {
        return newShader;
    }

    // ��� ������ 

    std::cerr << "Can't load shader program:\n"
        << "Vertex: " << vertexPath << "\n"
        << "Fragment: " << fragmentPath << std::endl;

    return nullptr;
}


std::shared_ptr<Rendering::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
    // ���� ������ �� ��� ����� � MAP

    ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
    if (it != m_shaderPrograms.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the shader program: " << shaderName << std::endl;
    return nullptr;
}


void ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
    //rgba ������
    int channels = 0;
    int width = 0;
    int height = 0;

    // ��� ��� � openGL �������� �������������� ����� ����� � stbi_image ��������, �������������� ��������
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << texturePath << std::endl;
        return;
    }

    stbi_image_free(pixels);
}