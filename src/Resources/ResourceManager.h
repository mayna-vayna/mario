#pragma once

#include <string>
#include <memory>
#include <map>

// поределение шейдерной программы
namespace Rendering
{
    class ShaderProgram;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    // «апрет на некоторые конструкторы

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    // ћетод загрузки шейдеров

    std::shared_ptr<Rendering::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    // ћетод получени€ самого шейдера из ресурсов

    std::shared_ptr<Rendering::ShaderProgram> getShaderProgram(const std::string& shaderName);

    // ћетод загрузки текстур

    void loadTexture(const std::string& textureName, const std::string& texturePath);

private:

    // метод возвращени€ string  с кодом шейдеров из текстовых файлов vertex.txt и fragment.txt
    std::string getFileString(const std::string& relativeFilePath) const;

    // сохранение шейдеров менеджере ресурсов (поинтера)

    typedef std::map<const std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    // путь к ресурсам

    std::string m_path;
};