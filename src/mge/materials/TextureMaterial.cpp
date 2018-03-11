#include <glm.hpp>

#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"

ShaderProgram* TextureMaterial::m_shader = NULL;

TextureMaterial::TextureMaterial(Texture* p_diffuseTexture) : m_diffuseTexture(p_diffuseTexture)
{
    lazyInitializeShader();
}

TextureMaterial::~TextureMaterial()
{}

void TextureMaterial::lazyInitializeShader()
{
    if (!m_shader)
    {
        m_shader = new ShaderProgram();
        m_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vs");
        m_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
        m_shader->finalize();
    }
}

void TextureMaterial::setDiffuseTexture(Texture* p_diffuseTexture)
{
    m_diffuseTexture = p_diffuseTexture;
}

void TextureMaterial::render(Mesh* p_mesh, const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix,
                             const glm::mat4& p_projectionMatrix)
{
    if (!m_diffuseTexture) return;

    m_shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture->getId());
    glUniform1i(m_shader->getUniformLocation("textureDiffuse"), 0);

    //pass in all MVP matrices separately
    glUniformMatrix4fv(m_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE,
                       glm::value_ptr(p_projectionMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(p_viewMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(p_modelMatrix));

    //now inform mesh of where to stream its data
    p_mesh->streamToOpenGL(
            m_shader->getAttribLocation("vertex"),
            m_shader->getAttribLocation("normal"),
            m_shader->getAttribLocation("uv")
    );
}
