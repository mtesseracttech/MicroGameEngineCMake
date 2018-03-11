#ifndef COLORMATERIAL_H
#define COLORMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"

/**
 * Simple single color material.
 * This material uses no lights.
 * This material demonstrates how to render a single color material, and how to cache all attributes, uniforms and pass in a single MVP matrix to the shader.
 */
class ColorMaterial : public AbstractMaterial
{
private:
    /*
     * Note that they are all PRIVATE, we do not expose this static info to the outside world
     */
    static ShaderProgram* m_shader;

    /*
     * In this example we cache all identifiers for uniforms & attributes
     * All the static properties are shared between instances of ColorMaterial
     */

    //Uniforms
    static GLint m_uMvpMatrix;
    static GLint m_uDiffuseColor;

    //Attributes
    static GLint m_aVertex;
    static GLint m_aNormal;
    static GLint m_aUv;

    /*
     * The color attribute is unique per instance of color material
     */
    glm::vec3 m_diffuseColor;

public:
    ColorMaterial(glm::vec3 p_color = glm::vec3(1, 0, 0));

    virtual ~ColorMaterial();

    void render(Mesh* p_mesh,
                const glm::mat4& p_modelMatrix,
                const glm::mat4& p_viewMatrix,
                const glm::mat4& p_projectionMatrix) override;

    //in rgb values
    void setDiffuseColor(glm::vec3 p_diffuseColor);

private:
    static void lazyInitializeShader();


};

#endif // COLORMATERIAL_H
