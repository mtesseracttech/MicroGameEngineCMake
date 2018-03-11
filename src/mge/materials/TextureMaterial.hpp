#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class TextureMaterial : public AbstractMaterial
{
private:
    static ShaderProgram* m_shader;
    Texture             * m_diffuseTexture;

public:
    TextureMaterial(Texture* p_diffuseTexture);

    virtual ~TextureMaterial();

    void render(Mesh* p_mesh,
                const glm::mat4& p_modelMatrix,
                const glm::mat4& p_viewMatrix,
                const glm::mat4& p_projectionMatrix) override;

    void setDiffuseTexture(Texture* p_diffuseTexture);

private:
    TextureMaterial(const TextureMaterial&);

    TextureMaterial& operator=(const TextureMaterial&);

    static void lazyInitializeShader();

};

#endif // TEXTUREMATERIAL_H
