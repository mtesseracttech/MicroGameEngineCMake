#include <glm.hpp>

#include "mge/materials/ColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* ColorMaterial::m_shader = nullptr;

GLint ColorMaterial::m_uMvpMatrix    = 0;
GLint ColorMaterial::m_uDiffuseColor = 0;

GLint ColorMaterial::m_aVertex = 0;
GLint ColorMaterial::m_aNormal = 0;
GLint ColorMaterial::m_aUv     = 0;

ColorMaterial::ColorMaterial(glm::vec3 p_color) : m_diffuseColor(p_color)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    lazyInitializeShader();
}

void ColorMaterial::lazyInitializeShader()
{
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!m_shader)
    {
        m_shader = new ShaderProgram();
        m_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "color.vs");
        m_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "color.fs");
        m_shader->finalize();

        //cache all the uniform and attribute indexes
        m_uMvpMatrix    = m_shader->getUniformLocation("mvpMatrix");
        m_uDiffuseColor = m_shader->getUniformLocation("diffuseColor");

        m_aVertex = m_shader->getAttribLocation("vertex");
        m_aNormal = m_shader->getAttribLocation("normal");
        m_aUv     = m_shader->getAttribLocation("uv");
    }
}

ColorMaterial::~ColorMaterial()
{
    //dtor
}

void ColorMaterial::setDiffuseColor(glm::vec3 p_diffuseColor)
{
    m_diffuseColor = p_diffuseColor;
}

void ColorMaterial::render(Mesh* p_mesh, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                           const glm::mat4& p_projectionMatrix)
{
    m_shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = p_projectionMatrix * p_viewMatrix * p_modelMatrix;
    glUniformMatrix4fv(m_uMvpMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //set the material color
    glUniform3fv(m_uDiffuseColor, 1, glm::value_ptr(m_diffuseColor));

    //now inform mesh of where to stream its data
    p_mesh->streamToOpenGL(m_aVertex, m_aNormal, m_aUv);

}
