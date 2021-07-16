#pragma once

#include <string>
#include <memory>
#include <map>

// ����������� ��������� ���������
namespace Rendering
{
    class ShaderProgram;
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

private:

    // ����� ����������� string  � ����� �������� �� ��������� ������ vertex.txt � fragment.txt
    std::string getFileString(const std::string& relativeFilePath) const;

    // ���������� �������� ��������� �������� (��������)

    typedef std::map<const std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    // ���� � ��������

    std::string m_path;
};