#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <vector>
#include <string>

#include <GL/glew.h>

/**
 * Generic shader program to which you can add separate shaders.
 * Nice exercise for the reader: make it possible to add shaders by passing in the code as a string instead of through a file.
 *
 * Usage:
 *  create shader program
 *  add shaders
 *  finalize shader program
 *  use shader program
 */
class ShaderProgram
{
private:
    GLint               m_programId;
    std::vector<GLuint> p_shaderIds;

public:
    ShaderProgram();

    virtual ~ShaderProgram();

    //add a specific shader
    void addShader(GLuint p_shaderType, const std::string& p_shaderPath);

    //link and compile all added shaders
    void finalize();

    //tell opengl this is now the current shader
    void use();

    //get access to uniforms of the shader
    GLuint getUniformLocation(const std::string& p_name);

    //get access to attributes of the shader
    GLuint getAttribLocation(const std::string& p_name);

private:

    std::string readFile(const std::string& p_shaderPath);

    GLuint compileShader(GLuint p_shaderType, const std::string& p_shaderSource);
};

#endif // SHADERPROGRAM_H

