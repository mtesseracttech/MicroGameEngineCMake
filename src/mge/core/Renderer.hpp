#ifndef RENDERER_H
#define RENDERER_H

#include <glm.hpp>

class World;

class GameObject;

class Camera;

class Mesh;

class AbstractMaterial;

/**
 * Renderer implements a default single pass forward renderer.
 */
class Renderer
{
public:
    Renderer();

    virtual ~Renderer();

    //utility call
    void setClearColor(int pR, int pG, int pB);

    //convenience method to render whole world
    void render(World* p_world);

    //render specific game object within the world, and optionally all its children
    void render(GameObject* p_gameObject,
                const glm::mat4& p_modelMatrix,
                const glm::mat4& p_viewMatrix,
                const glm::mat4& p_projectionMatrix,
                bool p_recursive);

    //renders a specific mesh at the given positions etc with the given material
    void renderMesh(Mesh* p_mesh,
                    AbstractMaterial* p_material,
                    const glm::mat4& p_modelMatrix,
                    const glm::mat4& p_viewMatrix,
                    const glm::mat4& p_projectionMatrix);

    void renderChildren(GameObject* p_gameObject,
                        const glm::mat4& p_modelMatrix,
                        const glm::mat4& p_viewMatrix,
                        const glm::mat4& p_projectionMatrix,
                        bool p_recursive);

    //helper method to render all the children of a gameobject
    void renderMeshDebugInfo(Mesh* p_mesh,
                             const glm::mat4& p_modelMatrix,
                             const glm::mat4& p_viewMatrix,
                             const glm::mat4& p_projectionMatrix);

private:
    //helper method to render a single gameobject
    void renderSelf(GameObject* p_gameObject,
                    const glm::mat4& p_modelMatrix,
                    const glm::mat4& p_viewMatrix,
                    const glm::mat4& p_projectionMatrix);

};

#endif // RENDERER_H
