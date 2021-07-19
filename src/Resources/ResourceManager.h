#pragma once

#include <string>
#include <memory>
#include <map>

// ����������� ��������� ���������
namespace Rendering
{
    class ShaderProgram;
    class Texture2D;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    // ������ �� ��������� ������������

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    // ����� �������� ��������

    std::shared_ptr<Rendering::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    // ����� ��������� ������ ������� �� ��������

    std::shared_ptr<Rendering::ShaderProgram> getShaderProgram(const std::string& shaderName);

    // ����� �������� �������

    std::shared_ptr<Rendering::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<Rendering::Texture2D> getTextures(const std::string& TextureName);

private:

    // ����� ����������� string  � ����� �������� �� ��������� ������ vertex.txt � fragment.txt
    std::string getFileString(const std::string& relativeFilePath) const;

    // ���������� �������� ��������� �������� (��������)

    typedef std::map<const std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    // co�������� ������ ������� 

    typedef std::map<const std::string, std::shared_ptr<Rendering::Texture2D>>TexturesMap;
    TexturesMap m_textures;

    // ���� � ��������

    std::string m_path;
};