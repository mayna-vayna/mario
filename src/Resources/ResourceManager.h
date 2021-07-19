#pragma once

#include <string>
#include <memory>
#include <map>

// поределение шейдерной программы
namespace Rendering
{
    class ShaderProgram;
    class Texture2D;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    // Запрет на некоторые конструкторы

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    // Метод загрузки шейдеров

    std::shared_ptr<Rendering::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    // Метод получения самого шейдера из ресурсов

    std::shared_ptr<Rendering::ShaderProgram> getShaderProgram(const std::string& shaderName);

    // Метод загрузки текстур

    std::shared_ptr<Rendering::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<Rendering::Texture2D> getTextures(const std::string& TextureName);

private:

    // метод возвращения string  с кодом шейдеров из текстовых файлов vertex.txt и fragment.txt
    std::string getFileString(const std::string& relativeFilePath) const;

    // сохранение шейдеров менеджере ресурсов (поинтера)

    typedef std::map<const std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    // coхранение списка текстур 

    typedef std::map<const std::string, std::shared_ptr<Rendering::Texture2D>>TexturesMap;
    TexturesMap m_textures;

    // путь к ресурсам

    std::string m_path;
};