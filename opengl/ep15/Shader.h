#pragma once

#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

enum ShaderType
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class Shader
{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;

    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

    private:
        unsigned int GetUniformLocation(const std::string& name);
        struct ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};
