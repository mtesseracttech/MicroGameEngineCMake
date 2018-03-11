#include "mge/core/ShaderProgram.hpp"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram() : m_programId(0), p_shaderIds()
{
    //why does opengl use glCreateProgram and not glGenProgram (1, &_programID)? Who knows:) *shrugs*
    m_programId = glCreateProgram();
    std::cout << std::endl << "Program created with id:" << m_programId << std::endl;
}

ShaderProgram::~ShaderProgram()
{}

void ShaderProgram::addShader(GLuint p_shaderType, const std::string& p_shaderPath)
{
    std::string shaderCode = readFile(p_shaderPath);
    GLuint      shaderId   = compileShader(p_shaderType, shaderCode);

    if (shaderId != 0)
    {
        p_shaderIds.push_back(shaderId);
    }
}

void ShaderProgram::use()
{
    glUseProgram(static_cast<GLuint>(m_programId));
}

GLuint ShaderProgram::getUniformLocation(const std::string& p_name)
{
    return static_cast<GLuint>(glGetUniformLocation(static_cast<GLuint>(m_programId), p_name.c_str()));
}

GLuint ShaderProgram::getAttribLocation(const std::string& p_name)
{
    return static_cast<GLuint>(glGetAttribLocation(static_cast<GLuint>(m_programId), p_name.c_str()));
}

void ShaderProgram::finalize()
{
    for (unsigned int shaderId : p_shaderIds)
    {
        glAttachShader(static_cast<GLuint>(m_programId), shaderId);
    }

    glLinkProgram(static_cast<GLuint>(m_programId));

    // Check the program
    GLint linkResult = GL_FALSE;
    glGetProgramiv(static_cast<GLuint>(m_programId), GL_LINK_STATUS, &linkResult);

    if (linkResult)
    {
        std::cout << "Program linked ok." << std::endl << std::endl;
    }
    else
    { // error, show message
        std::cout << "Program error:" << std::endl;

        int infoLogLength;
        glGetProgramiv(static_cast<GLuint>(m_programId), GL_INFO_LOG_LENGTH, &infoLogLength);
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(static_cast<GLuint>(m_programId), infoLogLength, nullptr, errorMessage);
        std::cout << errorMessage << std::endl << std::endl;
        delete[] errorMessage;
    }

    for (unsigned int shaderId : p_shaderIds)
    {
        glDeleteShader(shaderId);
    }
}

std::string ShaderProgram::readFile(const std::string& p_shaderPath)
{
    std::string   contents;
    std::ifstream file(p_shaderPath, std::ios::in);
    if (file.is_open())
    {
        std::cout << "Reading shader file... " << p_shaderPath << std::endl;
        std::string line = "";
        while (getline(file, line)) contents += "\n" + line;
        file.close();
    }
    else
    {
        std::cout << "Error reading shader " << p_shaderPath << std::endl;
        contents = "";
    }
    return contents;
}

// compile the code, and detect errors.
GLuint ShaderProgram::compileShader(GLuint p_shaderType, const std::string& p_shaderSource)
{
    std::cout << "Compiling shader... " << std::endl;
    const char* sourcePointer = p_shaderSource.c_str();
    GLuint shaderId = glCreateShader(p_shaderType);
    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    GLint compilerResult = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilerResult);

    if (compilerResult)
    {
        std::cout << "Shader compiled ok." << std::endl;
        return shaderId;
    }
    else
    { // get error message
        std::cout << "Shader error:" << std::endl;
        int infoLogLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, errorMessage);
        std::cout << errorMessage << std::endl << std::endl;
        delete[] errorMessage;
        return 0;
    }
}
